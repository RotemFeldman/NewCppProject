#include "Node.h"

void Node::print() const
{
	cout << "| " << id << " |-->";

	for (auto& neighbor : neighbors)
	{
		cout << "( " << neighbor.first->id << ", distance: " << neighbor.second << " ),";
	}

	cout << endl << " - - - " << endl << endl;;
}
