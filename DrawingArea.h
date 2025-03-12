#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStack>
#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QDomDocument>
#include "SketcherPluginInterface.h"

struct Shape {
    int type;
    QPoint p1, p2;
};

class DrawingArea : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingArea(QWidget* parent = nullptr);
    ~DrawingArea();

    void clearCanvas();
    void setDrawingMode(int mode);
    void undo();
    void redo();
    void saveAsSvg(const QString& filePath);
    void openSvg(const QString& filePath);
    void closeSvg();
    void setActivePlugin(SketcherPluginInterface* plugin);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void redrawCanvas();

    enum ShapeMode { NONE, LINE, CIRCLE, PLUGIN };
    ShapeMode currentMode = NONE;

    QPoint startPoint, endPoint;
    QStack<Shape> undoStack;
    QStack<Shape> redoStack;
    QSvgRenderer* svgRenderer = nullptr;
    QDomDocument svgDocument;
    bool isSvgOpen = false;

    SketcherPluginInterface* activePlugin = nullptr;
};

#endif // DRAWINGAREA_H

