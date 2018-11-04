cmake_minimum_required(VERSION 2.8.3)
project(supplysim)

SET("OpenCV_DIR" "/usr/local/share/OpenCV")

find_package(OpenCV REQUIRED PATHS "/usr/local/share")
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(supplysim main.cpp)

target_link_libraries(supplysim ${OpenCV_LIBS} ${Boost_LIBRARIES})
