#ifndef _BOARD_H_
#define _BOARD_H_


#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

//struct scrabble action movement
struct SMove
{
	int direction;
	string word;
	int startRow;
	int startCol;
	int score;
	string all;
	int rowAnchor;
	int colAnchor;
	string usedTiles;
	float heuristic;
};

struct tile
{
	bool isSet;
	bool isBlankTile;
	int tileType;
	char letter;
};


class Board
{
	private:
		tile tiles[15][15];
		int rowPlayed;
		int colPlayed;
		string newTilesOnBoard;
	public:
		Board();
		void initPapan();
		void setNewTilesOnBoard();
		string getNewTilesOnBoard();
		void setTileType(int type, int row, int col);
		int getTileType(int row, int col);
		void setIsSetTile(bool set, int row, int col);
		void setIsBlankTile(bool b, int row, int col);
		bool getBlankTileStatus(int row, int col);
		bool getSetStatus(int row, int col);
		void setRowPlayed(int row);
		void setColPlayed(int col);
		int getRowPLayed();
		int getColPlayed();
		void setCharOnBoard(int row, int col, char huruf);
		char getLetterOnPosition(int row, int column);
		void printBoard();
		int getTotalNotSetTile();
		string getNewTilesByWord(int row, int col, string word, int direction);
		string boardToString();
		~Board();
};
#endif