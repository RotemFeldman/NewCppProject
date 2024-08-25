#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Node
{
public:
	string id;
	vector<pair<Node*, int>> neighbors;

	Node(string id) : id(id){}
	void print() const;
};

