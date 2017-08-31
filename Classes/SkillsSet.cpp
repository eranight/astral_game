#include "SkillsSet.h"

#include "Skill.h"

USING_NS_CC;
using namespace astral_game;

const std::string SkillsSet::NAME = "skillsset";

SkillsSet * SkillsSet::create()
{
	auto pRet = new (std::nothrow) SkillsSet();
	if (pRet != nullptr && pRet->init())
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool SkillsSet::init()
{
	if (!Controller::init(NAME))
		return false;
	return true;
}

void SkillsSet::update(float dt)
{
	for (auto & skill : vectorOfSkills)
		skill->update(dt);
}