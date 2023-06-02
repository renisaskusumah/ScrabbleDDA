#include "MenuScene.h"
#include "GameScene.h"
#include "GameHumanScene.h"
#include "HelpScene.h"
#include "AboutScene.h"

USING_NS_CC;


Scene *MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	

	Size screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto _background = Sprite::create("bg.png");

	_background->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	addChild(_background,0);

	//title
	auto _title = Sprite::create("title.png");
	_title->setPosition(ccp(screenSize.width/2,screenSize.height * 80/100));
	addChild(_title,1);

	//membuat button
	/*CCMenuItem *_aiButton = CCMenuItemImage::create("ai_btn.png","ai_hover.png",this,menu_selector(MenuScene::menuAiCallBack));
	_aiButton->setPosition(ccp(screenSize.width/2,screenSize.height * 40 /100));*/
	CCMenuItem *_playButton = CCMenuItemImage::create("play_btn.png","play_hover.png",this,menu_selector(MenuScene::menuPlayCallBack));
	_playButton->setPosition(ccp(screenSize.width/2,screenSize.height * 0.55 ));
	CCMenuItem *_helpButton = CCMenuItemImage::create("help_btn.png","help_hover.png",this,menu_selector(MenuScene::menuHelpCallBack));
	_helpButton->setPosition(ccp(_playButton->getPositionX() - (_playButton->getContentSize().width * 0.50),screenSize.height * 0.45 ));
	CCMenuItem *_aboutButton = CCMenuItemImage::create("about_btn.png","about_hover.png",this,menu_selector(MenuScene::menuAboutCallBack));
	_aboutButton->setPosition(ccp(_helpButton->getPositionX() + (_helpButton->getContentSize().width * 1.1),screenSize.height * 0.45 ));


	//membuat menu
	auto _menu = Menu::create(_playButton,_helpButton,_aboutButton,NULL);
	_menu->setPosition(Point::ZERO);
	addChild(_menu,1);
	
	
	return true;
}

void MenuScene::menuAiCallBack(CCObject *pSender)
{
	//CCDirector::sharedDirector()->replaceScene(GameScene::scene());
	//CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,AiMenuScene::scene()) );
	
}



void MenuScene::menuPlayCallBack(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,GameHumanScene::scene()) );
}

void MenuScene::menuHelpCallBack(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,HelpScene::scene()) );
}

void MenuScene::menuAboutCallBack(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,AboutScene::scene()) );
}