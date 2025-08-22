#pragma once
#include <QString>
#include <QStringList>
#include <QVector>
#include <QImage>
#include <stdexcept>

struct Am95Subtile {
    uint16_t tileIndex;
    bool hFlip;
    bool vFlip;
    bool priority;
    uint8_t palRow;
};

struct Am95Metatile {
    Am95Subtile subtile[4];
};

struct Am95MetatileAttributes {
    uint16_t behavior;
    uint8_t collisionFlags;
    uint8_t palRow;
    uint8_t reserved;
};

struct Am95ImportResult {
    QVector<Am95Metatile> metatiles;
    QVector<Am95MetatileAttributes> attributes;
    QVector<QImage> paletteRows;
    QStringList warnings;
};

class Am95Importer {
public:
    static Am95ImportResult parse(const QString &path);
};

