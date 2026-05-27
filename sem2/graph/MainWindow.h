#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Graph.h"

class GraphWidget;
class QTableWidget;
class QTextEdit;
class QLineEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onChangeWeight();
    void onBFS();
    void onDFS();
    void onDijkstra();
    void onFloyd();
    void onUpdateMatrix(int row, int col);
    void onResetGraph();

private:
    Graph graph;
    GraphWidget* graphWidget;
    QTableWidget* matrixTable;
    QTextEdit* outputEdit;
    QLineEdit* startEdit;
    QLineEdit* endEdit;

    void updateMatrixTable();
    void showResult(const QString& text);
    int getStartVertex() const;
    int getEndVertex() const;
};

#endif // MAINWINDOW_H
