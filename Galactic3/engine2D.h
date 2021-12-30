#pragma once
#include <cmath>
#include "constants.h"
struct vector2
{
	float x, y;
	vector2() { x = y = 0; }
	vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	float length() { return sqrt(x * x + y * y); }
	//float length() { return pow(abs(x * x * x) + abs(y * y * y),1.0/3.0); }
	//float length() 
	//{
	//	float sum = abs(powf(abs(x), p)) + abs(powf(abs(y), p));
	//	return pow(sum, 1.0 / p);
	//}
	void norm()
	{
		float k = 1 / length();
		x *= k;
		y *= k;
	}
	vector2 operator*(float k) { return vector2(x * k, y * k); }
	vector2 operator+(vector2 v) { return vector2(x + v.x, y + v.y); }
	vector2 operator-(vector2 v) { return vector2(x - v.x, y - v.y); }
};
struct obj2
{
	float x, y, m;
	vector2 v;
	obj2() { x = y = 0; v = vector2(); }
	obj2(float _x, float _y, float _m, vector2 _v)
	{
		x = _x;
		y = _y;
		m = _m;
		v = _v;
	}
	float dist(obj2 p) { return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); }
	//float dist(obj2 p){return pow(abs((x-p.x)*(x-p.x)*(x-p.x))+abs((y-p.y)*(y-p.y)*(y-p.y)),1.0/3.0);}
	//float dist(obj2 t)
	//{//возвращаем расстояние между объектами
	//	float sum = abs(powf(abs(x - t.x), p))+ abs(powf(abs(y - t.y), p));
	//	return powf(sum, 1.0 / p);
	//}
	float dist2(obj2 p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
	//float dist2(obj2 p){return abs((x-p.x)*(x-p.x)*(x-p.x))+abs((y-p.y)*(y-p.y)*(y-p.y));}
	//float dist2(obj2 t)
	//{//возвращаем расстояние между объектами
	//	float sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p));
	//	return sum;
	//}
	void change_double_side(obj2 *f)
	{
		vector2 k = vector2(f->x - x, f->y - y);
		k.norm();
		//float m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//float m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//float d2 = (m1 * m1 + m2 * m2)*1000000;
		//float d2 = (dist2(f))/(powf(G,1.0/p));//а комментарии, блять, для кого???
		//float d2 = (dist2(f));
		k = k * (G * G * f->m / ((x - f->x) * (x - f->x) + (y - f->y) * (y - f->y)));//dist2(f));
		v = v + k;
		float lngth = v.length();
		if (lngth > MAX_SPEED*4)
		{
			v = v * (MAX_SPEED*4/ lngth);
			//v.norm();
			//v = v * MAX_SPEED;
		}
		f->v = f->v - k;
		lngth = f->v.length();
		if (lngth > MAX_SPEED * 4)
		{
			f->v = f->v * (MAX_SPEED * 4 / lngth);
			//v.norm();
			//v = v * MAX_SPEED;
		}
	}
	void change(obj2 f)
	{
		vector2 k = vector2(f.x - x, f.y - y);
		k.norm();
		//float m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//float m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//float d2 = (m1 * m1 + m2 * m2)*1000000;
		//float d2 = (dist2(f))/(powf(G,1.0/p));//а комментарии, блять, для кого???
		//float d2 = (dist2(f));
		k = k * (G*G*f.m / dist2(f));
		v = v + k;
		float lngth = v.length();
		if (lngth > MAX_SPEED )//if (lngth*Mytime > MAX_SPEED* 1)
		{
			v=v*(MAX_SPEED /lngth);
			//v.norm();
			//v = v * MAX_SPEED;
		}
	}
	void move()
	{
		x += v.x;
		y += v.y;
		//x=x>50?(-49):(x<-50?(49):x);//пе(и?)ремещение
		//y=y>50?(-49):(y<-50?(49):y);
		v.x=(x>50||x<-50)?-v.x:(v.x);//отражение
		v.y=(y>50||y<-50)?-v.y:(v.y);
		
	}
	void draw()
	{
		for (int i = 0; i < 4; i++)
		{
			glVertex2d(x + m * cos(i * PI / 2), y + m * sin(i * PI / 2));
		}
	}
};
obj2* a;
obj2 mid;
obj2 mid2;
void SetNewMidElement(float x, float y, int magic_index)
{
	if (magic_index == 0)	mid = obj2(x, y, M, vector2(0, 0));
	if (magic_index == 1)	mid2 = obj2(x, y, M, vector2(0, 0));
}
void Init(int num)
{//инициализируем массив частиц
	a = new obj2[num];
	for (int i = 0; i < num; i++)
	{
		vector2 www = vector2((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001);
		//www.norm();
		//www = www * 0.01;
		a[i] = obj2((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 100 + 1) * 1000, www);
		//xm += a[i].x * a[i].m;
		//ym += a[i].y * a[i].m;
		M += a[i].m;
	}
	//SetNewMidElement(0, 0, 0);// mid = obj2(0, 0, M, vector2(0, 0));
	//SetNewMidElement(0, 0, 1);//mid2 = obj2(0, 0, M, vector2(0, 0));
	mid = obj2(0, 0, M, vector2(0, 0));
	//mid2 = obj2(10, 10, M, vector2(0, 0));
}
void some_unbelivable_function(int i)
{
	glColor3d(1, (i % 5 == 0), (i % 20 == 0));
	a[i].change(mid);
	//a[i].change(mid2);
	a[i].move();//как эту хуету оптимизировать еще???
	glVertex2d(a[i].x, a[i].y);
	//a[i].x = a1;
	//a[i].y = a2;
}
void MOVE()
{//передвигаем
	//float a1, a2;
	//glColor3d(1, 1, 1);
	//glColor4d(1, 1, 1, 0.1);
	srand(1);
	glBegin(GL_POINTS);
	glColor3d(1,1,1);
	for (int i = 0; i < num; i++)
	{
		//glColor4d((i%10==0), (i%10==0), 1,0.2);
		glColor4d(1, (i%5==0), (i % 20 == 0),0.2);
		//glColor3d((i%(1+rand()%100)==0), (i % (1 + rand() % 100) == 0), (i % (1 + rand() % 10) == 0));
		a[i].change(mid);
		//a[i].change(mid2);
		a[i].move();
		glVertex2d(a[i].x, a[i].y);
	}
	
	//mid2.change_no_limits(mid);
	//mid.change_no_limits(mid2);
	//mid2.move();
	//mid.move();
	
	//#pragma omp parallel shared(a)
	//{
	//	//float a1, a2;
	//	for (int i = 0; i < num; i++)
	//	{
	//		some_unbelivable_function(i);
	//	}
	//}
	glEnd();
}
void MOVE_NO_DRAW()
{
	for (int i = 0; i < num; i++)
	{
		a[i].change(mid);
		a[i].move();
	}
}
void RELOAD()
{
	M = 0;
	for (int i = 0; i < num; i++)
	{
		vector2 www = vector2((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001);
		//www.norm();
		//www = www * 0.01;
		a[i] = obj2((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 100 + 1) * 1000, www);
		//xm += a[i].x * a[i].m;
		//ym += a[i].y * a[i].m;
		M += a[i].m;
	}
}