#include "SectorScene.h"
#include "Sector.h"
#include "Utils.h"

#include "Engine.h"
#include "Hittable.h"
#include "Descriptor.h"
#include "ShipPlayer.h"

USING_NS_CC;
using namespace astral_game;

Scene* SectorScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SectorScene::create();
	scene->addChild(layer);
	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	scene->addChild(camera);
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
	sector->setTag(LayerTag::SECTOR);
	sector->setPosition(origin + visibleSize * 0.5f);
	this->addChild(sector, 0);

	createShip();

	sector->setCameraMask((unsigned short)CameraFlag::USER1, true); //last step

	scheduleUpdate();
	return true;
}

Sector * SectorScene::getSector()
{
	return dynamic_cast<Sector *>(getChildByTag(LayerTag::SECTOR));
}

void SectorScene::createShip()
{
	Node * ship = Node::create();
	Sprite * shipSprite = Sprite::create("ship.png");
	ship->addChild(shipSprite);
	Descriptor * descriptor = Descriptor::create(ship);
	ship->setUserObject(descriptor);
	descriptor->addProperty<Hittable>(500);
	Engine * engine = Engine::create(); //FIXME: add max velocity as argument to the create method!
	engine->setMaxMovVelocity(SF(140.0f));
	engine->setRotVelocity(SF(70.0f));
	ship->addComponent(engine);
	ship->setPosition(Vec2::ZERO);
	this->getChildByTag(LayerTag::SECTOR)->addChild(ship);

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
			shipPlayer->setVelocity(SF(70.0f));
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