#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include <QObject>
#include <QString>
#include <QQuickView>
#include <QQmlContext>
#include <QGuiApplication>
#include <QTimer>
#include <QGeoSatelliteInfoSource>

#include "accelerometer.h"
#include "gyroscope.h"
#include "magnetometer.h"
#include "rotation.h"
#include "light.h"
#include "proximity.h"
#include "satelliteinfo.h"
#include "position.h"

#include "settings.h"

#include "plotwidget.h"
#include "satelliteposwidget.h"
#include "satellitestrengthwidget.h"


int main(int argc, char *argv[])
{
    int result = 0;

    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    qmlRegisterType<PlotWidget>("harbour.messwerk.MesswerkWidgets", 1, 0, "PlotWidget");
    qmlRegisterType<SatellitePosWidget>("harbour.messwerk.MesswerkWidgets", 1, 0, "SatellitePosWidget");
    qmlRegisterType<SatelliteStrengthWidget>("harbour.messwerk.MesswerkWidgets", 1, 0, "SatelliteStrengthWidget");

    QTimer refreshTimer;

    Accelerometer accelerometer(false);
    Gyroscope gyroscope(false);
    Magnetometer magnetometer(false);
    Rotation rotation(false);
    Light light(false);
    Proximity proximity(true);
    SatelliteInfo satelliteinfo;
    Position position;

    // connect not self-refreshing sensors to the global timer
    QObject::connect(&refreshTimer, SIGNAL(timeout()), &accelerometer, SLOT(refresh()));
    QObject::connect(&refreshTimer, SIGNAL(timeout()), &gyroscope, SLOT(refresh()));
    QObject::connect(&refreshTimer, SIGNAL(timeout()), &magnetometer, SLOT(refresh()));
    QObject::connect(&refreshTimer, SIGNAL(timeout()), &rotation, SLOT(refresh()));
    QObject::connect(&refreshTimer, SIGNAL(timeout()), &light, SLOT(refresh()));

    QString qml = QString("qml/%1.qml").arg("Messwerk");
    view->rootContext()->setContextProperty("accelerometer", &accelerometer);
    view->rootContext()->setContextProperty("gyroscope", &gyroscope);
    view->rootContext()->setContextProperty("magnetometer", &magnetometer);
    view->rootContext()->setContextProperty("rotationsensor", &rotation);
    view->rootContext()->setContextProperty("lightsensor", &light);
    view->rootContext()->setContextProperty("proximitysensor", &proximity);
    view->rootContext()->setContextProperty("satelliteinfo", &satelliteinfo);
    view->rootContext()->setContextProperty("positionsensor", &position);
    view->rootContext()->setContextProperty("settings", &(Settings::instance()));
    view->setSource(SailfishApp::pathTo(qml));
    view->show();

    refreshTimer.start(100);

    result = app->exec();

    delete view;
    delete app;

    return result;
}

