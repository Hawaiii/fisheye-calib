cmake_minimum_required(VERSION 2.8)
project(OpencvFisheye)

#add_definitions(-DBOOST_LOG_DYN_LINK)
#find_package(Boost 1.54.0 COMPONENTS system log REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

find_package(Threads)
find_package( OpenCV REQUIRED )
include_directories(/opt/pylon5/include)
link_directories(/opt/pylon5/lib64)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

set(SOURCE_FILES OpencvFisheyeCalib.cpp)
add_executable(OpencvFisheyeCalib ${SOURCE_FILES})
target_link_libraries(OpencvFisheyeCalib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${GCC_XI_FLAGS})
