#include "Notifier.h"
#include "SectorScene.h"

USING_NS_CC;
using namespace astral_game;

void Notifier::notify(Notification notification, cocos2d::Node * node)
{
	//Sector::getSector()->broadCastNotifyExclude(notification, node)
	auto sectorScene = dynamic_cast<SectorScene *>(Director::getInstance()->getRunningScene()->getChildByName(SectorScene::NAME));
	sectorScene->receiveNotification(notification, node);
}