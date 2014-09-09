#include "HomeLayer.h"


HomeLayer::HomeLayer()
{
	init();
}


HomeLayer::~HomeLayer()
{
}
bool HomeLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto label = LabelTTF::create("HELLO", "Arial", 32);


	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);
	return true;
}