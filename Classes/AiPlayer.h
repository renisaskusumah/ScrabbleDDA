#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "cocos2d.h"
#include<string>
#include<iostream>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <vector>


USING_NS_CC;
using namespace std;

class AiPlayer {
	private:
		//active rack
		vector<char> _rack;
		//game scene
		CCLayer* game;
		//1 human, 2 AI
		int gameType; 
		//count number of consecutive passes
		int passTurn;
		//number of total duration taken in one round
		float totalDurasi;
	public:

		AiPlayer();
		void initPlayer(CCLayer * g, int gt);
		char getTileOnRack(int index);
		void setTileOnRack(char tile);
		void deleteTileOnRack(int index);
		vector<char> getRackVector();
		float getTotalDurasi();
		void addDurasi(float d);
		void setRack(vector<char> rack);
		string getRackInString();
		int isContainBlank();
		void setPassTurn(int turn);
		int getPassTurn();
		~AiPlayer();

};

#endif