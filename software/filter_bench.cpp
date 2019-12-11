#include <iostream>
#include <chrono>
#include <vector>

#include <opencv2/opencv.hpp>


double filter_video(const std::string& source, int iter, int ksize){
    
    cv::VideoCapture inputVideo(source);
    if(!inputVideo.isOpened()){
        std::cout << "Could not open the input video.\n";
        return -1;
    }

    auto out_name = source.substr(0, source.find_last_of(".")) + 
                    std::to_string(iter) + "_out.mp4";

    cv::Size S(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH),
               inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::VideoWriter outputVideo;

    auto ex = static_cast<int>(inputVideo.get(cv::CAP_PROP_FOURCC));
    char EXT[] = { (char)(ex & 0XFF),
                   (char)((ex & 0XFF00) >> 8),
                   (char)((ex & 0XFF0000) >> 16),
                   (char)((ex & 0XFF000000) >> 24),
                   0 };

    outputVideo.open(out_name, ex, inputVideo.get(cv::CAP_PROP_FPS), S, true);

    if(!outputVideo.isOpened()){
        std::cout << "Could not open output.\n";
        return -1;
    }

    cv::Mat src, res;

    auto frames = 0L;
    auto millis = 0L;

    auto gftt = cv::GFTTDetector::create(ksize, 0.04);

    for(;;){
        inputVideo >> src;
        if(src.empty()) break;

        frames++;
        
        res.create(src.size(), src.type());

        auto start = std::chrono::steady_clock::now();

        std::vector<cv::KeyPoint> keypoints;
        gftt->detect(src, keypoints, cv::Mat());
        //cv::Laplacian(src, res, 0, ksize);
        //cv::GaussianBlur(src, res, { ksize, ksize }, 0);
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        millis += std::chrono::duration<double,std::milli>(diff).count();

        for(auto& kpt : keypoints){
            cv::circle(src, kpt.pt, 1, CV_RGB(255,0,0), 3); 
        }

        outputVideo.write(src);
    }

    return (double)millis / (double)frames; 
}

int main(int argc, char* argv[]){
    if(argc != 5){
        std::cout << "Usage ./filter_bench <input file> <runs> <k_lo> <k_hi>\n";
        return -1;
    }

    const std::string source = argv[1];
    const auto iters = atoi(argv[2]);
    const auto ksize_lo = atoi(argv[3]);
    const auto ksize_hi = atoi(argv[4]);

    for(int i = 0; i < iters; i++){
        for(int k = ksize_lo; k < ksize_hi; k *= 2){
            auto millis = filter_video(source, i, k);
            std::cout << k << " : " << millis << std::endl;
        }
    }
}
