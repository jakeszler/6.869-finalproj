Build with:
g++ $(pkg-config --cflags --libs opencv4) -std=c++17 filter_bench.cpp -o filter_bench

Run with:
./filter_bench <input file> <runs> <k_lo> <k_hi>
