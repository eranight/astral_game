#include "SectorScene.h"
#include "Sector.h"
#include "Utils.h"

#include "Engine.h"
#include "Hittable.h"
#include "Descriptor.h"

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
	ship->addComponent(Engine::create());
	ship->setPosition(Vec2::ZERO);
	this->getChildByTag(LayerTag::SECTOR)->addChild(ship);
}