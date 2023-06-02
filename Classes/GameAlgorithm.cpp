#include"GameAlgorithm.h"

using namespace std;
GameAlgorithm::GameAlgorithm()
{
	MCTS.setGaddagAlgorithm(&gaddag);
}

/*-----------GADDAG------------*/

Gaddag& GameAlgorithm::getGaddag()
{
	return gaddag;
}

Board& GameAlgorithm::getBoard()
{
	return gaddag.getBoard();
}

/*------------HEURISTIC------------*/

/*----------NEGASCOUT---------------*/

void GameAlgorithm::setFileName(string s)
{
	fileName = "GAME_TREE/"+s;
	logFile = s;
	ofstream fileGame;
	fileGame.open(fileName.c_str());
	fileGame.close();
	string logNega = "LOG_NEGA/"+s;
	fileGame.open(logNega.c_str());
	fileGame.close();
}

vector<char> GameAlgorithm::playNegaScout(vector<char> rack2,int p1,int p2)
{
	//vector<char> opponentRack;
	nega_stat = 1;
	vector<SMove> vector_movement,vector_movement2;
	int tempSize;
	int i;
	score = 0;
	nodetree* evaluasi;
	vector<vector<int> > tempUnseen;
	string newTiles;
	vector<char>::iterator found;
	tempSize = rack2.size();
	tempUnseen = letterBag;
	if(opponentRack.size() == 0){ opponentRack = getRandomUnseenTiles(rack2); }
	gaddag.setActiveRack(rack2);
	tempPapan = gaddag.getBoard();
	Negascout nega;
	nega.setLogNega(logFile);
	nega.setTree(999);
	nega.setPlayerScore(p2);
	nega.setOpponentScore(p1);
	totalNode = 0;
	clock_t start;
	float durasi;
	start = clock();
	gaddag.setHeuristic(true);
	ofstream ofile(fileName.c_str(), ios::app);
	ofile<<"\n\n";
	ofile.close();
	generateTree(nega,opponentRack,rack2, __LEVEL,nega.getTree().root,vector_movement,vector_movement2);
	durasi = ( clock() - start ) / (float) CLOCKS_PER_SEC;
	ofstream ofile2(fileName.c_str(), ios::app);
	ofile2<<"durasi : "<<durasi<<"\n";
	ofile2.close();
	CCLOG("durasi %f",durasi);
	nega.setTotalNode(totalNode);
	//std::cout<<"Total Node : " <<totalNode<<"\n";
	CCLOG("Total Node : %d",totalNode);
	if(totalNode > 0)
	{
		nega.setDepth(__LEVEL + 1);
		nega.setVisited(0);
		nega.setLogFile("LOG_COMPUTER/" +logFile);
		ofstream ofile(nega.getLogNega().c_str(),ios::app);
		ofile<<"\n\n";
		ofile.close();
		int result = nega.negaScout(nega.getTree().root,-999,999,1);
		CCLOG("result : %d",result);
		CCLOG("visited : %d",nega.getVisited());
		nega.ambilSolusi((result * -1) , nega.getTree().root);
		if(result != -999 && result != 999)
		{
			nega.printChild(nega.getTree().root);
			evaluasi = nega.result(result * -1,nega.getTree().root);
			gaddag.setBoard(tempPapan);
			//std::cout<<g.getHint(rack2);
			/*put word berdasar negascout*/
			gaddag.setActiveRack(rack2);
			score = 0;
			score =gaddag.wordScore(evaluasi->word,evaluasi->row, evaluasi->col, evaluasi->direction);
			score +=gaddag.getScoreByAnchor(evaluasi->word,evaluasi->row, evaluasi->col, evaluasi->direction);
			word = evaluasi->word;
			CCLOG("eval word %s",evaluasi->word.c_str());
			gaddag.getBoard().setNewTilesOnBoard();
			eval = evaluasi;
			//gaddag.addWordToPapanGui(evaluasi->word,evaluasi->row, evaluasi->col, evaluasi->direction);
			//p2+=score;
			/*newTiles =gaddag.getBoard().getNewTilesOnBoard();
			for(i = 0 ; i < newTiles.length() ; i++)
			{
				found = std::find(rack2.begin(), rack2.end(),newTiles.at(i)) ;
				if(found!=rack2.end())
				{
					rack2.erase(found);
				}
			}*/
			//gameToFile("negascout",evaluasi->word,0,score,"NEGASCOUT");
		}
	}
	else
	{
		nega_stat = 0;
		gaddag.setBoard(tempPapan);
		gaddag.getBoard().setNewTilesOnBoard();
		gaddag.playGame(rack2);
		score = gaddag.getScore();
	}
	letterBag = tempUnseen;
	/*updateUnseenLetterByWord(gaddag.getBoard().getNewTilesOnBoard());*/
	return rack2;
}

