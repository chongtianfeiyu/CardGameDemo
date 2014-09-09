#include "SceneGame.h"

SceneGame::SceneGame(int level)
{


	init(level);
	
	mHudLayer = new HomeLayer();
	mHudLayer->setPosition(Vec2(0, 0));
	mHudLayer->autorelease();
	this->addChild(mHudLayer, 1, HOMETAG);
	

}
bool SceneGame::init(int level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景
	auto bg = Sprite::create("homebg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setScaleX(visibleSize.width / 640);
	bg->setScaleY(visibleSize.height / 960);
	addChild(bg);
	//标题
	auto tile = Sprite::create("tile.png");
	tile->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 80 - tile->getContentSize().height / 2));
	addChild(tile);
	//菜单按钮
	
	auto Itemhome = MenuItemImage::create("HomeNormal.png", "HomeSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	auto Itemone = MenuItemImage::create("OneNormal.png", "OneSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	auto Itemtwo = MenuItemImage::create("TwoNormal.png", "TwoSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	auto Itemthree = MenuItemImage::create("ThreeNormal.png", "ThreeSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	auto Itemfour = MenuItemImage::create("FourNormal.png", "FourSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	auto Itemfive = MenuItemImage::create("FiveNormal.png", "FiveSelected.png",
		CC_CALLBACK_1(SceneGame::menuSelectCallback, this));
	Itemhome->setTag(0);
	Itemone->setTag(1);
	Itemtwo->setTag(2);
	Itemthree->setTag(3);
	Itemfour->setTag(4);
	Itemfive->setTag(5);
	auto menu = Menu::create(Itemhome, Itemone, Itemtwo, Itemthree, Itemfour, Itemfive, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + Itemhome->getContentSize().height / 2));
	menu->setTag(888);
	this->addChild(menu, 1000);
	return true;
}
void SceneGame::menuSelectCallback(Ref *sender){

}
SceneGame::~SceneGame()
{
}