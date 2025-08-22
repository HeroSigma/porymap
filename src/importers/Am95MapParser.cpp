#include "importers/Am95MapParser.h"
#include <QFile>
#include <QtEndian>
#include <stdexcept>

static uint16_t readLE16(const QByteArray &data, int offset) {
    return qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(data.constData() + offset));
}

static uint32_t readLE32(const QByteArray &data, int offset) {
    return qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + offset));
}

Am95MapParser::Am95MapImportResult Am95MapParser::parse(const QString &filepath, bool *error, const Am95ProjectContext &ctx) {
    if (error) *error = false;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) *error = true;
        return Am95MapImportResult();
    }
    QByteArray data = file.readAll();
    file.close();
    if (data.size() < 23) {
        if (error) *error = true;
        return Am95MapImportResult();
    }
    if (data.left(7) != QByteArray("AM95MAP")) {
        if (error) *error = true;
        return Am95MapImportResult();
    }
    int offset = 7;
    uint32_t width = readLE32(data, offset); offset += 4;
    uint32_t height = readLE32(data, offset); offset += 4;
    uint32_t primaryIdx = readLE32(data, offset); offset += 4;
    uint32_t secondaryIdx = readLE32(data, offset); offset += 4;
    int expectedSize = offset + static_cast<int>(width * height * 2);
    if (data.size() != expectedSize) {
        if (error) *error = true;
        return Am95MapImportResult();
    }
    Am95MapImportResult result;
    result.width = static_cast<int>(width);
    result.height = static_cast<int>(height);
    for (uint32_t i = 0; i < width * height; ++i) {
        uint16_t word = readLE16(data, offset); offset += 2;
        result.blockdata.append(word);
    }
    result.primaryTilesetLabel = ctx.tilesetLabelsOrdered.value(static_cast<int>(primaryIdx), ctx.defaultPrimaryTileset);
    if (!ctx.primaryTilesetLabels.contains(result.primaryTilesetLabel))
        result.primaryTilesetLabel = ctx.defaultPrimaryTileset;
    result.secondaryTilesetLabel = ctx.tilesetLabelsOrdered.value(static_cast<int>(secondaryIdx), ctx.defaultSecondaryTileset);
    if (!ctx.secondaryTilesetLabels.contains(result.secondaryTilesetLabel))
        result.secondaryTilesetLabel = ctx.defaultSecondaryTileset;
    return result;
}

