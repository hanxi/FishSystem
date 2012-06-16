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

	double system_time;//��̬ϵͳʱ��
	double spawn_T;//��������
	double spawn_time;//��ʱ����

public:
	Environment():predator(Fish(1)),prey(Fish(10))
	{
		initEnvironment();
	}
	
	//��ʼ������
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

