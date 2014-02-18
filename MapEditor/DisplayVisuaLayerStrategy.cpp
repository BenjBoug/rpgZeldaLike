#include "DisplayVisuaLayerStrategy.h"

DisplayVisuaLayerStrategy::DisplayVisuaLayerStrategy(MapView *mapView)
{
    this->mapView=mapView;
}

void DisplayVisuaLayerStrategy::execute()
{
    mapView->clear();
    QPixmap chipset = mapView->getChipset();
    Model::Map * map = mapView->getMap();
    int valueMax = (chipset.width()/BLOCSIZE)*(chipset.height()/BLOCSIZE);
    for(int i=0;i<map->getDim().width();i++)
    {
        for(int j=0;j<map->getDim().height();j++)
        {

            QPixmap background = chipset.copy(0,0,BLOCSIZE,BLOCSIZE);
            if (background.width() == BLOCSIZE && background.height() == BLOCSIZE)
            {
                QGraphicsPixmapItem * tileItem = mapView->addPixmap(background);
                tileItem->setPos(i*BLOCSIZE,j*BLOCSIZE);
                tileItem->setZValue(0);
            }

            int couche1 = map->getBloc(i,j)->getCouche1();
            if (couche1!=0 && couche1 < valueMax)
            {
                QPixmap tile = chipset.copy((couche1%(chipset.width()/BLOCSIZE))*BLOCSIZE,(couche1/(chipset.width()/BLOCSIZE))*BLOCSIZE,BLOCSIZE,BLOCSIZE);
                QGraphicsPixmapItem * tileItem = mapView->addPixmap(tile);
                tileItem->setPos(i*BLOCSIZE,j*BLOCSIZE);
                tileItem->setZValue(0);
            }

            int couche2 = map->getBloc(i,j)->getCouche2();
            if (couche2!=0 && couche2 < valueMax)
            {
                QPixmap tile2 = chipset.copy((couche2%(chipset.width()/BLOCSIZE))*BLOCSIZE,(couche2/(chipset.width()/BLOCSIZE))*BLOCSIZE,BLOCSIZE,BLOCSIZE);
                QGraphicsPixmapItem * tileItem = mapView->addPixmap(tile2);
                tileItem->setPos(i*BLOCSIZE,j*BLOCSIZE);
                tileItem->setZValue(100);
            }
        }
    }

    QPen pen;
    pen.setColor(QColor(200,200,200));

    for(int i=0;i<map->getDim().height();i++)
        mapView->addLine(0,i*BLOCSIZE,map->getDim().width()*BLOCSIZE,i*BLOCSIZE,pen)->setZValue(500);


    for(int i=0;i<map->getDim().width();i++)
        mapView->addLine(i*BLOCSIZE,0,i*BLOCSIZE,map->getDim().height()*BLOCSIZE,pen)->setZValue(500);

}
