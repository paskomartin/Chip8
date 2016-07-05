TEMPLATE = app
CONFIG += console c++14 Wall Wextra pedantic
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    chip8.cpp \
    instructionset.cpp \
    instruction.cpp \
    chip8internaldata.cpp \
    chip8opcodedata.cpp

HEADERS += \
    chip8.h \
    instructionset.h \
    instruction.h \
    chip8internaldata.h \
    chip8opcodedata.h

