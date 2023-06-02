#ifndef MCTREE_H
#define MCTREE_H
#include<string>
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
#include<algorithm> 
#include "Board.h"
#include "cocos2d.h"
#include <cstdio>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>


#define COCOS2D_DEBUG 1
USING_NS_CC;

using namespace std;
struct MCNode{

	//this node prepared for scrabble gameplay
	int ID = 0;
	int t = 0;
	int n = 0;
	Board state;
	string word;
	SMove data;
	bool isAI; //is the level is on AI turn or user
	vector<MCNode *> child;
	vector<vector<int> > leftTiles;
	vector<char> rack;
	MCNode *parent;
	int level = 1;
	int visitCount = 0;
	double winScore = 0;
	int playerScore = 0;
	int uct = 0;
};

class MCTree
{
	private:
		MCNode *root;
		int treeLevel;
		int nodeID = 0;
	public:
		MCTree();
		void initTree();
		void setRoot(MCNode * node);
		MCNode& getRoot();
		void insertNode(MCNode *node, MCNode *parent);
		void deleteNode(MCNode *node);
		int getTreeLevel();
		void setTreeLevel(int level);
		MCNode* getChildWithMaxScore(MCNode *node);
		void printTree(MCNode node);
		void printTreeToFile(MCNode node, string filename);
		string printNode(MCNode node);
		int getTotalChildVisited(MCNode node);
		int getLatestNodeID();
		void deleteTree(MCNode * node);
		void printTreeLevelOrder(MCNode *node, bool onlyVisited);
		void printTreeLevelOrderToFile(MCNode node, bool onlyVisited, string filename);
		~MCTree();
};
#endif