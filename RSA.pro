TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        SHA1.cpp \
        bignum.cpp \
        main.cpp

HEADERS += \
    SHA1.h \
    bignum.h
