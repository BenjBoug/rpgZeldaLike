#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T13:58:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    ChipsetView.cpp \
    MapView.cpp \
    BrushStrategy.cpp \
    PaintPotStratgey.cpp \
    DisplayLowerLayerStrategy.cpp \
    DisplayHigherLayerStrategy.cpp \
    DisplayVisuaLayerStrategy.cpp \
    DisplayCollisionLayerStrategy.cpp \
    GridLayerStratgey.cpp \
    LayerStrategy.cpp \
    PaintStrategy.cpp \
    GroupeCheckBox.cpp \
    BlitCommand.cpp \
    EraseCommand.cpp \
    QGraphicsTileItem.cpp \
    ICommand.cpp \
    PipetteStrategy.cpp \
    CollideCommand.cpp \
    IMouseMove.cpp \
    UndoSingleton.cpp \
    ClearMapCommand.cpp \
    ChangeDimensionCommand.cpp \
    ChangeChipsetCommand.cpp

HEADERS  += MainWindow.h \
    ChipsetView.h \
    MapView.h \
    ICommand.h \
    IStrategy.h \
    BrushStrategy.h \
    PaintPotStratgey.h \
    DisplayLowerLayerStrategy.h \
    DisplayHigherLayerStrategy.h \
    DisplayVisuaLayerStrategy.h \
    DisplayCollisionLayerStrategy.h \
    GridLayerStratgey.h \
    LayerStrategy.h \
    PaintStrategy.h \
    GroupeCheckBox.h \
    BlitCommand.h \
    EraseCommand.h \
    QGraphicsTileItem.h \
    PipetteStrategy.h \
    CollideCommand.h \
    IMouseMove.h \
    UndoSingleton.h \
    ClearMapCommand.h \
    ChangeDimensionCommand.h \
    ChangeChipsetCommand.h

FORMS    += MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Modele/release/ -lZelda_Model
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Modele/debug/ -lZelda_Model
else:unix: LIBS += -L$$OUT_PWD/../Modele/ -lZelda_Model

INCLUDEPATH += $$PWD/../Modele
DEPENDPATH += $$PWD/../Modele

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modele/release/Zelda_Model.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modele/debug/Zelda_Model.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Modele/libZelda_Model.a
