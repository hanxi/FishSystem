//Tools.cpp
#include "Tools.h"
using namespace Tools;
#include <cmath>
#include <time.h>
const double pi = 3.14159;

//随机生成一点
Point Tools::randomPoint(int i)
{
	//窗口大小
	int win_width=800,win_height=600;
	Point pt;
	srand((unsigned int)time(NULL)<<i);
	int x = rand()%(win_width-200)+100;
	int y = rand()%(win_height-200)+100;
	pt.setXYVXVY(x,y,10,10);
	return pt;
}


//点p1(x1,y1)到点p2(x2,y2)的距离
double Tools::disP2P(double x1, double y1, double x2, double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//点p1到点p2的距离
double Tools::disP2P(Point p1, Point p2)
{
	double x1,y1,x2,y2;
	p1.getXY(x1,y1);
	p2.getXY(x2,y2);
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

//求两向量(vx1,vy1)和(vx2,vy2)的夹角alpha
double Tools::alphaP2P(double vx1, double vy1, double vx2, double vy2)
{
	//cos(alpha=cos((a.*b)/(|a|.*|b|)
	double aa = sqrt(vx1*vx1+vy1*vy1);
	double bb = sqrt(vx2*vx2+vy2*vy2);
	double ab = vx1*vx2+vy1*vy2;
	double cosalpha = ab/(aa*bb);
	if (cosalpha>1)
	{
		cosalpha = 1;
	}
	else if (cosalpha<-1)
	{
		cosalpha = -1;
	}
	return acos(cosalpha);
}

/////////////////////////////////////////////////////
//设定下一个位置和方向(x,y,vx,vy)，运用了物体运动方程
//控制速度在[MINV,MAXV]之内
////////////////////////////////////////////////////
void Tools::setNextPosition(double &x, double &y, double &vx, double &vy, double ax, double ay, double dt)
{
	vx += ax*dt;
	vy += ay*dt;
	double v = sqrt(vx*vx+vy*vy);//速度大小
	if (v > MAXV)//改变速度大小，不改变速度方向
	{
		vx = MAXV*vx/v;
		vy = MAXV*vy/v;
	}
	if (v < MINV)
	{
		vx = MINV*vx/v;
		vy = MINV*vy/v;
	}
	x += vx*dt;
	y += vy*dt;
}

///////////////////////////////////////////////////
//求加速度大小
//加速度大小和距离成反比：距离越小，加速度越大
//最小距离为0
///////////////////////////////////////////////////
double Tools::A_Fun(double d, double r)
{
	if (d<r)
	{
		return MAXA*d/r;
	}
	else
	{
		return 0.0;
	}
}

///////////////////////////////////////////////////
//求加速度大小
//加速度大小和距离成反比：距离越小，加速度越大
//最小距离为mind
///////////////////////////////////////////////////
double Tools::A_Fun(double d, double r, double min_d)
{
	if (d<r)
	{
		return MAXA*(r-d)/(r-min_d);
	}
	else
	{
		return 0.0;
	}
}
double Tools::A_FunMin(double d, double r, double min_d)
{
	if (d<r)
	{
		return MAXA*(r-d)/(r-min_d);
	}
	else
	{
		return 0.0;
	}
}
double Tools::A_FunMax(double d, double r, double max_d)
{
	if (d>r)
	{
		return MAXA*(d-r)/(max_d-r);
	}
	else
	{
		return MAXA;
	}
}

double Tools::A_FunPower(double power, double MINPOWER)
{
	if (power>MINPOWER)
	{
		return MAXA*power/MINPOWER;
	}
	else
	{
		return 0.0;
	}
}

///////////////////////////////////////////////////
//求旋转加速度大小
//加速度大小和角度成正比：角度越大，加速度越大
///////////////////////////////////////////////////
double Tools::A_Fun(double alpha)
{
	return MAXA*alpha/pi;
}

//////////////////////////////////////////////////
//x是否在(t1,t2)之间
//x在(t1,t2)之间返回true,否则返回false
//////////////////////////////////////////////////
bool Tools::in_range(double t1, double t2,double x)
{
	return x>t1 && x<t2 || x<t1 && x>t2;
}

//////////////////////////////////////////////////
//点p到直线line的距离
//如果垂点ver_p不在line上面，返回p到line端点的距离（取距离小的）
//	ver_p取距离较小的端点
//////////////////////////////////////////////////
double Tools::disP2L2(Point p, Point line, Point &ver_p)
{
	double d;
	if (0 == line.getVX())
	{
		ver_p.setXY(line.getX(),p.getY());
		d = fabs(line.getX()-p.getX());
	}
	else
	{
		double k=line.getVY()/line.getVX();//直线的斜率
		//求垂点
		//(line.y-y)/(line.x-x)=k;
		//(p.y-y)/(p.x-x)=-1/k;
		double y=(line.getY()-k*line.getX()+k*p.getX()+k*k*p.getY())/(1+k*k);
		double x=p.getX()+k*p.getY()-k*y;
		ver_p.setXY(x,y);
		//ver_p.x = (p.x+k*(p.y-line.y+k*line.x))/(1-k*k);
		//ver_p.y = line.y-k*(line.x-ver_p.x);
		//垂点在线段上，距离为点p到垂点的距离
		d=disP2P(p, ver_p);
	}
	if (!in_range(line.getX(),line.getX()+line.getVX(),ver_p.getVX()))//如果垂点不在线段上
	{
		double td1 = disP2P(p,line);
		Point linea;
		linea.setXY(line.getX()+line.getVX(),line.getY()+line.getVY());
		double td2 = disP2P(p,linea);
		if (td1>td2)
		{
			d = td1;
			ver_p.setXY(line.getX(),line.getY());
		}
		else
		{
			d = td2;
			ver_p.setXY(linea.getX(),linea.getY());
		}
	}
	return d;
}

//////////////////////////////////////////////////
//求点p到线段集lines中距离最小的line
//返回line的序号
//////////////////////////////////////////////////
int Tools::getMinDisIndex(vector<Point> lines, const Point &p, double &mind)
{
	int index=0;
	Point ver_p;
	int N = lines.size();
	mind=disP2L2(p,lines.at(0),ver_p);
	for (int i=1; i<N;i++)
	{
		double d = disP2L2(p,lines.at(i),ver_p);
		if (mind>d)
		{
			mind = d;
			index = i;
		}
	}
	return index;
}

//使用a标准化(ax,ay)
void Tools::a_to_std(double a, double &ax, double &ay)
{
	double sq = sqrt(ax*ax+ay*ay);
	if (sq > 0)
	{
		ax = a*ax/sq;
		ay = a*ay/sq;
	}
}


double Tools::SCurve(double a, double b, double C, double x)
{
	return (b-(b-a)*exp(-x*x/C));
}

double Tools::invSCurve(double a, double b, double C, double y)
{
	return sqrt(-log((b-y)/(b-a))*C);
}