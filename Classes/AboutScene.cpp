#include "AboutScene.h"
#include "MenuScene.h"

CCScene *AboutScene::scene()
{
	//initialize scene and layer
	CCScene *scene = CCScene::create();
	AboutScene *layer = AboutScene::create();
	//adding layer to the scene
	scene->addChild(layer);
	//return scene with layer in it
	return scene;
}

bool AboutScene::init()
{
	//initialize all components to the screen
	CCSprite *_background;
	CCSprite *_about;
	CCSize screenSize = CCDirector::sharedDirector()->getWinSizeInPixels();
	
	//background image
	_background = CCSprite::create("bg.png");
	_background->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	addChild(_background,0);

	//title
	CCSprite *_title = CCSprite::create("title.png");
	_title->setPosition(ccp(screenSize.width/2,screenSize.height * 80/100));
	addChild(_title,1);
	
	//about texts
	_about = CCSprite::create("about.png");
	_about->setPosition(ccp(screenSize.width/2,screenSize.height * 0.5));
	addChild(_about,1);

	//exit button (back to main menu) and set the callback
	CCMenuItem *_exitButton = CCMenuItemImage::create("exit_btn.png","exit_btn.png",this,menu_selector(AboutScene::menuExitCallBack));
	_exitButton->setPosition(ccp(screenSize.width * 0.9 , screenSize.height * 0.9));


	//implement exitButton as a menu
	CCMenu *_menu = CCMenu::create(_exitButton,NULL);
	_menu->setPosition(Point::ZERO);
	addChild(_menu,1);
	
	
	return true;
}

//action on exit button clicked
void AboutScene::menuExitCallBack(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,MenuScene::scene()) );
	
}
