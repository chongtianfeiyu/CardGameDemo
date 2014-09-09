#include "AppDelegate.h"
#include "LoginScene.h"
#include "SceneGame.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.height / visibleSize.width;

	/* 设置Win32屏幕大小为480X800, */
	//glview->setFrameSize(400, 600 );

	/* 简单的屏幕适配，按比例拉伸，可能有黑边 */
	glview->setDesignResolutionSize(640, 640 * x, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	//if first
	bool bfirst = UserDefault::getInstance()->getBoolForKey("first", false);
	if (!bfirst)
	{
		UserDefault::getInstance()->setBoolForKey("first", true);
		UserDefault::getInstance()->flush();
		auto scene = LoginScene::createScene();
		// run
		director->runWithScene(scene);
	}
	else
	{
		auto pScene = new SceneGame(0);
		director->runWithScene(pScene);
	}

 

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
