PROJECT(check_cli)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)

#########################################
set(EXECUTABLE_OUTPUT_PATH ../../bin.check_cli)  
set(LIBRARY_OUTPUT_PATH ../libs)

add_definitions (${QT_DEFINITIONS})
set(QT_USE_QTNETWORK true)


## libs
link_directories(/usr/local/lib)
link_directories(/usr/lib)
link_directories(/home/hanxi/workspace/check_system/lib)

## includes
include(${QT_USE_FILE})
# 包含文件夹：${CMAKE_CURRENT_BINARY_DIR}和${CMAKE_CURRENT_SOURCE_DIR}用于确保moc产生的文件能正确编译。
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(/usr/local/include)
include_directories(./src SRC_DIR)
include_directories(../include)
include_directories(../Modules/Log)
include_directories(../Modules/Conf)
include_directories(../Modules/Net)
include_directories(../Modules/Net/cli)

## sources
aux_source_directory(./src SRC_DIR)

## module sources
aux_source_directory(../Modules/Log LOG_DIR)
aux_source_directory(../Modules/Conf CONF_DIR)
aux_source_directory(../Modules/Net NET_DIR)
aux_source_directory(../Modules/Net/cli NET_CLI_DIR)

# 对于含有Q_OBJECT一类宏的代码（主要是头文件），需要列出以备交给moc处理
set(qt_HDRS ./src/mainwindowimpl.h ../Modules/Net/cli/net.h)

# UI文件
set(qt_UI ./ui/mainwindow.ui)

## QT
qt4_wrap_cpp(qt_MOCS ${qt_HDRS})
qt4_wrap_ui(qt_UIS ${qt_UI})

## apps
add_executable(check_cli
    ${SRC_DIR}
    ${LOG_DIR}
    ${CONF_DIR}
    ${NET_DIR}
    ${NET_CLI_DIR}
    ${qt_MOCS}
    ${qt_UIS}
)

## link libs
target_link_libraries(check_cli ${QT_LIBRARIES} opencv_core opencv_highgui opencv_imgproc)

