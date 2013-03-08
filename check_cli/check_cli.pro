TEMPLATE = app
QT = gui core
CONFIG += qt warn_on console release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui
HEADERS = src/mainwindowimpl.h
SOURCES = src/mainwindowimpl.cpp src/main.cpp

INCLUDEPATH += ../include/opencv
LIBS +=  ../lib/libopencv_calib3d.so\
../lib/libopencv_contrib.so\
../lib/libopencv_core.so\
../lib/libopencv_features2d.so\
../lib/libopencv_flann.so\
../lib/libopencv_highgui.so\
../lib/libopencv_imgproc.so\
../lib/libopencv_legacy.so\
../lib/libopencv_ml.so\
../lib/libopencv_objdetect.so\
../lib/libopencv_video.so\
