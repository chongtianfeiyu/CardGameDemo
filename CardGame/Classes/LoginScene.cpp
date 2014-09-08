#include "LoginScene.h"

#include "HelloWorldScene.h"
#define TAG_CHAT_BG 1
USING_NS_CC;


Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
void LoginScene::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		return true;
	};
	listener->onTouchEnded = CC_CALLBACK_2(LoginScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	m_iCurMsgIndex = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景
	auto lsBg = Sprite::create("storybg.png");
	lsBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	lsBg->setScaleX(visibleSize.width / 640);
	lsBg->setScaleY(visibleSize.height / 960);
	this->addChild(lsBg, 0, 0);
	//对话框
	auto chatBg = Sprite::create("chatbg.png");
	chatBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + chatBg->getContentSize().height / 2));
	chatBg->setScaleX(visibleSize.width / 640);
	chatBg->setScaleY(visibleSize.height / 960);
	this->addChild(chatBg, 1, TAG_CHAT_BG);

	//
	readStoryJson();
	showNextMsg();

	return true;
}
void LoginScene::readStoryJson()
{
	
	/*读取配置文件字符串数据 */
	std::string sData = FileUtils::getInstance()->getStringFromFile("story.json");

	/* 用于解析Json */
	storyroot.Parse<rapidjson::kParseDefaultFlags>(sData.c_str());

}
void LoginScene::showNextMsg()
{
	rapidjson::Value &datas = storyroot["datas"];

	int size = datas.Size();
	if (m_iCurMsgIndex > size) {
		return;
	}
	//走完故事，初始化数据，进入下一界面
	if (m_iCurMsgIndex == size)
	{
		std::string path = FileUtils::getInstance()->getWritablePath();
		path.append("myhero.json");//保存战斗英雄
		rapidjson::Document mhroot;
		mhroot.SetObject();
		rapidjson::Document::AllocatorType& allocator = mhroot.GetAllocator();
		rapidjson::Value array(rapidjson::kArrayType);
		rapidjson::Value mhperson1(rapidjson::kObjectType);

		mhperson1.AddMember("level", 1, allocator);//等级
		mhperson1.AddMember("exlevel", 0, allocator);//品介
		mhperson1.AddMember("type", 3, allocator);//类型
		mhperson1.AddMember("xp", 0, allocator);//经验
		mhperson1.AddMember("pos", 1, allocator);//位置
		mhperson1.AddMember("index", 0, allocator);//卡牌索引
		mhperson1.AddMember("zhuang0", 300000, allocator);//头盔
		mhperson1.AddMember("zhuang1", 400000, allocator);//盔甲
		mhperson1.AddMember("zhuang2", 500000, allocator);//武器
		mhperson1.AddMember("zhuang3", 600000, allocator);//宝物
		mhperson1.AddMember("zhuang4", 700000, allocator);//鞋子
		mhperson1.AddMember("zhuang5", 800000, allocator);//坐骑
		array.PushBack(mhperson1, allocator);
		rapidjson::Value mhperson2(rapidjson::kObjectType);
		mhperson2.AddMember("exlevel", 1, allocator);
		mhperson2.AddMember("exlevel", 0, allocator);//品介
		mhperson2.AddMember("exlevel", 108, allocator);
		mhperson2.AddMember("exlevel", 0, allocator);
		mhperson2.AddMember("exlevel", 2, allocator);
		mhperson2.AddMember("exlevel", 1, allocator);
		mhperson2.AddMember("zhuang0", 300000, allocator);//头盔
		mhperson2.AddMember("zhuang1", 400000, allocator);//盔甲
		mhperson2.AddMember("zhuang2", 500000, allocator);//武器
		mhperson2.AddMember("zhuang3", 600000, allocator);//宝物
		mhperson2.AddMember("zhuang4", 700000, allocator);//鞋子
		mhperson2.AddMember("zhuang5", 800000, allocator);//坐骑
		array.PushBack(mhperson2, allocator);

		mhroot.AddMember("mhjson", array, allocator);
		rapidjson::StringBuffer  buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		mhroot.Accept(writer);
		
		//创建一个文件指针
		//路径、模式
		FILE* mhfile = fopen(path.c_str(), "wb");
		if (mhfile)
		{
			fputs(buffer.GetString(), mhfile);
			fclose(mhfile);
		}
		SaveZhuangBei();//保存装备
		//SaveKaPai();//保存卡牌	
		auto scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(scene);
		//SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene, true);
		return;
	}

	std::string name = datas[m_iCurMsgIndex]["name"].GetString();
	std::string msg = datas[m_iCurMsgIndex]["msg"].GetString();
	std::string strpic = datas[m_iCurMsgIndex]["picture"].GetString();
	//清空信息
	auto chatBG = (Sprite*)this->getChildByTag(TAG_CHAT_BG);
	chatBG->removeAllChildrenWithCleanup(true);
	Size bgSize = chatBG->getContentSize();
	/* 人物名字 */
	/* 人物名字 */
	auto nameLab = LabelTTF::create(name.c_str(), "Arial", 32);
	nameLab->setPosition(Vec2(bgSize.width * 0.2f, bgSize.height * 0.9f));
	nameLab->setColor(Color3B::RED);
	chatBG->addChild(nameLab, 1);
	/*

	TTFConfig ttfConfigname("fonts/hwls.ttf", 32);
	auto nameLab = Label::createWithTTF(ttfConfigname, name.c_str(), TextHAlignment::CENTER, bgSize.width);
	nameLab->setTextColor(Color4B::RED);
	nameLab->setPosition(Vec2(bgSize.width * 0.2f, bgSize.height * 0.9f));
	chatBG->addChild(nameLab, 1);
	*/
	//test
	



	/* 对话内容 */
	auto msgLab = LabelTTF::create(msg.c_str(), "Arial", 32, CCSize(300, 0), kCCTextAlignmentLeft);
	msgLab->setPosition(Vec2(bgSize.width / 2 - 120, bgSize.height * 0.4f));
	msgLab->setColor(Color3B::BLUE);
	//msgLab->setDimensions(CCSizeMake(bgSize.width * 0.55f, 0));
	//msgLab->setAnchorPoint(ccp(0, 0.5f));
	chatBG->addChild(msgLab, 1);
	/*
	TTFConfig ttfConfigmsg("fonts/hwfs.ttf", 32);
	auto msgLab = Label::createWithTTF(ttfConfigmsg, msg.c_str(), TextHAlignment::LEFT, 300);
	msgLab->setPosition(Vec2(bgSize.width / 2 - 120, bgSize.height * 0.4f));
	msgLab->setTextColor(Color4B::BLUE);
	chatBG->addChild(msgLab, 1);
	*/
	/* 人物图片 */
	auto actorSp = Sprite::create(strpic.c_str());
	Size actorSize = actorSp->getContentSize();
	actorSp->setPosition(Vec2(bgSize.width - actorSize.width / 2, actorSize.height / 2));
	chatBG->addChild(actorSp, 1);

	m_iCurMsgIndex++;

}
void LoginScene::SaveZhuangBei()
{



	std::string path = FileUtils::getInstance()->getWritablePath();
	path.append("myzhuangbei.json");//保存战斗英雄
	rapidjson::Document zbroot;
	zbroot.SetObject();
	rapidjson::Document::AllocatorType& allocator = zbroot.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	rapidjson::Value zbperson1(rapidjson::kObjectType);
	zbperson1.AddMember("level", 1, allocator);//等级
	zbperson1.AddMember("exlevel", 0, allocator);//品介
	zbperson1.AddMember("type", 301, allocator);//类型
	zbperson1.AddMember("index", 0, allocator);//卡牌索引
	zbperson1.AddMember("user", -1, allocator);//哪个英雄装备
	array.PushBack(zbperson1, allocator);

	rapidjson::Value zbperson2(rapidjson::kObjectType);
	zbperson2.AddMember("level", 1, allocator);
	zbperson2.AddMember("exlevel", 0, allocator);//品介
	zbperson2.AddMember("type", 401, allocator);
	zbperson2.AddMember("index", 1, allocator);
	zbperson2.AddMember("user", -1, allocator);//哪个英雄装备
	array.PushBack(zbperson2, allocator);

	rapidjson::Value zbperson3(rapidjson::kObjectType);
	zbperson3.AddMember("level", 1, allocator);
	zbperson3.AddMember("exlevel", 0, allocator);//品介
	zbperson3.AddMember("type", 501, allocator);//公孙胜武器七星剑
	zbperson3.AddMember("index", 2, allocator);
	zbperson3.AddMember("user", -1, allocator);//哪个英雄装备
	array.PushBack(zbperson3, allocator);

	rapidjson::Value zbperson4(rapidjson::kObjectType);
	zbperson4.AddMember("level", 1, allocator);
	zbperson4.AddMember("exlevel", 0, allocator);//品介
	zbperson4.AddMember("type", 601, allocator);//
	zbperson4.AddMember("index", 3, allocator);
	zbperson4.AddMember("user", -1, allocator);//哪个英雄装备
	array.PushBack(zbperson4, allocator);

	rapidjson::Value zbperson5(rapidjson::kObjectType);
	zbperson5.AddMember("level", 1, allocator);
	zbperson5.AddMember("exlevel", 0, allocator);//品介
	zbperson5.AddMember("type", 701, allocator);//
	zbperson5.AddMember("index", 4, allocator);
	zbperson5.AddMember("user", -1, allocator);//哪个英雄装备
	array.PushBack(zbperson5, allocator);

	zbroot.AddMember("mzjson", array, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	zbroot.Accept(writer);

	//创建一个文件指针
	//路径、模式
	FILE* mhfile = fopen(path.c_str(), "wb");
	if (mhfile)
	{
		fputs(buffer.GetString(), mhfile);
		fclose(mhfile);
	}


}

void LoginScene::onTouchEnded(Touch *pTouch, Event *pEvent)
{

	showNextMsg();
}




