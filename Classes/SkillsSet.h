#ifndef __SKILLSSET_H__
#define __SKILLSSET_H__

#include <vector>
#include <memory>

#include "Controller.h"
#include "Skill.h"

namespace astral_game
{
	class SkillsSet : public Controller
	{
	protected:
		SkillsSet() = default;
	public:
		static SkillsSet * create();
		bool init() override;
		void update(float dt) override;
	public:
		std::vector<std::shared_ptr<Skill>> vectorOfSkills;
	};
}


#endif //__SKILLSSET_H__