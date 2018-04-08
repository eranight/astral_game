#ifndef __UTILS_H__
#define __UTILS_H__

#define TAGINT(tag) static_cast<int>(tag)
#define SF(num) num / Director::getInstance()->getContentScaleFactor()

namespace astral_game
{
	enum class Notification
	{
		HITTABLE_DEAD,
		AVAILABLE_ENABLE,
		AVAILABLE_DISABLE,
		AVAILABLE_INVALID,
		COUNT
	};

	enum class PropertyTag
	{
		HITTABLE,
		AVAILABLE,
		CLICKABLE,
		COUNT
	};

	enum class LayerTag
	{
		SECTOR,
		COUNT
	};

	enum class SectorTag
	{
		SHIP,
		MONSTER,
		PORTAL,
		ISLAND,
		BULLET,
		COUNT
	};

	enum class SkillTag
	{
		CANNON,
		COUNT
	};

}
	
#endif //__UTILS_H__