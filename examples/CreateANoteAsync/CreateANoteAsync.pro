
TARGET = CreateANote

CONFIG   += console
CONFIG += c++11
CONFIG += silent
CONFIG -= debug_and_release debug_and_release_target

QT -= gui
QT += network


SOURCES += main.cpp

RC_ICONS = mainicon.ico

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc

path = $$absolute_path($$PWD/../QEverCloud/include)  # change to the path to the QEverCloud include dir
path = $$clean_path($$path)
INCLUDEPATH += $$path


win32-msvc* {
  LIB_PREFIX =
  LIB_EXT = .lib
} else { #mingw
  LIB_PREFIX = lib
  LIB_EXT = .a
}
libpath = $${OUT_PWD}/../QEverCloud/bin/$${LIB_PREFIX}QEverCloud$${LIB_EXT} # change to the path to the QEverCloud compiled library
libpath = $$clean_path($$libpath)


LIBS += $${libpath}
PRE_TARGETDEPS += $${libpath}

win32-msvc* {
    LIBS += kernel32.lib user32.lib gdi32.lib crypt32.lib
}


