TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QMAKE_CFLAGS += -std=c++11
#CONFIG -= qt
#DEFINES += GUI
QT += core gui widgets

SOURCES += main.cpp \
    interface/arguments.cpp \
    encoders/iencoder.cpp \
    encoders/simpleencoder.cpp \
    communicator/communicator.cpp \
    interface/qtinterface.cpp

HEADERS += \
    _include.hpp   \
    interface/arguments.hpp \
    encoders/iencoder.hpp \
    encoders/_include.hpp \
    encoders/simpleencoder.hpp \
    communicator/communicator.hpp \
    communicator/_include.hpp \
    interface/_include.hpp   \
    interface/qtinterface.hpp


