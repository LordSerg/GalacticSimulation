#include <iostream>
#include <GLFW/glfw3.h>
const double G = 0.000001;
const double PI = 3.14159265358979;
double min(double a, double b) { return a < b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }
struct vector
{
	double x, y;
	vector() { x = y = 0; }
	vector(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
	double length() { return sqrt(x * x + y * y); }
	void norm()
	{
		double k = 1/sqrt(x * x + y * y);
		x *= k;
		y *= k;
	}
	vector operator*(double k) { return vector(x * k, y * k); }
	vector operator+(vector v) { return vector(x + v.x, y + v.y); }
	vector operator-(vector v) { return vector(x - v.x, y - v.y); }
};
struct obj
{
	double x, y, m;
	vector v;
	obj() { x = y = 0; v = vector(); }
	obj(double _x, double _y, double _m, vector _v)
	{
		x = _x;
		y = _y;
		m = _m ;
		v = _v;
	}
	double dist(obj p){return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
	void change(obj p)
	{
		vector k = vector(p.x - x, p.y - y);
		k.norm();
		//double m1 = min(abs(x - p.x), abs(x - p.x - 2));
		//double m2 = min(abs(y - p.y), abs(y - p.y - 2));
		//double d2 = (m1 * m1 + m2 * m2)*1000000;
		double d2 = ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y))*1000000;
		k = k * (G * p.m / d2);
		v = v + k;
		if (v.length() > 0.02)
		{
			v.norm();
			v = v * 0.02;
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
const int num = 200000;
obj* a;
int main()
{
	if (!glfwInit())
		return -1;
	int w = 1250, h = 900;
	GLFWwindow* window = glfwCreateWindow(w,h,"galactic",NULL/*glfwGetPrimaryMonitor()*/,NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	a = new obj[num];
	double xm=0, ym=0,M=0;
	for (int i = 0; i < num; i++)
	{
		a[i] = obj((rand() % 2000 - 1000) * 0.001, (rand() % 2000 - 1000) * 0.001, (rand()%5+1)*400, vector((rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001));
		xm += a[i].x * a[i].m;
		ym += a[i].y * a[i].m;
		M += a[i].m;
	}
	//a[num-2]= obj((rand() % 2000 - 1000) * 0.0001, (rand() % 2000 - 1000) * 0.0001, rand() % 5 + 100000, vector((rand() % 10 - 5) * 0.00001, (rand() % 10 - 5) * 0.00001));
	//a[num-1]= obj(0,0, rand() % 5 + 100000, vector((rand() % 10 - 5) * 0.00001, (rand() % 10 - 5) * 0.00001));

	obj mid = obj(0,0,M,vector(0,0));
	double a1, a2, msX, msY;
	int msState;
	if (w > h)
		glScalef((float)h / (float)w, 1.0f, 1.0f);
	else if (h > w)
		glScalef(1.0f, (float)w / (float)h, 1.0f);
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
		//mid = obj(xm/num, ym/num, M, vector(0, 0));
		for (int i = 0; i < num; i++)
		{
			a[i].change(mid);
		}
		//glBegin(GL_QUADS);
		glBegin(GL_POINTS);
		for (int i = 0; i < num; i++)
		{
			a[i].move();
			a1 = a[i].x;
			a2 = a[i].y;
			if (abs(a1) > 5)
				a1 = -a1;//a[i].v.x = -a[i].v.x;
			if (abs(a2) > 5)
				a2 = -a2;//a[i].v.y = -a[i].v.y;
			//a[i].draw();
			//if (i < num - 1)
			//	glColor3d(1, 0, 0);
			//else
			//	glColor3d(1, 1, 1);
			glVertex2d(a1,a2);
			a[i].x = a1;
			a[i].y = a2;
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
			mid = obj(msX, msY, M, vector(0, 0));
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}