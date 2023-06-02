#ifndef _GAMEHUMANSCENE_H_
#define _GAMEHUMANSCENE_H_


#include "cocos2d.h"
#include "GameAlgorithm.h"
#include "AiPlayer.h"
#include <cstdio>
#include <ctime>
#include <thread>
#include <mutex>
#include <math.h>

#define COCOS2D_DEBUG 0

USING_NS_CC;
using namespace std;

class GameHumanScene : public CCLayer
{
	
	Sprite *_tiles[7];
	Sprite *_trackerBox;
	Sprite *_hintBox;
	Sprite *_blankBox;
	Size screenSize;
	MenuItem *_startButton;
	MenuItem *_executeButton;
	MenuItem *_exchangeButton;
	Menu *_exchangeMenu;
	Menu *_menu;
	Menu *_resumeMenu;
	Sprite *_paused;
	Sprite *_exchangeBox;
	Sprite *_exchangeTile[7];
	Sprite *_blankTile[26];
	Sprite *_winnerBg;
	int totalTiles;
	vector<vector<int>> letterBag;
	//int scorePlayer1;
	//int scorePlayer2;
	bool isPaused;
	int _arrTiles[7];
	int _exchangeIndex[7];
	int holdTile;
	int holdPosition;
	int totalPass;
	int blankTag;
	float sec;
	clock_t _start_human;
	float _durasi_human;
	vector<int> exchangeTile;
	CCLabelTTF* letterBagLabel;
	CCLabelTTF* countdownPlayer1;
	CCLabelTTF* countdownPlayer2;
	CCLabelTTF* scoreLabelPlayer1;
	CCLabelTTF* scoreLabelPlayer2;
	CCLabelTTF* guideLabel;
	CCLabelTTF* wordLabel;
	CCLabelTTF* scoreLabel;
	CCLabelTTF* winnerLabel;
	CCLabelTTF* hintLabel;
	CCLabelTTF* trackerLabel;
	int playerTurn;
	GameAlgorithm algorithm;
	BasicTiles basicTiles;
	AiPlayer playerTwo;
	vector<int> tileOnBoardTag;
	string saveFile;
	string logFile;
	vector<string> hintResult;
	vector<string> tracker;
	mutex mtx;
	float stop;
	int thingkingIndex;
	string treeMCTSFile;
	string logBoardFile;

	vector<char> rack;
	string playerRack = "";
	
public:
	static CCScene *scene();
	virtual bool init();
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void randomRack();
	void exitGame(CCObject *pSender);
	int getHoldTile();
	void setHoldTile(int tile);
	int getHoldPosition();
	void setHoldPosition(int p);
	void takeTileFromRack(int position,int tag);
	void putTileToRack(int position, int tag);
	void startGame(CCObject *pSender);
	void playTile(CCObject *pSender);
	void pass(CCObject *pSender);
	void showExchange(CCObject *pSender);
	void cancelExchange(CCObject *pSender);
	void exchange(CCObject *pSender);
	void pause(CCObject *pSender);
	void resume(CCObject *pSender);
	void hint(CCObject *pSender);
	void setLetterBag();
	void updateLetterBag(int index);
	char getLetterOnRack(int index);
	void userPlayTurn();
	void endUserPlayTurn();
	void computerPlayTurn();
	void setComputerPlay(float dt);
	void setEndgame();
	void changeBlank();
	void closeBlank();
	void updateTracker();
	void setBlankTag(int t);
	int getBlankTag();
	void goToEndGame(float dt);
	void takeBackTileOnBoard();
	void endPlayComputer();
	void updateLoading();
	void setUserPlay(float dt);
	void callBackStopStatus();
	CREATE_FUNC(GameHumanScene);
};

#endif