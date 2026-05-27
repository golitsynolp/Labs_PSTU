#ifndef GRAPH_H
#define GRAPH_H
#include <limits>
#include <vector>
#include <QString>
#include <QVector>
const int INF = std::numeric_limits<int>::max() / 2;

struct Edge {
    int from;
    int to;
    int weight;
};

class Graph {
private:
    int vertexCount;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int vertices = 0);
    void addVertex();
    void removeVertex(int v);
    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void setEdgeWeight(int from, int to, int weight);
    int getEdgeWeight(int from, int to) const;
    int getVertexCount() const { return vertexCount; }
    const std::vector<std::vector<int>>& getAdjMatrix() const { return adjMatrix; }

    QVector<int> bfs(int start) const;
    QVector<int> dfs(int start) const;
    QVector<int> dijkstra(int start, int end) const;
    std::vector<std::vector<int>> floydWarshall() const;
};

#endif // GRAPH_H
