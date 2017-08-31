#ifndef __SKILLSSET_H__
#define __SKILLSSET_H__

#include <vector>
#include <memory>
#include <algorithm>

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
		static const std::string NAME;
	public:
		template <typename T>
		std::shared_ptr<T> getSkill(SkillTag skillTag)
		{
			auto iter = std::find_if(vectorOfSkills.begin(), vectorOfSkills.end(),
				[skillTag](const std::shared_ptr<Skill> & skillPtr) { return skillPtr->getTag() == skillTag; });
			if (iter != vectorOfSkills.end())
				return std::dynamic_pointer_cast<T>(*iter);
			return nullptr;
		}
		template<typename T, typename... Args>
		void addSkill(Args && ... args)
		{
			auto skillPtr = std::make_shared<T>(args...);
			vectorOfSkills.push_back(skillPtr);
		}
	private:
		std::vector<std::shared_ptr<Skill>> vectorOfSkills;
	};
}


#endif //__SKILLSSET_H__