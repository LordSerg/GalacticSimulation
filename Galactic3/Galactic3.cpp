#include "engine.h"
#include <cmath>
#include <math.h>
//using namespace oknelaksoms;

const double G = 0.00007;//отвечает за силу притяжения
const double PI = 3.14159265358979;
const double MAX_SPEED = 0.03;//максимальная скорость (кэп)
double min(double a, double b) { return a < b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }
const int num = 10000;
double p = 0.5;//для метрики
struct vector2
{
	double x, y;
	vector2() { x = y = 0; }
	vector2(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
	//double length() { return sqrt(x * x + y * y); }
	//double length() { return pow(abs(x * x * x) + abs(y * y * y),1.0/3.0); }
	double length() 
	{
		double sum = abs(powf(abs(x), p)) + abs(powf(abs(y), p));
		return pow(sum, 1.0 / p);
	}
	void norm()
	{
		double k = 1 / length();
		x *= k;
		y *= k;
	}
	vector2 operator*(double k) { return vector2(x * k, y * k); }
	vector2 operator+(vector2 v) { return vector2(x + v.x, y + v.y); }
	vector2 operator-(vector2 v) { return vector2(x - v.x, y - v.y); }
};
struct vector3
{
	double x, y,z;
	vector3() { x = y =z= 0; }
	vector3(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	//double length() { return sqrt(x * x + y * y + z * z); }
	//double length() { return pow(abs(x * x *x)+ abs(y * y*y )+ abs(z * z*z),1.0/3.0); }
	double length()
	{
		double sum = abs(powf(abs(x), p)) + abs(powf(abs(y), p)) + abs(powf(abs(z), p));
		return pow(sum, 1.0 / p);
	}
	void norm()
	{
		double k = 1 / length();
		x *= k;
		y *= k;
		z *= k;
	}
	vector3 operator*(double k) { return vector3(x * k, y * k, z * k); }
	vector3 operator+(vector3 v) { return vector3(x + v.x, y + v.y, z + v.z); }
	vector3 operator-(vector3 v) { return vector3(x - v.x, y - v.y, z - v.z); }
};
struct obj2
{
	double x, y, m;
	vector2 v;
	obj2() { x = y = 0; v = vector2(); }
	obj2(double _x, double _y, double _m, vector2 _v)
	{
		x = _x;
		y = _y;
		m = _m;
		v = _v;
	}
	//double dist(obj2 p){return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
	//double dist(obj2 p){return pow(abs((x-p.x)*(x-p.x)*(x-p.x))+abs((y-p.y)*(y-p.y)*(y-p.y)),1.0/3.0);}
	double dist(obj2 t)
	{//возвращаем расстояние между объектами
		double sum = abs(powf(abs(x - t.x), p))+ abs(powf(abs(y - t.y), p));
		return powf(sum, 1.0 / p);
	}
	//double dist2(obj2 p){return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);}
	//double dist2(obj2 p){return abs((x-p.x)*(x-p.x)*(x-p.x))+abs((y-p.y)*(y-p.y)*(y-p.y));}
	double dist2(obj2 t)
	{//возвращаем расстояние между объектами
		double sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p));
		return sum;
	}

	void change(obj2 f)
	{
		vector2 k = vector2(f.x - x, f.y - y);
		k.norm();
		//double m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//double m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//double d2 = (m1 * m1 + m2 * m2)*1000000;
		double d2 = (dist2(f))/(powf(G,1.0/p));
		k = k * (G * f.m / d2);
		v = v + k;
		if (v.length() > MAX_SPEED)
		{
			v.norm();
			v = v * MAX_SPEED;
		}

	}
	void move()
	{
		x += v.x;
		y += v.y;
	}
	void draw()
	{
		for (int i = 0; i < 4; i++)
		{
			glVertex2d(x+m*cos(i*PI/2),y+m*sin(i*PI/2));
		}
	}
};
struct obj3
{
	double x, y, z, m;
	vector3 v;
	obj3() { x = y = 0; v = vector3(); }
	obj3(double _x, double _y, double _z, double _m, vector3 _v)
	{
		x = _x;
		y = _y;
		z = _z;
		m = _m;
		v = _v;
	}
	//double dist(obj3 p) { return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z)); }
	//double dist(obj3 p) { return pow(abs((x - p.x) * (x - p.x) * (x - p.x)) +
	//	abs((y - p.y) * (y - p.y) * (y - p.y)) + abs((z - p.z) * (z - p.z) * (z - p.z)),1.0/3.0); }
	double dist(obj3 t)
	{//возвращаем расстояние между объектами
		double sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p)) + abs(powf(abs(z - t.z), p));
		return powf(sum, 1.0 / p);
	}
	//double dist2(obj3 p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z); }
	//double dist2(obj3 p) { return abs((x - p.x) * (x - p.x) * (x - p.x)) +
	//	abs((y - p.y) * (y - p.y) * (y - p.y)) + abs((z - p.z) * (z - p.z) * (z - p.z)); }
	double dist2(obj3 t)
	{//возвращаем расстояние между объектами
		double sum = abs(powf(abs(x - t.x), p)) + abs(powf(abs(y - t.y), p)) + abs(powf(abs(z - t.z), p));
		return sum;
	}
	void change(obj3 f)
	{
		vector3 k = vector3(f.x - x, f.y - y, f.z - z);
		k.norm();
		//double m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//double m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//double d2 = (m1 * m1 + m2 * m2)*1000000;
		double d2 = (dist2(f)) / (powf(G, 1.0 / p));
		
		k = k * (G * f.m / d2);
		v = v + k;
		if (v.length() > MAX_SPEED)
		{
			v.norm();
			v = v * MAX_SPEED;
		}

	}
	void move()
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void draw()
	{//TODO
		for (int i = 0; i < 4; i++)
		{
			glVertex2d(x + m * cos(i * PI / 2), y + m * sin(i * PI / 2));
		}
	}
};
//obj2* a;
obj3* b;
//const int num_of_elements = 100000;

int main()
{
	if (!glfwInit())
		return -1;
	//Init(2,2);//двухмерное эвклидово пространство
	//Reload();
	int w = 1280, h = 1024;
	int statR, statL, statD, statU, statQ, statE, statZ, statX;
	//std::cout << "w,a,s,d,q,e - are for rotation\nmouse left click - is for changing location of TheMiddle\nz - is for zooming in\nx - is for zooming out\n";
	//std::cout << powf(p,p);
	//std::system("pause");
	GLFWwindow* window = glfwCreateWindow(w,h,"galactic",glfwGetPrimaryMonitor(),NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//a = new obj2[num];
	b = new obj3[num];

	double xm=0, ym=0,M=0;
	//for (int i = 0; i < num; i++)
	//{
	//	vector2 www = vector2((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001);
	//	//www.norm();
	//	//www = www * 0.01;
	//	a[i] = obj2((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 100 + 1) * 1000 ,www);
	//	xm += a[i].x * a[i].m;
	//	ym += a[i].y * a[i].m;
	//	M += a[i].m;
	//}
	
	//a[num-2]= obj2((rand() % 2000 - 1000) * 0.0001, (rand() % 2000 - 1000) * 0.0001, rand() % 5 + 100000, vector2((rand() % 10 - 5) * 0.00001, (rand() % 10 - 5) * 0.00001));
	//a[num-1]= obj2(0,0, rand() % 5 + 100000, vector2((rand() % 10 - 5) * 0.00001, (rand() % 10 - 5) * 0.00001));
	for (int i = 0; i < num; i++)
	{
		b[i] = obj3((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01
			, (rand() % 100 + 1) * 1000,
			vector3((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001));
		xm += b[i].x * b[i].m;
		ym += b[i].y * b[i].m;
		M += b[i].m;
	}

	//bj2 mid = obj2(0,0,M,vector2(0,0));
	obj3 mid = obj3(0,0,0,M,vector3(0,0,0));
	//double a1, a2, a3;
	double msX, msY, zoom = 30;
	int msState;
	if (w > h)
		glScalef((float)h / (float)w, 1.0f, 1.0f);
	else if (h > w)
		glScalef(1.0f, (float)w / (float)h, 1.0f);
	glScalef(1.0 / zoom, 1.0 / zoom, 1.0 / zoom);
	//glScalef(1.0 / 5.0, 1.0 / 5.0, 1.0 / 5.0);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		//for (int i = 0; i < num; i++)
		//	for (int j = 0; j < num; j++)
		//	{
		//		if (i != j)
		//			a[i].change(a[j]);
		//	}
		//xm = ym = 0;
		//for (int i = 0; i < num; i++)
		//{
		//	xm += a[i].x * a[i].m;
		//	ym += a[i].y * a[i].m;
		//}
		//mid = obj2(xm/num, ym/num, M, vector2(0, 0));
		//for (int i = 0; i < num; i++)
		//{
		//	a[i].change(mid);
		//	//b[i].change(mid);
		//}
		//glBegin(GL_QUADS);
		glColor3d(1,1,1);
		//Move();
		//Draw();
		
		//glBegin(GL_POINTS);
		//#pragma omp parallel shared(a)
		//{
		//	double a1, a2;
		//	for (int i = 0; i < num; i++)
		//	{
		//		a[i].change(mid);
		//		a[i].move();
		//		a1 = a[i].x;
		//		a2 = a[i].y;
		//		if (abs(a1) > 50)
		//			a1 = -a1;//a[i].v.x = -a[i].v.x;
		//		if (abs(a2) > 50)
		//			a2 = -a2;//a[i].v.y = -a[i].v.y;
		//		//if (a[i].m == 100)
		//		//	glColor3d(0, 0, 1);
		//		//else if (a[i].m == 10000)
		//		//	glColor3d(0, 1, 0);
		//		//else if (a[i].m == 100000000)
		//		//	glColor3d(1, 0, 0);
		//		glVertex2d(a[i].x, a[i].y);
		//		a[i].x = a1;
		//		a[i].y = a2;
		//	}
		//}
		//glEnd();
		/*double a1, a2;
		for (int i = 0; i < num; i++)
		{
			a[i].change(mid);
			a[i].move();
			a1 = a[i].x;
			a2 = a[i].y;
			if (abs(a1) > 50)
				a1 = -a1;//a[i].v.x = -a[i].v.x;
			if (abs(a2) > 50)
				a2 = -a2;//a[i].v.y = -a[i].v.y;
			//if (a[i].m == 100)
			//	glColor3d(0, 0, 1);
			//else if (a[i].m == 10000)
			//	glColor3d(0, 1, 0);
			//else if (a[i].m == 100000000)
			//	glColor3d(1, 0, 0);
			glVertex2d(a1, a2);
			a[i].x = a1;
			a[i].y = a2;
		}*/
		glBegin(GL_POINTS);
		for (int i = 0; i < num; i++)
		{
			double a1, a2,a3;
			b[i].change(mid);
			b[i].move();
			a1 = b[i].x;
			a2 = b[i].y;
			a3 = b[i].z;
			if (abs(a1) > 50)
				a1 = -a1;//a[i].v.x = -a[i].v.x;
			if (abs(a2) > 50)
				a2 = -a2;//a[i].v.y = -a[i].v.y;
			if (abs(a3) > 50)
				a3 = -a3;
			double alpha = sqrt(a1 * a1 + a2 * a2 + a3 * a3);
			alpha = zoom - alpha > 0.2 ? 0.2 : zoom - alpha;
			//if (b[i].m == 100)
			//	glColor4d(1, 1, 1, zoom -alpha);
			//else
			//	glColor4d(1, 1, 1, zoom - alpha);
			//glColor4d(abs(a1), abs(a2), abs(a3), alpha);
			glColor4d(1,1,1, alpha);
			glVertex3d(a1, a2, a3);
			b[i].x = a1;
			b[i].y = a2;
			b[i].z = a3;
		}
		glEnd();
		msState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (msState == 1)
		{
			glfwGetCursorPos(window, &msX, &msY);
			if (w > h)
			{
				msX = (msX * 2 / (double)h) - ((double)w / (double)h);
				msY = ((-msY) * 2 / (double)h + 1);
			}
			else
			{
				msX = (msX * 2 / (double)w) - 1;
				msY = ((-msY) * 2 / (double)w) + (double)h / (double)w;
			}
			msX *= zoom;
			msY *= zoom;
			//SetNewPosition(vector(new double[]{ msX, msY }));
			//mid = obj2(msX, msY, M, vector2(0, 0));
			mid = obj3(msX, msY, 0.5*(cos(msX * 2 * PI) - sin(msY * 2 * PI)), M, vector3(0, 0, 0));
		}
		msState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		if (msState == 1)
		{
			//Reload();
			M = 0;
			for (int i = 0; i < num; i++)
			{
				//vector2 www = vector2((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001);
				//www.norm();
				//www = www * 0.01;
				//a[i] = obj2((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 100 + 1) * 1000, www);
				//xm += a[i].x * a[i].m;
				//ym += a[i].y * a[i].m;
				//M += a[i].m;

				b[i] = obj3((rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01, (rand() % 2000 - 1000) * 0.01
					, (rand() % 100 + 1) * 1000,
					vector3((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001));
				xm += b[i].x * b[i].m;
				ym += b[i].y * b[i].m;
				M += b[i].m;
			}
		}
		statR = glfwGetKey(window, GLFW_KEY_D);
		statL = glfwGetKey(window, GLFW_KEY_A);
		statU = glfwGetKey(window, GLFW_KEY_W);
		statD = glfwGetKey(window, GLFW_KEY_S);
		statQ = glfwGetKey(window, GLFW_KEY_Q);
		statE = glfwGetKey(window, GLFW_KEY_E);
		statZ = glfwGetKey(window, GLFW_KEY_Z);
		statX = glfwGetKey(window, GLFW_KEY_X);
		if (statR || statL || statU || statD || statQ || statE)
		{
			glRotated(0.3, statR - statL, statU - statD, statQ - statE);
		}
		if (statZ)
		{
			zoom *= 1000.f / 1001.f;
			glScaled(1.001, 1.001, 1.001);
		}
		if (statX)
		{
			zoom *= 1.001;
			glScaled(1000.f / 1001.f, 1000.f / 1001.f, 1000.f / 1001.f);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}