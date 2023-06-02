#include"MonteCarloTreeSearch.h"
#include"GameAlgorithm.h"
using namespace std;
/*
	Plan : 
	record every action took by players.
	Set node as taken move.
	expand possible moves. -> only select based on player's previous behaviour
	simulate every possible moves and back propagate
*/

MonteCarloTreeSearch::MonteCarloTreeSearch()
{
	tree.initTree();
	maxTreeLevel = 1;
	originalRootNode = &tree.getRoot();
}

void MonteCarloTreeSearch::setGaddagAlgorithm(Gaddag *g)
{
	gaddag = g;
}

/*Select promising node using UCT calculation
*/
MCNode * MonteCarloTreeSearch::selectPromisingNode(MCNode * rootNode)
{
	MCNode *node = rootNode;
	while (!(*node).child.empty())
	{
		node = UCT::findBestNodeWithUCT(*node);
	}
	return node;
}

/*
	On generate tree, GADDAG will be called to get all possible moves and put it on the tree
	to shorten the movements generation time, only take possible movements based on user behaviour (avg word length, avg score)
*/
void MonteCarloTreeSearch::expansion(MCNode * parent, Board board, vector<char> rack, vector<vector<int>> leftTiles)
{
	//call GADDAG get all possible moves
	Board tempBoard = board;
	gaddag->setBoard(board);
	gaddag->getAllPossible(rack);
	CCLOG("user avg word length %d , avg score %d", gaddag->getMaxWordLength(), gaddag->getMaxScore());
	//filter potentials data that in range of avg score of user

	for each (SMove move in gaddag->getAllPotentialsDataInScoreRange())
	{
		//update board condition according to Move
		MCNode *node = new MCNode;
		gaddag->setBoard(tempBoard);
		gaddag->addWordToPapan(move.word, move.startRow, move.startCol, move.direction);
		//check if using blank tiles
		vector<vector<int>> newLeftTiles = basicTiles.updateUnseenLetterByWord(move.usedTiles, leftTiles);
		node->data = move;
		node->parent = parent;
		node->isAI = (parent->isAI) ? false : true;
		node->state = gaddag->getBoard();
		node->word = move.word;
		node->rack = rack;
		//left tiles in letter bag
		node->leftTiles = newLeftTiles;
		node->visitCount = 0;
		node->level = parent->level + 1;
		node->playerScore = AIScore + move.score;
		node->ID = tree.getLatestNodeID() + 1;
		tree.insertNode(node, parent);
	}
}

/*
	Simulate selected node to play the game between user and AI for ROLLOUT_NUM consecutive turns
	Accumulate gained score in the simulation and return it as win score to be used in the backpropagate function
*/


int MonteCarloTreeSearch::simulation(MCNode node)
{
	MCNode tempNode = node;
	int totalPassUser = 0;
	int totalPassComputer = 0;
	bool isAi = false;
	vector<vector<int>> leftTiles = node.leftTiles;
	Board board = node.state;
	vector<char> rack = tempNode.rack;
	vector<char> userRack;
	int rollOutIter = 0;
	int tempUserScore = userScore;
	int tempAIScore = AIScore;
	for (int i = 0; i < 7; i++)
	{
		srand(time(NULL));
		if(!leftTiles.empty()) userRack.push_back(letters.at(leftTiles.at(rand() % leftTiles.size()).at(0)));
	}
	gaddag->setBoard(board);
	while (totalPassUser != 3 && totalPassComputer != 3 && !leftTiles.empty() && rollOutIter < ROLLOUT_NUM)
	{
		/*==RANDOM PLAY==*/
		gaddag->getAllPossible((isAi) ? rack : userRack);
		if (gaddag->getAllPotentialsDataInScoreRange().size() == 0)
		{
			if (isAi)
			{
				totalPassComputer += 1;
			}
			else
			{
				totalPassUser += 1;
			}
		}
		else
		{
			srand(time(NULL));
			SMove move = gaddag->getAllPotentialsDataInScoreRange().at(rand() % gaddag->getAllPotentialsDataInScoreRange().size());
			gaddag->addWordToPapan(move.word, move.startRow, move.startCol, move.direction);
			leftTiles = basicTiles.updateUnseenLetterByWord(move.usedTiles, leftTiles);
			board = gaddag->getBoard();
			if (isAi)
			{
				//reload AI rack
				tempAIScore += move.score;
				for (int i = 0; i < move.usedTiles.length(); i++)
				{
					//check if using blank tiles
					(find(rack.begin(), rack.end(), move.usedTiles.at(i)) != rack.end()) 
						? rack.erase(find(rack.begin(), rack.end(), move.usedTiles.at(i))) 
						: rack.erase(find(rack.begin(), rack.end(), '*'));
					srand(time(NULL));
					if (!leftTiles.empty()) rack.push_back(letters.at(leftTiles.at(rand() % leftTiles.size()).at(0)));
				}
				totalPassComputer = 0;
			}
			else
			{
				//reload user rack
				tempUserScore += move.score;
				for (int i = 0; i < move.usedTiles.length(); i++)
				{
					//check if using blank tiles
					(find(userRack.begin(), userRack.end(), move.usedTiles.at(i)) != userRack.end()) 
						? userRack.erase(find(userRack.begin(), userRack.end(), move.usedTiles.at(i))) 
						: userRack.erase(find(userRack.begin(), userRack.end(), '*'));
					srand(time(NULL));
					if(!leftTiles.empty()) userRack.push_back(letters.at(leftTiles.at(rand() % leftTiles.size()).at(0)));
				}
				totalPassUser = 0;
			}
			rollOutIter++;
		}
		isAi = (isAi) ? false : true;
	}
	//evaluate gap score between AI and user , only accept for minim gapscore
	CCLOG("player score : %d \n AI score : %d", tempUserScore, tempAIScore);
	CCLOG("%s", (gaddag->getBoard()).boardToString().c_str());
	//jika nilai tertinggal, win score merupakan pertambahan dari old score (untuk mencoba menyusul)
	int winScore = (tempAIScore > tempUserScore) ? tempAIScore - tempUserScore : tempAIScore - AIScore;
	return  ((tempAIScore > tempUserScore)  && (winScore > ALLOWABLE_GAP_SCORE)) ? ALLOWABLE_GAP_SCORE : winScore;
}

