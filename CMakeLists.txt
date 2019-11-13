cmake_minimum_required(VERSION 3.0)

project(RTSP
  LANGUAGES CXX
  VERSION 1.0.0)

set(SHARED_LIBRARY_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set(CMAKE_C_STANDARD 03)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Poco REQUIRED COMPONENTS Foundation Net Util)

add_subdirectory(RTSP)
add_subdirectory(SDP)
