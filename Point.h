//Point.h

/*************************************
类：坐标类
功能：存储点的坐标及方向
类名：Point
**************************************/

#ifndef POINT_H
#define POINT_H

class Point
{
private:
	double x;//位置
	double y;
	double vx;//方向
	double vy;
	
public:

	//set
	void setX(double in_x)
	{
		x = in_x;
	}
	void setY(double in_y)
	{
		y = in_y;
	}
	void setXY(double in_x, double  in_y)
	{
		x = in_x;
		y = in_y;
	}
	void setVX(double in_vx)
	{
		vx = in_vx;
	}
	void setVY(double in_vy)
	{
		vy = in_vy;
	}
	void setVXVY(double in_vx, double in_vy)
	{
		vx = in_vx;
		vy = in_vy;
	}
	void setXYVXVY(double in_x, double  in_y,double in_vx, double in_vy)
	{
		x = in_x;
		y = in_y;
		vx = in_vx;
		vy = in_vy;
	}

	//get
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getVX()
	{
		return vx;
	}
	double getVY()
	{
		return vy;
	}
	void getXY(double &out_x, double &out_y)
	{
		out_x = x;
		out_y = y;
	}
	void getVXVY(double &out_vx, double &out_vy)
	{
		out_vx = vx;
		out_vy = vy;
	}
	void getXYVXVY(double &out_x, double &out_y, double &out_vx, double &out_vy)
	{
		out_x = x;
		out_y = y;
		out_vx = vx;
		out_vy = vy;
	}
};
#endif