vector<char> GameAlgorithm::negaResultToGui(vector<char> rack )
{
	gaddag.getBoard().setNewTilesOnBoard();
	if(nega_stat == 1)
	{
		string newTiles;
		int i;
		vector<char>::iterator found;
		gaddag.addWordToPapanGui(eval->word,eval->row, eval->col, eval->direction);
		newTiles =gaddag.getBoard().getNewTilesOnBoard();
		for(i = 0 ; i < newTiles.length() ; i++)
		{
			found = std::find(rack.begin(), rack.end(),newTiles.at(i)) ;
			if(found!=rack.end())
			{
				rack.erase(found);
			}
		}
	}
	else
	{
		gaddag.generateToGui(rack);
	}
	CCLOG("new tiles : %s",gaddag.getBoard().getNewTilesOnBoard().c_str());
	letterBag = updateUnseenLetterByWord(gaddag.getBoard().getNewTilesOnBoard(), letterBag);
	return rack;
}

int GameAlgorithm::getNegaScore()
{
	return score;
}

string GameAlgorithm::getNegaWord()
{
	return word;
}

void GameAlgorithm::generateTree(Negascout nega,vector<char> opponent,vector<char> rack,int depth,nodetree *node,vector<SMove> movement_computer,vector<SMove> movement_human)
{
	int tempDepth;
	nodetree *now;
	string stringOfRack;
	if(depth > 0 && rack.size() > 0 && opponent.size() > 0)
	{
		papan = gaddag.getBoard();
		tempDepth = depth;
		vector<char> temp,active,rack_temp;
		vector<SMove> result;
		vector<SMove> result_2;
		if(depth %2 == 1)
		{
			active = rack;
			result = movement_computer;
		}
		else
		{
			active = opponent;
			result = movement_human;
		}
		temp = active;
		stringOfRack = basicTiles.getStringByRack(active);
		int i,j,row,col;
		vector<char>::iterator found;
		if(result.size() == 0)
		{
			gaddag.getAllPossible(active);
			result_2 = gaddag.getAllPotentialsData();
			//result = gaddag.evaluateAllPossible(gaddag.getVectorHeuristic().size());
			result = gaddag.evaluateAllPossible(50);
			//jika mengandung blank tambahkan evaluate lagi di gaddag untuk menyederhanakan total possible
		}
		else
		{
			result_2 = result;
		}
		for(i = 0 ; i < result.size() ; i++)
		{
			active = temp;
			depth = tempDepth;
			gaddag.setBoard(papan);
			if(depth == this->__LEVEL)
			{
				gaddag.setBoard(tempPapan);
			}
			//periksa dulu apakah used tilesnya ad di rack active tidak
			rack_temp = active;
			//periksa juga apakah use tiles nya ada di rack active atau tidak
			string str2 = result.at(i).usedTiles;
			string str = stringOfRack;
			std::size_t found2 = str.find_first_of(str2);
			int sama = 0;
			while (found2!=std::string::npos)
			{
				sama++;
				string::size_type loc = str2.find( str.at(found2), 0 );
				if( loc != string::npos ) {
					str2.erase(str2.begin()+loc);
				}
				str.at(found2) = '-';
				found2=str.find_first_of(str2,found2+1);
			}
			if(sama == result.at(i).usedTiles.length())
			{
				//jika ada , maka periksa apakah masih bisa ditaruh di board atau tidak (cek jajaran tersebut sudah diisi belum)
				if(gaddag.isFitOnBoard(result.at(i).word,result.at(i).startRow,result.at(i).startCol,result.at(i).direction) == 1)
				{
					row = result.at(i).startRow;
					col = result.at(i).startCol;
					for(j = 0 ; j < result.at(i).word.length() ; j++)
					{
						if(gaddag.getBoard().getLetterOnPosition(row,col) == '-')
						{
							found = std::find(active.begin(), active.end(),result.at(i).word.at(j)) ;
							if (found!=active.end())
							{
								active.erase(found);
							}
						}
						if(result.at(i).direction == 1)
						{
							col++;
						}
						else
						{
							row++;
						}
					}
					gaddag.addWordToPapan(result.at(i).word,result.at(i).startRow,result.at(i).startCol,result.at(i).direction);
					ofstream ofile(fileName.c_str(), ios::app);
					ofile<<"word : "<<result.at(i).word<<" anchor( col : "<<result.at(i).colAnchor<<" row : "<<result.at(i).rowAnchor<<" ) score : "<<result.at(i).score<<" new tiles : "<<result.at(i).usedTiles<<" heuristic : "<<result.at(i).heuristic<<" level : "<< __LEVEL - depth + 1<<"\n";
					ofile.close();
					now = nega.addChild(999, node,result.at(i).word,result.at(i).startRow,result.at(i).startCol,result.at(i).direction , result.at(i).score,basicTiles.getLeftTilesScoreByVector(active),result.at(i).rowAnchor,result.at(i).colAnchor,result.at(i).heuristic,result.at(i).usedTiles.length());
					totalNode++;
					vector<int> new_anchor = gaddag.getAnchorByWord(result.at(i).startRow,result.at(i).startCol,result.at(i).word,result.at(i).direction);
					gaddag.getPossibleMovementByAnchor(active,new_anchor);
					vector<SMove> hasil = gaddag.getAllPotentialsData();
					// result.insert(result.end(),g.getAllPossibleVector().begin(),g.getAllPossibleVector().end());
					if(depth %2 == 1)
					{
						rack = active;
						movement_computer = result;
						movement_computer.insert(movement_computer.end(),hasil.begin(),hasil.end());
					}
					else
					{
						opponent = active;
						movement_human = result;
						movement_human.insert(movement_human.end(),hasil.begin(),hasil.end());
					}
					generateTree(nega,opponent,rack,depth - 1,now,movement_computer,movement_human);
				}
			}
		}
	}
}

