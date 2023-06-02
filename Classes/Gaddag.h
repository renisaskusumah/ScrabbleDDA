#ifndef GADDAG_H
#define GADDAG_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Board.h"
#include "cocos2d.h"
#include "TileOnBoard.h"
#include "GraphDict.h"
#include "Heuristic.cpp"
#include <ctype.h>

#define COCOS2D_DEBUG 1
USING_NS_CC;

using namespace std;

class Gaddag
{
	private:

		GraphDict *G;
		Board board; // kelas papan
		Heuristic heuristic;
		ofstream fileGraf;
		ifstream grafFile;
		int count;
		SMove finalAction;
		vector<SMove> evalPossible;
		vector<string> result; //hasil generate movement(getWord)
		vector<string> evalResult; // hasil generate movement(generatemovement)
		vector<char> activeRack;//set rack yg dipakai dalam generate movement
		string maxWord; //kata yang terpilih untuk diambil jadi langkah
		int maxScore; //score dari kata yg terpilih
		string hook; //kata yang menempel pada tiles yang akan di taruh
		int startRow, startCol; // menyimpan startRow dan col dari kata yg terpilih
		int direction; //1 ke samping , 2 menurun
		CCLayer* gameScene; //scene
		string logFileName;
		string newTiles;
		string tempNewTiles;
		string column_string;
		bool useBlank; //apakah kata yg terpilih mengandung blank tile atau tidak (keperluan menandakan di file txt)
		bool useHeuristic;
		float maxHeuristic;
		vector<int> left_tiles;
		vector<SMove> allPotentials;
		vector<float> vector_heuristic;
		string directWord;
		int MAX_WORD_LENGTH = INT_MAX;
		int MAX_SCORE = INT_MAX;


	public:
		Gaddag();
		void setHeuristic(bool set);
		void restartGaddag();
		void setLogFile(string logName);
		void setBoard(Board p);
		Board & getBoard();
		void initGraph();
		void startPlaying(int initRow, int initCol);
		vector<char> getActiveRack();
		void setActiveRack(vector<char> rack);
		int getScore();
		string getUseBlank();
		string getAllPossibleWord();
		string getEvalWord();
		void playGame(vector<char> rack);
		vector<char> generateToGui(vector<char> rack);
		void getAllPossible(vector<char> rack);
		void getPossibleMovementByAnchor(vector<char> rack, vector<int> anchor);
		vector<float> getVectorHeuristic();
		vector<SMove> evaluateAllPossible(int limit);
		void setAllPotentialsData(vector<SMove> data);
		vector<SMove> getAllPotentialsData();
		vector<SMove> getAllPotentialsDataInScoreRange();
		void printAllPotentialsData();
		vector<SMove> possibleMovementInVectorByAnchor(vector<char> rack, vector<int> anchor);
		vector<SMove> possibleMovementInVector(vector<char> rack);
		string getHint(vector<char> rack);
		vector<SMove> getPossibleMovement();
		vector<char> getWord(vector<char> rack);
		vector<char> generateMovement(vector<char> rack);
		vector<int> getAnchorByWord(int startRow, int startCol, string word, int direction);
		int checkAnchor(int row, int col);
		void gen(int pos, string word, vector<char> rack, node * arc);
		void goOn(int pos, char l, string word, vector<char> rack, node * newArc, node * oldArc);
		void recordAndValidateMove(string word, int sisa, int row, int col);
		int checkRoom(int direction, int row, int col);
		int wordScore(string word, int row, int col, int direction);
		int getScoreByAnchor(string word, int row, int col, int direction);
		int getScoreTypeByPosition(int length, int row, int col, int direction);
		int getScoreByWord(string word);
		char getLetterByIndex(int index);
		int getIndexByLetter(char alphabet);
		int getTilesScoreByIndex(int index);
		node * nextArc(node * arc, char l);
		void addWordToPapan(string word, int row, int col, int direction);
		void addWordToPapanGui(string word, int row, int col, int direction);
		string getHook(string word, int row, int col, int direction);
		int isFitOnBoard(string word, int row, int col, int direction);
		string getFirstWord(string str);
		string getWordDefinition(string word);
		int getTotalAnchor(Board * board);
		void setFinalAction(SMove move);
		SMove getFinalAction();
		int getMaxWordLength();
		void setMaxWordLength(int val);
		int getMaxScore();
		void setMaxScore(int val);
		GraphDict * getGraphDict();
		~Gaddag();
};

#endif