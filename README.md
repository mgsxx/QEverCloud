QEverCloud
==========

**Unofficial Evernote Cloud API for Qt**

## What's this

This library presents complete Evernote SDK for Qt. 
All the functionality that is described on [Evernote site](http://dev.evernote.com/doc/)
is implemented and ready to use. In particular OAuth authentication is implemented.

Read doxygen generated [documentation](http://mgsxx.github.io/QEverCloud) for detailed info.

The documentstion is also available as a .qch file which you can register with
your copy of Qt Creator to have context-sensitive help. See *qch* subdir.


## Compatibility

While the library initially supported Qt 4 it became too constraining so I've dropped the support.
If you're stuck with Qt 4 you can use the previous version which is available through `qt4` branch.

I do not use C++11 features directly but only through macros Qt 5 have like Q_DECL_OVERRIDE, Q_STATIC_ASSERT_X
QStringLiteral and others. So QEverCloud supports any given compiler as good as Qt 5 supports it.

Personally I test the library with MSVC2012 and MinGW 4.8 on Windows.

## How to compile

QEverCloud depends on Qt only. So there is nothing special to compiling it.


## How to link

* Link compiled library to your project in the usual way. 
* Add it's *include* subdir to your app INCLUDE qmake variable.
* Add to QT variabe the *network* module. If you use OAuth functionality than add also *widgets* and *webkitwidgets* modules.

Include *QEverCloud.h* or *QEverCloudOAuth.h* to use the library. The latter header is needed if you use OAuth functionality.


## Runtime dependencies

Qt uses OpenSSL to implement https protocol. As a result OpenSSL dynamically linked libraries (libeay32 and ssleay32) must be 
availabe in the PATH for your app to run successfully.