vector<char> GameAlgorithm::randomRackFromUnseen(vector<char> rack)
{
	srand(time(NULL));
	int i,kosong,temp;
	kosong = 7 - rack.size();
	for(i = rack.size() ; i < 7; i++)
	{
		if(letterBag.size() > 0)
		{
			temp = rand() % letterBag.size();
			rack.push_back(basicTiles.getCharByIndex(letterBag.at(temp).at(0)));
			letterBag = updateUnseenLetter(letterBag.at(temp).at(0), letterBag);
		}
	};
	return rack;
}

void GameAlgorithm::initLetterBag()
{
	int i;
	vector<int> letter;
	for(i = 0 ; i < 27 ; i++)
	{
		letter.push_back(i);
		letter.push_back(basicTiles.getTilesFrequentByIndex(i));
		letterBag.push_back(letter);
		letter.clear();
	}
	unseenLetters = letterBag;
}

vector<vector<int>>  GameAlgorithm::updateUnseenLetterByWord(string word, vector<vector<int> > currentState)
{
	for(int i = 0 ; i < word.length() ; i++)
	{
		currentState =  updateUnseenLetter(basicTiles.getIndexByLetter(word.at(i)), currentState);
	}
	return currentState;
}

void GameAlgorithm::setOpponentRack(vector <char> rack)
{
	opponentRack = getRandomUnseenTiles(rack);
}

vector<char> GameAlgorithm::getOpponentRack(){
	return opponentRack;
}

void GameAlgorithm::updateOpponentRack(string newTiles)
{
	if(opponentRack.size() > 0)
	{
		int i;
		vector<char>::iterator found;
		for(i = 0 ; i < newTiles.length() ; i++)
		{
			found = std::find(opponentRack.begin(), opponentRack.end(),newTiles.at(i)) ;
			if(found!=opponentRack.end())
			{
				opponentRack.erase(found);
			}
		}
	}
}

