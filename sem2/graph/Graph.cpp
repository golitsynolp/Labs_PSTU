#include "Graph.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>

Graph::Graph(int vertices) : vertexCount(vertices) {
    adjMatrix.assign(vertexCount, std::vector<int>(vertexCount, INF));
    for (int i = 0; i < vertexCount; ++i) adjMatrix[i][i] = 0;
}

void Graph::addVertex() {
    vertexCount++;
    for (auto& row : adjMatrix) row.push_back(INF);
    adjMatrix.push_back(std::vector<int>(vertexCount, INF));
    adjMatrix.back().back() = 0;
}

void Graph::removeVertex(int v) {
    if (v < 0 || v >= vertexCount) return;
    adjMatrix.erase(adjMatrix.begin() + v);
    for (auto& row : adjMatrix) row.erase(row.begin() + v);
    vertexCount--;
}

void Graph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return;
    adjMatrix[from][to] = weight;
    // если неориентированный граф, раскомментировать:
    // adjMatrix[to][from] = weight;
}

void Graph::removeEdge(int from, int to) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return;
    adjMatrix[from][to] = INF;
    // для неориентированного:
    // adjMatrix[to][from] = INF;
}

void Graph::setEdgeWeight(int from, int to, int weight) {
    addEdge(from, to, weight);
}

int Graph::getEdgeWeight(int from, int to) const {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return INF;
    return adjMatrix[from][to];
}

// BFS
QVector<int> Graph::bfs(int start) const {
    if (start < 0 || start >= vertexCount) return {};
    QVector<bool> visited(vertexCount, false);
    QVector<int> order;
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        for (int u = 0; u < vertexCount; ++u) {
            if (adjMatrix[v][u] != INF && !visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    return order;
}

// DFS (рекурсивный)
void dfsRec(const Graph& g, int v, QVector<bool>& visited, QVector<int>& order) {
    visited[v] = true;
    order.push_back(v);
    for (int u = 0; u < g.getVertexCount(); ++u) {
        if (g.getEdgeWeight(v, u) != INF && !visited[u]) {
            dfsRec(g, u, visited, order);
        }
    }
}

QVector<int> Graph::dfs(int start) const {
    if (start < 0 || start >= vertexCount) return {};
    QVector<bool> visited(vertexCount, false);
    QVector<int> order;
    dfsRec(*this, start, visited, order);
    return order;
}

// Алгоритм Дейкстры
QVector<int> Graph::dijkstra(int start, int end) const {
    if (start < 0 || start >= vertexCount || end < 0 || end >= vertexCount) return {};
    std::vector<int> dist(vertexCount, INF);
    std::vector<int> prev(vertexCount, -1);
    std::vector<bool> used(vertexCount, false);
    dist[start] = 0;

    for (int i = 0; i < vertexCount; ++i) {
        int v = -1;
        for (int j = 0; j < vertexCount; ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) v = j;
        }
        if (dist[v] == INF) break;
        used[v] = true;
        for (int to = 0; to < vertexCount; ++to) {
            if (adjMatrix[v][to] != INF) {
                int nd = dist[v] + adjMatrix[v][to];
                if (nd < dist[to]) {
                    dist[to] = nd;
                    prev[to] = v;
                }
            }
        }
    }

    QVector<int> path;
    for (int v = end; v != -1; v = prev[v]) path.push_front(v);
    if (path.front() != start) return {};
    return path;
}

// Алгоритм Флойда
std::vector<std::vector<int>> Graph::floydWarshall() const {
    int n = vertexCount;
    std::vector<std::vector<int>> dist = adjMatrix;
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    return dist;
}
