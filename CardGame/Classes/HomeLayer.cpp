#include "HomeLayer.h"



HomeLayer::HomeLayer()
{
	isBeingUsed = false;
	init();
}


HomeLayer::~HomeLayer()
{
}
bool HomeLayer::init()
{
	if (!Layer::init())
	return false;
	this->setKeypadEnabled(true);
	//位置
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*UI************************************************************/
	Layout * ul = Layout::create();
	this->addChild(ul);
    //等级框
	ImageView *image = ImageView::create("level.png");
	image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 240));
	ul->addChild(image);
	//
	levellabel = Text::create();
	levellabel->setFontSize(48);
	levellabel->setString("0");
	levellabel->setPosition(Vec2(image->getPosition().x + 20, image->getPosition().y - 10));
	ul->addChild(levellabel);
	auto label = LabelTTF::create("HELLO", "Arial", 32);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);
	return true;
	
}