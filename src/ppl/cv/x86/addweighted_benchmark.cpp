#include "ppl/cv/x86/addweighted.h"
#include "ppl/cv/debug.h"
#include <memory>
#include <benchmark/benchmark.h>
#include <opencv2/imgproc.hpp>

namespace {

template<typename T, int32_t nc>
void BM_AddWeighted_ppl_x86(benchmark::State &state) {
    int32_t width = state.range(0);
    int32_t height = state.range(1);
    std::unique_ptr<T[]> src0(new T[width * height * nc]);
    std::unique_ptr<T[]> src1(new T[width * height * nc]);
    std::unique_ptr<T[]> dst(new T[width * height * nc]);
    ppl::cv::debug::randomFill<T>(src0.get(), width * height * nc, 0, 1);
    ppl::cv::debug::randomFill<T>(src1.get(), width * height * nc, 0, 1);
    for (auto _ : state) {
        ppl::cv::x86::AddWeighted<T, nc>(height, width, width * nc, src0.get(), 0.3f,
                                                            width * nc, src1.get(), 0.7f,
                                                            1.3f,
                                                            width * nc, dst.get());
    }
    state.SetItemsProcessed(state.iterations() * 1);
}
#ifdef PPLCV_BENCHMARK_OPENCV
using namespace ppl::cv::debug;

BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, float, c1)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, float, c3)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, float, c4)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, uint8_t, c1)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, uint8_t, c3)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_ppl_x86, uint8_t, c4)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});

template<typename T, int32_t nc>
void BM_AddWeighted_opencv_x86(benchmark::State &state) {
    int32_t width = state.range(0);
    int32_t height = state.range(1);
    std::unique_ptr<T[]> src0(new T[width * height * nc]);
    std::unique_ptr<T[]> src1(new T[width * height * nc]);
    std::unique_ptr<T[]> dst(new T[width * height * nc]);
    ppl::cv::debug::randomFill<T>(src0.get(), width * height * nc, 0, 255);
    ppl::cv::debug::randomFill<T>(src1.get(), width * height * nc, 0, 255);
    cv::Mat iMat0(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), src0.get(), sizeof(T) * width * nc);
    cv::Mat iMat1(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), src1.get(), sizeof(T) * width * nc);
    cv::Mat oMat(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), dst.get(), sizeof(T) * width * nc);
    for (auto _ : state) {
        cv::addWeighted(iMat0, 0.3f, iMat1, 0.7f, 1.3f, oMat);
    }
    state.SetItemsProcessed(state.iterations() * 1);
}

BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, float, 1)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, float, 3)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, float, 4)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, uint8_t, 1)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, uint8_t, 3)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AddWeighted_opencv_x86, uint8_t, 4)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
#endif //! PPLCV_BENCHMARK_OPENCV
}
