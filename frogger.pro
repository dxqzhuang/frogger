TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

#WINDOWS
# put SFML file in the same location as project
LIBS += -L"..\SFML-2.3.2\lib"
LIBS += -L"..\SFML-2.3.2\bin"

#MAC
#LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS
INCLUDEPATH += "..\SFML-2.3.2\include"
DEPENDPATH += "..\SFML-2.3.2\include"

#MAC
#INCLUDEPATH += "/usr/local/include"
#DEPENDPATH += "/usr/local/include"

SOURCES += main.cpp \
    game.cpp \
    frog.cpp \
    log.cpp \
    truck.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    constants.h \
    game.h \
    frog.h \
    log.h \
    truck.h
