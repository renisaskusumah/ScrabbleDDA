#ifndef _AIPLAYER_CPP_
#define _AIPLAYER_CPP_
#include "AiPlayer.h"
	
AiPlayer::AiPlayer()
{
}

void AiPlayer::initPlayer(CCLayer* g,int gt)
{
	//initialize player attributes
	game = g;
	gameType = gt;
	passTurn = 0;
	totalDurasi = 0;
}

//get character on rack based on index number
char AiPlayer::getTileOnRack(int index)
{
	return _rack.at(index);
}

//set character on rack based on index number
void AiPlayer::setTileOnRack(char tile)
{
	_rack.push_back(tolower(tile));
}

//delete character on rack based on index number
void AiPlayer::deleteTileOnRack(int index)
{
	_rack.erase(_rack.begin() + index);
}

//get active rack
vector<char> AiPlayer::getRackVector()
{
	return _rack;
}
		
//get total duration in one game round
float AiPlayer::getTotalDurasi()
{
	return totalDurasi;
}

//adding up total duration on every movement taken
void AiPlayer::addDurasi(float d)
{
	totalDurasi+=d;
}

//set active rack
void AiPlayer::setRack(vector<char> rack)
{
	_rack.clear();
	_rack = rack;
}

//get rack as a string
string AiPlayer::getRackInString()
{
			
	int i;
	string rack = "";
	for (i = 0 ; i < _rack.size() ; i++)
	{
		rack+=_rack.at(i);
	}
	return rack;
}

//check is rack contains blank tile
int AiPlayer::isContainBlank()
{
	int status = 0;
	if(std::find(_rack.begin(),_rack.end(),'*')!= _rack.end())
	{
		status = 1;
	}
	return status;
}

//set total passes
void AiPlayer::setPassTurn(int turn)
{
	passTurn= turn;
}

//get total number of pass
int AiPlayer::getPassTurn()
{
	return passTurn;
}
		
AiPlayer::~AiPlayer()
{
}
#endif