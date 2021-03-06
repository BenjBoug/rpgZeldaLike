#include "ChipsetView.h"

ChipsetView::ChipsetView():
    QGraphicsScene()
{
	init();
}

ChipsetView::ChipsetView(QPixmap chipset)
{
	this->chipset=chipset;
	init();
}

ChipsetView::ChipsetView(QString chip) :
    QGraphicsScene()
{
	loadChipset(chip);
    init();
}

void ChipsetView::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	setSelectionArea(QPainterPath());
    selection.setLeft((int)mouseEvent->scenePos().x()/BLOCSIZE*BLOCSIZE);
    selection.setTop((int)mouseEvent->scenePos().y()/BLOCSIZE*BLOCSIZE);
    selection.setWidth(BLOCSIZE);
	selection.setHeight(BLOCSIZE);
	setSelectedTile();
}

void ChipsetView::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
    selection = selectionArea().boundingRect();
    selection.setLeft((int)selection.left()/BLOCSIZE*BLOCSIZE);
    selection.setTop((int)selection.top()/BLOCSIZE*BLOCSIZE);
    selection.setWidth(((int)selection.width()/BLOCSIZE*BLOCSIZE)+BLOCSIZE);
    selection.setHeight(((int)selection.height()/BLOCSIZE*BLOCSIZE)+BLOCSIZE);
    itemRectSelected->setRect(selection);
}

void ChipsetView::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (this->selectionArea() != QPainterPath())
    {
        selection = selectionArea().boundingRect();
        selection.setLeft((int)selection.left()/BLOCSIZE*BLOCSIZE);
        selection.setTop((int)selection.top()/BLOCSIZE*BLOCSIZE);
        selection.setWidth(((int)selection.width()/BLOCSIZE*BLOCSIZE)+BLOCSIZE);
        selection.setHeight(((int)selection.height()/BLOCSIZE*BLOCSIZE)+BLOCSIZE);
        QRectF rectScene = this->sceneRect();
        if (!rectScene.contains(selection)) {
            selection.setLeft(qMin(rectScene.right(), qMax(selection.left(), rectScene.left())));
            selection.setTop(qMin(rectScene.bottom(), qMax(selection.top(), rectScene.top())));
            selection.setRight(qMin(rectScene.right(), qMax(selection.right(), rectScene.left())));
            selection.setBottom(qMin(rectScene.bottom(), qMax(selection.bottom(), rectScene.top())));
        }
        itemRectSelected->setRect(selection);
        this->clearSelection();
    }
    else
    {
        selection.setLeft((int)mouseEvent->scenePos().x()/BLOCSIZE*BLOCSIZE);
        selection.setTop((int)mouseEvent->scenePos().y()/BLOCSIZE*BLOCSIZE);
        selection.setWidth(BLOCSIZE);
        selection.setHeight(BLOCSIZE);
        itemRectSelected->setRect(selection);
    }
    setSelectedTile();
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

QVector<QVector<int> > ChipsetView::getSelectedTile()
{
    return selectedTile;
}

void ChipsetView::selectTile(int t)
{
    selectedTile.resize(1);
    selectedTile[0].resize(1);
    selectedTile[0][0] = t;
    selection.setX((t%(chipset.width()/BLOCSIZE))*BLOCSIZE);
    selection.setY((t/(chipset.width()/BLOCSIZE))*BLOCSIZE);
    selection.setWidth(BLOCSIZE);
    selection.setHeight(BLOCSIZE);
    QList<QGraphicsView*>::iterator it;
    QList<QGraphicsView*> views = this->views();
    for(it=views.begin();it!=views.end();it++)
		(*it)->ensureVisible(selection);
	setSelectedTile();
}

void ChipsetView::init()
{
	QGraphicsPixmapItem * chipsetItem = this->addPixmap(chipset);
	chipsetItem->setZValue(0);
	setSceneRect(chipsetItem->sceneBoundingRect());

    selectedTile.resize(1);
    selectedTile[0].resize(1);
    selectedTile[0][0] = 0;
    selection.setX(0);
    selection.setY(0);
    selection.setWidth(BLOCSIZE);
	selection.setHeight(BLOCSIZE);
	itemRectSelected = this->addRect(selection,QPen(Qt::lightGray, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	itemRectSelected->setZValue(100);
	setSelectedTile();
}

void ChipsetView::loadChipset(QString chip)
{
	chipset.load(chip);
}


void ChipsetView::setChipset(QPixmap chipset)
{
	this->chipset = chipset;
	this->clear();
	init();
}


void ChipsetView::setSelectedTile()
{
	itemRectSelected->setRect(selection);
    selectedTile.clear();
    for(int i=0;i<(selection.right()/BLOCSIZE)-(selection.left()/BLOCSIZE);i++)
    {
        QVector<int> tmp;
        for(int j=0;j<(selection.bottom()/BLOCSIZE)-(selection.top()/BLOCSIZE);j++)
        {
            int bloc = ((selection.left()/BLOCSIZE)+i) + ((selection.top()/BLOCSIZE)+j)*(chipset.width()/BLOCSIZE);
            tmp.push_back(bloc);
        }
        selectedTile.push_back(tmp);
    }
}

