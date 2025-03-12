#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QFileDialog>
#include <QPluginLoader>
#include "DrawingArea.h"
#include "SketcherPluginInterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void setLineMode();
    void setCircleMode();
    void clearDrawing();
    void undoAction();
    void redoAction();
    void saveDrawing();
    void openDrawing();
    void loadPlugin();
    void removePlugin();
    void closeSvg();

private:
    Ui::MainWindow* ui;
    DrawingArea* drawingArea;
    QToolBar* toolBar;
    QList<SketcherPluginInterface*> loadedPlugins;
};

#endif // MAINWINDOW_H
