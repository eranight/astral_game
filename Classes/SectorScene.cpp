#include "SectorScene.h"
#include "Sector.h"
#include "Utils.h"

#include "Tracing.h"
#include "ShipPlayer.h"
#include "MonsterAI.h"

#include "SectorObjectsFactory.h"

USING_NS_CC;
using namespace astral_game;

Scene* SectorScene::createScene()
{
	auto scene = Scene::create();

	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	scene->addChild(camera);

	auto layer = SectorScene::create();
	scene->addChild(layer);
	dynamic_cast<Sector *>(layer->getChildByTag(TAGINT(LayerTag::SECTOR)))->setShipCamera(camera);

	return scene;
}

bool SectorScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sector = Sector::create(SF(1024.0f));
	sector->setTag(TAGINT(LayerTag::SECTOR));
	sector->setPosition(origin + visibleSize * 0.5f);
	this->addChild(sector);

	createShip();
	createMonster();

	sector->setCameraMask((unsigned short)CameraFlag::USER1, true); //last step

	scheduleUpdate();
	return true;
}

void SectorScene::update(float dt)
{
	Layer::update(dt);
	for (auto & manager : managers)
		manager->update(dt);
}

Sector * SectorScene::getSector()
{
	return dynamic_cast<Sector *>(getChildByTag(TAGINT(LayerTag::SECTOR)));
}

void SectorScene::createShip()
{
	Node * ship = SectorObjectsFactory::getInstance()->createShip();
	ship->setPosition(Vec2::ZERO);
	ship->setTag(TAGINT(SectorTag::SHIP));
	this->getChildByTag(TAGINT(LayerTag::SECTOR))->addChild(ship);

	ShipPlayer * shipPlayer = new ShipPlayer();
	shipPlayer->initWithWard(ship);
	managers.push_back(std::shared_ptr<Manager>(shipPlayer));

	auto eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyPressed = [shipPlayer](EventKeyboard::KeyCode keyCode, Event * event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (shipPlayer->getRotationDirection() == 0.0f) shipPlayer->setLeftRotation();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (shipPlayer->getRotationDirection() == 0.0f) shipPlayer->setRightRotation();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			shipPlayer->setVelocity(shipPlayer->getMaxVelocity() * 0.5f);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			shipPlayer->turnOnAngle(shipPlayer->getAngle() + 90.0f);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			shipPlayer->setVelocity(0.0f);
			break;
			break;
		default:
			break;
		}
	};

	eventListenerKeyboard->onKeyReleased = [shipPlayer](EventKeyboard::KeyCode keyCode, Event * event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (shipPlayer->getRotationDirection() == -1.0f) shipPlayer->resetRotDirection();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (shipPlayer->getRotationDirection() == 1.0f) shipPlayer->resetRotDirection();
			break;
		}
	};
	_eventDispatcher->addEventListenerWithFixedPriority(eventListenerKeyboard, 30);
}

void SectorScene::createMonster()
{
	auto monster = SectorObjectsFactory::getInstance()->createMonster();
	auto tracing = dynamic_cast<Tracing *>(monster->getComponent(Tracing::NAME));
	tracing->captureTarget(this->getChildByTag(TAGINT(LayerTag::SECTOR))->getChildByTag(TAGINT(SectorTag::SHIP)));

	monster->setPosition(Vec2(SF(-400.0f), SF(-400.0f)));
	this->getChildByTag(TAGINT(LayerTag::SECTOR))->addChild(monster);

	MonsterAI * monsterAI = new MonsterAI();
	monsterAI->initWithWard(monster);
	managers.push_back(std::shared_ptr<Manager>(monsterAI));
}