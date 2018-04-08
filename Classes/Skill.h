#ifndef __SKILL_H__
#define __SKILL_H__

#include "Utils.h"
#include "Updatable.h"

namespace astral_game
{
	class Skill : public Updatable
	{
	public:
		Skill(SkillTag tag) : tag(tag) {}
		SkillTag getTag() { return tag; }
	private:
		SkillTag tag;
	};
}

#endif //__SKILL_H__