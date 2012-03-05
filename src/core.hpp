#ifndef __CORE_HPP__
#define __CORE_HPP__

#include "tiledata.hpp"

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>


class Core : public QObject {

    Q_OBJECT

public:
    Core();

    Q_PROPERTY(QDeclarativeListProperty<TileData> tiles READ tiles CONSTANT)
    QDeclarativeListProperty<TileData> tiles();

    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    bool isPlaying() const {
        return _playing;
    }

    Q_PROPERTY(bool hasWon READ hasWon NOTIFY hasWonChanged)
    bool hasWon() const {
        return _won;
    }

    Q_PROPERTY(int numMines READ numMines NOTIFY numMinesChanged)
    int numMines() const {
        return _nMines;
    }

    Q_PROPERTY(int numFlags READ numFlags NOTIFY numFlagsChanged)
    int numFlags() const {
        return _nFlags;
    }

public slots:
    Q_INVOKABLE bool flip(int row, int col, bool end = false);
    Q_INVOKABLE bool flag(int row, int col);
    void setBoard();
    void reset();

signals:
    void isPlayingChanged();
    void hasWonChanged();
    void numMinesChanged();
    void numFlagsChanged();

private:
    bool onBoard(unsigned int r, unsigned int c) const;
    TileData* tile(int row, int col);
    int getHint(int row, int col);
    void setPlaying(bool b);

    QList<TileData*>   _tiles;
    unsigned int       _numCols;
    unsigned int       _numRows;
    bool               _playing;
    bool               _won;
    unsigned int       _remaining;
    unsigned int       _nMines;
    unsigned int       _nFlags;
};

#endif // __CORE_HPP__
