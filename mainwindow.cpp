#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingArea = new DrawingArea(this);
    setCentralWidget(drawingArea);

    toolBar = addToolBar("Toolbar");

    QAction* loadPluginAction = toolBar->addAction("Load Plugin");
    QAction* removePluginAction = toolBar->addAction("Remove Plugin");
    QAction* lineAction = toolBar->addAction("Line");
    QAction* circleAction = toolBar->addAction("Circle");
    QAction* clearAction = toolBar->addAction("Clear");
    QAction* undoAction = toolBar->addAction("Undo");
    QAction* redoAction = toolBar->addAction("Redo");
    QAction* saveAction = toolBar->addAction("Save");
    QAction* openAction = toolBar->addAction("Open");
    QAction* closeSvgAction = toolBar->addAction("Close SVG");

    connect(loadPluginAction, &QAction::triggered, this, &MainWindow::loadPlugin);
    connect(removePluginAction, &QAction::triggered, this, &MainWindow::removePlugin);
    connect(lineAction, &QAction::triggered, this, &MainWindow::setLineMode);
    connect(circleAction, &QAction::triggered, this, &MainWindow::setCircleMode);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearDrawing);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undoAction);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redoAction);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveDrawing);
    connect(openAction, &QAction::triggered, this, &MainWindow::openDrawing);
    connect(closeSvgAction, &QAction::triggered, this, &MainWindow::closeSvg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlugin()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load Plugin", "", "Sketcher Plugins (*.dll *.so)");
    if (filePath.isEmpty()) return;

    QPluginLoader loader(filePath);
    QObject* pluginInstance = loader.instance();

    if (pluginInstance) {
        SketcherPluginInterface* plugin = qobject_cast<SketcherPluginInterface*>(pluginInstance);
        if (plugin) {
            loadedPlugins.append(plugin);
            QAction* newAction = toolBar->addAction(plugin->shapeName());

            connect(newAction, &QAction::triggered, [this, plugin]() {
                drawingArea->setActivePlugin(plugin);
                qDebug() << "Active Plugin: " << plugin->shapeName();
                });
        }
        else {
            QMessageBox::warning(this, "Plugin Error", "Invalid plugin.");
            loader.unload();
        }
    }
    else {
        QMessageBox::warning(this, "Plugin Error", "Failed to load plugin.");
    }
}

void MainWindow::removePlugin()
{
    drawingArea->setActivePlugin(nullptr);

    for (QAction* action : toolBar->actions()) {
        if (action->text() == "Rectangle") {
            toolBar->removeAction(action);
            delete action;
            break;
        }
    }

    qDebug() << "Plugin removed.";
}

void MainWindow::closeSvg()
{
    drawingArea->closeSvg();
    qDebug() << "SVG file closed.";
}

void MainWindow::setLineMode()
{
    drawingArea->setDrawingMode(1);
}

void MainWindow::setCircleMode()
{
    drawingArea->setDrawingMode(2);
}

void MainWindow::clearDrawing()
{
    drawingArea->clearCanvas();
}

void MainWindow::undoAction()
{
    drawingArea->undo();
}

void MainWindow::redoAction()
{
    drawingArea->redo();
}

void MainWindow::saveDrawing()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Drawing", "", "SVG Files (*.svg)");
    if (!filePath.isEmpty()) {
        drawingArea->saveAsSvg(filePath);
    }
}

void MainWindow::openDrawing()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Drawing", "", "SVG Files (*.svg)");
    if (filePath.isEmpty()) return;

    drawingArea->clearCanvas();
    drawingArea->openSvg(filePath);
}

