//control.h

#ifndef CONTROL_H
#define CONTROL_H
#include <algorithm>
#include "BoidsControl.h"
#include "Fish.h"
#include "Point.h"

namespace Control
{
	namespace ControlPredator
	{
		void hunt(Fish &predator, int index_predator,  Fish &prey, int index_prey, double dt);
	}
	namespace ControlPrey
	{
		void escape(Fish &predator, int index_predator,  Fish &prey, int index_prey, double dt);
	}
	//控制fish,更新鱼的位置和身体的大小
	void updateFish(Fish &predator, Fish &prey, double dt);
	//更新鱼的大小
	void updateBodySize(vector<double> &bodySize, double dt);
	void wander(vector<Point> &position, int index, double dt);

	//检测周围的鱼,fishA中第index_A条鱼周围有多少条fishB,最近的一条fishB是index_B
	int roundFish(Point& fishA, vector<Point>& positionB, int& index_B);
}
#endif
