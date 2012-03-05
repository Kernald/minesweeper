#include "core.hpp"

#include <QtCore/QTime>
#include <QtCore/QTimer>

// Append not supported
void tilesPropAppend(QDeclarativeListProperty<TileData>* /*prop*/, TileData* /*value*/) {
    return;
}

int tilesPropCount(QDeclarativeListProperty<TileData>* prop) {
    return static_cast<QList<TileData*>*>(prop->data)->count();
}

TileData* tilesPropAt(QDeclarativeListProperty<TileData>* prop, int index) {
    return static_cast<QList<TileData*>*>(prop->data)->at(index);
}

QDeclarativeListProperty<TileData> Core::tiles() {
    return QDeclarativeListProperty<TileData>(this, &_tiles, &tilesPropAppend, &tilesPropCount, &tilesPropAt, 0);
}

Core::Core() : _numCols(9), _numRows(9), _playing(true), _won(true) {
    setObjectName("mainObject");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // initialize array
    for (unsigned int i = 0; i < _numRows * _numCols; ++i)
        _tiles << new TileData;

    reset();
}

void Core::setBoard() {
    foreach (TileData* t, _tiles) {
        t->setHasMine(false);
        t->setHint(-1);
    }
    // place mines
    int mines = _nMines;
    _remaining = _numRows * _numCols - mines;
    while (mines) {
        int col = int((double(qrand()) / double(RAND_MAX)) * _numCols);
        int row = int((double(qrand()) / double(RAND_MAX)) * _numRows);

        TileData* t = tile(row, col);

        if (t && !t->hasMine()) {
            t->setHasMine(true);
            --mines;
        }
    }

    // set hints
    for (unsigned int r = 0; r < _numRows; ++r)
        for (unsigned int c = 0; c < _numCols; ++c) {
            TileData* t = tile(r, c);
            if (t && !t->hasMine()) {
                int hint = getHint(r, c);
                t->setHint(hint);
            }
        }

    setPlaying(true);
}

void Core::reset() {
    foreach (TileData* t, _tiles) {
        t->unflip();
        t->setHasFlag(false);
    }
    _nMines = 12;
    _nFlags = 0;
    _won = true;
    emit numMinesChanged();
    emit numFlagsChanged();
    setPlaying(false);
    QTimer::singleShot(600, this, SLOT(setBoard()));
}

int Core::getHint(int row, int col) {
    int hint = 0;
    for (int c = col - 1; c <= col + 1; ++c)
        for (int r = row - 1; r <= row + 1; ++r) {
            TileData* t = tile(r, c);
            if (t && t->hasMine())
                hint++;
        }
    return hint;
}

bool Core::flip(int row, int col) {
    if (!_playing)
        return false;

    TileData *t = tile(row, col);
    if (!t || t->hasFlag())
        return false;

    if (t->flipped()) {
        int flags = 0;
        for (int c = col - 1; c <= col + 1; ++c)
            for (int r = row - 1; r <= row + 1; ++r) {
                TileData* nearT = tile(r, c);
                if (!nearT || nearT == t)
                    continue;
                if (nearT->hasFlag())
                    flags++;
            }
        if (!t->hint() || t->hint() != flags)
            return false;
        for (int c = col - 1; c <= col + 1; ++c)
            for (int r = row - 1; r <= row + 1; ++r) {
                TileData* nearT = tile(r, c);
                if (nearT && !nearT->flipped() && !nearT->hasFlag())
                    flip(r, c);
            }
        return true;
    }

    t->flip();

    if (t->hint() == 0) {
        for (int c = col - 1; c <= col + 1; ++c)
            for (int r = row - 1; r <= row + 1; ++r) {
                TileData* t = tile(r, c);
                if (t && !t->flipped())
                    flip(r, c);
            }
    }

    // Flip all other mines
    if (t->hasMine()) {
        for (unsigned int r = 0; r < _numRows; ++r)
            for (unsigned int c = 0; c < _numCols; ++c) {
                TileData* t = tile(r, c);
                if (t && t->hasMine())
                    flip(r, c);
            }
        if (_won) {
            _won = false;
            hasWonChanged();
        }
        setPlaying(false);
        return true;
    }

    --_remaining;
    if (!_remaining) {
        _won = true;
        hasWonChanged();
        setPlaying(false);
        return true;
    }
    return true;
}

bool Core::flag(int row, int col) {
    TileData *t = tile(row, col);
    if (!t || !_playing || t->flipped())
        return false;

    t->setHasFlag(!t->hasFlag());
    _nFlags += (t->hasFlag() ? 1 : -1);
    emit numFlagsChanged();
    return true;
}

bool Core::onBoard(unsigned int r, unsigned int c) const {
    return r < _numRows && c < _numCols;
}

TileData* Core::tile(int row, int col) {
    return onBoard(row, col) ? _tiles[col + _numRows * row] : NULL;
}

void Core::setPlaying(bool b) {
    if (b == _playing)
        return;
    _playing = b;
    emit isPlayingChanged();
}
