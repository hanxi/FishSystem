//Tools.h
#include "Point.h"
#include <vector>
using std::vector;

#ifndef TOOLS_H
#define TOOLS_H
namespace Tools
{
	const double MAXA=0.1;//最大加速度
	const double MAXV=6.0;//最大速度
	const double MINV=3.0;

	//随机生成一点
	Point randomPoint(int i);

	//点p1(x1,y1)到点p2(x2,y2)的距离
	double disP2P(double x1, double y1, double x2, double y2);
	//点p1到点p2的距离
	double disP2P(Point p1, Point p2);
	//求两向量(vx1,vy1)和(vx2,vy2)的夹角alpha
	double alphaP2P(double vx1, double vy1, double vx2, double vy2);

	//设定下一个位置和方向(x,y,vx,vy)，控制速度在[MINV,MAXV]之内
	void setNextPosition(double &x, double &y, double &vx, double &vy, double ax, double ay, double dt);

	//加速度大小和距离成反比：距离越小，加速度越大,最小距离为0
	double A_Fun(double d, double r);
	//加速度大小和距离成反比：距离越小，加速度越大,最小距离为mind
	double A_Fun(double d, double r, double mind);
	//加速度大小和角度成正比：角度越大，加速度越大
	double A_Fun(double alpha);
	double A_FunMin(double d, double r, double min_d);
	double A_FunMax(double d, double r, double max_d);
	double A_FunPower(double power, double MINPOWER);

	//x在(t1,t2)之间返回true,否则返回false
	bool in_range(double t1, double t2,double x);

	//求点p到线段(非直线)line的距离
	double disP2L2(Point p, Point line, Point &ver_p);

	//求点p到线段集lines中距离最小的line的序号
	int getMinDisIndex(vector<Point> lines, const Point &p, double &min_d);

	//使用a标准化(ax,ay)
	void a_to_std(double a, double &ax, double &ay);

	//s型曲线函数
	double SCurve(double a, double b, double C, double x);
	double invSCurve(double a, double b, double C, double y);//逆函数
}
#endif