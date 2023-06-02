#ifndef BOARD_CPP
#define BOARD_CPP

#include "Board.h"
Board::Board()
{

}

//initialize board grid
void Board::initPapan()
{
	int i,j;
	//set papan jadi kosong
	for(i = 0 ; i < 15 ; i ++)
	{
		for(j = 0 ; j < 15 ; j++)
		{
			tiles[i][j].letter = '-';
			tiles[i][j].isBlankTile = false;
			tiles[i][j].isSet = false;
		}
	}
}

//record latest added new tiles on board
void Board::setNewTilesOnBoard()
{	
	newTilesOnBoard = "";
}

//get latest added new tiles on board
string Board::getNewTilesOnBoard()
{
	return newTilesOnBoard;
}

//set tile type on the board grid (2L, 2W, 3L, 3W, center tile, normal tile)
void Board::setTileType(int type,int row,int col)
{
	tiles[row][col].tileType = type ;
}

//get tile type on the board grid (2L, 2W, 3L, 3W, center tile, normal tile)
int Board::getTileType(int row,int col)
{
	int tiletype = tiles[row][col].tileType;
	if ( tiles[row][col].isSet == true)
	{
		tiletype = 1;
	}
	return tiletype ;
}

//set tile on board grid is occupied or not
void Board::setIsSetTile(bool set,int row,int col)
{
	tiles[row][col].isSet = set;
}

//check is tile on board grid is occupied by blank tile or not
void Board::setIsBlankTile(bool b,int row,int col)
{
	tiles[row][col].isBlankTile = b;
}

//check is tile on board grid is occupied by blank tile or not
bool Board::getBlankTileStatus(int row,int col)
{
	return tiles[row][col].isBlankTile;
}

//check is tile on board grid is occupied or not
bool Board::getSetStatus(int row,int col)
{
	return tiles[row][col].isSet;
}

//set anchor row played
void Board::setRowPlayed(int row)
{
	rowPlayed = row;
}

//set anchor col played
void Board::setColPlayed(int col)
{
	colPlayed = col;
}

//get anchor row played
int Board::getRowPLayed()
{
	return rowPlayed;
}

//get anchor col played
int Board::getColPlayed()
{
	return colPlayed;
}

//set a letter on board
void Board::setCharOnBoard(int row,int col, char huruf)
{
	if(tiles[row][col].isSet == false)
	{
		if(tiles[row][col].isBlankTile == false)
		{
			newTilesOnBoard += huruf;
		}
		else
		{
			newTilesOnBoard +="*";
		}
	}
	tiles[row][col].letter =  huruf;
	tiles[row][col].isSet = true;
}

//get a letter of tile in board grid
char Board::getLetterOnPosition(int row,int column)
{
	char l;
	//l = papan[row][column].letter ;
	if(row < 0 || row > 14 ||column < 0 || column > 14)
	{
		l = '-';
		//std::cout<<row<<" "<<column<<"\n";
	}
	else
	{
		l = tiles[row][column].letter ;
	}
	return l;
}

//print board
void Board::printBoard()
{
	int i,j;
	for(i = 0 ; i < 15 ; i++)
	{
		for(j = 0 ; j < 15 ; j++)
		{	
			std::cout<<tiles[i][j].letter<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

//get total unoccupied tiles in board grid
int Board::getTotalNotSetTile()
{
	int i,j,total;
	total = 0;
	for(i = 0 ; i < 15 ; i++)
	{
		for(j = 0 ; j < 15 ; j++)
		{	
			if(tiles[i][j].isSet == false)
			{
				total++;
			}
		}
	}
	return total;
}

//check new tiles on board by position and word
string Board::getNewTilesByWord(int row,int col,string word,int direction)
{
	int i,j;
	string usedTiles = "";
	for(i = 0 ; i < word.length(); i++)
	{
		if(getSetStatus(row,col) == false)
		{
			usedTiles = usedTiles + word.at(i);
		}
		if(direction == 1)
		{
			col++;
		}
		else
		{
			row++;
		}
	}
	return usedTiles;
		
}

//return board state in a string
string Board::boardToString()
{
	string text = "";
	int i, j;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			text += tiles[i][j].letter;
			text += "";
		}

		text += "\n";
	}
	text += "\n";
	return text;
}

Board::~Board()
{
}

#endif
