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
    adminpage.cpp \
    cart.cpp \
    choosepay.cpp \
    client.cpp \
    clientprof.cpp \
    clothes_filter.cpp \
    clothes_filter_info.cpp \
    customer.cpp \
    customerlogin.cpp \
    customerprof.cpp \
    dialog_add.cpp \
    dialog_options.cpp \
    forgetpasclient.cpp \
    forgetpascustomer.cpp \
    fruitandveg_filter.cpp \
    fruitandveg_filter_info.cpp \
    gooddetails.cpp \
    goodslist.cpp \
    groupinggoods.cpp \
    homeapps_filter.cpp \
    listofcustomersforadmin.cpp \
    listoftransactions.cpp \
    loginadmin.cpp \
    loginclient.cpp \
    main.cpp \
    loginpage.cpp \
    mainlogin.cpp \
    others_filter_info.cpp \
    paymentgateway.cpp \
    product.cpp \
    recoverypasclient.cpp \
    recoverypascustomer.cpp \
    signup.cpp \
    signupclient.cpp \
    signupcustomer.cpp \
    storecustomer.cpp \
    super_filter.cpp \
    tech_filter.cpp

HEADERS += \
    adminpage.h \
    cart.h \
    choosepay.h \
    client.h \
    clientprof.h \
    clothes_filter.h \
    clothes_filter_info.h \
    customer.h \
    customerlogin.h \
    customerprof.h \
    dialog_add.h \
    dialog_options.h \
    forgetpasclient.h \
    forgetpascustomer.h \
    fruitandveg_filter.h \
    fruitandveg_filter_info.h \
    gooddetails.h \
    goodslist.h \
    groupinggoods.h \
    homeapps_filter.h \
    listofcustomersforadmin.h \
    listoftransactions.h \
    loginadmin.h \
    loginclient.h \
    loginpage.h \
    mainlogin.h \
    others_filter_info.h \
    paymentgateway.h \
    product.h \
    recoverypasclient.h \
    recoverypascustomer.h \
    signup.h \
    signupclient.h \
    signupcustomer.h \
    storecustomer.h \
    super_filter.h \
    tech_filter.h

FORMS += \
    adminpage.ui \
    cart.ui \
    choosepay.ui \
    clientprof.ui \
    clothes_filter.ui \
    customerlogin.ui \
    customerprof.ui \
    dialog_add.ui \
    dialog_options.ui \
    forgetpasclient.ui \
    forgetpascustomer.ui \
    fruitandveg_filter.ui \
    gooddetails.ui \
    goodslist.ui \
    groupinggoods.ui \
    homeapps_filter.ui \
    listofcustomersforadmin.ui \
    listoftransactions.ui \
    loginadmin.ui \
    loginclient.ui \
    loginpage.ui \
    mainlogin.ui \
    paymentgateway.ui \
    recoverypasclient.ui \
    recoverypascustomer.ui \
    signup.ui \
    signupclient.ui \
    signupcustomer.ui \
    storecustomer.ui \
    super_filter.ui \
    tech_filter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
