//Environment.h

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Point.h"
#include "Fish.h"
#include "control.h"

class Environment
{
private:
	Fish predator;
	Fish prey;

	double system_time;//生态系统时间
	double spawn_T;//产卵周期
	double spawn_time;//计时产卵

public:
	Environment():predator(Fish(1)),prey(Fish(10))
	{
		initEnvironment();
	}
	
	//初始化环境
	void initEnvironment()
	{
	}
	
	void updatePosition(double dt)
	{
		Control::updateFish(predator,prey,dt);
	}
	
	Fish& getPredator()
	{
		return predator;
	}

	Fish& getPrey()
	{
		return prey;
	}
};
#endif

