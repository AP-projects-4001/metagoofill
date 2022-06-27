QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    customer.cpp \
    customerlogin.cpp \
    customerprof.cpp \
    dialog_add.cpp \
    dialog_options.cpp \
    forgetpasclient.cpp \
    forgetpascustomer.cpp \
    loginadmin.cpp \
    loginclient.cpp \
    main.cpp \
    loginpage.cpp \
    mainlogin.cpp \
    product.cpp \
    recoverypasclient.cpp \
    recoverypascustomer.cpp \
    signup.cpp \
    signupclient.cpp \
    signupcustomer.cpp \
    storecustomer.cpp

HEADERS += \
    client.h \
    customer.h \
    customerlogin.h \
    customerprof.h \
    dialog_add.h \
    dialog_options.h \
    forgetpasclient.h \
    forgetpascustomer.h \
    loginadmin.h \
    loginclient.h \
    loginpage.h \
    mainlogin.h \
    product.h \
    recoverypasclient.h \
    recoverypascustomer.h \
    signup.h \
    signupclient.h \
    signupcustomer.h \
    storecustomer.h

FORMS += \
    customerlogin.ui \
    customerprof.ui \
    dialog_add.ui \
    dialog_options.ui \
    forgetpasclient.ui \
    forgetpascustomer.ui \
    loginadmin.ui \
    loginclient.ui \
    loginpage.ui \
    mainlogin.ui \
    recoverypasclient.ui \
    recoverypascustomer.ui \
    signup.ui \
    signupclient.ui \
    signupcustomer.ui \
    storecustomer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
