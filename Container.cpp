#include "Container.h"
#include "Container.h"
#include <fstream>
#include <sstream>
#include <set>
#include <sstream>
#include "Dijkstra.h"
#include <stdexcept>

void Container::getAndParseAndShowData(const string& fileName)
{
	if (tryParseData(fileName))
	{
		printData();

		Dijkstra dijkstra;
		for (auto& pair : _findList)
		{
			dijkstra.search(getNodes(), pair.first, pair.second);
		}
			
	}
	cleanup();
}



//return the string split to tokens
vector<string> Container::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}

bool Container::isInteger(const string& str)
{
	// Check for empty string
	if (str.empty()) {
		return false;
	}

	// Allow optional leading whitespace
	size_t start = str.find_first_not_of(" \t");
	if (start == std::string::npos) {
		return false; // String is only whitespace
	}

	// Check if the remaining characters are digits
	return std::all_of(str.begin() + start, str.end(), ::isdigit);
}

bool Container::isDouble(const string& str)
{
	try 
	{
		size_t pos;
		stod(str, &pos);

		// Check if the entire string was parsed
		return pos == str.length();
	}
	catch (const invalid_argument& e)
	{
		return false;
	}
	catch (const out_of_range& e) 
	{
		return false;
	}
}



bool Container::tryParseData(const string& fileName)
{
	ifstream file(fileName);

	if (!file)
	{
		cerr << "Error opening file: " << fileName << endl;
		return false;
	}

	string line;
	int lineNum = 0;
	


	while (getline(file, line))
	{
		lineNum++;
		vector<string> tokens = split(line, ',');


		// node validation and creation
		if (tokens[0] == "node")
		{
			if (tokens.size() != 2)
			{
				cout << "Error in line " << lineNum << ". Node must be \"node,\'nodeId\'\" " << endl;
				return false;
			}

			// create node
			string nodeName = tokens[1];

			_nodes[nodeName] = new Node(nodeName);
			_nodeNames.push_back(nodeName);

			cout << "added node " << nodeName << endl;

		}
		//edge validation and creation
		else if (tokens[0] == "edge")
		{
			if (tokens.size() != 4)
			{
				cout << "Error in line " << lineNum << ". edge must include 4 tokens" << endl;
				return false;
			}

			string from = tokens[1];

			// check if nodes exist
			if (find(_nodeNames.begin(), _nodeNames.end(), from) == _nodeNames.end())
			{
				cout << "line " << lineNum << ": node " + from + " not found" << endl;
				return false;
			}

			string to = tokens[2];

			if (find(_nodeNames.begin(), _nodeNames.end(), to) == _nodeNames.end())
			{
				cout << "line " << lineNum << ": node " + to + " not found" << endl;
				return false;
			}


			//check if double
			if (!isDouble(tokens[3]))
			{
				cout << "line " << lineNum << ": weight value must be an numeric. the writen value is: " << tokens[3] << endl;
				return false;
			}


			double weight = stod(tokens[3]);

			// add edge to nodes
			_nodes[from]->neighbors.push_back({ _nodes[to],weight });
			_nodes[to]->neighbors.push_back({ _nodes[from],weight });

			cout << "added edge from " << from << " to " << to << " with a weight of " << weight << endl;


		}
		// nodes to find path between
		else if (tokens[0] == "find")
		{
			if (tokens.size() != 3)
			{
				cout << "Error in line " << lineNum << ". find must include 3 tokens" << endl;
				return false;
			}

			string from = tokens[1];

			// check if nodes exist
			if (find(_nodeNames.begin(), _nodeNames.end(), from) == _nodeNames.end())
			{
				cout << "line " << lineNum << ": node " + from + " not found" << endl;
				return false;
			}

			string to = tokens[2];

			if (find(_nodeNames.begin(), _nodeNames.end(), to) == _nodeNames.end())
			{
				cout << "line " << lineNum << ": node " + to + " not found" << endl;
				return false;
			}

			_findList.push_back({ from, to });

		}
		else
		{
			// first token is not valide
			cout << "line " << lineNum << ": first key is not valid" << endl;
			return false;
		}
	}

	file.close();
	return true;
}


void Container::printData() const
{
	system("cls");

	for (const auto& node : _nodes)
	{
		node.second->print();
	}
}

vector<Node*> Container::getNodes() const
{
	vector<Node*> ret;

	for (auto node : _nodes)
	{
		ret.push_back(node.second);
	}

	return ret;
}

void Container::cleanup()
{
	for (auto& pair : _nodes) {
		delete pair.second;
	}
}




