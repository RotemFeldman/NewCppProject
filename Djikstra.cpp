#include "Dijkstra.h"
#include <unordered_map>
#include <queue>
#include <stack>

void Dijkstra::search(const vector<Node*>& nodes, const string& startId, const string& endId)
{
    unordered_map<string, double> distances;
    unordered_map<string, Node*> previous;

    Node* startNode = nullptr;
    Node* endNode = nullptr;

    // initialize distances and find start and end nodes
    for (Node* node : nodes) {
        distances[node->id] = numeric_limits<double>::infinity();
        if (node->id == startId) startNode = node;
        if (node->id == endId) endNode = node;
    }

    if (!startNode) {
        cout << "Start node with ID " << startId << " does not exist." << endl;
        return;
    }

    if (!endNode) {
        cout << "End node with ID " << endId << " does not exist." << endl;
        return;
    }

    distances[startId] = 0;

    //priority queue to prefer the smallest distance
    priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> pq;
    pq.push({ startNode, 0.0 });

    
    while (!pq.empty()) {
        Node* current = pq.top().node;
        pq.pop();

        if (current->id == endId) {
            break;
        }

        for (const auto& neighbor : current->neighbors) {
            Node* neighborNode = neighbor.first;
            double weight = neighbor.second;
            double altDist = distances[current->id] + weight;

            if (altDist < distances[neighborNode->id]) {
                distances[neighborNode->id] = altDist;
                previous[neighborNode->id] = current;
                pq.push({ neighborNode, altDist });
            }
        }
    }

    if (distances[endId] == numeric_limits<double>::infinity()) {
        cout << "No path exists between " << startId << " and " << endId << "." << endl;
    }
    else {
        cout << "Shortest path from " << startId << " to " << endId << ": " << distances[endId] << endl;
    }

    // Reconstruct the path
    stack<string> path;
    for (Node* at = endNode; at != nullptr; at = previous[at->id]) {
        path.push(at->id);
    }

    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) {
            cout << " -> ";
        }
    }
    cout << endl;
}
    

