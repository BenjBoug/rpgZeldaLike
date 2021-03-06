#ifndef IGUI_H
#define IGUI_H

#include <QString>
#include <QPoint>
#include <QRect>
#include <QPixmap>

namespace Model
{
class IGui
{
public:
    virtual void init() = 0;
    virtual void clearScreen() = 0;
    virtual void display() = 0;
	virtual void draw(QPixmap chipset,QPoint position, QRect rect) = 0;
    virtual void quit() = 0;

};
}

#endif // IGUI_H
