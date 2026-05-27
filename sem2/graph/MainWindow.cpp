#include "MainWindow.h"
#include "GraphWidget.h"
#include "AddEdgeDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <exception>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), graph(0) {
    QWidget* central = new QWidget;
    setCentralWidget(central);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    graphWidget = new GraphWidget;
    graphWidget->setMinimumHeight(400);
    graphWidget->setGraph(&graph);
    mainLayout->addWidget(graphWidget);

    QHBoxLayout* controlLayout = new QHBoxLayout;
    QPushButton* addVertexBtn = new QPushButton("Добавить вершину");
    QPushButton* removeVertexBtn = new QPushButton("Удалить вершину");
    QPushButton* addEdgeBtn = new QPushButton("Добавить ребро");
    QPushButton* removeEdgeBtn = new QPushButton("Удалить ребро");
    QPushButton* changeWeightBtn = new QPushButton("Изменить вес");
    QPushButton* resetBtn = new QPushButton("Сбросить граф");
    controlLayout->addWidget(addVertexBtn);
    controlLayout->addWidget(removeVertexBtn);
    controlLayout->addWidget(addEdgeBtn);
    controlLayout->addWidget(removeEdgeBtn);
    controlLayout->addWidget(changeWeightBtn);
    controlLayout->addWidget(resetBtn);
    mainLayout->addLayout(controlLayout);

    connect(addVertexBtn, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(removeVertexBtn, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(addEdgeBtn, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(removeEdgeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(changeWeightBtn, &QPushButton::clicked, this, &MainWindow::onChangeWeight);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::onResetGraph);

    matrixTable = new QTableWidget;
    matrixTable->setMinimumHeight(200);
    mainLayout->addWidget(matrixTable);

    QHBoxLayout* algoLayout = new QHBoxLayout;
    QPushButton* bfsBtn = new QPushButton("BFS");
    QPushButton* dfsBtn = new QPushButton("DFS");
    QPushButton* dijkstraBtn = new QPushButton("Дейкстра");
    QPushButton* floydBtn = new QPushButton("Флойд");
    QLabel* startLabel = new QLabel("Старт:");
    startEdit = new QLineEdit;
    startEdit->setFixedWidth(50);
    QLabel* endLabel = new QLabel("Конец:");
    endEdit = new QLineEdit;
    endEdit->setFixedWidth(50);
    algoLayout->addWidget(bfsBtn);
    algoLayout->addWidget(dfsBtn);
    algoLayout->addWidget(dijkstraBtn);
    algoLayout->addWidget(floydBtn);
    algoLayout->addWidget(startLabel);
    algoLayout->addWidget(startEdit);
    algoLayout->addWidget(endLabel);
    algoLayout->addWidget(endEdit);
    mainLayout->addLayout(algoLayout);

    connect(bfsBtn, &QPushButton::clicked, this, &MainWindow::onBFS);
    connect(dfsBtn, &QPushButton::clicked, this, &MainWindow::onDFS);
    connect(dijkstraBtn, &QPushButton::clicked, this, &MainWindow::onDijkstra);
    connect(floydBtn, &QPushButton::clicked, this, &MainWindow::onFloyd);

    outputEdit = new QTextEdit;
    outputEdit->setReadOnly(true);
    mainLayout->addWidget(outputEdit);

    updateMatrixTable();
    setWindowTitle("Графы - обходы, Дейкстра, Флойд");
    resize(900, 700);
}

MainWindow::~MainWindow() {}

void MainWindow::updateMatrixTable() {
    int n = graph.getVertexCount();
    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);
    QStringList headers;
    for (int i = 0; i < n; ++i) headers << QString::number(i + 1);
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph.getEdgeWeight(i, j);
            QTableWidgetItem* item = new QTableWidgetItem;
            if (w == INF) item->setText("∞");
            else item->setText(QString::number(w));
            matrixTable->setItem(i, j, item);
        }
    }
    disconnect(matrixTable, &QTableWidget::cellChanged, this, &MainWindow::onUpdateMatrix);
    connect(matrixTable, &QTableWidget::cellChanged, this, &MainWindow::onUpdateMatrix);
}

void MainWindow::onUpdateMatrix(int row, int col) {
    QTableWidgetItem* item = matrixTable->item(row, col);
    if (!item) return;
    QString text = item->text();
    if (text == "∞") graph.setEdgeWeight(row, col, INF);
    else {
        bool ok;
        int w = text.toInt(&ok);
        if (ok) graph.setEdgeWeight(row, col, w);
        else item->setText("∞");
    }
    graphWidget->redraw();
}

