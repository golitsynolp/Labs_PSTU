#include "GraphWidget.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <cmath>
#include <QMouseEvent>

class Arrow : public QGraphicsLineItem {
public:
    Arrow(const QLineF& line, QGraphicsItem* parent = nullptr)
        : QGraphicsLineItem(line, parent) {}

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        QGraphicsLineItem::paint(painter, option, widget);

        QLineF line = this->line();
        double angle = std::atan2(line.dy(), line.dx());
        double arrowSize = 15.0;

        QPointF p1 = line.p1();
        QPointF p2 = line.p2();

        QPointF arrowEnd = p2 - QPointF(std::cos(angle), std::sin(angle)) * 10;
        QPointF arrowBase = arrowEnd - QPointF(std::cos(angle), std::sin(angle)) * arrowSize;

        QPointF leftWing = arrowBase +
            QPointF(std::sin(angle) * arrowSize / 2, -std::cos(angle) * arrowSize / 2);
        QPointF rightWing = arrowBase -
            QPointF(std::sin(angle) * arrowSize / 2, -std::cos(angle) * arrowSize / 2);

        QPolygonF arrowHead;
        arrowHead << arrowEnd << leftWing << rightWing;

        painter->setBrush(Qt::black);
        painter->drawPolygon(arrowHead);
    }
};

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent), graph(nullptr) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    draggingVertex = -1;
    isDragging = false;
}

void GraphWidget::setGraph(Graph* g) {
    graph = g;
    refresh();
}

void GraphWidget::refresh() {
    scene->clear();
    if (!graph) return;
    computeLayout();
    drawGraph();
}

void GraphWidget::redraw() {
    scene->clear();
    if (!graph) return;
    drawGraph();
}

void GraphWidget::computeLayout() {
    int n = graph->getVertexCount();
    if (n == 0) return;
    nodePositions.resize(n);
    double angleStep = 2 * M_PI / n;
    double w = width();
    double h = height();
    if (w <= 0 || h <= 0) {
        w = 800;
        h = 600;
    }
    double radius = std::min(w, h) * 0.35;
    QPointF center(w / 2.0, h / 2.0);
    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        nodePositions[i] = center + QPointF(radius * cos(angle), radius * sin(angle));
    }
}

void GraphWidget::drawGraph() {
    int n = graph->getVertexCount();
    if (n == 0) return;

    // Защита: убедимся, что размер nodePositions совпадает с количеством вершин
    if (nodePositions.size() != n) {
        computeLayout();          // пересчитываем позиции, если размер не совпадает
        if (nodePositions.size() != n) return;  // если всё ещё не совпадает – выходим
    }

    QPen edgePen(Qt::black, 2);
    QPen weightPen(Qt::darkBlue);

    // Рёбра
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph->getEdgeWeight(i, j);
            if (i != j && w != INF) {
                QPointF p1 = nodePositions[i];
                QPointF p2 = nodePositions[j];
                Arrow* arrow = new Arrow(QLineF(p1, p2));
                arrow->setPen(edgePen);
                scene->addItem(arrow);

                QPointF mid = (p1 + p2) / 2;
                QGraphicsTextItem* text = scene->addText(QString::number(w));
                text->setDefaultTextColor(weightPen.color());
                text->setPos(mid);
            }
        }
    }

    // Вершины (нумерация с 1)
    for (int i = 0; i < n; ++i) {
        QPointF pos = nodePositions[i];
        scene->addEllipse(pos.x() - 20, pos.y() - 20, 40, 40, QPen(Qt::black), QBrush(Qt::lightGray));
        QGraphicsTextItem* label = scene->addText(QString::number(i + 1));
        label->setPos(pos.x() - 8, pos.y() - 8);
    }
}

void GraphWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    refresh();
}

void GraphWidget::mousePressEvent(QMouseEvent* event) {
    QPointF scenePos = mapToScene(event->pos());
    for (int i = 0; i < nodePositions.size(); ++i) {
        QPointF vp = nodePositions[i];
        double dx = scenePos.x() - vp.x();
        double dy = scenePos.y() - vp.y();
        if (dx*dx + dy*dy <= 400) {
            draggingVertex = i;
            isDragging = true;
            break;
        }
    }
    if (!isDragging) {
        QGraphicsView::mousePressEvent(event);
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        QPointF newPos = mapToScene(event->pos());
        if (draggingVertex >= 0 && draggingVertex < nodePositions.size()) {
            nodePositions[draggingVertex] = newPos;
            redraw();
        }
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (isDragging) {
        isDragging = false;
        draggingVertex = -1;
        redraw();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
