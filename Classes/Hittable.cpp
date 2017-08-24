#include "Hittable.h"

using namespace astral_game;

Hittable::Hittable(int maxHp) :
Property(PropertyTag::HITTABLE), maxHp(maxHp), currentHp(maxHp)
{
}

void Hittable::impactDamage(int damage)
{
	currentHp -= damage;
	if (currentHp < 0)
	{
		currentHp = 0;
		if (onDead != nullptr) onDead();
		notify(Notification::HITTABLE_DEAD, getOwner());
	}
}

void Hittable::impactHealing(int healing)
{
	currentHp += healing;
	if (currentHp > maxHp)
		currentHp = maxHp;
}