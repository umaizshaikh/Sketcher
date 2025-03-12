#include "DrawingArea.h"
#include <QFile>
#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QPainter>
#include <QDebug>

DrawingArea::DrawingArea(QWidget* parent) : QWidget(parent)
{
    setStyleSheet("background-color: white;");
}

DrawingArea::~DrawingArea()
{
    delete svgRenderer;
}

void DrawingArea::setDrawingMode(int mode)
{
    currentMode = static_cast<ShapeMode>(mode);
    activePlugin = nullptr;
}

void DrawingArea::setActivePlugin(SketcherPluginInterface* plugin)
{
    activePlugin = plugin;
    currentMode = PLUGIN;
}

void DrawingArea::clearCanvas()
{
    if (!undoStack.isEmpty()) {
        undoStack.push({ -1, QPoint(), QPoint() });
    }
    redoStack.clear();
    undoStack.clear();
    update();
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);

    if (svgRenderer && svgRenderer->isValid()) {
        svgRenderer->render(&painter);
    }
    else {
        for (const auto& shape : undoStack) {
            if (shape.type == 1) {
                painter.drawLine(shape.p1, shape.p2);
            }
            else if (shape.type == 2) {
                int radius = qSqrt(qPow(shape.p2.x() - shape.p1.x(), 2) +
                    qPow(shape.p2.y() - shape.p1.y(), 2));
                painter.drawEllipse(shape.p1, radius, radius);
            }
            else if (shape.type == 3) {
                painter.drawRect(QRect(shape.p1, shape.p2));
            }
        }
    }
}

void DrawingArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        Shape shape;
        shape.p1 = startPoint;
        shape.p2 = endPoint;

        if (activePlugin) {
            shape.type = 3;
        }
        else if (currentMode == LINE) {
            shape.type = 1;
        }
        else if (currentMode == CIRCLE) {
            shape.type = 2;
        }

        if (shape.type != 0) {
            undoStack.push(shape);
            redoStack.clear();
        }

        update();
    }
}

void DrawingArea::undo()
{
    if (!undoStack.isEmpty()) {
        redoStack.push(undoStack.pop());
        redrawCanvas();
    }
}

void DrawingArea::redo()
{
    if (!redoStack.isEmpty()) {
        undoStack.push(redoStack.pop());
        redrawCanvas();
    }
}

void DrawingArea::redrawCanvas()
{
    update();
}

void DrawingArea::saveAsSvg(const QString& filePath)
{
    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(size());
    generator.setViewBox(QRect(0, 0, width(), height()));

    QPainter painter(&generator);
    painter.setPen(Qt::black);

    for (const auto& shape : undoStack) {
        if (shape.type == 1) {
            painter.drawLine(shape.p1, shape.p2);
        }
        else if (shape.type == 2) {
            int radius = qSqrt(qPow(shape.p2.x() - shape.p1.x(), 2) +
                qPow(shape.p2.y() - shape.p1.y(), 2));
            painter.drawEllipse(shape.p1, radius, radius);
        }
        else if (shape.type == 3) {
            painter.drawRect(QRect(shape.p1, shape.p2));
        }
    }
}

void DrawingArea::openSvg(const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists()) {
        qWarning("SVG file does not exist: %s", qPrintable(filePath));
        return;
    }

    if (svgRenderer) {
        delete svgRenderer;
        svgRenderer = nullptr;
    }

    svgRenderer = new QSvgRenderer(filePath, this);
    if (!svgRenderer->isValid()) {
        qWarning("Failed to load SVG file.");
        delete svgRenderer;
        svgRenderer = nullptr;
        return;
    }

    undoStack.clear();
    redoStack.clear();
    this->resize(svgRenderer->viewBox().size());
    update();
}

void DrawingArea::closeSvg()
{
    if (svgRenderer) {
        delete svgRenderer;
        svgRenderer = nullptr;
    }
    undoStack.clear();
    redoStack.clear();
    update();
}
