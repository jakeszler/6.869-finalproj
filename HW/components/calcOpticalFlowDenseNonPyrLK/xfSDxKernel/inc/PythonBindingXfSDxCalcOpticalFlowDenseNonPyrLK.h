/******************************************************************************
 *  Copyright (c) 2018, Xilinx, Inc.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1.  Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *
 *  2.  Redistributions in binary form must reproduce the above copyright 
 *      notice, this list of conditions and the following disclaimer in the 
 *      documentation and/or other materials provided with the distribution.
 *
 *  3.  Neither the name of the copyright holder nor the names of its 
 *      contributors may be used to endorse or promote products derived from 
 *      this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
 
/*****************************************************************************
*
*     Author: Kristof Denolf <kristof@xilinx.com>
*             Jack Lo <jackl@xilinx.com>
*     Date:   2018/01/23
*
*****************************************************************************/

#ifndef PYOPENCV_XF_CALCOPTICALFLOWDENSENONPYRLK
#define PYOPENCV_XF_CALCOPTICALFLOWDENSENONPYRLK

#include "xfSDxCalcOpticalFlowDenseNonPyrLK.h"

static PyObject* pyopencv_cv_calcOpticalFlowDenseNonPyrLK(PyObject* , PyObject* args, PyObject* kw)
{
    using namespace cv;

    PyObject* pyobj_prev = NULL;
    Mat prev;
    PyObject* pyobj_next = NULL;
    Mat next;
	PyObject* pyobj_flowX = NULL;
    Mat flowX;
    PyObject* pyobj_flowY = NULL;
    Mat flowY;

    const char* keywords[] = { "prev", "next", "flowX", "flowY", NULL };
    if( PyArg_ParseTupleAndKeywords(args, kw, "OO|OO:calcOpticalFlowDenseNonPyrLK", (char**)keywords, &pyobj_prev, &pyobj_next, &pyobj_flowX, &pyobj_flowY) &&
        pyopencv_to(pyobj_prev, prev, ArgInfo("prev", 0)) &&
        pyopencv_to(pyobj_next, next, ArgInfo("next", 0)) &&
        pyopencv_to(pyobj_flowX, flowX, ArgInfo("flowX", 1)) &&
        pyopencv_to(pyobj_flowY, flowY, ArgInfo("flowY", 1)) )
    {
        ERRWRAP2(xF::calcOpticalFlowDenseNonPyrLK(prev, next, flowX, flowY));
        //ERRWRAP2(cv::dilate(src, dst, kernel, anchor, iterations, borderType, borderValue));
		return Py_BuildValue("(NN)", pyopencv_from(flowX), pyopencv_from(flowY));
    }

    return NULL;
}

#endif
