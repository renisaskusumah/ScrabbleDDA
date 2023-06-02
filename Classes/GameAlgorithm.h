#ifndef _GAMEALGORITHM_H_
#define _GAMEALGORITHM_H_

#include <string>
#include "cocos2d.h"
#include <stdio.h>
#include <ctype.h>
#include "Gaddag.h"
#include "NegaScout.cpp"
#include "BasicTiles.h"
#include "MonteCarloTreeSearch.h"

using namespace std;

class GameAlgorithm
{
	private:
		Gaddag gaddag;
		Board papan;
		BasicTiles basicTiles;
		Board tempPapan;
		vector<vector<int> > letterBag;
		vector<vector<int> > unseenLetters;
		vector<char> opponentRack;
		int totalNode;
		int score;
		string word;
		nodetree* eval; // hasil evaluasi negascout
		int nega_stat; //apakah jadinya pakai nega atau heuristic biasa
		string fileName;
		string logFile;
		MonteCarloTreeSearch MCTS;
		SMove latestAction;
		vector<SMove> userMoves;
		const int __LEVEL = 20;
		int userScore = 0;
		int AIScore = 0;
	public:
		GameAlgorithm();
		Gaddag & getGaddag();
		Board & getBoard();
		void setFileName(string s);
		vector<char> playNegaScout(vector<char> rack2, int p1, int p2);
		vector<char> negaResultToGui(vector<char> rack);
		int getNegaScore();
		string getNegaWord();
		void generateTree(Negascout nega, vector<char> opponent, vector<char> rack, int depth, nodetree * node, vector<SMove> movement_computer, vector<SMove> movement_human);
		vector<char> randomRackFromUnseen(vector<char> rack);
		void initLetterBag();
		vector<vector<int>> updateUnseenLetterByWord(string word, vector<vector<int>> currentState);
		void setOpponentRack(vector<char> rack);
		vector<char> getOpponentRack();
		void updateOpponentRack(string newTiles);
		vector<vector<int>> updateUnseenLetter(int alphabetIndex, vector<vector<int>> currentState);
		vector<char> getRandomUnseenTiles(vector<char> rack2);
		SMove getLatestAction();
		void setLatestAction(SMove action);
		void computerPlayerTurn(vector<char> playerRack);
		SMove MCTSrun(vector<char> rack);
		vector<vector<int>> getLetterBag();
		void setLetterBag(vector<vector<int>> lBag);
		vector<vector<int>> getUnseenLetters();
		void setUnseenLetters(vector<vector<int>> letters);
		void recordUserMovement(SMove move);
		void calculateUserBehaviour();
		void setPlayerScore(int val, int playerNum);
		int getPlayerScore(int playerNum);
		void printMCTSOriginialTreeToFile(string filename);
		void clearGame();
		~GameAlgorithm();
};
#endif