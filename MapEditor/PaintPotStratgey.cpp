#include "PaintPotStratgey.h"

PaintPotStrategy::PaintPotStrategy(MapView * mapView, ChipsetView * chipsetView)
    : PaintStrategy(mapView,chipsetView)
{
    this->mapView=mapView;
    this->chipsetView=chipsetView;
}

void PaintPotStrategy::leftButtonPressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int blocRef = mapView->getMap()->getBloc(mouseEvent->scenePos().x()/BLOCSIZE,mouseEvent->scenePos().y()/BLOCSIZE)->getLayer(mapView->getCurrentLayer()->getLayer());
    paintPot(mouseEvent->scenePos().x()/BLOCSIZE,mouseEvent->scenePos().y()/BLOCSIZE,blocRef);
}

void PaintPotStrategy::rightButtonPressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int blocRef = mapView->getMap()->getBloc(mouseEvent->scenePos().x()/BLOCSIZE,mouseEvent->scenePos().y()/BLOCSIZE)->getLayer(mapView->getCurrentLayer()->getLayer());
    erase(mouseEvent->scenePos().x()/BLOCSIZE,mouseEvent->scenePos().y()/BLOCSIZE,blocRef);
}

void PaintPotStrategy::paintPot(int i, int j, int blocRef)
{
    if (mapView->getMap()->getBloc(i,j)->getLayer(mapView->getCurrentLayer()->getLayer())==blocRef)
    {
        QVector<QVector<int> > selectedTile = chipsetView->getSelectedTile();

        for(int x=0;x<selectedTile.size();x++)
        {
            for(int y=0;y<selectedTile[x].size();y++)
            {
                UndoSingleton::getInstance()->execute(new BlitCommand(mapView,i+x,j+y,selectedTile[x][y]));
            }
        }

        if (i-selectedTile.size()>=0)
            paintPot(i-selectedTile.size(),j,blocRef);
        if (i+selectedTile.size()<mapView->getMap()->getDim().width())
            paintPot(i+selectedTile.size(),j,blocRef);
        if (j-selectedTile[0].size()>=0)
            paintPot(i,j-selectedTile[0].size(),blocRef);
        if (j+selectedTile[0].size()<mapView->getMap()->getDim().height())
            paintPot(i,j+selectedTile[0].size(),blocRef);
    }
}

void PaintPotStrategy::erase(int i, int j, int blocRef)
{
    if (mapView->getMap()->getBloc(i,j)->getLayer(mapView->getCurrentLayer()->getLayer())==blocRef)
    {
        UndoSingleton::getInstance()->execute(new EraseCommand(mapView,i,j));

        if (i-1>=0)
            erase(i-1,j,blocRef);
        if (i+1<mapView->getMap()->getDim().width())
            erase(i+1,j,blocRef);
        if (j-1>=0)
            erase(i,j-1,blocRef);
        if (j+1<mapView->getMap()->getDim().height())
            erase(i,j+1,blocRef);
    }
}
