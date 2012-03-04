#include "tiledata.hpp"

void TileData::flip() {
    if (_flipped)
        return;
    _flipped = true;
    emit flippedChanged();
}

void TileData::unflip() {
    if (!_flipped)
        return;
    _flipped = false;
    emit flippedChanged();
}
