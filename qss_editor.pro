TARGET = qss_editor
TEMPLATE = app
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

MOC_DIR = moc
OBJECTS_DIR = obj
RCC_DIR = rcc

INCLUDEPATH += editor
INCLUDEPATH += preview

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    preview/QssWidgetsPreview.cpp \
    editor/LineNumberArea.cpp \
    editor/Parser.cpp \
    editor/SyntaxHighlighter.cpp \
    editor/QssTextEditor.cpp 
    

HEADERS += \
    MainWindow.h \
    preview/QssWidgetsPreview.h \
    editor/Ast.h \
    editor/LineNumberArea.h \
    editor/Parser.h \
    editor/SyntaxHighlighter.h \
    editor/QssTextEditor.h 
    
######

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
