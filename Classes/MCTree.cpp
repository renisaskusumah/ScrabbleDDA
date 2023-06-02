#include "MCTree.h"

MCTree::MCTree()
{
}

void MCTree::initTree()
{
	treeLevel = 1;
	root = new MCNode;
	root->isAI = false;
	root->level = 1;
	root->ID = 1;
	nodeID += 1;
}

void MCTree::setRoot(MCNode *node)
{
	root = node;
}

MCNode& MCTree::getRoot()
{
	return *root;
}


void MCTree::insertNode(MCNode * node, MCNode *parent)
{
	if (root == NULL) 
	{ 
		root = node; 
	}
	else
	{
		(*parent).child.push_back(node);
		(*node).parent = parent;
		if (treeLevel < node->level)
		{
			treeLevel += 1;
		}
		nodeID += 1;
	}
}

void MCTree::deleteNode(MCNode *node)
{
	delete node;
}

int MCTree::getTreeLevel()
{
	return treeLevel;
}

void MCTree::setTreeLevel(int level)
{
	treeLevel = level;
}

//find node with most minimum difference score between player AI vs user
MCNode * MCTree::getChildWithMaxScore(MCNode *node)
{
	if ((*node).child.size() == 0)
	{
		return NULL;
	}
	MCNode *max = (*node).child.at(0);
	for (MCNode *move : (*node).child)
	{
		if ((move->visitCount > max->visitCount) || (move->visitCount == max->visitCount && move->winScore > max->winScore)) max = move;
	}
	return max;
}

void MCTree::printTree(MCNode node)
{
	Board board = node.state;
	CCLOG("%s", printNode(node).c_str());
	CCLOG("%s", board.boardToString().c_str());
	if (node.child.size() > 0)
	{
		for (MCNode *child : node.child)
		{
			printTree(*child);
		}
	}
}

void MCTree::printTreeLevelOrder(MCNode *node, bool onlyVisited)
{
	queue<MCNode *> q;
	q.push(node);
	while (!q.empty())
	{
		MCNode *curr = q.front();
		Board board = (*curr).state;
		if (onlyVisited == false || curr->visitCount > 0) 
		{
			CCLOG("%s", printNode(*curr).c_str());
			CCLOG("%s", board.boardToString().c_str());
		}
		q.pop();

		for (MCNode *c : curr->child)
		{
			q.push(c);
		}

	}
		
}


void MCTree::printTreeLevelOrderToFile(MCNode node, bool onlyVisited, string filename)
{
	ofstream oTreeFile(filename.c_str(), ios::out | ios::trunc);
	queue<MCNode> q;
	q.push(node);
	while (!q.empty())
	{
		MCNode curr = q.front();
		Board board = curr.state;
		if (oTreeFile)
		{
			oTreeFile << printNode(curr).c_str() << "\n";
			oTreeFile << board.boardToString().c_str() << "\n";
		}
		q.pop();

		for (MCNode* c : curr.child)
		{
			if (onlyVisited == false || c->visitCount > 0)
			{

				q.push(*c);
			}
		}

	}
	oTreeFile.close();

}


void MCTree::printTreeToFile(MCNode node, string filename)
{
	ofstream oTreeFile(filename.c_str(), ios::app);
	Board board = node.state;
	if (oTreeFile)
	{
		oTreeFile << printNode(node).c_str() << "\n";
		oTreeFile << board.boardToString().c_str() << "\n";
		oTreeFile.close();
	}
	if (node.child.size() > 0)
	{
		for (MCNode *child : node.child)
		{
			printTreeToFile(*child, filename);
		}
	}
}


string MCTree::printNode(MCNode node)
{
	string rack = "";
	for (char c : node.rack)
	{
		rack += c;
	}
	string parentID = (node.ID == 1) ? "-" : std::to_string((node.parent)->ID);
	return "ID: " + std::to_string(node.ID) + "|Parent ID: " + parentID.c_str() + "| level: " + std::to_string(node.level) + "| word: " + node.word.c_str()
		+ "| rack: " + rack + "| visit count: "+std::to_string(node.visitCount)+"| win score: " + std::to_string(node.winScore) + "| num of child: " + std::to_string(node.child.size()) + "| uct val: " + std::to_string(node.uct);
}

int MCTree::getTotalChildVisited(MCNode node)
{
	int total = 0;
	for (MCNode* n : node.child)
	{
		if (n->visitCount > 0) total += 1;
	}
	return total;
}

int MCTree::getLatestNodeID()
{
	return nodeID;
}

void MCTree::deleteTree(MCNode *node)
{
	queue<MCNode *> q;
	q.push(node);
	while (!q.empty())
	{
		MCNode *curr = q.front();
		q.pop();
		for (MCNode *c : curr->child)
		{
			q.push(c);
		}
		delete(curr);
	}
}


MCTree::~MCTree()
{
}
