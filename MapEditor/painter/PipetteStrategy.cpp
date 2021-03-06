#include "PipetteStrategy.h"

PipetteStrategy::PipetteStrategy(MapView * mapView, ChipsetView * chipsetView)
    : PaintStrategy(mapView,chipsetView)
{
}

void PipetteStrategy::leftButtonPressEvent(int i, int j)
{
	chipsetView->selectTile(mapView->getMap()->getBloc(i,j)->getAtLayer(mapView->getCurrentLayer()));
}

void PipetteStrategy::leftButtonMoveEvent(int i, int j)
{
	chipsetView->selectTile(mapView->getMap()->getBloc(i,j)->getAtLayer(mapView->getCurrentLayer()));
}
