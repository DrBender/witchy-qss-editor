TARGET = qss_editor
TEMPLATE = app
QT += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
# CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += editor
INCLUDEPATH += preview
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    preview/QssWidgetsPreview.cpp \
    editor/LineNumberArea.cpp \
    editor/SyntaxHighlighter.cpp \
    editor/QssTextEditor.cpp 
    

HEADERS += \
    MainWindow.h \
    preview/QssWidgetsPreview.h \
    editor/LineNumberArea.h \
    editor/SyntaxHighlighter.h \
    editor/QssTextEditor.h 
    


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
