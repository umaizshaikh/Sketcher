#include "RectanglePlugin.h"
#include <QPainter>

void RectanglePlugin::draw(QPainter& painter, const QPoint& start, const QPoint& end)
{
    painter.setPen(Qt::black);
    painter.drawRect(QRect(start, end));
}

QString RectanglePlugin::shapeName() const
{
    return "Rectangle";
}
