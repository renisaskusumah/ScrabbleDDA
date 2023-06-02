#pragma once
#ifndef BASICTILES_H
#define BASICTILES_H

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BasicTiles {

	private:
		int count;
	public:
		BasicTiles();
		char * getLetterFile(int index);
		char * getSmallLetterFile(int index);
		char * getBlankLetterFile(int index);
		int getStatusBoardByPosition(int row, int col);
		int getTilesFrequentByIndex(int index);
		int getTileScoreByChar(char tile);
		int getTilesScoreByIndex(int index);
		string getLetterByIndex(int index);
		char getCharByIndex(int index);
		int getIndexByLetter(char alphabet);
		int getLeftTilesScoreByVector(vector<char> tiles);
		string getStringByRack(vector<char> vec);
		vector<vector<int>> updateUnseenLetterByWord(string word, vector<vector<int>> currentState);
		vector<vector<int>> updateUnseenLetter(int alphabetIndex, vector<vector<int>> currentState);
		bool isVocalPresent(int tiles[7]);
		~BasicTiles();
};

#endif