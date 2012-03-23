var component;

function createFireworks() {
    component = Qt.createComponent("qrc:/qml/Core/Fireworks.qml");
    if (component.status === Component.Ready)
        finishFireworks();
    else
        component.statusChanged.connect(finishFireworks);
}

function finishFireworks() {
    if (component.status === Component.Ready) {
        for (var i = 0; i < 20; i++) {
            var fw = component.createObject(fireworks, {
                                                "x": Math.floor((Math.random() * 2000)) % 1024,
                                                "y": Math.floor((Math.random() * 2000)) % 1024
                                            });
            if (fw === null)
                console.log("Error creating object");
            else
                fw.burst(50);
        }
    } else if (component.status === Component.Error) {
        console.log("Error loading component:", component.errorString());
    }
}
