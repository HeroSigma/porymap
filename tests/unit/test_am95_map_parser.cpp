#include <QtTest>
#include <QtEndian>
#include "importers/Am95MapParser.h"

static void appendLE16m(QByteArray &arr, quint16 v) {
    char buf[2];
    qToLittleEndian(v, reinterpret_cast<uchar*>(buf));
    arr.append(buf, 2);
}

static void appendLE32m(QByteArray &arr, quint32 v) {
    char buf[4];
    qToLittleEndian(v, reinterpret_cast<uchar*>(buf));
    arr.append(buf, 4);
}

static QByteArray makeSampleMap() {
    QByteArray data;
    data.append("AM95MAP", 7);
    appendLE32m(data, 2); // width
    appendLE32m(data, 1); // height
    appendLE32m(data, 0); // primary tileset index
    appendLE32m(data, 1); // secondary tileset index
    appendLE16m(data, 0); // block 0
    appendLE16m(data, 5); // block 1
    return data;
}

class TestAm95MapParser : public QObject {
    Q_OBJECT
private slots:
    void parseFile();
    void truncated();
};

void TestAm95MapParser::parseFile() {
    Am95ProjectContext ctx;
    ctx.tilesetLabelsOrdered = QStringList{"prim", "sec"};
    ctx.primaryTilesetLabels = QStringList{"prim"};
    ctx.secondaryTilesetLabels = QStringList{"sec"};
    ctx.defaultPrimaryTileset = "prim";
    ctx.defaultSecondaryTileset = "sec";

    QByteArray data = makeSampleMap();
    QTemporaryFile tmp;
    QVERIFY(tmp.open());
    tmp.write(data);
    tmp.flush();
    bool error = false;
    Am95MapParser::Am95MapImportResult res = Am95MapParser::parse(tmp.fileName(), &error, ctx);
    QVERIFY(!error);
    QCOMPARE(res.width, 2);
    QCOMPARE(res.height, 1);
    QCOMPARE(res.blockdata.size(), 2);
    QCOMPARE(res.primaryTilesetLabel, QString("prim"));
    QCOMPARE(res.secondaryTilesetLabel, QString("sec"));
}

void TestAm95MapParser::truncated() {
    Am95ProjectContext ctx;
    ctx.tilesetLabelsOrdered = QStringList{"prim"};
    ctx.primaryTilesetLabels = QStringList{"prim"};
    ctx.secondaryTilesetLabels = QStringList{"sec"};
    ctx.defaultPrimaryTileset = "prim";
    ctx.defaultSecondaryTileset = "sec";

    QByteArray data = makeSampleMap();
    data.chop(1);
    QTemporaryFile tmp;
    QVERIFY(tmp.open());
    tmp.write(data);
    tmp.flush();
    bool error = false;
    Am95MapParser::Am95MapImportResult res = Am95MapParser::parse(tmp.fileName(), &error, ctx);
    QVERIFY(error);
    QCOMPARE(res.blockdata.size(), 0);
}

#include "test_am95_map_parser.moc"
