#ifndef MCTS_H
#define MCTS_H
#include<string>
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
#include "MCTree.h"
#include "Gaddag.h"
#include "BasicTiles.h"
#include "UCT.cpp"
#include "cocos2d.h"

using namespace std;


#define COCOS2D_DEBUG 0
USING_NS_CC;

class MonteCarloTreeSearch
{
	private:
		const int WIN_SCORE = 10;
		MCTree tree;
		Gaddag *gaddag;
		string alphabet[27] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","*" };
		string letters = "abcdefghijklmnopqrstuvwxyz*";
		BasicTiles basicTiles;
		UCT uct;
		int maxTreeLevel;
		//Policy
		int ROLLOUT_NUM = 6;
		int ALLOWABLE_GAP_SCORE = 10;
		int MAX_CHILD_TO_BE_VISITED = 3;
		int userScore = 0;
		int AIScore = 0;
		MCNode *originalRootNode;
	public:
		MonteCarloTreeSearch();
		void setGaddagAlgorithm(Gaddag *g);
		MCNode * selectPromisingNode(MCNode * rootNode);
		void expansion(MCNode * parent, Board board, vector<char> computerRack, vector<vector<int>> leftTiles);
		int simulation(MCNode node);
		void backpropagation(MCNode * nodeToExplore, int score);
		SMove search(MCNode * node, Board board, vector<char> computerRack, vector<vector<int>> leftTiles, SMove latestMove);
		void printOriginalTree();
		void printOriginalTreeToFile(string filename);
		MCTree& getTree();
		void setPlayerScore(int val, int playerNum);
		int getPlayerScore(int playerNum);
		~MonteCarloTreeSearch();
};
#endif