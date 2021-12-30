#pragma once
#include "engine2D.h"
obj2* a;
obj2* mids;
int mids_num = 100;
obj2 mid;
obj2 mid2;
void SetNewMidElement(float x, float y, int magic_index)
{
	if (magic_index == 0)	mid = obj2(x, y, M, vector2(0, 0));
	if (magic_index == 1)	mid2 = obj2(x, y, M, vector2(0, 0));
}
void Init_Mod(int num)
{//инициализируем массив частиц
	a = new obj2[num];
	mids = new obj2[mids_num];
	for (int i = 0; i < num; i++)
	{
		vector2 www = vector2((rand() % 20 - 10) * 0.01, (rand() % 20 - 10) * 0.01);
		//www.norm();
		//www = www * 0.01;
		a[i] = obj2((rand() % 2000 - 1000) * 0.03, (rand() % 2000 - 1000) * 0.03, (rand() % 100 + 1) * 1000, www);
		xm += a[i].x * a[i].m;
		ym += a[i].y * a[i].m;
		M += a[i].m;
	}
	//M *= 2;
	for (int i = 0; i < mids_num; i++)
	{
		vector2 www = vector2((rand() % 20 - 10) * 0.01, (rand() % 20 - 10) * 0.01);
		mids[i] = obj2((rand() % 2000 - 1000) * 0.03, (rand() % 2000 - 1000) * 0.03, M, www);
	}
	//SetNewMidElement(0, 0, 0);// mid = obj2(0, 0, M, vector2(0, 0));
	//SetNewMidElement(0, 0, 1);//mid2 = obj2(0, 0, M, vector2(0, 0));
	mid = obj2(0, 0, M, vector2(0, 0));
	mid2 = obj2(10, 10, M, vector2(0, 0));
}
void some_unbelivable_function(int i)
{
	a[i].change(mid);
	//a[i].change(mid2);
	a[i].move();//как эту хуету оптимизировать еще???
	//float a1 = abs(a[i].x)>50?-a[i].x:a[i].x;
	//float a2 = abs(a[i].y)>50?-a[i].y:a[i].y;;
	//if (abs(a1) > 50)
	//	a1 = -a1;//a[i].v.x = -a[i].v.x;//
	//if (abs(a2) > 50)
	//	a2 = -a2;//a[i].v.y = -a[i].v.y; //
	//if (a[i].m == 100)
	//	glColor3d(0, 0, 1);
	//else if (a[i].m == 10000)
	//	glColor3d(0, 1, 0);
	//else if (a[i].m == 100000000)
	//	glColor3d(1, 0, 0);
	//glVertex2d(a1, a2);
	glVertex2d(a[i].x, a[i].y);
	//a[i].x = a1;
	//a[i].y = a2;
}
void MOVE_Mod()
{//передвигаем
	//float a1, a2;
	glColor4d(1, 0, 0, 0.5);
	//glColor3d(1, 1, 1);
	for (int i = 0; i < num; i++)
	{
		//a[i].change(mid);
		//a[i].change(mid2);
		for (int j = 0; j < mids_num; j++)a[i].change(mids[j]);
		a[i].move();
		glVertex2d(a[i].x, a[i].y);
	}
	for (int i = 0; i < mids_num; i++)
		for (int j = i + 1; j < mids_num; j++)mids[i].change_double_side(&mids[j]);
	glColor3d(1, 1, 1);
	for (int i = 0; i < mids_num; i++)
	{
		mids[i].move();
		//glVertex2d(mids[i].x, mids[i].y);
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
}
void RELOAD_Mod()
{
	M = 0;
	for (int i = 0; i < num; i++)
	{
		vector2 www = vector2((rand() % 20 - 10) * 0.01, (rand() % 20 - 10) * 0.01);
		www.norm();
		www = www * 0.01;
		a[i] = obj2((rand() % 2000 - 1000) * 0.03, (rand() % 2000 - 1000) * 0.03, (rand() % 100 + 1) * 1000, www);
		//xm += a[i].x * a[i].m;
		//ym += a[i].y * a[i].m;
		M += a[i].m;
	}
}