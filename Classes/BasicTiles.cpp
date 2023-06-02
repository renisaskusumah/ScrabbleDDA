#ifndef BASICTILES_CPP
#define BASICTILES_CPP
#include "BasicTiles.h"

//An class about board & tiles general functions
BasicTiles::BasicTiles()
{
}

//get letter image for tiles on rack
char* BasicTiles::getLetterFile(int index)
{
	char* fileName[27] = {"A.png","B.png","C.png","D.png","E.png","F.png","G.png","H.png","I.png","J.png","K.png","L.png","M.png","N.png","O.png","P.png","Q.png","R.png","S.png","T.png","U.png","V.png","W.png","X.png","Y.png","Z.png","blank.png"}; 
			
	return fileName[index];
}

//get letter image small version for tiles on board
char* BasicTiles::getSmallLetterFile(int index)
{
	char* fileName[26] = {"A_small.png","B_small.png","C_small.png","D_small.png","E_small.png","F_small.png","G_small.png","H_small.png","I_small.png","J_small.png","K_small.png","L_small.png","M_small.png","N_small.png","O_small.png","P_small.png","Q_small.png","R_small.png","S_small.png","T_small.png","U_small.png","V_small.png","W_small.png","X_small.png","Y_small.png","Z_small.png"}; 
			
	return fileName[index];
}

//get letter image of converted blank tile into letter
char* BasicTiles::getBlankLetterFile(int index)
{
	char* fileName[26] = {"A_blank.png","B_blank.png","C_blank.png","D_blank.png","E_blank.png","F_blank.png","G_blank.png","H_blank.png","I_blank.png","J_blank.png","K_blank.png","L_blank.png","M_blank.png","N_blank.png","O_blank.png","P_blank.png","Q_blank.png","R_blank.png","S_blank.png","T_blank.png","U_blank.png","V_blank.png","W_blank.png","X_blank.png","Y_blank.png","Z_blank.png"}; 
			
	return fileName[index];
}

//get board grid status (type normal / 2L / 3L / 2W / 3W / center tile
int BasicTiles::getStatusBoardByPosition(int row,int col)
{
	int arrPapan[15][15] = {
	{6,0,0,0,0,0,0,6,0,0,0,0,0,0,6},
	{0,4,0,2,0,3,0,0,0,3,0,2,0,4,0},
	{0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
	{2,0,0,4,0,0,0,2,0,0,0,4,0,0,2},
	{0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
	{0,3,0,0,0,3,0,0,0,3,0,0,0,3,0},
	{0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
	{6,0,0,2,0,0,0,-1,0,0,0,2,0,0,6},
	{0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
	{0,3,0,0,0,3,0,0,0,3,0,0,0,3,0},
	{0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
	{2,0,0,4,0,0,0,2,0,0,0,4,0,0,2},
	{0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
	{0,4,0,0,0,3,0,0,0,3,0,0,0,4,0},
	{6,0,0,2,0,0,0,6,0,0,0,2,0,0,6}
	};
	return arrPapan[row][col];
}

//get number of letter frequency in letter bag / game
int BasicTiles::getTilesFrequentByIndex(int index)
{
	int frequent[27] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2};

	return frequent[index];
}

//get tiles / letters point by letter
int BasicTiles::getTileScoreByChar(char tile)
{
	string letters = "abcdefghijklmnopqrstuvwxyz*";
	size_t found = letters.find(tile);
	return getTilesScoreByIndex(found);
}

//get tiles / letters point by index in alphabet sequence
int BasicTiles::getTilesScoreByIndex(int index)
{
	int score[27] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10,0};

	return score[index];
}

//get letter by index number as uppercase
string BasicTiles::getLetterByIndex(int index)
{
	string alphabet[27] =  {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","*"}; 
			
	return alphabet[index];
}

//get letter by index number as lowercase
char BasicTiles::getCharByIndex(int index)
{
	char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','*'};  
			
	return alphabet[index];
}

//get index number of letter in lette sequence
int BasicTiles::getIndexByLetter(char alphabet)
{
	string letters = "abcdefghijklmnopqrstuvwxyz*";
	std::size_t found = letters.find(alphabet);
	return found;
}

//get total points of tiles on rack
int BasicTiles::getLeftTilesScoreByVector(vector<char> tiles)
{
	int score = 0;
	int i;
	for(i = 0 ; i < tiles.size();i++)
	{
		score+= getTileScoreByChar(tiles.at(i));
	}
			
	return score;
}

//convert rack vector into string
string BasicTiles::getStringByRack(vector<char> vec)
{
	string str = "";
	int size,i;
	size = vec.size();
	for(i = 0 ; i < size ; i++)
	{
		str+= vec.at(i);
	}
	return str;
}

//update letterbag (left tiles) based on word
vector<vector<int>>  BasicTiles::updateUnseenLetterByWord(string word, vector<vector<int> > currentState)
{
	int i;
	for (i = 0; i < word.length(); i++)
	{
		currentState = updateUnseenLetter(getIndexByLetter(word.at(i)), currentState);
	}
	return currentState;
}

//delete a letter from letter bag (left tiles)
vector<vector<int>> BasicTiles::updateUnseenLetter(int alphabetIndex, vector<vector<int> > currentState)
{
	//find element
	int status = 0;
	int i = 0;
	while (i < currentState.size() && status == 0)
	{
		if (currentState.at(i).at(0) == alphabetIndex)
		{
			if (currentState.at(i).at(1) == 1)
			{
				//sudah habis, hapus huruf dari unseen
				currentState.erase(currentState.begin() + i);
			}
			else
			{
				currentState.at(i).at(1) = currentState.at(i).at(1) - 1;
			}
			status = 1;
		}
		else
		{
			i++;
		}
	}
	return currentState;
}

//check is a vocal letter present in a rack
bool BasicTiles::isVocalPresent(int tiles[7])
{
	for (int i = 0 ; i  < 7 ; i++)
	{
		int c = tiles[i];
		if (c != -1 && (getCharByIndex(c) == 'a' || getCharByIndex(c) == 'i' || getCharByIndex(c) == 'u' 
			|| getCharByIndex(c) == 'e' || getCharByIndex(c) == 'o' || getCharByIndex(c) == '*'))
		{
			return true;
			break;
		}
	}
	return false;
}

BasicTiles::~BasicTiles()
{
}

#endif
	