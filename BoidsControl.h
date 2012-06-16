//BoidsControl.h

/**************************************************************************
类：Boids算法控制类,继承控制类,用于表示鱼闲游的状态
功能：控制鱼的位置和运动方向
类名：BoidsControl
**************************************************************************/

#ifndef BOIDSCONTROL_H
#define BOIDSCONTROL_H
#include "Point.h"
#include "Tools.h"
#include <vector>
using std::vector;
using namespace Tools;

namespace BoidsControl
{
	void boidsAlgorithm(vector<Point>& position, int index, double dt);
	void rule1(double &a1x, double &a1y, double sumx, double sumy, int n, double x, double y);
	void rule2(double &a2x, double &a2y, double sumvx, double sumvy, int n,double x, double y, double vx, double vy);
	void rule3(double &a3x, double &a3y, double d, double tmp_a3x, double tmp_a3y);
	void rule4(double &a4x, double &a4y,  Point &p);
}
#endif