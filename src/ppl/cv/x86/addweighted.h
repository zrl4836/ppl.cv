#ifndef __ST_HPC_PPL_CV_X86_ADDWEIGHTED_H_
#define __ST_HPC_PPL_CV_X86_ADDWEIGHTED_H_

#include "ppl/common/retcode.h"

namespace ppl {
namespace cv {
namespace x86 {

/**
* @brief Calculates the weighted sum of two arrays.
* @tparam T The data type of input and output image, currently \a float and \a uint8_t are supported.
* @tparam nc The number of channels of input image and output image, 1, 3 and 4 are supported.
* @param height            input image's height
* @param width             input image's width
* @param inWidthStride0    first input image's width stride, usually it equals to `width * nc`
* @param inData0           first input image data
* @param alpha             weight of the first image elements.
* @param inWidthStride1    second input image's width stride, usually it equals to `width * nc`
* @param inData1           second input image data
* @param beta              weight of the second image elements.
* @param gamma             scalar added to each sum
* @param outWidthStride    output image's width stride, usually it equals to `width * nc`
* @param outData           output image data
* @warning All input parameters must be valid, or undefined behaviour may occur.
* @remark The following table show which data type and channels are supported.
* <table>
* <tr><th>Data type(T)<th>channels
* <tr><td>uint8_t(uchar)<td>1
* <tr><td>uint8_t(uchar)<td>3
* <tr><td>uint8_t(uchar)<td>4
* <tr><td>float<td>1
* <tr><td>float<td>3
* <tr><td>float<td>4
* </table>
* <table>
* <caption align="left">Requirements</caption>
* <tr><td>x86 platforms supported<td> All
* <tr><td>Header files<td> #include &lt;ppl/cv/x86/addWeighted.h&gt;
* <tr><td>Project<td> ppl.cv
* @since ppl.cv-v1.0.0
* ###Example
* @code{.cpp}
* #include <ppl/cv/x86/addWeighted.h>
* int32_t main(int32_t argc, char** argv) {
*     const int32_t W = 640;
*     const int32_t H = 480;
*     const int32_t C = 3;
*     float* dev_iImage0 = (float*)malloc(W * H * C * sizeof(float));
*     float* dev_iImage1 = (float*)malloc(W * H * C * sizeof(float));
*     float* dev_oImage = (float*)malloc(W * H * C * sizeof(float));
*
*     ppl::cv::x86::AddWeighted<float, 3>(H, W, W * C, dev_iImage0, 1.0, W * C, dev_iImage1, 1.0, 0.0, W * C, dev_oImage);
*
*     free(dev_iImage0);
*     free(dev_iImage1);
*     free(dev_oImage);
*     return 0;
* }
* @endcode
***************************************************************************************************/

template <typename T, int32_t nc>
::ppl::common::RetCode AddWeighted(
    int32_t height,
    int32_t width,
    int32_t inWidthStride0,
    const T *inData0,
    float alpha,
    int32_t inWidthStride1,
    const T *inData1,
    float beta,
    float gamma,
    int32_t outWidthStride,
    T *outData);

} //! namespace x86
} //! namespace cv
} //! namespace ppl

#endif //!__ST_HPC_PPL3_CV_X86_ADDWEIGHTED_H_

