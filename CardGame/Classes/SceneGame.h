#ifndef _SCENEGAME_SCENE_H_
#define _SCENEGAME_SCENE_H_
#include "cocos2d.h"
#include "HomeLayer.h"
#define HOMETAG   101


USING_NS_CC;
class SceneGame : public Scene
{
public:
	SceneGame(int level);
	bool init(int level);
	~SceneGame();

private:
	HomeLayer* mHudLayer;
	//GroupLayer* mGroupLayer;
	//HeroLayer* mHeroLayer;
	//GameMapLayer *mMap;
	//TuJianLayer *mTujian;
	//shopLayer *mStoreLayer;
	cocos2d::Sprite *m_map1;
	cocos2d::Sprite *m_map2;
	void broadcastInput(float dt);
	int mlevel;
	int scrollwidth;
	void setMenuVisible(Ref *sender);
	void menuSelectCallback(Ref *sender);
	void getCoin(Ref *sender);

};

#endif