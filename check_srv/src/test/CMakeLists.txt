PROJECT(test)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)

#########################################
set(EXECUTABLE_OUTPUT_PATH ./)  
set(LIBRARY_OUTPUT_PATH ../libs)


## libs
link_directories(/usr/local/lib)
link_directories(/usr/lib)
link_directories(/home/hanxi/workspace/check_system/lib)

## includes
# 包含文件夹：${CMAKE_CURRENT_BINARY_DIR}和${CMAKE_CURRENT_SOURCE_DIR}用于确保moc产生的文件能正确编译。
include_directories(/usr/local/include)
include_directories(../../../include)


## apps
add_executable(test ../faceDetect.cpp)

## link libs
target_link_libraries(test opencv_core opencv_highgui opencv_imgproc opencv_objdetect)

