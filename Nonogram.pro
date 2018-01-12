TEAMPLTE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ffnonogram

SOURCES += main.cpp \
		   nonogram.cpp \
		   linesolver.cpp \
    inputreader.cpp \
    worklist.cpp \
    fixcache.cpp

HEADERS += nonogram.h \
    linesolver.h \
    inputreader.h \
    macro.h \
    worklist.h \
    fixcache.h