/*
	Backpropagation / backup = Use to accumulate rewards of simulations to back upwards root node
*/

void MonteCarloTreeSearch::backpropagation(MCNode *nodeToExplore, int score)
{
	//accumulate number of visitcount and winscore from selected node to original root node
	while (nodeToExplore != NULL)
	{
		if (nodeToExplore != originalRootNode)
		{
			nodeToExplore->visitCount += 1;
			nodeToExplore->winScore += score;
			nodeToExplore = (*nodeToExplore).parent;
		}
		else 
		{
			nodeToExplore = NULL;
		}
	}
}

SMove MonteCarloTreeSearch::search(MCNode * node, Board board, vector<char> computerRack, vector<vector<int> > leftTiles, SMove latestMove)
{
	SMove result;
	//remove blank tiles
	//limit time to 1.5 minutes
	clock_t start = clock();
	clock_t end = start + (CLOCKS_PER_SEC * 90);
	leftTiles = basicTiles.updateUnseenLetter(26, leftTiles);
	leftTiles = basicTiles.updateUnseenLetter(26, leftTiles);
	//initalize original root (ancestor) node for first movement
	if (originalRootNode->word.length() == 0)
	{
		SMove latest = latestMove;
		node->data = latest;
		node->word = latest.word;
		tree.setRoot(node);
		originalRootNode = &tree.getRoot();
	}
	int iter = 0;
	clock_t now = clock();
	while (iter < 10 && (iter == 0 || iter < (&tree.getRoot())->child.size()) && now < end)
	{
		//1. selection
		MCNode *promisingNode = selectPromisingNode(&tree.getRoot());
		//2. expansion
		if((&tree.getRoot())->child.empty())
			expansion(promisingNode, board, computerRack, leftTiles);
		//3. simulation
		MCNode *nodeToExplore = promisingNode;
		if (!promisingNode->child.empty())
		{
			srand(time(NULL));
			nodeToExplore = promisingNode->child.at(rand() % promisingNode->child.size());
		}
		int playOutResult = simulation(*nodeToExplore);
		//4. backpropagation
		backpropagation(nodeToExplore, playOutResult);
		iter++;
		now = clock();
	}

	MCNode* bestNode = tree.getChildWithMaxScore(&tree.getRoot());
	if (bestNode != NULL)
	{
		tree.setRoot(bestNode);
		return (&tree.getRoot())->data;
	}
	else
	{
		return SMove{};
	}
	
}

void MonteCarloTreeSearch::printOriginalTree()
{
	tree.printTree(*originalRootNode);
}

void MonteCarloTreeSearch::printOriginalTreeToFile(string filename)
{
	tree.printTreeLevelOrderToFile(*originalRootNode, false, filename);
}

MCTree& MonteCarloTreeSearch::getTree()
{
	return tree;
}

void MonteCarloTreeSearch::setPlayerScore(int val, int playerNum)
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

int MonteCarloTreeSearch::getPlayerScore(int playerNum)
{
	return (playerNum == 1) ? userScore : AIScore;
}

MonteCarloTreeSearch::~MonteCarloTreeSearch()
{
}
