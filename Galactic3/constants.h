#pragma once
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
const float G = 0.000008;// 0.00007;//�������� �� ���� ����������
const float PI = 3.14159265358979;
const float MAX_SPEED = 0.5;// 0.03;//������������ �������� (���)
const float p = 2;//��� �������
const int num = 100000;//���������� ������
float M;//����� �����
float xm = 0, ym = 0;//����� ����
//double msX, msY;//��������� ����
float zoom = 1;//
float Mytime = 1;//���������� ��� ����������
float min(float a, float b) { return a < b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }