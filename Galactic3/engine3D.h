#include <cmath>
#include "constants.h"
struct vector3
{
	float x, y, z;
	vector3() { x = y = z = 0; }
	vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	float length() { return sqrt(x * x + y * y + z * z); }
	//float length() { return pow(abs(x * x *x)+ abs(y * y*y )+ abs(z * z*z),1.0/3.0); }
	//float length()
	//{
	//	float sum = abs(powf(abs(x), p)) + abs(powf(abs(y), p)) + abs(powf(abs(z), p));
	//	return pow(sum, 1.0 / p);
	//}
	void norm()
	{
		float k = 1 / length();
		x *= k;
		y *= k;
		z *= k;
	}
	vector3 operator*(float k) { return vector3(x * k, y * k, z * k); }
	vector3 operator+(vector3 v) { return vector3(x + v.x, y + v.y, z + v.z); }
	vector3 operator-(vector3 v) { return vector3(x - v.x, y - v.y, z - v.z); }
};
struct obj3
{
	float x, y, z, m;
	vector3 v;
	obj3() { x = y = 0; v = vector3(); }
	obj3(float _x, float _y, float _z, float _m, vector3 _v)
	{
		x = _x;
		y = _y;
		z = _z;
		m = _m;
		v = _v;
	}
	float dist(obj3 p) { return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z)); }
	//float dist(obj3 p) { return pow(abs((x - p.x) * (x - p.x) * (x - p.x)) +
	//	abs((y - p.y) * (y - p.y) * (y - p.y)) + abs((z - p.z) * (z - p.z) * (z - p.z)),1.0/3.0); }
	//float dist(obj3 t)
	//{//возвращаем расстояние между объектами
	//	float sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p)) + abs(powf(abs(z - t.z), p));
	//	return powf(sum, 1.0 / p);
	//}
	
	float dist2(obj3 p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z); }
	//float dist2(obj3 p) { return abs((x - p.x) * (x - p.x) * (x - p.x)) +
	//	abs((y - p.y) * (y - p.y) * (y - p.y)) + abs((z - p.z) * (z - p.z) * (z - p.z)); }
	//float dist2(obj3 t)
	//{//возвращаем расстояние между объектами
	//	float sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p)) + abs(powf(abs(z - t.z), p));
	//	return sum;
	//}
	void change(obj3 f)
	{
		vector3 k = vector3(f.x - x, f.y - y, f.z - z);
		k.norm();
		//float m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//float m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//float d2 = (m1 * m1 + m2 * m2)*1000000;
		//float d2 = (dist2(f)) / (powf(G, 1.0 / p));//очень интересно))))(нет, что это???)
		//float d2 = (dist2(f)) / G;

		k = k * (G *G* f.m / dist2(f));
		v = v + k;
		float lngth = v.length();
		if (lngth > MAX_SPEED)
		{
			//v.norm();
			//v = v * MAX_SPEED;
			v = v * (MAX_SPEED/lngth);
		}

	}
	void move()
	{
		x += v.x;
		y += v.y;
		z += v.z;
		//x=x>50?(-49):(x<-50?(49):x);//пе(и?)ремещение
		//y=y>50?(-49):(y<-50?(49):y);
		//z=z>50?(-49):(z<-50?(49):z);
		v.x = (x > 50 || x < -50) ? -v.x : (v.x);//отражение
		v.y = (y > 50 || y < -50) ? -v.y : (v.y);
		v.z = (z > 50 || z < -50) ? -v.z : (v.z);
	}
	void draw()
	{//TODO
		for (int i = 0; i < 4; i++)
		{
			glVertex2d(x + m * cos(i * PI / 2), y + m * sin(i * PI / 2));
		}
	}
};
obj3* b;
obj3 mid;
void Init(int num)
{
	b = new obj3[num];
	for (int i = 0; i < num; i++)
	{
		b[i] = obj3((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01
			, (rand() % 100 + 1) * 1000,
			vector3((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001));
		//xm += b[i].x * b[i].m;
		//ym += b[i].y * b[i].m;
		M += b[i].m;
	}
	mid = obj3(0, 0, 0, M, vector3(0, 0, 0));
}
void MOVE()
{
	//float a1, a2, a3;
	glBegin(GL_POINTS);
	glColor4d(1, 1, 1,0.1);
	for (int i = 0; i < num; i++)
	{
		b[i].change(mid);
		b[i].move();
		//float alpha = b[i].v.length();// sqrt(a1 * a1 + a2 * a2 + a3 * a3);
		//alpha = zoom - alpha > 0.2 ? 0.2 : zoom - alpha;
		//glColor4d(1,1,1, alpha);
		glVertex3d(b[i].x, b[i].y, b[i].z);
	}
	glEnd();
}
void MOVE_NO_DRAW()
{
	//float a1, a2, a3;
	for (int i = 0; i < num; i++)
	{
		b[i].change(mid);
		b[i].move();
	}
}
void RELOAD()
{
	M = 0;
	for (int i = 0; i < num; i++)
	{
		b[i] = obj3((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01
			, (rand() % 100 + 1) * 1000,
			vector3((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001));
		//xm += b[i].x * b[i].m;
		//ym += b[i].y * b[i].m;
		M += b[i].m;
	}
}
void SetNewMidElement(float x, float y,int magic_index)
{
	//mid = obj3(msX, msY, 0.5 * (cos(msX * 2 * PI) - sin(msY * 2 * PI)), M, vector3(0, 0, 0));
	mid = obj3(x, y, min(x,y), M, vector3(0, 0, 0));
}
glm::vec3 GetMidElementPosition()
{
	return glm::vec3(mid.x,mid.y,mid.z);
}