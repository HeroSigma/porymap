#pragma once
#include <QString>
#include <QStringList>
#include <QVector>

class Layout;

struct Am95ProjectContext {
    QStringList tilesetLabelsOrdered;
    QStringList primaryTilesetLabels;
    QStringList secondaryTilesetLabels;
    QString defaultPrimaryTileset;
    QString defaultSecondaryTileset;
};

namespace Am95MapParser {
struct Am95MapImportResult {
    int width = 0;
    int height = 0;
    QVector<uint16_t> blockdata;
    QString primaryTilesetLabel;
    QString secondaryTilesetLabel;
};

Am95MapImportResult parse(const QString &filepath, bool *error, const Am95ProjectContext &ctx);
}

