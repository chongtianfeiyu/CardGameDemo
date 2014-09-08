#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include "json/rapidjson.h"  
#include "json/document.h" 
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
USING_NS_CC;

class LoginScene :public Layer{
public:
	bool init();
	static Scene * createScene();
	CREATE_FUNC(LoginScene);
	virtual void onEnter();
	//virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//virtual void TouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
	/* 解析Json后的根节点 */
//	Json::Value storyroot;
	rapidjson::Document storyroot;
	int m_iCurMsgIndex;
	void readStoryJson();
	void showNextMsg();
	void SaveZhuangBei();
	void SaveKaPai();

};
#endif //__LOGIN_SCENE_H__


