# PPL CV x86 source cmake script
file(GLOB PPLCV_X86_PUBLIC_HEADERS src/ppl/cv/x86/*.h)
install(FILES ${PPLCV_X86_PUBLIC_HEADERS}
        DESTINATION include/ppl/cv/x86)

option(WITH_X86 "Build pplcv with x86 support" ON)
option(PPLCV_USE_X86 "Build unittest & benchmark with x86 support" ON)
option(USE_X86_OMP "Build x86 kernel with openmp support" OFF)

if(NOT IS_X86 OR NOT WITH_X86)
    return()
endif()
if(WITH_OMP)
    set(USE_X86_OMP ON)
endif()

list(APPEND PPLCV_COMPILE_DEFINITIONS PPLCV_USE_X86)

file(GLOB PPLCV_X86_SSE_SRC
     src/ppl/cv/x86/*.cpp
     src/ppl/cv/x86/*.S)
file(GLOB PPLCV_X86_AVX_SRC
     src/ppl/cv/x86/avx/*.cpp)
file(GLOB PPLCV_X86_FMA_SRC
     src/ppl/cv/x86/fma/*.cpp)

set(PPLCV_X86_SRC
    ${PPLCV_X86_SSE_SRC}
    ${PPLCV_X86_AVX_SRC}
    ${PPLCV_X86_FMA_SRC})

foreach(filename ${PPLCV_X86_FMA_SRC})
    set_source_files_properties(${filename} PROPERTIES COMPILE_FLAGS "${FMA_ENABLED_FLAGS}")
endforeach()
foreach(filename ${PPLCV_X86_AVX_SRC})
    set_source_files_properties(${filename} PROPERTIES COMPILE_FLAGS "${AVX_ENABLED_FLAGS}")
endforeach()
foreach(filename ${PPLCV_X86_SSE_SRC})
    set_source_files_properties(${filename} PROPERTIES COMPILE_FLAGS "${SSE_ENABLED_FLAGS}")
endforeach()

if(USE_X86_OMP)
    FIND_PACKAGE(OpenMP REQUIRED)
    if(OPENMP_FOUND)
        list(APPEND PPLCV_LINK_LIBRARIES OpenMP::OpenMP_CXX)
    endif()
endif()

list(APPEND PPLCV_SRC ${PPLCV_X86_SRC})

# glog benchmark and unittest sources
file(GLOB PPLCV_X86_BENCHMARK_SRC "src/ppl/cv/x86/*_benchmark.cpp")
file(GLOB PPLCV_X86_UNITTEST_SRC "src/ppl/cv/x86/*_unittest.cpp")
list(APPEND PPLCV_BENCHMARK_SRC ${PPLCV_X86_BENCHMARK_SRC})
list(APPEND PPLCV_UNITTEST_SRC ${PPLCV_X86_UNITTEST_SRC})
