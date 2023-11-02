cmake_minimum_required (VERSION 3.18)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
#
if (CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
  set (BUILD_MSVC_COMPILE_OPTIONS "/arch:AVX" CACHE STRING "msvc compile options")
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
  set (BUILD_LINUX_COMPILE_OPTIONS "-Ofast" CACHE STRING "gcc compile options")
endif()
#
project (rtsp_h264 VERSION 1.0.0)
  file (GLOB FILES rtsp_h264_file.cpp src/*.hpp src/*.cpp md5.hpp)
  add_executable (${PROJECT_NAME} ${FILES})

  target_include_directories (${PROJECT_NAME} PRIVATE . src)

  message (STATUS "using ${CMAKE_HOST_SYSTEM_NAME}")
  if (CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
    target_compile_options (${PROJECT_NAME} PUBLIC /W4
                                                   /wd4100
                                                   #/wd4244 /wd4245 /wd4457 /wd4834 /wd4189
                                                   /fp:fast
                                                   ${BUILD_MSVC_COMPILE_OPTIONS})
    target_link_libraries (${PROJECT_NAME} PRIVATE ws2_32)

  else (CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
    target_compile_definitions (${PROJECT_NAME} PUBLIC _LARGEFILE64_SOURCE _FILE_OFFSET_BITS=64)
    target_compile_options (${PROJECT_NAME} PUBLIC -Wall
                                                   -Wextra
                                                   -Wno-missing-field-initializers
                                                   -Wno-format-security
                                                   -Wno-format-overflow
                                                   -Wno-unused-parameter
                                                   -Wno-unused-variable
                                                   -pedantic
                                                   -flax-vector-conversions
                                                   -ftree-vectorize
                                                   -fno-exceptions
                                                   -march=native
                                                   -g
                                                   ${BUILD_LINUX_COMPILE_OPTIONS})
  target_link_libraries (${PROJECT_NAME} PRIVATE m rt pthread dl)
  endif()
