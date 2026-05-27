#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "Graph.h"

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setGraph(Graph* g);
    void refresh();
    void redraw();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Graph* graph;
    QGraphicsScene* scene;
    QVector<QPointF> nodePositions;
    int draggingVertex;
    bool isDragging;

    void computeLayout();
    void drawGraph();
};

#endif // GRAPHWIDGET_H
