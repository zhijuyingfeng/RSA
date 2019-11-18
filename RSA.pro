TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        SHA1.cpp \
        bigint.cpp \
        main.cpp \
        mpn.cpp \
        oaep.cpp \
        rsa.cpp

HEADERS += \
    SHA1.h \
    bigint.h \
    mpn.h \
    oaep.h \
    rsa.h
