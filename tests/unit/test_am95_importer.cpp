#include <QtTest>
#include <QtEndian>
#include "importers/Am95Importer.h"

static void appendLE16(QByteArray &arr, quint16 v) {
    char buf[2];
    qToLittleEndian(v, reinterpret_cast<uchar*>(buf));
    arr.append(buf, 2);
}

static void appendLE32(QByteArray &arr, quint32 v) {
    char buf[4];
    qToLittleEndian(v, reinterpret_cast<uchar*>(buf));
    arr.append(buf, 4);
}

static QByteArray makeSampleExport() {
    QByteArray data;
    data.append("AM95", 4);
    appendLE32(data, 2); // two metatiles

    // Metatile 0
    appendLE16(data, 1); // subtile0 tileIndex=1
    appendLE16(data, 0);
    appendLE16(data, 0);
    appendLE16(data, 0);
    appendLE16(data, 0); // behavior
    data.append(char(0)); // collisionFlags
    data.append(char(0)); // palRow
    data.append(char(0)); // reserved

    // Metatile 1
    appendLE16(data, 0x400); // subtile0 with hFlip
    appendLE16(data, 0);
    appendLE16(data, 0);
    appendLE16(data, 0);
    appendLE16(data, 0); // behavior
    data.append(char(0)); // collisionFlags
    data.append(char(1)); // palRow
    data.append(char(0)); // reserved

    appendLE32(data, 2); // two palette rows
    for (int p=0; p<2; ++p) {
        for (int c=0; c<16; ++c) {
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
        }
    }

    return data;
}

class TestAm95Importer : public QObject {
    Q_OBJECT
private slots:
    void parseFile();
    void corruption();
    void badPaletteRow();
};

void TestAm95Importer::parseFile() {
    QByteArray data = makeSampleExport();
    QTemporaryFile tmp;
    QVERIFY(tmp.open());
    tmp.write(data);
    tmp.flush();
    Am95ImportResult res = Am95Importer::parse(tmp.fileName());
    QCOMPARE(res.metatiles.size(), 2);
    QCOMPARE(res.paletteRows.size(), 2);
    QCOMPARE(res.metatiles.at(0).subtile[0].tileIndex, (uint16_t)1);
    QVERIFY(res.metatiles.at(1).subtile[0].hFlip);
    QCOMPARE(res.attributes.at(1).palRow, (uint8_t)1);
}

void TestAm95Importer::corruption() {
    QByteArray data = makeSampleExport();
    data.chop(1);
    QTemporaryFile tmp;
    QVERIFY(tmp.open());
    tmp.write(data);
    tmp.flush();
    QVERIFY_EXCEPTION_THROWN(Am95Importer::parse(tmp.fileName()), std::runtime_error);
}

void TestAm95Importer::badPaletteRow() {
    QByteArray data = makeSampleExport();
    // set palRow of first metatile to 12
    int palRowOffset = 8 + 8 + 2 + 1; // header+count, subtiles, behavior, collision
    data[palRowOffset] = char(12);
    QTemporaryFile tmp;
    QVERIFY(tmp.open());
    tmp.write(data);
    tmp.flush();
    Am95ImportResult res = Am95Importer::parse(tmp.fileName());
    QCOMPARE(res.attributes.at(0).palRow, (uint8_t)7);
    QCOMPARE(res.warnings.size(), 1);
}

#include "test_am95_importer.moc"
