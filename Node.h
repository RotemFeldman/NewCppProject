#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Node
{
public:
	string id;
	vector<pair<Node*, double>> neighbors;

	Node(string id) : id(id){}
	void print() const;

	bool operator!=(const Node& other) const {
		return id != other.id;
	}
};

