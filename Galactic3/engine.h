#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
namespace oknelaksoms
{
	const double G = 0.000001;//отвечает за силу притяжения
	const double PI = 3.14159265358979;
	const double MAX_SPEED = 0.1;//максимальная скорость (кэп)
	double min(double a, double b) { return a < b ? a : b; }
	double max(double a, double b) { return a > b ? a : b; }
	const int _num = 100000;
	//class galactic
	//{
	//public:
	int _n=2, _p=2, _M;// , _num;
	struct vector
	{
		double* a;
		vector() 
		{
			a = new double[_n];
			for (int i = 0; i < _n; i++)a[i] = 0;
		}
		vector(double* arr)
		{//конструктор вектора
			a = new double[_n];
			for (int i = 0; i < _n; i++)
				a[i] = arr[i];
		}
		double length()
		{//возвращаем длинну вектора
			double sum = 0;
			for (int i = 0; i < _n; i++)
				sum += abs(pow(a[i], _p));
			return pow(sum, 1.0 / _p);
		}
		void norm()
		{//нормируем вектор
			double k = 1 / length();
			for (int i = 0; i < _n; i++)
				a[i] *= k;
		}
		vector operator=(vector v)
		{
			//for (int i = 0; i < _n; i++)
			//	a[i] = v.a[i];
			return v;// vector(a);
		}
		vector operator*(double k)
		{
			for (int i = 0; i < _n; i++)
				a[i] *= k;
			return vector(a);
		}
		vector operator+(vector v)
		{
			for (int i = 0; i < _n; i++)
				a[i] += v.a[i];
			return vector(a);
		}
		vector operator-(vector v)
		{
			for (int i = 0; i < _n; i++)
				a[i] -= v.a[i];
			return vector(a);
		}
		//~vector()
		//{
		//	//free(a);
		//	delete[]a;
		//}
	};
	struct obj
	{
		double _m;
		vector pos, dir;
		obj()
		{
			_m = 0;
			//pos = nullptr;
			//dir = nullptr;
		}
		obj(double m, vector position, vector direction)
		{
			_m = m;
			pos = position;
			dir = direction;
		}
		double dist(obj t)
		{//возвращаем расстояние между объектами
			double sum = 0;
			for (int i = 0; i < _n; i++)
				sum += abs(pow(pos.a[i] - t.pos.a[i], _p));
			return pow(sum, 1.0 / _p);
		}
		double dist2(obj t)
		{//возвращаем "p"-тую степень расстояние между объектами
			double sum = 0;
			for (int i = 0; i < _n; i++)
				sum += abs(pow(pos.a[i] - t.pos.a[i], _p));
			return sum;
		}
		void change(obj t)
		{//t - объект, относительно которого меняем положения
			vector k = t.pos - pos;
			k.norm();
			double d2 = (dist2(t)) / (sqrt(G));
			k = k * (G * t._m / d2);
			dir = dir + k;
			if (dir.length() > MAX_SPEED)
			{
				dir.norm();
				dir = dir * MAX_SPEED;
			}

		}
		void move() { pos = pos + dir; }
	};
	static obj _mid;//центральный объект
	static void Init(int n, int p);
	static void Reload();//расстановка элементов заново
	static void SetNewPosition(vector);//меняем позицию центрального элемента
	static void Draw();//отрисовка
	static void Draw_parallel();//отрисовка с распаралеливанием (по ядрам процессора)
	static void Move();//двигаем все элементы
	static void Move_parallel();//распаралелено двигаем все элементы
	//private:
		//static int _n, _p, _num,_M;//n - измерение, p - размерность, _num - чилсо элементов
		/*static*/ obj * _all;
	//};
	void /*galactic::*/Init(int n, int p)
	{
		_n = n;
		_p = p;
		//_num = num;
		int M = 0, m = 0;
		_all = new obj[_num];
		double from=-1, to=1;//TODO: range of speed & position
		//double* somearray = new double[_n];
		vector dir, pos;
		for (int i = 0; i < _num; i++)
		{
			if (_n == 2)
			{
				dir = vector(new double []{(rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001});
				pos = vector(new double [] {(rand() % 2000 - 1000) * 0.001, (rand() % 2000 - 1000) * 0.001});
			}
			else if (_n == 3)
			{
				dir = vector(new double [] {(rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001, (rand() % 20 - 10) * 0.001});
				pos = vector(new double [] {(rand() % 2000 - 1000) * 0.001, (rand() % 2000 - 1000) * 0.001, (rand() % 2000 - 1000) * 0.001});
			}
			m = (rand() % 100 + 1) * 1000;
			//w.norm();
			//w = w * 0.01;
			_all[i] = obj(m,pos,dir);
			M += m;
		}
		_M = M;
		_mid = obj(_M, vector(), vector());
	}
	void /*galactic::*/Reload()
	{
		int M = 0, m = 0;
		_all = new obj[_num];
		double from = -1, to = 1;//TODO: range of speed & position
		double* somearray = new double[_n];
		for (int i = 0; i < _num; i++)
		{
			for (int j = 0; j < _n; j++)somearray[j] = (rand() % 20 - 10) * 0.001;
			vector dir = vector(somearray);
			for (int j = 0; j < _n; j++)somearray[j] = (rand() % 2000 - 1000) * 0.001;
			vector pos = vector(somearray);
			m = (rand() % 100 + 1) * 1000;
			//w.norm();
			//w = w * 0.01;
			_all[i] = obj(m, pos, dir);
			M += m;
		}
		_M = M;
		_mid._m = _M;
	}
	void /*galactic::*/SetNewPosition(vector v)
	{
		_mid.pos = v;
	}
	void /*galactic::*/Draw()
	{
		glColor4d(1, 1, 1, 0.1);
		glBegin(GL_POINTS);
		if (_n == 2)
		{
			for (int i = 0; i < _num; i++)
				glVertex2d(_all[i].pos.a[0], _all[i].pos.a[1]);
		}
		else if (_n == 3)
		{
			for (int i = 0; i < _num; i++)
				glVertex3d(_all[i].pos.a[0], _all[i].pos.a[1], _all[i].pos.a[2]);
		}
		else if (_n == 4)
		{
			for (int i = 0; i < _num; i++)
				glVertex4d(_all[i].pos.a[0], _all[i].pos.a[1], _all[i].pos.a[2], _all[i].pos.a[3]);
		}
		glEnd();
	}
	void /*galactic::*/Draw_parallel()
	{
		glColor4d(1, 1, 1, 0.1);
		glBegin(GL_POINTS);
		#pragma omp parallel shared(_all)
		{
			if (_n == 2)
			{
				for (int i = 0; i < _num; i++)
					glVertex2d(_all[i].pos.a[0], _all[i].pos.a[1]);
			}
			else if (_n == 3)
			{
				for (int i = 0; i < _num; i++)
					glVertex3d(_all[i].pos.a[0], _all[i].pos.a[1], _all[i].pos.a[2]);
			}
			else if (_n == 4)
			{
				for (int i = 0; i < _num; i++)
					glVertex4d(_all[i].pos.a[0], _all[i].pos.a[1], _all[i].pos.a[2], _all[i].pos.a[3]);
			}
		}
		glEnd();
	}
	void /*galactic::*/Move()
	{
		for (int i = 0; i < _num; i++)
		{
			_all[i].change(_mid);
			//for (int j = 0; j < _n; j++)
			//	if (abs(_all[i].pos.a[j]) > 50)
			//		_all[i].pos.a[j] = -_all[i].pos.a[j];
		}
	}
	void /*galactic::*/Move_parallel()
	{
		#pragma omp parallel shared(_all)
		{
			for (int i = 0; i < _num; i++)
			{
				_all[i].change(_mid);
				for (int j = 0; j < _n; j++)
					if (abs(_all[i].pos.a[j]) > 50)
						_all[i].pos.a[j] = -_all[i].pos.a[j];
			}
		}
	}
}