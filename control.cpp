#include "control.h"
using namespace Control;
#include "Tools.h"

void Control::ControlPredator::hunt(Fish &predator, int index_predator,  Fish &prey, int index_prey, double dt)
{
	vector<Point>& predator_position = predator.getPosition();//使用引用，可以修改元素
	vector<Point>& prey_position = prey.getPosition();
	if (predator.power[index_predator]<MINPOWER)
	{
		Control::wander(predator_position, index_predator, dt);
		predator.state[index_predator] = STATE_RECOVER;//恢复体力状态
		return;
	}
	predator.state[index_predator] = STATE_CONSUME;//消耗体力体力状态
	//predator.power[index_predator] -= 0.01;

	Point p1 = predator_position[index_predator],
		p2 = prey_position[index_prey];
	double d = disP2P(p1,p2);
	if (d < EAT_DISTANCE)//可吃范围
	{
//		system("pause");
		prey.deleteOneFish(index_prey);
	}
	else
	{
		double a = 1.5*A_FunPower(predator.power[index_predator],MINPOWER);
		//追捕
		double ax=0,ay=0;
		ax = p2.getX()-p1.getX();
		ay = p2.getY()-p1.getY();
		a_to_std(a,ax,ay);
		double a4x=0,a4y=0;
		BoidsControl::rule4(a4x,a4y,p1);
		ax = 0.5*ax + 2.5*a4x;
		ay = 0.5*ay + 2.5*a4y;
		double x,y,vx,vy;//当前点的坐标和方向
		p1.getXYVXVY(x,y,vx,vy);
		setNextPosition(x,y,vx,vy,ax,ay,dt);
		p1.setXYVXVY(x,y,vx,vy);
		predator_position[index_predator] = p1;
	}
}

void Control::ControlPrey::escape(Fish &predator, int index_predator,  Fish &prey, int index_prey, double dt)
{
	vector<Point>& predator_position = predator.getPosition();//使用引用，可以修改元素
	vector<Point>& prey_position = prey.getPosition();
	if (prey.power[index_prey]<MINPOWER)
	{
		Control::wander(prey_position, index_prey, dt);
		prey.state[index_prey] = STATE_RECOVER;//恢复体力状态
		return;
	}
	prey.state[index_prey] = STATE_CONSUME;//消耗体力体力状态
	//prey.power[index_prey] -= 0.01;

	Point p1 = predator_position[index_predator],
		p2 = prey_position[index_prey];
	double a = 0.5*A_FunPower(prey.power[index_prey],MINPOWER);
	//逃跑
	double ax,ay;
	ax = p2.getX()-p1.getX();
	ay = p2.getY()-p1.getY();
	a_to_std(a,ax,ay);
	double a4x=0,a4y=0;
	BoidsControl::rule4(a4x,a4y,p1);
	ax = 0.5*ax + 2.5*a4x;
	ay = 0.5*ay + 2.5*a4y;
	double x,y,vx,vy;//当前点的坐标和方向
	p2.getXYVXVY(x,y,vx,vy);
	setNextPosition(x,y,vx,vy,ax,ay,dt);
	p2.setXYVXVY(x,y,vx,vy);
	prey_position[index_prey] = p2;
}

//控制fish,更新鱼的位置和身体的大小
void Control::updateFish(Fish &predator, Fish &prey, double dt)
{
	vector<Point>& predator_position = predator.getPosition();
	int num_predator = predator_position.size();
	vector<Point>& prey_position = prey.getPosition();

	for (int i=0; i<num_predator; i++)
	{
		int index_prey;
		int round_prey = roundFish(predator_position[i],prey_position, index_prey);
		if (round_prey>0)
		{
			Control::ControlPredator::hunt(predator,i,prey,index_prey,dt);
		}
		else
		{
			Control::wander(predator_position, i, dt);//可以直接更改位置了，下面那句可以不用了
			//predator.setPosition(predator_position);
		}
	}
	int num_prey = prey_position.size();
	for (int i=0; i<num_prey; i++)
	{
		int index_predator;
		int round_predator = roundFish(prey_position[i],predator_position, index_predator);
		if (round_predator>0)
		{
			Control::ControlPrey::escape(predator,index_predator,prey,i,dt);
		}
		else
		{
			Control::wander(prey_position, i, dt);
		}
	}
}

//更新鱼的大小
void Control::updateBodySize(vector<double> &bodySize, double dt)
{
}

void Control::wander(vector<Point> &position, int index, double dt)
{
	BoidsControl::boidsAlgorithm(position, index, dt);
}

//检测周围的鱼,fishA中第index_A条鱼周围有多少条fishB,最近的一条fishB是index_B
int Control::roundFish(Point& fishA, vector<Point>& positionB, int& index_B)
{
	int roundNumFish=0;
	double minDistance=10000;
	index_B=0;
	Point p;
	int n=positionB.size();
	for (int i=0; i<n; i++)
	{
		p = positionB[i];
		double d = disP2P(fishA,p);
		if (d < VIEW_DISTANCE)
		{
			roundNumFish++;
			if (minDistance>d)
			{
				minDistance = d;
				index_B = i;
			}
		}
	}
	return roundNumFish;
}
