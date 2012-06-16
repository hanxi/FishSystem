//ShowEnvironment.cpp

#include "ShowEnvironment.h"
#include <cmath>
const double pi=3.14159;

//////////////////////////////////////////////////////
//计算鱼的位置
/////////////////////////////////////////////////////
void ShowEnvironment::Frame_Environment(double in_dt)
{
	dt = in_dt;
	environment.updatePosition(20*dt);
}

///////////////////////////////////////////////////////
//显示鱼
///////////////////////////////////////////////////////
void ShowEnvironment::Render_Environment()
{
	//先载入背景图
	bgspr->RenderStretch(0,0,win_width,win_height);
	Fish& predator = environment.getPredator();
	Fish& prey = environment.getPrey();
	vector<double>& predator_bodySize = predator.getBodySize();
	vector<Point>& predator_position = predator.getPosition();
	showFish(predator_bodySize,predator_position,predator_ani);
	vector<double>& prey_bodySize = prey.getBodySize();
	vector<Point>& prey_position = prey.getPosition();
	showFish(prey_bodySize,prey_position,prey_ani);
}

void ShowEnvironment::showFish(const vector<double>& bodySize, const vector<Point>& position, hgeAnimation* fish_ani)
{
	int n=position.size();
	for (int i=0; i<n; i++)
	{
		double x,y,vx,vy;
		Point p = position[i];
		p.getXYVXVY(x,y,vx,vy);
		double a;
		double f = vx/(sqrt(vx*vx+vy*vy));
		if (vy<0)
		{
			a=2*pi-acos(f);
		}
		else if (vy>0)
		{
			a=acos(f);
		}
		fish_ani->RenderEx(x,y,a+pi,bodySize[i],bodySize[i]);
	}
	fish_ani->Update(dt*5);
}
