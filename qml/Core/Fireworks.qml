import Qt.labs.particles 1.0

Particles {
    id: particles
    width: 1;
    height: 1;
    emissionRate: 0
    lifeSpan: 3500;
    lifeSpanDeviation: 600
    angle: 0;
    angleDeviation: 360;
    velocity: 100;
    velocityDeviation: 30;
    source: randomImage();

    function randomImage() {
        var images = ["red", "blue", "green", "white", "yellow"];
        var idx = Math.floor((Math.random() * 100)) % images.length;
        return ("qrc:/res/fireworks/" + images[idx]);
    }
}
