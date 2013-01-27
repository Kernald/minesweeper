#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "core.hpp"

int main(int argc, char *argv[]) {
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<TileData>();
    Core* game = new Core;
    QmlApplicationViewer viewer;
    viewer.engine()->rootContext()->setContextObject(game);
    viewer.engine()->rootContext()->setContextProperty("core", game);
    viewer.addImportPath(QLatin1String("modules")); // ADDIMPORTPATH
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait); // ORIENTATION
    viewer.setMainQmlFile(QLatin1String("qml/main.qml")); // MAINQML
    viewer.showExpanded();

    return app->exec();
}
