#ifndef SKETCHERPLUGININTERFACE_H
#define SKETCHERPLUGININTERFACE_H

#include <QObject>
#include <QPoint>
#include <QPainter>

class SketcherPluginInterface
{
public:
    virtual ~SketcherPluginInterface() = default;

    // Function to draw a shape
    virtual void draw(QPainter& painter, const QPoint& start, const QPoint& end) = 0;

    // Function to return shape name
    virtual QString shapeName() const = 0;
};

#define SketcherPluginInterface_iid "com.sketcher.plugin"
Q_DECLARE_INTERFACE(SketcherPluginInterface, SketcherPluginInterface_iid)

#endif // SKETCHERPLUGININTERFACE_H
