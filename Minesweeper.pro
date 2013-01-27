TEMPLATE = app

include(qmlapplicationviewer/qmlapplicationviewer.pri)

QML_IMPORT_PATH =


SOURCES += src/main.cpp \
    src/tiledata.cpp \
    src/core.cpp

HEADERS += \
    src/tiledata.hpp \
    src/core.hpp

RESOURCES += \
    res.qrc

OTHER_FILES += \
    bar-descriptor.xml \
    qml/main.qml \
    qml/Core/Tile.qml \
    qml/Core/Explosion.qml \
    qml/Core/Fireworks.qml \
    qml/fireworksCreation.js
