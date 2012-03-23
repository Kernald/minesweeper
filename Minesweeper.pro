CONFIG -= debug_and_release debug
CONFIG += release

QT += declarative

LIBS += -lbps

SOURCES += src/main.cpp \
    src/tiledata.cpp \
    src/core.cpp

RESOURCES += \
    res.qrc

HEADERS += \
    src/tiledata.hpp \
    src/core.hpp

QMAKE_LFLAGS += '-Wl,-rpath,\'./app/native/lib\''

package.target = $${TARGET}.bar
package.depends = $$TARGET
package.commands = blackberry-nativepackager \
    -devMode -debugToken ~/.rim/debugtoken1.bar \
    -package $${TARGET}.bar -arg -platform -arg blackberry \
	-arg -platformpluginpath -arg app/native/lib/platforms \
    blackberry-tablet.xml $$TARGET \
    -e res/icon.png res/icon.png \
    -e res/splashscreen.png res/splashscreen.png \
    -e $$[QT_INSTALL_LIBS]/libQtCore.so.4 lib/libQtCore.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtGui.so.4 lib/libQtGui.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtOpenGL.so.4 lib/libQtOpenGL.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtNetwork.so.4 lib/libQtNetwork.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtDeclarative.so.4 lib/libQtDeclarative.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtScript.so.4 lib/libQtScript.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtSvg.so.4 lib/libQtSvg.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtSql.so.4 lib/libQtSql.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtXmlPatterns.so.4 lib/libQtXmlPatterns.so.4 \
    -e $$[QT_INSTALL_PLUGINS]/platforms/libblackberry.so lib/platforms/libblackberry.so \
    -e $$[QT_INSTALL_IMPORTS]/Qt/labs/particles/libqmlparticlesplugin.so lib/qml/libqmlparticlesplugin.so

QMAKE_EXTRA_TARGETS += package

OTHER_FILES += \
    qml/Minesweeper/main.qml \
    qml/Minesweeper/Core/Tile.qml \
    qml/Minesweeper/Core/Explosion.qml \
    qml/Minesweeper/Core/Fireworks.qml \
    qml/Minesweeper/fireworksCreation.js
