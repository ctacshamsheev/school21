QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../arithmetic.cpp \
    ../s21CalcController.cpp \
    ../s21CalcModel.cpp \
    creditcontroller.cpp \
    creditmodel.cpp \
    depositcontroller.cpp \
    depositmodel.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    slimcalccontroller.cpp

HEADERS += \
    ../arithmetic.h \
    ../s21CalcController.h \
    ../s21CalcModel.h \
    creditcontroller.h \
    creditmodel.h \
    depositcontroller.h \
    depositmodel.h \
    dialog.h \
    mainwindow.h \
    qcustomplot.h \
    slimcalccontroller.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
