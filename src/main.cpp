#include "core.hpp"

#include <QtDeclarative>
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	qmlRegisterType<TileData>();
	QDeclarativeView viewer;
	Core* game = new Core;
	viewer.engine()->rootContext()->setContextObject(game);
    viewer.engine()->rootContext()->setContextProperty("core", game);
#ifdef __QNX__
	viewer.engine()->importPlugin("app/native/lib/qml/libqmlparticlesplugin.so", "Qt.labs.particles", NULL);
#endif // __QNX__
	viewer.setSource(QUrl("qrc:/qml/main.qml"));
	viewer.setWindowIcon(QPixmap(":/res/mine"));
	viewer.show();

	return app.exec();
}

