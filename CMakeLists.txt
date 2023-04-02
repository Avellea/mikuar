cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(miku_ar)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -fno-inline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

enable_language(C ASM)

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(miku_ar
  src/main.c
)

target_link_libraries(miku_ar
  SceLibKernel_stub
  # SceKernelModuleMgr_stub
  SceRtc_stub 
  taihen_stub
)

set_target_properties(miku_ar
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(miku_ar.suprx miku_ar
  CONFIG exports.yml
  UNSAFE
)