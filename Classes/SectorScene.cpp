#include "SectorScene.h"
#include "Sector.h"

#include "Tracing.h"
#include "Engine.h"
#include "ShipPlayer.h"
#include "MonsterAI.h"
#include "BulletAI.h"
#include "Descriptor.h"
#include "Clickable.h"

#include "SectorObjectsFactory.h"

USING_NS_CC;
using namespace astral_game;

std::string SectorScene::NAME = "MainSectorLayer";

Scene* SectorScene::createScene()
{
	auto scene = Scene::create();

	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	scene->addChild(camera);

	auto layer = SectorScene::create();
	layer->setName(NAME);
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

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	scheduleUpdate();
	return true;
}

void SectorScene::update(float dt)
{
	Layer::update(dt);
	auto tempManagers = managers; //now we can edit the "managers" field inside update method!
	                              //but is it a good solution?
	for (auto & manager : tempManagers)
		manager->update(dt);
}

bool SectorScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return true;
}

void SectorScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto sector = getSector();
	Vec2 touchCoord = sector->convertToNodeSpace(touch->getLocation());

	if (touchCoord.length() <= sector->getRadius())
	{
		for (auto & child : sector->getChildren())
		{
			if (child->getUserObject() == nullptr) continue;
			auto clickable = dynamic_cast<Descriptor *>(child->getUserObject())->getProperty<Clickable>(PropertyTag::CLICKABLE);
			if (clickable != nullptr && clickable->click(touchCoord))
			{
				CCLOG("the monster was clicked!");
				break;
			}
		}
	}
}

Sector * SectorScene::getSector()
{
	return dynamic_cast<Sector *>(getChildByTag(TAGINT(LayerTag::SECTOR)));
}

void SectorScene::receiveNotification(Notification notification, Node * sender)
{
	for (auto & manager : managers)
		manager->receive(notification, sender);
	if (notification == Notification::AVAILABLE_INVALID)
	{
		for (auto iter = managers.begin(); iter != managers.end(); ++iter)
		{
			if ((*iter)->getWard() == sender)
			{
				managers.erase(iter);
				sender->runAction(RemoveSelf::create());
				break;
			}
		}
	}
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
	tracing->captureTarget(getSector()->getChildByTag(TAGINT(SectorTag::SHIP)));

	monster->setPosition(Vec2(SF(-400.0f), SF(-400.0f)));
	getSector()->addChild(monster);

	MonsterAI * monsterAI = new MonsterAI();
	monsterAI->initWithWard(monster);
	managers.push_back(std::shared_ptr<Manager>(monsterAI));
}

void SectorScene::createBullet(Node * sender, const Vec2 & position)
{
	auto bullet = SectorObjectsFactory::getInstance()->createBullet();
	bullet->setPosition(getSector()->convertToNodeSpace(sender->convertToWorldSpace(position)));
	bullet->setCameraMask((unsigned short)CameraFlag::USER1, true);
	auto engine = dynamic_cast<Engine *>(bullet->getComponent(Engine::NAME));
	auto target = dynamic_cast<Tracing *>(sender->getComponent(Tracing::NAME))->getTarget();
	engine->setMovDirection((target->getPosition() - sender->getPosition()).getNormalized());
	engine->setCurrMovVelocity(engine->getMaxMovVelocity());

	auto tracing = dynamic_cast<Tracing *>(bullet->getComponent(Tracing::NAME));
	tracing->captureTarget(target);

	BulletAI * bulletAI = new BulletAI();
	bulletAI->initWithWard(bullet);
	managers.push_back(std::shared_ptr<Manager>(bulletAI));

	getSector()->addChild(bullet);
}