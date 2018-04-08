#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cocos2d.h"
#include "Utils.h"
#include "Updatable.h"

namespace astral_game
{
	class Manager : public Updatable
	{
	public:
		Manager() : invalid(false) {}
		virtual ~Manager() = default;
	public:
		cocos2d::Node * getWard() { return ward; }
		virtual bool initWithWard(cocos2d::Node * ward) = 0;
		virtual void receive(Notification notification, cocos2d::Node * sender) = 0;
		void setInvalid() { invalid = true; }
		bool isInvalid() { return invalid; }
	protected:
		cocos2d::Node * ward;
	private:
		bool invalid;
	};
}

#endif //__MANAGER_H__