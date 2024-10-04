//#include "engine.h"
#include <cmath>
#include <math.h>
#include "engine2D.h"
//#include "engine3D.h"
#include "Camera.h"
#include <ctime>
#include <iostream>
/*void some_unbelivable_function(obj2* axaxa, obj2 mid)
{
	axaxa->change(mid);
	axaxa->move();
	float a1 = axaxa->x;
	float a2 = axaxa->y;
	if (abs(a1) > 50)
		axaxa->v.x = -axaxa->v.x;//a1 = -a1;
	if (abs(a2) > 50)
		axaxa->v.y = -axaxa->v.y; a2 = -a2;
	//if (a[i].m == 100)
	//	glColor3d(0, 0, 1);
	//else if (a[i].m == 10000)
	//	glColor3d(0, 1, 0);
	//else if (a[i].m == 100000000)
	//	glColor3d(1, 0, 0);
	glVertex2d(axaxa->x, axaxa->y);
	//axaxa->x = a1;
	//axaxa->y = a2;
}
*/
int main()
{
	srand(time(0));
	if (!glfwInit())
		return -1;
	//Init(2,2);//двухмерное эвклидово пространство
	//Reload();
	//Init2D(num);
	Init(num);
	int w = 1280, h = 1024;
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	w = mode->width;
	h = mode->height;
	double msX, msY;
	//int w = 640, h = 512;
	int statR, statL, statD, statU, statQ, statE, statZ, statX;
	std::cout << "w,a,s,d,q,e - are for rotation\n"<<
		"mouse left click - is for changing location of TheMiddle\n"<<
		"mouse right click - is for restart\n"<<
		"z - is for zooming in\n"<<
		"x - is for zooming out\n";
	//std::cout << powf(p,p);
	//std::system("pause");
	GLFWwindow* window = glfwCreateWindow(w,h,"galactic",glfwGetPrimaryMonitor(),NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	int msState;
	if (w > h)
		glScalef((float)h / (float)w, 1.0f, 1.0f);
	else if (h > w)
		glScalef(1.0f, (float)w / (float)h, 1.0f);
	glScalef(1.0 / zoom, 1.0 / zoom, 1.0 / zoom);
	//glScalef(1.0 / 5.0, 1.0 / 5.0, 1.0 / 5.0);
	//GLCameraTarget* camera = new GLCameraTarget();
	//camera->setPerspective((180.0f), 1/*(float)w / h*/, 0.01f, 1000.0f);
	//camera->setPos(glm::vec3(1,1,1),GetMidElementPosition());
	bool b = false;//для просмотра сингулярности
	while (!glfwWindowShouldClose(window))
	{
		if (b)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);
		}
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
		//glColor3d(1,1,1);
		
		if (b)
		{
			//camera->Start();
			MOVE();
			//camera->End();
		}
		else
			MOVE_NO_DRAW();
		
		msState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (msState == 1)
		{
			glfwGetCursorPos(window, &msX, &msY);
			if (w > h)
			{
				msX = (msX * 2 / (float)h) - ((float)w / (float)h);
				msY = ((-msY) * 2 / (float)h + 1);
			}
			else
			{
				msX = (msX * 2 / (float)w) - 1;
				msY = ((-msY) * 2 / (float)w) + (float)h / (float)w;
			}
			msX *= zoom;
			msY *= zoom;
			SetNewMidElement(msX, msY,0);
			//camera->setPos(camera->getPos(), GetMidElementPosition());
			//glm::vec3 xyu = camera->getPos();
			//glm::vec3 pizda = camera->getDir();
			//system("cls");
			//std::cout << "cam pos:" << xyu.x << " " << xyu.y << " " << xyu.z << "\n";
			//std::cout << "cam pos:" << pizda.x << " " << pizda.y << " " << pizda.z << "\n";
		}
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == 1)//центральная
		//{
		//	glfwGetCursorPos(window, &msX, &msY);
		//	if (w > h)
		//	{
		//		msX = (msX * 2 / (float)h) - ((float)w / (float)h);
		//		msY = ((-msY) * 2 / (float)h + 1);
		//	}
		//	else
		//	{
		//		msX = (msX * 2 / (float)w) - 1;
		//		msY = ((-msY) * 2 / (float)w) + (float)h / (float)w;
		//	}
		//	msX *= zoom;
		//	msY *= zoom;
		//	SetNewMidElement(msX, msY,1);
		//}
		msState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		if (msState == 1)
		{
			RELOAD();
		}
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == 1)RELOAD();//левая
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == 1)RELOAD();//правая
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_4) == 1)RELOAD();
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5) == 1)RELOAD();
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
			//camera->setPos(camera->getPos()+glm::vec3((statD - statU)*0.1, (statR - statL)*0.1, (statQ - statE)*0.1),
			//	GetMidElementPosition());
			//glm::vec3 xyu = camera->getPos();
			//glm::vec3 pizda = camera->getDir();
			//system("cls");
			//std::cout << "cam pos:" << xyu.x << "\t" << xyu.y << "\t" << xyu.z<<"\n";
			//std::cout << "cam dir:" << pizda.x << "\t" << pizda.y << "\t" << pizda.z<<"\n";
			glRotated(3, statU - statD, statR - statL, statQ - statE);

		}
		if (statZ)
		{
			zoom *= 100.f / 101.f;
			glScaled(1.01, 1.01, 1.01);
		}
		if (statX)
		{
			zoom *= 1.01;
			glScaled(100.f / 101.f, 100.f / 101.f, 100.f / 101.f);
		}
		if(!b)glfwSwapBuffers(window);
		glfwPollEvents();
		b = !b;
	}
}