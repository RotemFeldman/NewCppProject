#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Node.h"
using namespace std;

class Container
{
public:
	void getAndParseAndShowData(const string& fileName);
	void printData() const;
	vector<Node*> getNodes() const;
	void cleanup();

private:
	unordered_map<string, Node*> _nodes;
	vector<string> _nodeNames;
	vector<pair<string, string>> _findList;

	vector<string> split(const string& s, char delimiter);
	bool isInteger(const string& str);
	bool isDouble(const string& str);
	bool tryParseData(const string& filename);

};



