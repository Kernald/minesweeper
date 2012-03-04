#ifndef __TILEDATA_HPP__
#define __TILEDATA_HPP__

#include <QtCore/QObject>

class TileData : public QObject {

    Q_OBJECT

public:
    TileData() : _hasFlag(false), _hasMine(false), _hint(-1), _flipped(false) {}

    Q_PROPERTY(bool hasFlag READ hasFlag WRITE setHasFlag NOTIFY hasFlagChanged)
    bool hasFlag() const {
        return _hasFlag;
    }
    void setHasFlag(bool flag) {
        if (flag == _hasFlag)
            return;
        _hasFlag = flag;
        emit hasFlagChanged();
    }

    Q_PROPERTY(bool hasMine READ hasMine NOTIFY hasMineChanged)
    bool hasMine() const {
        return _hasMine;
    }
    void setHasMine(bool mine) {
        if (mine == _hasMine)
            return;
        _hasMine = mine;
        emit hasMineChanged();
    }

    Q_PROPERTY(int hint READ hint NOTIFY hintChanged)
    int hint() const {
        return _hint;
    }
    void setHint(int hint) {
        if (hint == _hint)
            return;
        _hint = hint;
        emit hintChanged();
    }

    Q_PROPERTY(bool flipped READ flipped NOTIFY flippedChanged())
    bool flipped() const {
        return _flipped;
    }

    void flip();
    void unflip();

signals:
    void flippedChanged();
    void hasFlagChanged();
    void hintChanged();
    void hasMineChanged();

private:
    bool    _hasFlag;
    bool    _hasMine;
    int     _hint;
    bool    _flipped;
};

#endif // __TILEDATA_HPP__
