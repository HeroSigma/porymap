#include "importers/Am95Importer.h"
#include <QFile>
#include <QFileInfo>
#include <QtEndian>

static uint16_t readLE16(const QByteArray &data, int offset) {
    return qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(data.constData() + offset));
}

static uint32_t readLE32(const QByteArray &data, int offset) {
    return qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + offset));
}

static Am95ImportResult parseSingleFile(const QString &path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Could not open file");
    }
    QByteArray data = f.readAll();
    if (data.size() < 8)
        throw std::runtime_error("File too small");
    if (data.left(4) != QByteArray("AM95"))
        throw std::runtime_error("Bad signature");
    int offset = 4;
    uint32_t count = readLE32(data, offset); offset += 4;
    Am95ImportResult result;
    result.metatiles.reserve(static_cast<int>(count));
    result.attributes.reserve(static_cast<int>(count));
    for (uint32_t i=0;i<count;i++) {
        if (offset + 8 > data.size())
            throw std::runtime_error("Truncated metatile data");
        Am95Metatile m{};
        for (int j=0;j<4;j++) {
            if (offset + 2 > data.size())
                throw std::runtime_error("Truncated subtile data");
            uint16_t word = readLE16(data, offset); offset += 2;
            Am95Subtile st{};
            st.tileIndex = word & 0x3FF;
            if (st.tileIndex >= 1024)
                throw std::runtime_error("Tile index out of range");
            st.hFlip = word & 0x400;
            st.vFlip = word & 0x800;
            st.priority = word & 0x1000;
            st.palRow = (word >> 13) & 0x7;
            m.subtile[j] = st;
        }
        if (offset + 5 > data.size())
            throw std::runtime_error("Truncated attributes");
        Am95MetatileAttributes attr{};
        attr.behavior = readLE16(data, offset); offset += 2;
        attr.collisionFlags = static_cast<uint8_t>(data.at(offset++));
        attr.palRow = static_cast<uint8_t>(data.at(offset++));
        if (attr.palRow > 7) {
            result.warnings << QString("Palette row %1 out of range (0-7). Clamped to 7.").arg(attr.palRow);
            attr.palRow = 7;
        }
        attr.reserved = static_cast<uint8_t>(data.at(offset++));
        result.metatiles.append(m);
        result.attributes.append(attr);
    }
    if (offset + 4 > data.size())
        throw std::runtime_error("Truncated palette header");
    uint32_t numPal = readLE32(data, offset); offset += 4;
    for (uint32_t p=0; p<numPal; ++p) {
        if (offset + 16*3 > data.size())
            throw std::runtime_error("Truncated palette data");
        QImage img(16,1,QImage::Format_ARGB32);
        for (int c=0;c<16;c++) {
            uint8_t r = static_cast<uint8_t>(data.at(offset++));
            uint8_t g = static_cast<uint8_t>(data.at(offset++));
            uint8_t b = static_cast<uint8_t>(data.at(offset++));
            img.setPixel(c,0,qRgb(r,g,b));
        }
        result.paletteRows.append(img);
    }
    return result;
}

Am95ImportResult Am95Importer::parse(const QString &path) {
    QFileInfo info(path);
    if (info.isDir())
        throw std::runtime_error("Directory imports are not supported");
    return parseSingleFile(path);
}

