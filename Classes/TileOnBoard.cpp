#include "TileOnBoard.h"
#include "GameHumanScene.h"

TileOnBoard::TileOnBoard(void)
{
		position = -1;
		isSet = false;
		isBlankTile = false;

		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();

		listener->onTouchBegan = CC_CALLBACK_2(TileOnBoard::ccTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(TileOnBoard::ccTouchEnded, this);

		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		//area = NULL;
}

TileOnBoard::~TileOnBoard(void)
{
}

Rect TileOnBoard::rect()
{
	CCSize s = getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

TileOnBoard* TileOnBoard::TileOnBoardWithTexture(CCTexture2D* aTexture)
{
    TileOnBoard* pTileOnBoard = new TileOnBoard();
    pTileOnBoard->initWithTexture( aTexture );
    pTileOnBoard->autorelease();

    return pTileOnBoard;
}


bool TileOnBoard::initWithTexture(CCTexture2D* aTexture)
{
    if( CCSprite::initWithTexture(aTexture) ) 
    {
        m_state = kTileOnBoardStateUngrabbed;
    }

    
    return true;
}

void TileOnBoard::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();

 //   pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void TileOnBoard::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
  //  pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}    

bool TileOnBoard::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool TileOnBoard::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

    if (m_state != kTileOnBoardStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    m_state = kTileOnBoardStateGrabbed;
	if(gameType == 1 && isSet == false)
	{
		if(position != -1)
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(oriTile.c_str()));
			((GameHumanScene*)area)->putTileToRack(position,getTag());
			((GameHumanScene*)area)->closeBlank();
			letter = '-';
			position = -1;
			isBlankTile = false;
			((GameHumanScene*)area)->setBlankTag(-1);
		}
		else if(((GameHumanScene*)area)->getHoldTile() != -1)
		{
			changeTileImage(((GameHumanScene*)area)->getHoldTile());
			if(((GameHumanScene*)area)->getHoldTile() < 26)
			{
				((GameHumanScene*)area)->setHoldTile(-1);
				position = ((GameHumanScene*)area)->getHoldPosition();
				((GameHumanScene*)area)->takeTileFromRack(position,getTag());
				letter = ((GameHumanScene*)area)->getLetterOnRack(position);
				isBlankTile = false;
				((GameHumanScene*)area)->setBlankTag(-1);
			}
			else
			{
				if(((GameHumanScene*)area)->getBlankTag() == -1)
				{
					((GameHumanScene*)area)->setBlankTag(getTag());
					((GameHumanScene*)area)->changeBlank();
					((GameHumanScene*)area)->setHoldTile(-1);
					position = ((GameHumanScene*)area)->getHoldPosition();
					((GameHumanScene*)area)->takeTileFromRack(position,getTag());
					isBlankTile = true;
				}
			}
		}
	}
    return true;
}



CCObject* TileOnBoard::copyWithZone(CCZone *pZone)
{
    this->retain();
    return this;
}

void TileOnBoard::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kTileOnBoardStateGrabbed, "TileOnBoard - Unexpected state!");    
    m_state = kTileOnBoardStateUngrabbed;
	
	//area->addHighligth(this->getPositionX(),this->getPositionY(),CCInteger::create(getTag()),thingId);

	
} 

void TileOnBoard::touchDelegateRetain()
{
    this->retain();
}

void TileOnBoard::touchDelegateRelease()
{
    this->release();
}

void TileOnBoard::setArea(CCLayer* scene)
{
	area = scene;
}

void TileOnBoard::setGameType(int gt)
{
	gameType = gt;
}

void TileOnBoard::setId(CCInteger* id)
{
	thingId = id;
}


CCInteger* TileOnBoard::getId()
{
	return thingId;
}

void TileOnBoard::setOriTile(string file)
{
	oriTile = file;
}

void TileOnBoard::setOrderFromRack(int p)
{
	position = p;
}

void TileOnBoard::setTileType(int tt)
{
	tileType = tt;
}

int TileOnBoard::getTileType()
{
	if (isSet != false)
	{
		tileType = 1;
	}
	return tileType;
}

void TileOnBoard::setIsSetTile(bool set)
{
	isSet = set;
}

bool TileOnBoard::getSetStatus()
{
	return isSet;
}

void TileOnBoard::setLetter(char l)
{
	letter = l;
}

char TileOnBoard::getLetter()
{
	return letter;
}

void TileOnBoard::setIsBlankTile(bool b)
{
	isBlankTile = b;
}

bool TileOnBoard::getBlankTileStatus()
{
	return isBlankTile;
}

void TileOnBoard::changeTileImage(int index)
{
	char* _alphabetSmall[27] = {"A_small.png","B_small.png","C_small.png","D_small.png","E_small.png","F_small.png","G_small.png","H_small.png","I_small.png","J_small.png","K_small.png","L_small.png","M_small.png","N_small.png","O_small.png","P_small.png","Q_small.png","R_small.png","S_small.png","T_small.png","U_small.png","V_small.png","W_small.png","X_small.png","Y_small.png","Z_small.png","blank_small.png"}; 
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(_alphabetSmall[index]));
}

void TileOnBoard::changeBlankTileImage(int index)
{
	char* fileName[26] = {"A_blank.png","B_blank.png","C_blank.png","D_blank.png","E_blank.png","F_blank.png","G_blank.png","H_blank.png","I_blank.png","J_blank.png","K_blank.png","L_blank.png","M_blank.png","N_blank.png","O_blank.png","P_blank.png","Q_blank.png","R_blank.png","S_blank.png","T_blank.png","U_blank.png","V_blank.png","W_blank.png","X_blank.png","Y_blank.png","Z_blank.png"}; 
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(fileName[index]));
}

void TileOnBoard::takeBack()
{
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(oriTile.c_str()));
	((GameHumanScene*)area)->putTileToRack(position,getTag());
	((GameHumanScene*)area)->closeBlank();
	letter = '-';
	position = -1;
	isBlankTile = false;
	((GameHumanScene*)area)->setBlankTag(-1);
}

int TileOnBoard::getTilePosition()
{
	return position;
}