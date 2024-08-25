#pragma once
#include <vector>
#include "Node.h"
using namespace std;

class Dijkstra
{
public:
    Dijkstra() {};

	void search(const vector<Node*>& nodes, const string& startId, const string& endId);

    struct NodeDistance {
        Node* node;
        double distance;

        bool operator>(const NodeDistance& other) const {
            return distance > other.distance;
        }
    };
};

