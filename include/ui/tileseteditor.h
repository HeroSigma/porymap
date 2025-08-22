#ifndef TILESETEDITOR_H
#define TILESETEDITOR_H

#include <QMainWindow>
#include <QPointer>
#include <QKeyEvent>
#include "project.h"
#include "history.h"
#include "paletteeditor.h"
#include "tileseteditormetatileselector.h"
#include "tileseteditortileselector.h"
#include "metatilelayersitem.h"
#include "metatileimageexporter.h"

class NoScrollComboBox;
class Layout;

namespace Ui {
class TilesetEditor;
}

class MetatileHistoryItem {
public:
    MetatileHistoryItem() {};
    MetatileHistoryItem(uint16_t metatileId, Metatile *prevMetatile, Metatile *newMetatile, QString prevLabel, QString newLabel) {
        this->metatileId = metatileId;
        this->prevMetatile = prevMetatile;
        this->newMetatile = newMetatile;
        this->prevLabel = prevLabel;
        this->newLabel = newLabel;
    }
    MetatileHistoryItem(uint16_t metatileIdA, uint16_t metatileIdB) {
        this->metatileId = metatileIdA;
        this->swapMetatileId = metatileIdB;
        this->isSwap = true;
    }
    ~MetatileHistoryItem() {
        delete this->prevMetatile;
        delete this->newMetatile;
    }

    uint16_t metatileId = 0;
    Metatile *prevMetatile = nullptr;
    Metatile *newMetatile = nullptr;
    QString prevLabel;
    QString newLabel;

    uint16_t swapMetatileId = 0;
    bool isSwap = false;
};

class TilesetEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TilesetEditor(Project *project, Layout *layout, QWidget *parent = nullptr);
    ~TilesetEditor();
    void update(Layout *layout, QString primaryTilsetLabel, QString secondaryTilesetLabel);
    void updateLayout(Layout *layout);
    void updateTilesets(QString primaryTilsetLabel, QString secondaryTilesetLabel);
    bool selectMetatile(uint16_t metatileId);
    uint16_t getSelectedMetatileId();
    void setMetatileLabel(QString label);
    void queueMetatileReload(uint16_t metatileId);

    QObjectList shortcutableObjects() const;

    void setPaletteId(int paletteId);
    int paletteId() const;

public slots:
    void applyUserShortcuts();
    void onSelectedMetatileChanged(uint16_t);

private slots:
    void onWindowActivated();
    void onHoveredMetatileCleared();
    void onHoveredTileCleared();
    void onMetatileLayerSelectionChanged(const QPoint&, const QSize&);
    void onPaletteEditorChangedPaletteColor();

    void on_actionChange_Metatiles_Count_triggered();

    void on_actionChange_Palettes_triggered();

    void on_actionShow_Unused_toggled(bool checked);
    void on_actionShow_Counts_toggled(bool checked);
    void on_actionShow_UnusedTiles_toggled(bool checked);
    void on_actionMetatile_Grid_triggered(bool checked);
    void on_actionLayer_Grid_triggered(bool checked);
    void on_actionShow_Tileset_Divider_triggered(bool checked);

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_copyButton_MetatileLabel_clicked();

    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_horizontalSlider_MetatilesZoom_valueChanged(int value);
    void on_horizontalSlider_TilesZoom_valueChanged(int value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private:
    void initAttributesUi();
    void initMetatileSelector();
    void initTileSelector();
    void initSelectedTileItem();
    void initMetatileLayersItem();
    void initShortcuts();
    void initExtraShortcuts();
    void restoreWindowState();
    void initMetatileHistory();
    void setTilesets(QString primaryTilesetLabel, QString secondaryTilesetLabel);
    void reset();
    void drawSelectedTiles();
    void redrawTileSelector();
    void redrawMetatileSelector();
    void importTilesetTiles(Tileset*);
    void importAdvanceMapMetatiles(Tileset*);
    void importAdvanceMap95Metatiles(Tileset*);
    void exportTilesImage(Tileset*);
    void exportPorytilesLayerImages(Tileset*);
    void exportMetatilesImage();
    void refresh();
    void commitMetatileLabel();
    void countMetatileUsage();
    void countTileUsage();
    void copyMetatile(bool cut);
    void pasteMetatile(const Metatile &toPaste, QString label);
    bool replaceMetatile(uint16_t metatileId, const Metatile &src, QString label);
    void commitMetatileChange(Metatile * prevMetatile);
    void commitMetatileAndLabelChange(Metatile * prevMetatile, QString prevLabel);
    uint32_t attributeNameToValue(Metatile::Attr attribute, const QString &text, bool *ok);
    void commitAttributeFromComboBox(Metatile::Attr attribute, NoScrollComboBox *combo);
    void onRawAttributesEdited();
    void refreshMetatileAttributes();
    void commitMetatileBehavior();
    void commitEncounterType();
    void commitTerrainType();
    void commitLayerType();
    void commit(MetatileHistoryItem *item);
    void updateEditHistoryActions();
    void setRawAttributesVisible(bool visible);
    void refreshTileFlips();
    void refreshPaletteId();
    void paintSelectedLayerTiles(const QPoint &pos, bool paletteOnly = false);
    void setMetatileLayerOrientation(Qt::Orientation orientation);
    void commitMetatileSwap(uint16_t metatileIdA, uint16_t metatileIdB);
    bool swapMetatiles(uint16_t metatileIdA, uint16_t metatileIdB);
    void applyMetatileSwapToLayouts(uint16_t metatileIdA, uint16_t metatileIdB);
    void applyMetatileSwapsToLayouts();
    void rebuildMetatilePropertiesFrame();
    void addWidgetToMetatileProperties(QWidget *w, int *row, int rowSpan);
    void updateLayerTileStatus();
    void showTileStatus(const Tile &tile);
    void showTileStatus(uint16_t tileId);
    void updateMetatileStatus();
    void showMetatileStatus(uint16_t metatileId);

    Ui::TilesetEditor *ui;
    History<MetatileHistoryItem*> metatileHistory;
    TilesetEditorMetatileSelector *metatileSelector = nullptr;
    TilesetEditorTileSelector *tileSelector = nullptr;
    MetatileLayersItem *metatileLayersItem = nullptr;
    QPointer<PaletteEditor> paletteEditor = nullptr;
    Project *project = nullptr;
    Layout *layout = nullptr;
    Metatile *metatile = nullptr;
    Metatile *copiedMetatile = nullptr;
    QString copiedMetatileLabel;
    bool hasUnsavedChanges;
    Tileset *primaryTileset = nullptr;
    Tileset *secondaryTileset = nullptr;
    QGraphicsScene *metatilesScene = nullptr;
    QGraphicsScene *tilesScene = nullptr;
    QGraphicsScene *selectedTileScene = nullptr;
    QGraphicsPixmapItem *selectedTilePixmapItem = nullptr;
    QGraphicsScene *metatileLayersScene = nullptr;
    bool lockSelection = false;
    QSet<uint16_t> metatileReloadQueue;
    MetatileImageExporter::Settings *metatileImageExportSettings = nullptr;
    QList<QPair<uint16_t,uint16_t>> metatileIdSwaps;
    int numLayerViewRows;

    bool save();

signals:
    void tilesetsSaved(QString, QString);
};

#endif // TILESETEDITOR_H
