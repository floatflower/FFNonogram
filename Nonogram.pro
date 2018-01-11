TEAMPLTE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ffnonogram

SOURCES += main.cpp \
		   nonogram.cpp \
		   linesolver.cpp

HEADERS += nonogram.h \
		   linesovler.h	