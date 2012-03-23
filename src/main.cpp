#include "core.hpp"

#ifdef __QNX__
#include <bps/event.h>
#include <bps/orientation.h>
#include <bps/sensor.h>
#endif // __QNX__

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
#ifdef __QNX__
    bps_initialize();
    int orientation_angle;
    orientation_direction_t direction;
    orientation_get(&direction, &orientation_angle);
    sensor_set_rate(SENSOR_TYPE_AZIMUTH_PITCH_ROLL, 25000);
    sensor_set_skip_duplicates(SENSOR_TYPE_AZIMUTH_PITCH_ROLL, true);
    sensor_request_events(SENSOR_TYPE_AZIMUTH_PITCH_ROLL);
#endif // __QNX__

	QApplication app(argc, argv);

	qmlRegisterType<TileData>();
	QDeclarativeView viewer;
    viewer.setResizeMode(QDeclarativeView::SizeRootObjectToView);
	Core* game = new Core;
	viewer.engine()->rootContext()->setContextObject(game);
	viewer.engine()->rootContext()->setContextProperty("core", game);
#ifdef __QNX__
	viewer.engine()->importPlugin("app/native/lib/qml/libqmlparticlesplugin.so", "Qt.labs.particles", NULL);
#endif // __QNX__
#ifdef _MSC_VER
	viewer.engine()->importPlugin(QDir().absolutePath() + "/qmlparticlesplugin.dll", "Qt.labs.particles", NULL);
#endif // _MSC_VER
	viewer.setSource(QUrl("qrc:/qml/main.qml"));
	viewer.setWindowIcon(QPixmap(":/res/mine"));
	viewer.show();

#ifdef __QNX__
    while (true) {
        bps_event_t *event = NULL;
        int rc = bps_get_event(&event, 0);
        if (rc != BPS_SUCCESS) {
            return 1;
        }
        if (event) {
            int domain = bps_event_get_domain(event);
            if (domain == sensor_get_domain()) {
                if (SENSOR_AZIMUTH_PITCH_ROLL_READING == bps_event_get_code(event)) {
                    int old_orientation_angle = orientation_angle;
                    orientation_get(&direction, &orientation_angle);
                    if (old_orientation_angle != orientation_angle) {
                        if (orientation_angle == 0 || orientation_angle == 180) {
                            viewer.resize(1024, 600);
                        } else {
                            viewer.resize(600, 1024);
                        }
                    }
                }
            }
        }
        app.processEvents();
    }
    return 0;
#else // __QNX__
    return app.exec();
#endif // __QNX__
}

