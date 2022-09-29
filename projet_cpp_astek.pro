TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        adresse.cpp \
        annuaire.cpp \
        contact.cpp \
        contactprive.cpp \
        contactpro.cpp \
        date.cpp \
        exceptionadresse.cpp \
        exceptioncontact.cpp \
        interafaceconsole.cpp \
        main.cpp

HEADERS += \
    adresse.h \
    annuaire.h \
    contact.h \
    contactprive.h \
    contactpro.h \
    date.h \
    exceptionadresse.h \
    exceptioncontact.h \
    interafaceconsole.h \
    utils.h
