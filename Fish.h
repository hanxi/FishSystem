//Fishs.h

/*************************************
类：鱼群类
功能：存储鱼群的位置、方向及大小
类名：Fish
**************************************/

#ifndef FISH_H
#define FISH_H
#include "Point.h"
#include "Tools.h"
#include <vector>
using std::vector;
const double MINPOWER=10;
const int STATE_RECOVER=1;
const int STATE_CONSUME=2;
const int STATE_NORMAL=0;
const double EAT_DISTANCE=50;
const double VIEW_DISTANCE=200.0;

class Fish
{
private:
	vector<double> bodySize;//鱼身体的大小
	vector<Point> position;//鱼的位置
	double system_time;
	const static int MAXNUMFISHS=10;//一种鱼中最多鱼条数
public:
	vector<double> power;//鱼的体力
	vector<int> state;//鱼的状态

public:
	Fish(int numFish)
	{
		initFish(numFish);
	}
	void initFish(int numFish)
	{
		initBodySize(numFish);
		initPosition(numFish);
		power.assign(numFish,100.0);
		state.assign(numFish,STATE_NORMAL);
	}
	void initBodySize(int numFish)
	{
		bodySize.assign(numFish,0.4);
	}
	void initPosition(int numFish)
	{
		for (int i=0; i<numFish; i++)
		{
			Point pt = Tools::randomPoint(i+numFish);
			position.push_back(pt);
		}
	}
	void deleteOneFish(int index)
	{
		vector<int>::iterator intIterator;
		vector<double>::iterator doubleIterator;
		vector<Point>::iterator pointIterator;
		intIterator = state.begin();
		intIterator += index;
		state.erase(intIterator);

		doubleIterator = bodySize.begin();
		doubleIterator += index;
		bodySize.erase(doubleIterator);

		doubleIterator = power.begin();
		doubleIterator += index;
		power.erase(doubleIterator);

		pointIterator = position.begin();
		pointIterator += index;
		position.erase(pointIterator);
	}
	void setBodySize(const vector<double>& in_bodySize)
	{
		bodySize = in_bodySize;
	}
	void setPosition(const vector<Point>& in_position)
	{
		position = in_position;
	}
	
	vector<double>& getBodySize()
	{
		return bodySize;
	}
	vector<Point>& getPosition()
	{
		return position;
	}
};
#endif