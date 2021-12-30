#pragma once
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
const float G = 0.000008;// 0.00007;//отвечает за силу притяжения
const float PI = 3.14159265358979;
const float MAX_SPEED = 0.5;// 0.03;//максимальная скорость (кэп)
const float p = 2;//для метрики
const int num = 100000;//количество частиц
float M;//общая масса
float xm = 0, ym = 0;//центр масс
//double msX, msY;//положение мыши
float zoom = 1;//
float Mytime = 1;//коэфициент для замедления
float min(float a, float b) { return a < b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }