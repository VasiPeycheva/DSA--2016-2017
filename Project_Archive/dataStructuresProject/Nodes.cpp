#include "Nodes.h"

void cleanNode(node *& root)
{
	if (root)
	{
		cleanNode(root->left);
		cleanNode(root->right);
		delete root;
	}
}

bool operator<(const weightedNode& lhs, const weightedNode rhs)
{
	return (lhs.weight < rhs.weight);
}

bool operator>(const weightedNode& lhs, const weightedNode rhs)
{
	return (lhs.weight > rhs.weight);
}
