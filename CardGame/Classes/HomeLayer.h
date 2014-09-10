#ifndef _HOMELAYER_H_
#define _HOMELAYER_H_
#include "cocos2d.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HomeLayer : public Layer
{
public:
	HomeLayer();
	~HomeLayer();
	bool init();
	bool isBeingUsed;
private:
	Text *levellabel;
};

#endif