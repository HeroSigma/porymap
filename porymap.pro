#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T15:19:13
#
#-------------------------------------------------

QT       += core gui

qtHaveModule(charts) {
    QT += charts
} else {
    warning("Qt module 'charts' not found, disabling chart features.")
}
qtHaveModule(qml) {
    QT += qml
} else {
    warning("Qt module 'qml' not found, disabling plug-in features.")
}
qtHaveModule(network) {
    QT += network
} else {
    warning("Qt module 'network' not found, disabling network features.")
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = porymap
TEMPLATE = app
RC_ICONS = resources/icons/porymap-icon-2.ico
ICON = resources/icons/porymap.icns
QMAKE_CXXFLAGS += -std=c++17 -Wall
QMAKE_TARGET_BUNDLE_PREFIX = com.pret

# Get latest commit hash if we can (to display alongside version information).
win32 {
    LATEST_COMMIT = $$system(git rev-parse --short HEAD 2> nul)
} else {
    LATEST_COMMIT = $$system(git rev-parse --short HEAD 2>/dev/null)
}

DEFINES += PORYMAP_LATEST_COMMIT=\\\"$$LATEST_COMMIT\\\"

VERSION = 6.2.0
DEFINES += PORYMAP_VERSION=\\\"$$VERSION\\\"

SOURCES += src/core/advancemapparser.cpp \
    src/importers/Am95Importer.cpp \
    src/core/block.cpp \
    src/ui/resizelayoutpopup.cpp \
    src/core/bitpacker.cpp \
    src/core/blockdata.cpp \
    src/core/events.cpp \
    src/core/filedialog.cpp \
    src/core/imageexport.cpp \
    src/core/map.cpp \
    src/core/mapconnection.cpp \
    src/core/mapheader.cpp \
    src/core/maplayout.cpp \
    src/core/metatile.cpp \
    src/core/network.cpp \
    src/core/paletteutil.cpp \
    src/core/parseutil.cpp \
    src/core/tile.cpp \
    src/core/tileset.cpp \
    src/core/utility.cpp \
    src/core/validator.cpp \
    src/core/regionmap.cpp \
    src/core/wildmoninfo.cpp \
    src/core/editcommands.cpp \
    src/lib/fex/lexer.cpp \
    src/lib/fex/parser.cpp \
    src/lib/collapsiblesection.cpp \
    src/lib/orderedjson.cpp \
    src/core/regionmapeditcommands.cpp \
    src/scriptapi/apimap.cpp \
    src/scriptapi/apioverlay.cpp \
    src/scriptapi/apiutility.cpp \
    src/scriptapi/scripting.cpp \
    src/ui/aboutporymap.cpp \
    src/ui/checkeredbgscene.cpp \
    src/ui/colorinputwidget.cpp \
    src/ui/connectionslistitem.cpp \
    src/ui/customattributesdialog.cpp \
    src/ui/customattributestable.cpp \
    src/ui/customscriptseditor.cpp \
    src/ui/customscriptslistitem.cpp \
    src/ui/divingmappixmapitem.cpp \
    src/ui/eventpixmapitem.cpp \
    src/ui/bordermetatilespixmapitem.cpp \
    src/ui/collisionpixmapitem.cpp \
    src/ui/connectionpixmapitem.cpp \
    src/ui/currentselectedmetatilespixmapitem.cpp \
    src/ui/gridsettings.cpp \
    src/ui/newmapconnectiondialog.cpp \
    src/ui/overlay.cpp \
    src/ui/prefab.cpp \
    src/ui/projectsettingseditor.cpp \
    src/ui/regionmaplayoutpixmapitem.cpp \
    src/ui/regionmapentriespixmapitem.cpp \
    src/ui/cursortilerect.cpp \
    src/ui/customattributesframe.cpp \
    src/ui/eventframes.cpp \
    src/ui/eventfilters.cpp \
    src/ui/filterchildrenproxymodel.cpp \
    src/ui/maplistmodels.cpp \
    src/ui/maplisttoolbar.cpp \
    src/ui/message.cpp \
    src/ui/graphicsview.cpp \
    src/ui/imageproviders.cpp \
    src/ui/layoutpixmapitem.cpp \
    src/ui/prefabcreationdialog.cpp \
    src/ui/regionmappixmapitem.cpp \
    src/ui/citymappixmapitem.cpp \
    src/ui/mapheaderform.cpp \
    src/ui/metatilelayersitem.cpp \
    src/ui/metatileselector.cpp \
    src/ui/movablerect.cpp \
    src/ui/movementpermissionsselector.cpp \
    src/ui/newdefinedialog.cpp \
    src/ui/neweventtoolbutton.cpp \
    src/ui/newlayoutdialog.cpp \
    src/ui/newlayoutform.cpp \
    src/ui/newlocationdialog.cpp \
    src/ui/newmapgroupdialog.cpp \
    src/ui/noscrollcombobox.cpp \
    src/ui/noscrollspinbox.cpp \
    src/ui/montabwidget.cpp \
    src/ui/encountertablemodel.cpp \
    src/ui/encountertabledelegates.cpp \
    src/ui/palettecolorsearch.cpp \
    src/ui/paletteeditor.cpp \
    src/ui/selectablepixmapitem.cpp \
    src/ui/tileseteditor.cpp \
    src/ui/tileseteditormetatileselector.cpp \
    src/ui/tileseteditortileselector.cpp \
    src/ui/tilemaptileselector.cpp \
    src/ui/regionmapeditor.cpp \
    src/ui/newmapdialog.cpp \
    src/ui/mapimageexporter.cpp \
    src/ui/metatileimageexporter.cpp \
    src/ui/newtilesetdialog.cpp \
    src/ui/flowlayout.cpp \
    src/ui/mapruler.cpp \
    src/ui/shortcut.cpp \
    src/ui/shortcutseditor.cpp \
    src/ui/multikeyedit.cpp \
    src/ui/prefabframe.cpp \
    src/ui/preferenceeditor.cpp \
    src/ui/regionmappropertiesdialog.cpp \
    src/ui/colorpicker.cpp \
    src/ui/loadingscreen.cpp \
    src/config.cpp \
    src/editor.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/project.cpp \
    src/settings.cpp \
    src/log.cpp \
    src/ui/uintspinbox.cpp \
    src/ui/updatepromoter.cpp \
    src/ui/wildmonchart.cpp \
    src/ui/wildmonsearch.cpp

HEADERS  += include/core/advancemapparser.h \
    src/importers/Am95Importer.h \
    include/core/block.h \
    include/core/bitpacker.h \
    include/core/blockdata.h \
    include/core/events.h \
    include/core/filedialog.h \
    include/core/history.h \
    include/core/imageexport.h \
    include/core/map.h \
    include/core/mapconnection.h \
    include/core/mapheader.h \
    include/core/maplayout.h \
    include/core/metatile.h \
    include/core/network.h \
    include/core/paletteutil.h \
    include/core/parseutil.h \
    include/core/tile.h \
    include/core/tileset.h \
    include/core/utility.h \
    include/core/validator.h \
    include/core/regionmap.h \
    include/core/wildmoninfo.h \
    include/core/editcommands.h \
    include/core/regionmapeditcommands.h \
    include/lib/fex/array.h \
    include/lib/fex/array_value.h \
    include/lib/fex/define_statement.h \
    include/lib/fex/lexer.h \
    include/lib/fex/parser.h \
    include/lib/collapsiblesection.h \
    include/lib/orderedmap.h \
    include/lib/orderedjson.h \
    include/ui/aboutporymap.h \
    include/ui/checkeredbgscene.h \
    include/ui/connectionslistitem.h \
    include/ui/customattributesdialog.h \
    include/ui/customattributestable.h \
    include/ui/customscriptseditor.h \
    include/ui/customscriptslistitem.h \
    include/ui/divingmappixmapitem.h \
    include/ui/eventpixmapitem.h \
    include/ui/bordermetatilespixmapitem.h \
    include/ui/collisionpixmapitem.h \
    include/ui/connectionpixmapitem.h \
    include/ui/currentselectedmetatilespixmapitem.h \
    include/ui/gridsettings.h \
    include/ui/mapheaderform.h \
    include/ui/newmapconnectiondialog.h \
    include/ui/prefabframe.h \
    include/ui/projectsettingseditor.h \
    include/ui/regionmaplayoutpixmapitem.h \
    include/ui/regionmapentriespixmapitem.h \
    include/ui/cursortilerect.h \
    include/ui/customattributesframe.h \
    include/ui/eventframes.h \
    include/ui/eventfilters.h \
    include/ui/filterchildrenproxymodel.h \
    include/ui/maplistmodels.h \
    include/ui/maplisttoolbar.h \
    include/ui/message.h \
    include/ui/graphicsview.h \
    include/ui/imageproviders.h \
    include/ui/layoutpixmapitem.h \
    include/ui/mapview.h \
    include/ui/prefabcreationdialog.h \
    include/ui/regionmappixmapitem.h \
    include/ui/citymappixmapitem.h \
    include/ui/colorinputwidget.h \
    include/ui/metatilelayersitem.h \
    include/ui/metatileselector.h \
    include/ui/movablerect.h \
    include/ui/movementpermissionsselector.h \
    include/ui/newdefinedialog.h \
    include/ui/neweventtoolbutton.h \
    include/ui/newlayoutdialog.h \
    include/ui/newlayoutform.h \
    include/ui/newlocationdialog.h \
    include/ui/newmapgroupdialog.h \
    include/ui/noscrollcombobox.h \
    include/ui/noscrollspinbox.h \
    include/ui/noscrolltextedit.h \
    include/ui/montabwidget.h \
    include/ui/encountertablemodel.h \
    include/ui/encountertabledelegates.h \
    include/ui/adjustingstackedwidget.h \
    include/ui/palettecolorsearch.h \
    include/ui/paletteeditor.h \
    include/ui/selectablepixmapitem.h \
    include/ui/tileseteditor.h \
    include/ui/tileseteditormetatileselector.h \
    include/ui/tileseteditortileselector.h \
    include/ui/tilemaptileselector.h \
    include/ui/regionmapeditor.h \
    include/ui/newmapdialog.h \
    include/ui/mapimageexporter.h \
    include/ui/metatileimageexporter.h \
    include/ui/newtilesetdialog.h \
    include/ui/overlay.h \
    include/ui/flowlayout.h \
    include/ui/mapruler.h \
    include/ui/shortcut.h \
    include/ui/shortcutseditor.h \
    include/ui/multikeyedit.h \
    include/ui/prefab.h \
    include/ui/preferenceeditor.h \
    include/ui/regionmappropertiesdialog.h \
    include/ui/colorpicker.h \
    include/ui/loadingscreen.h \
    include/config.h \
    include/editor.h \
    include/mainwindow.h \
    include/project.h \
    include/scripting.h \
    include/scriptutility.h \
    include/settings.h \
    include/log.h \
    include/ui/uintspinbox.h \
    include/ui/updatepromoter.h \
    include/ui/wildmonchart.h \
    include/ui/wildmonsearch.h \
    include/ui/resizelayoutpopup.h

FORMS    += forms/mainwindow.ui \
    forms/colorinputwidget.ui \
    forms/connectionslistitem.ui \
    forms/customattributesframe.ui \
    forms/gridsettingsdialog.ui \
    forms/loadingscreen.ui \
    forms/mapheaderform.ui \
    forms/maplisttoolbar.ui \
    forms/newdefinedialog.ui \
    forms/newlayoutdialog.ui \
    forms/newlayoutform.ui \
    forms/newlocationdialog.ui \
    forms/newmapconnectiondialog.ui \
    forms/newmapgroupdialog.ui \
    forms/prefabcreationdialog.ui \
    forms/prefabframe.ui \
    forms/tileseteditor.ui \
    forms/palettecolorsearch.ui \
    forms/paletteeditor.ui \
    forms/regionmapeditor.ui \
    forms/newmapdialog.ui \
    forms/aboutporymap.ui \
    forms/newtilesetdialog.ui \
    forms/mapimageexporter.ui \
    forms/metatileimageexporter.ui \
    forms/shortcutseditor.ui \
    forms/preferenceeditor.ui \
    forms/regionmappropertiesdialog.ui \
    forms/colorpicker.ui \
    forms/projectsettingseditor.ui \
    forms/customscriptseditor.ui \
    forms/customscriptslistitem.ui \
    forms/customattributesdialog.ui \
    forms/updatepromoter.ui \
    forms/wildmonchart.ui \
    forms/wildmonsearch.ui \
    forms/resizelayoutpopup.ui

RESOURCES += \
    resources/images.qrc \
    resources/themes.qrc \
    resources/text.qrc

INCLUDEPATH += include
INCLUDEPATH += include/core
INCLUDEPATH += include/ui
INCLUDEPATH += include/lib
INCLUDEPATH += forms
INCLUDEPATH += src

include(src/vendor/QtGifImage/gifimage/qtgifimage.pri)
