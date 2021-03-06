# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-messwerk

CONFIG += sailfishapp
QT += sensors positioning

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_LFLAGS += -std=c++0x

SOURCES += src/Messwerk.cpp \
    src/accelerometer.cpp \
    src/gyroscope.cpp \
    src/magnetometer.cpp \
    src/sensor.cpp \
    src/plotwidget.cpp \
    src/rotation.cpp \
    src/light.cpp \
    src/proximity.cpp \
    src/satelliteposwidget.cpp \
    src/satelliteinfo.cpp \
    src/activateable.cpp \
    src/satellitestrengthwidget.cpp \
    src/settings.cpp \
    src/wakelock.cpp \
    src/position.cpp

OTHER_FILES += qml/Messwerk.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/harbour-messwerk.changes.in \
    rpm/harbour-messwerk.spec \
    rpm/harbour-messwerk.yaml \
    translations/*.ts \
    harbour-messwerk.desktop \
    qml/pages/InfoPage.qml \
    qml/pages/MagnetPage.qml \
    qml/pages/LightPage.qml \
    qml/pages/GyroPage.qml \
    qml/pages/AccelPage.qml \
    qml/Constants.js \
    qml/pages/PlotTestPage.qml \
    qml/pages/RotationPage.qml \
    qml/pages/SettingsDialog.qml \
    qml/pages/SatellitePage.qml \
    qml/pages/PositionPage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-messwerk-de.ts \
    translations/harbour-messwerk-pl.ts \
    translations/harbour-messwerk-sv.ts

HEADERS += \
    src/accelerometer.h \
    src/gyroscope.h \
    src/magnetometer.h \
    src/sensor.h \
    src/plotwidget.h \
    src/rotation.h \
    src/light.h \
    src/proximity.h \
    src/satelliteposwidget.h \
    src/satelliteinfo.h \
    src/activateable.h \
    src/satellitestrengthwidget.h \
    src/settings.h \
    src/wakelock.h \
    src/position.h

# use this for harbour-compliant builds:
#DEFINES += FOR_HARBOUR
# and this for all features
LIBS += -lkeepalive
