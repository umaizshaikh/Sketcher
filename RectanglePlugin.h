#ifndef RECTANGLEPLUGIN_H
#define RECTANGLEPLUGIN_H

#include <QObject>
#include "SketcherPluginInterface.h"

class RectanglePlugin : public QObject, public SketcherPluginInterface
{
    Q_OBJECT
        Q_PLUGIN_METADATA(IID "com.yourcompany.SketcherPluginInterface")
        Q_INTERFACES(SketcherPluginInterface)

public:
    void draw(QPainter& painter, const QPoint& start, const QPoint& end) override;
    QString shapeName() const override;
};

#endif // RECTANGLEPLUGIN_H