//delete element jika sudah ditaruh di board
vector<vector<int> > GameAlgorithm::updateUnseenLetter(int alphabetIndex, vector<vector<int> > currentState)
{
	//find element
	int status = 0;
	int i = 0;
	while(i < currentState.size() && status == 0)
	{
		if(currentState.at(i).at(0) == alphabetIndex)
		{
			if(currentState.at(i).at(1) == 1)
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

vector<char> GameAlgorithm::getRandomUnseenTiles(vector<char> rack2)
{
	//getSisaUnseen();
	vector<vector<int> > temp = letterBag;
	vector<char> unseen;
	string randomSeen = "";
	int i,index;
	//std::cout<<"size rack : "<<rack2.size()<<"\n";
	for(i = 0 ; i < rack2.size() ; i++)
	{
		letterBag = updateUnseenLetter(basicTiles.getIndexByLetter(rack2.at(i)), letterBag);
	}
	//getSisaUnseen();
	i = 0;
	srand(time(NULL));
	while(i < 7 && letterBag.size() > 0 )
	{
		index = rand() % letterBag.size();
		unseen.push_back(basicTiles.getCharByIndex(letterBag.at(index).at(0)));
		randomSeen += basicTiles.getCharByIndex(letterBag.at(index).at(0));
		letterBag = updateUnseenLetter(letterBag.at(index).at(0), letterBag);
		i++;
	}
	//getSisaUnseen();
	letterBag = temp;
	std::cout<<"random rack opponent : "<<randomSeen<<"\n";
	CCLOG("random rack : %s",randomSeen.c_str());
	return unseen;
}

SMove GameAlgorithm::getLatestAction()
{
	return latestAction;
}

void GameAlgorithm::setLatestAction(SMove action)
{
	latestAction = action;
}

void GameAlgorithm::computerPlayerTurn(vector<char> playerRack)
{
	Board existedBoard = gaddag.getBoard();
	vector<SMove> move;
	setLatestAction(MCTSrun(playerRack));
	gaddag.setBoard(existedBoard);
	if (latestAction.word.length() > 0)
		move.push_back(latestAction);
	gaddag.setAllPotentialsData(move);
	gaddag.setFinalAction(latestAction);
	gaddag.setMaxScore(INT_MAX);
	gaddag.setMaxWordLength(INT_MAX);
}

SMove GameAlgorithm::MCTSrun(vector<char> rack)
{
	//update unseenletters
	string r = "";
	for (char c : rack) r += c;
	vector<vector<int>> unseen = updateUnseenLetterByWord(r, unseenLetters);
	calculateUserBehaviour();
	MCTS.setPlayerScore(userScore, 1);
	MCTS.setPlayerScore(AIScore, 2);
	return MCTS.search(&MCTS.getTree().getRoot(),  gaddag.getBoard(), rack, unseen, latestAction);
}

vector<vector<int> > GameAlgorithm::getLetterBag()
{
	return letterBag;
}

void GameAlgorithm::setLetterBag(vector<vector<int> > lBag)
{
	letterBag = lBag;
}

vector<vector<int> > GameAlgorithm::getUnseenLetters()
{
	return unseenLetters;
}

void GameAlgorithm::setUnseenLetters(vector<vector<int> > letters)
{
	unseenLetters = letters;
}

void GameAlgorithm::recordUserMovement(SMove move)
{
	//if it was a first move, than the score should be divided by two as center tiled will give double score
	//if (userMoves.empty()) move.score = move.score / 2;
	userMoves.push_back(move);
}

void GameAlgorithm::calculateUserBehaviour()
{
	int avgScore = 0;
	int avgWordLength = 0;
	if (!userMoves.empty()) {
		for (SMove move : userMoves)
		{
			avgScore += move.score;
			avgWordLength += move.word.length();
		}
		avgScore = int(avgScore / userMoves.size());
		avgWordLength = int(avgWordLength / userMoves.size());
		//adjust to increase opportunity to win
		if (avgScore + 10 > getPlayerScore(1) - getPlayerScore(2))
		{
			gaddag.setMaxScore(avgScore);
			gaddag.setMaxWordLength(avgWordLength);
		}
		else
		{
			gaddag.setMaxScore((getPlayerScore(1) - getPlayerScore(2)));
			gaddag.setMaxWordLength(INT_MAX);
		}
	}
}

void GameAlgorithm::setPlayerScore(int val, int playerNum)
{
	if (playerNum == 1)
	{
		userScore = val;
	}
	else
	{
		AIScore = val;
	}
}

int GameAlgorithm::getPlayerScore(int playerNum)
{
	return (playerNum == 1) ? userScore : AIScore;
}

void GameAlgorithm::printMCTSOriginialTreeToFile(string filename)
{
	MCTS.printOriginalTreeToFile(filename);
}

void GameAlgorithm::clearGame()
{
	MCTS.getTree().deleteTree(&MCTS.getTree().getRoot());
	getGaddag().restartGaddag();
}

GameAlgorithm::~GameAlgorithm()
{

}