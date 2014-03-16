QEverCloud
==========

**Unofficial Evernote Cloud API for Qt**

** What's this

This library peresents complete Evernote SDK for Qt. 
All the functionality that is described on [http://dev.evernote.com/doc/](Evernote site)
is implemented and ready to use. In particular OAuth autentication is implemented.

Read doxygen generated [documentation](http://mgsxx.github.io/QEverCloud) for detailed info.

The documentstion is also available as a .qch file which you can register with
your copy of Qt Creator to have context-senditive help. See *qch* subdir.


** Compatibility

Though I'm a big fan of C++11 QEverCloud does not use any new cool stuff.
So C++03 should be enough to build the library. 

I have not used any Qt 5 specific features so the library should compile for Qt 4 but I have not tested this.

To be pricise I've tested the library with Qt 5.2 on Windows with MSVC2010, MSVC2012 and MinGW 4.8.


** How to compile

QEverCloud depends on Qt only. So there is nothing special to compiling it.


** How to link

* Link compiled library to your project in the usual way. 
* Add it's *include* subdir to your app INCLUDE qmake variable.
* Add to QT variabe the *network* module. If you use OAuth functionality than add also *widgets* and *webkitwidgets* modules.

Include *QEverCloud.h* or *QEverCloudOAuth.h* to use the library. The latter header is needed if you use OAuth functionality.


** Runtime dependencies

Qt uses OpenSSL to implement https protocol. As a result OpenSSL dynamically linked libraries (libeay32 and ssleay32) must be 
availabe in the PATH for your app to run successfully.


