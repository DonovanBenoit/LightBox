cmake_minimum_required(VERSION 3.9)

project(LightBox)

add_executable(LightBox
  Source/main.cpp
  Source/Core/Array.h
  Source/Core/Log.h
  Source/Ray/Ray.h
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LightBox)

include_directories(LightBox ThirdParty/glm-0.9.8.4)
include_directories(LightBox ThirdParty/spdlog/include)
include_directories(LightBox ThirdParty/ThreadPool)

add_definitions(-std=c++11)

file(GLOB SOURCE *.cpp base/*.cpp)