void MainWindow::showResult(const QString& text) {
    outputEdit->append(text);
}

int MainWindow::getStartVertex() const {
    return startEdit->text().toInt();
}

int MainWindow::getEndVertex() const {
    return endEdit->text().toInt();
}

void MainWindow::onAddVertex() {
    try {
        graph.addVertex();
        updateMatrixTable();
        graphWidget->refresh();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при добавлении вершины: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при добавлении вершины");
    }
}

void MainWindow::onRemoveVertex() {
    int v = getStartVertex();
    if (v < 1 || v > graph.getVertexCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер вершины");
        return;
    }
    try {
        graph.removeVertex(v - 1);
        updateMatrixTable();
        graphWidget->refresh();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при удалении вершины: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при удалении вершины");
    }
}

void MainWindow::onAddEdge() {
    if (graph.getVertexCount() == 0) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте вершины");
        return;
    }
    AddEdgeDialog dlg(graph.getVertexCount(), this);
    if (dlg.exec() == QDialog::Accepted) {
        try {
            int from = dlg.getFrom();
            int to = dlg.getTo();
            int weight = dlg.getWeight();
            graph.addEdge(from, to, weight);
            updateMatrixTable();
            graphWidget->refresh();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", QString("Ошибка при добавлении ребра: %1").arg(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при добавлении ребра");
        }
    }
}

void MainWindow::onRemoveEdge() {
    if (graph.getVertexCount() == 0) return;
    AddEdgeDialog dlg(graph.getVertexCount(), this);
    dlg.setWindowTitle("Удалить ребро");
    if (dlg.exec() == QDialog::Accepted) {
        try {
            int from = dlg.getFrom();
            int to = dlg.getTo();
            graph.removeEdge(from, to);
            updateMatrixTable();
            graphWidget->refresh();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", QString("Ошибка при удалении ребра: %1").arg(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при удалении ребра");
        }
    }
}

void MainWindow::onChangeWeight() {
    onAddEdge();
}

void MainWindow::onResetGraph() {
    try {
        graph = Graph(0);
        updateMatrixTable();
        graphWidget->refresh();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при сбросе графа: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при сбросе графа");
    }
}

void MainWindow::onBFS() {
    int start = getStartVertex();
    if (start < 1 || start > graph.getVertexCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверная стартовая вершина");
        return;
    }
    try {
        int startIdx = start - 1;
        QVector<int> order = graph.bfs(startIdx);
        QStringList str;
        for (int v : order) str << QString::number(v + 1);
        showResult("BFS (с вершины " + QString::number(start) + "): " + str.join(" → "));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при BFS: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при BFS");
    }
}

void MainWindow::onDFS() {
    int start = getStartVertex();
    if (start < 1 || start > graph.getVertexCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверная стартовая вершина");
        return;
    }
    try {
        int startIdx = start - 1;
        QVector<int> order = graph.dfs(startIdx);
        QStringList str;
        for (int v : order) str << QString::number(v + 1);
        showResult("DFS (с вершины " + QString::number(start) + "): " + str.join(" → "));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при DFS: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при DFS");
    }
}

void MainWindow::onDijkstra() {
    int start = getStartVertex();
    int end = getEndVertex();
    if (start < 1 || start > graph.getVertexCount() || end < 1 || end > graph.getVertexCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверные номера вершин");
        return;
    }
    try {
        int startIdx = start - 1;
        int endIdx = end - 1;
        QVector<int> path = graph.dijkstra(startIdx, endIdx);
        if (path.isEmpty()) {
            showResult("Нет пути от " + QString::number(start) + " к " + QString::number(end));
        } else {
            QStringList str;
            for (int v : path) str << QString::number(v + 1);
            showResult("Кратчайший путь (Дейкстра): " + str.join(" → "));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при Дейкстре: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при Дейкстре");
    }
}

void MainWindow::onFloyd() {
    try {
        auto dist = graph.floydWarshall();
        QString result = "Матрица кратчайших расстояний:\n";
        int n = dist.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] >= INF) result += "∞ ";
                else result += QString::number(dist[i][j]) + " ";
            }
            result += "\n";
        }
        showResult(result);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при Флойде: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при Флойде");
    }
}
