TARGET = QEverCloud
TEMPLATE = lib
CONFIG += staticlib

QT += network widgets webkitwidgets

CONFIG -= c++11
CONFIG += silent
CONFIG -= debug_and_release debug_and_release_target

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc

HEADERS += \
    include/QEverCloud.h \
    include/QEverCloudOAuth.h \
    oauth.h \
    thrift.h \
    http.h \
    public.h \
    exceptions.h \
    globals.h \
    impl.h \
    thumbnail.h

SOURCES += \
    exceptions.cpp \
    oauth.cpp \
    http.cpp \
    services_nongenerated.cpp


THRIFT_GENERATED = constants.h constants.cpp services.h services.cpp types.h types_impl.h types.cpp

###############################################

for(g, THRIFT_GENERATED) {
  OTHER_FILES += generated/$$g
}

include(../common.pri)

thriftlist = $$files($$shell_path($$PWD/thrift/src/*.thrift))
ThriftParser = $${OUT_PWD}/../ThriftParser/bin/ThriftParser
ThriftParser = $$shell_path($$clean_path($$ThriftParser))
ThriftParserDependency = $$files($${ThriftParser}.*)

#thriftparser.name = ThriftParser generator
#thriftparser.input = thriftlist
#thriftparser.output = $$thriftmarker
#thriftparser.commands = $$ThriftParser $$shell_path($$PWD/thrift/src) $$shell_path($$PWD/generated) $$escape_expand(\n\t)echo ThriftParser have been executed > $$thriftmarker
#thriftparser.variable_out = JUNK
#thriftparser.depends = $$ThriftParserDependency $$generated_headers $$generated_sources
#thriftparser.CONFIG += combine
#QMAKE_EXTRA_COMPILERS += thriftparser

for(genfile, THRIFT_GENERATED) {
  genfile_full = $$shell_path($$PWD/generated/$$genfile)
  genfile_split = $$split(genfile, '.')
  genfile_name = $$first(genfile_split)
  genfile_ext = $$last(genfile_split)
  gen_command = $$ThriftParser $$shell_path($$PWD/thrift/src) $$shell_path($$PWD/generated)
  compiler_name = thrift_generator_$${genfile_name}_$${genfile_ext}
  #message(============== $$compiler_name)

  eval($${compiler_name}.name = generate $$genfile)
  #eval(v = \$\$$${compiler_name}.name)
  #message($$v)

  eval($${compiler_name}.input = thriftlist)
  #eval(v = \$\$$${compiler_name}.input)
  #message($$v)

  eval($${compiler_name}.commands = $$gen_command \$\$escape_expand(\\n\\t)echo ThriftParser have been executed)
  #eval(v = \$\$$${compiler_name}.commands)
  #message($$v)

  eval($${compiler_name}.output = $$genfile_full)
  #eval(v = \$\$$${compiler_name}.output)
  #message($$v)

  eval($${compiler_name}.depends = $$ThriftParserDependency)
  #eval(v = \$\$$${compiler_name}.depends)
  #message($$v)

  eval($${compiler_name}.CONFIG = combine)
  #eval(v = \$\$$${compiler_name}.CONFIG)
  #message($$v)

  isEqual(genfile_ext, 'h') {
    eval($${compiler_name}.variable_out = HEADERS)
  } else {
    eval($${compiler_name}.variable_out = SOURCES)
  }
  #eval(v = \$\$$${compiler_name}.variable_out)
  #message($$v)

  eval(QMAKE_EXTRA_COMPILERS += $${compiler_name})
}
#message($$QMAKE_EXTRA_COMPILERS)




