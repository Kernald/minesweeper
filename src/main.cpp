#include "core.hpp"

#include <QtDeclarative>
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

    qmlRegisterType<TileData>();
    QDeclarativeView viewer;
    Core* game = new Core;
    viewer.engine()->rootContext()->setContextObject(game);
	viewer.engine()->importPlugin("/accounts/1000/appdata/com.mpl.minesweeper.testDev_minesweeper964f3f34/app/native/lib/qml/libqmlparticlesplugin.so", "Qt.labs.particles", NULL); 
    viewer.setSource(QUrl("qrc:/qml/main.qml"));
    viewer.setWindowIcon(QPixmap(":/res/mine"));
    viewer.show();

    return app.exec();
}

