#include "MCTree.h"
#include <math.h> 
#include <algorithm> 

using namespace std;
class UCT
{
	public :

		//UCT value calculation. If node hasn't been visited, set to maximum int number, 1.41 = sqrt(2)
		static double UCTValue(int totalVisit, double nodeWinScore, int nodeVisit)
		{
			if (nodeVisit == 0)
				return INT_MAX;
			return (nodeWinScore / (double)nodeVisit) + (1.41 * sqrt(log(totalVisit) / (double)nodeVisit));
		}

		//find maximum uct value from same level child nodes where MCNode node = parent node
		static MCNode * findBestNodeWithUCT(MCNode node)
		{
			int parentVisit = node.visitCount;
			if (node.child.size() == 0)
				return NULL;
			MCNode *max = node.child.at(0);
			for (MCNode *move : node.child)
			{
				move->uct = UCTValue(parentVisit, move->winScore, move->visitCount);
				max->uct = UCTValue(parentVisit, max->winScore, max->visitCount);
				if( move->uct > max->uct) 
					max = move;
			}
			return max;
		}
};