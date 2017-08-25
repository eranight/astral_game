#ifndef __UTILS_H__
#define __UTILS_H__

#define TAGINT(tag) static_cast<int>(tag)

namespace astral_game
{
	enum class Notification
	{
		HITTABLE_DEAD,
		COUNT
	};

	enum class PropertyTag
	{
		HITTABLE,
		COUNT
	};

	enum class LayerTag
	{
		SECTOR,
		SHIP,
		COUNT
	};

	enum class SectorTag
	{
		SHIP,
		MONSTER,
		PORTAL,
		ISLAND,
		COUNT
	};
}
	
#endif //__UTILS_H__