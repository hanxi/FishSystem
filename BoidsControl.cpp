//BoidsControl.cpp

#include "BoidsControl.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <fstream>
using std::ifstream;
using std::ofstream;

double min_d = 80;
const double pi = 3.14159;
double r = 350;//可见区域的半径
const double eps=1e-5;
int win_width=800,win_height=600;

//////////////////////////////////////////////////////////////////
//规则一
/////////////////////////////////////////////////////////////////
void BoidsControl::rule1(double &a1x, double &a1y, double sumx, double sumy, int n, double x, double y)
{
	double avgx = sumx/n;
	double avgy = sumy/n;
	//求平均点到它的距离
	double d_avg = disP2P(avgx, avgy, x, y);
	double a1 = A_Fun(d_avg,r);
	a1x = avgx - x;
	a1y = avgy - y;
	//归一
	Tools::a_to_std(a1,a1x,a1y);
}

//////////////////////////////////////////////////////////////////
//规则二
/////////////////////////////////////////////////////////////////
void BoidsControl::rule2(double &a2x, double &a2y, double sumvx, double sumvy, int n,double x, double y, double vx, double vy)
{
	double avgvx = sumvx/n;
	double avgvy = sumvy/n;
	//求平均速度方向和其速度方向的夹角
	double alpha_avg = alphaP2P(avgvx, avgvy, vx, vy);
	double a2 =1.5* A_Fun(alpha_avg);
	//先假设加速度方向为（-vy,vx）
	a2x = -vy;
	a2y = vx;
	if (disP2P(x-vy,y+vx,x+avgvx,y+avgvy) > sqrt(avgvx*avgvx + avgvy*avgvy))
	{//选取方向朝着avgv
		a2x = vy;
		a2y = -vx;
	}
	//归一
	Tools::a_to_std(a2,a2x,a2y);
}

//////////////////////////////////////////////////////////////////
//规则三
/////////////////////////////////////////////////////////////////
void BoidsControl::rule3(double &a3x, double &a3y, double d, double tmp_a3x, double tmp_a3y)
{
	double tmp_a3 = A_Fun(d,r,min_d);
	//归一
	Tools::a_to_std(tmp_a3,tmp_a3x,tmp_a3y);
	a3x += tmp_a3x;
	a3y += tmp_a3y;
}


inline void sub_rule4(double &a4x, double x, int win_width)
{
	if (x<win_width*0.4)
	{
		a4x = A_FunMin(x,win_width*0.4,win_width*0.3);
	}
	else if (x>win_width*0.6)
	{
		a4x = -A_FunMax(x,win_width*0.6,win_width*0.7);
	}
	else
	{
		a4x = 0;
	}
}
//////////////////////////////////////////////////////////////////
//规则四:作用区域改为整个圆
/////////////////////////////////////////////////////////////////
void BoidsControl::rule4(double &a4x, double &a4y, Point &p)
{
	double vx,vy;
	p.getVXVY(vx,vy);
	double v=sqrt(vx*vx+vy*vy);//记录当前速度，以免速度突变

	double x,y;
	p.getXY(x,y);
	sub_rule4(a4x,x,win_width);
	sub_rule4(a4y,y,win_height);
}

//////////////////////////////////////////////////////////////
//Boids算法,改变第i条鱼的位置和方向
/////////////////////////////////////////////////////////////
void BoidsControl::boidsAlgorithm(vector<Point>& position, int index, double dt)
{
	int num_fish = position.size();
	Point mindleP;
	mindleP.setXY(win_width/2,win_height/2);
	double x,y,vx,vy;//当前点的坐标和方向
	Point p = position[index];
	p.getXYVXVY(x,y,vx,vy);
	double alpha = 2*pi/3;//可见区域的夹角
	double d;//到各个点的距离
	double a1x=0;//规则一中的加速度
	double a1y=0;
	double a2x=0;//规则二中的加速度
	double a2y=0;
	double a3x=0;//规则三中的加速度
	double a3y=0;
	double a4x=0;//规则四中的加速度
	double a4y=0;
	int n=0;
	double sumx=0,sumy=0,sumvx=0,sumvy=0;//区域内各个点的位置和速度之和
	//求区域内的点
	for (int i=0; i<num_fish; i++)
	{
		if (i == index)//排除自己不计算
		{
			continue;
		}
		d = disP2P(x,y,position.at(i).getX(),position.at(i).getY());
		//判断是否在区域内
		if (   (d < r)
		    && (alphaP2P(position.at(i).getX()-x,position.at(i).getY()-y, vx, vy) < alpha))
		{
			sumx += position.at(i).getX();
			sumy += position.at(i).getY();
			sumvx += position.at(i).getVX();
			sumvy += position.at(i).getVY();
			n++;
			if (d <  r/2)
			{
				//规则三
				double tmp_a3x = x - position.at(i).getX();
				double tmp_a3y = y - position.at(i).getY();
				rule3(a3x,a3y,d, tmp_a3x,tmp_a3y);
			}
		}
	}
	if (n>0)
	{
		rule1(a1x,a1y,sumx,sumy, n,x,y);
		rule2(a2x,a2y,sumvx,sumvy, n,x,y,vx,vy);
	}
	rule4(a4x,a4y,p);
	
	//鱼游动方向(逆时针还是顺时针)取决于(a5x,a5y)
	double a5x,a5y;//切向加速度
	double a5=MAXA;
	a5x = p.getY() - mindleP.getY();
	a5y = mindleP.getX() - p.getX();
	//归一
	a_to_std(a5,a5x,a5y);

	double ax=0,ay=0;
	ax = a1x*1.5+a2x+a3x*1.2+a4x*1.5+a5x;
	ay = a1y*1.5+a2y+a3y*1.2+a4y*1.5+a5y;

	setNextPosition(x,y,vx,vy,ax,ay,dt);
	p.setXYVXVY(x,y,vx,vy);
	position[index] = p;
}

/*
各个加速度之间的权重分析:

模型

加速度a1:趋近平均位置的加速度
加速度a2:趋近平均方向的加速度
加速度a3:远离其他鱼的加速度
加速度a4:躲避边界的加速度
加速度a5:切向加速度（提供环绕动力）

a1 = f1(d) = MAXA*d/r
a2 = f2(d) = MAXA*alpha/pi
a3 = f3(d) = MAXA*(r/2-d)/(r/2-min_d)
a4 = f4(d) = MAXA*(r/2-d)/(r/2-min_d)
a5 = MAXA

a = a1*1.5 + a2 + a3*1.2 + a4*1.5 + a5

a1*1.5使鱼更趋近在一起
a3*1.2使鱼相隔更开
a4*1.5使鱼更快远离边界
*/