#define _USE_MATH_DEFINES
#define D2R M_PI / 180
#define R2D 180 / M_PI
#define SCREENW 1600
#define SCREENH 900

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <conio.h>
#include <vector>

struct vec3{ float x, y, z; };
struct poly{int idx[3]; bool hide;};

struct mesh
{
	std::vector<vec3*> vertex;
	std::vector<poly*> polygon;
	vec3 position;
	vec3 rotation;
};

mesh m;
vec3 camPos;
float fov;

COLORREF COLOR = RGB(15, 255, 15);

void main()
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	HPEN pen = CreatePen(PS_SOLID, 1, COLOR);
	SelectObject(mydc, pen);

	fov = 45.f * D2R * 0.5f;
	
	camPos.x = 0;
	camPos.y = 0;
	camPos.z = -10;

	m.position.x = 0;
	m.position.y = 0;
	m.position.z = 5;

	vec3* ve;
	ve = new vec3;
	ve->x = -1;
	ve->y = 1;
	ve->z = -1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = 1;
	ve->z = -1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = -1;
	ve->z = -1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = -1;
	ve->z = -1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = 1;
	ve->z = 1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = 1;
	ve->z = 1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = -1;
	ve->z = 1;
	m.vertex.insert(m.vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = -1;
	ve->z = 1;
	m.vertex.insert(m.vertex.end(), ve);

	poly* po;
	po = new poly;
	po->idx[0] = 0;
	po->idx[1] = 1;
	po->idx[2] = 2;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 1;
	po->idx[1] = 3;
	po->idx[2] = 2;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 4;
	po->idx[1] = 0;
	po->idx[2] = 6;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 0;
	po->idx[1] = 2;
	po->idx[2] = 6;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 4;
	po->idx[2] = 6;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 7;
	po->idx[1] = 5;
	po->idx[2] = 6;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 1;
	po->idx[1] = 5;
	po->idx[2] = 3;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 7;
	po->idx[2] = 3;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 4;
	po->idx[1] = 5;
	po->idx[2] = 0;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 1;
	po->idx[2] = 0;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 7;
	po->idx[1] = 6;
	po->idx[2] = 2;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);
	po = new poly;
	po->idx[0] = 3;
	po->idx[1] = 7;
	po->idx[2] = 2;
	po->hide = false;
	m.polygon.insert(m.polygon.end(), po);

	char inT;
	while(true)
	{
		inT = _getch();
		system("cls");
		switch (inT)
		{
		case 'd':
			camPos.x -= 0.1f;
			break;
		case 'a':
			camPos.x += 0.1f;
			break;
		case 'w':
			camPos.z -= 0.1f;
			break;
		case 's':
			camPos.z += 0.1f;
			break;
		case 'r':
			camPos.y += 0.1f;
			break;
		case 'f':
			camPos.y -= 0.1f;
			break;
		case 'c':
			return;
			break;
		default:
			break;
		}

		for (int i = 0; i < m.polygon.size(); ++i)
		{
			vec3 point[3];
			vec3 line[3];
			bool sethide = true;
			
			for(int j = 0; j < 3; ++j)
			{
				line[j].x = point[j].x = atan((m.vertex[m.polygon[i]->idx[j]]->x + m.position.x - camPos.x) / (m.vertex[m.polygon[i]->idx[j]]->z + m.position.z - camPos.z));
				line[j].y = point[j].y = atan((m.vertex[m.polygon[i]->idx[j]]->y + m.position.y - camPos.y) / (m.vertex[m.polygon[i]->idx[j]]->z + m.position.z - camPos.z));
				if(!(point[j].x > fov * 0.5f || point[j].x < -fov * 0.5f) && !(point[j].y > fov * 0.5f || point[j].y < -fov * 0.5f))
					sethide = false;
				point[j].x /= fov / SCREENW;
				point[j].y /= fov / SCREENW;
//				printf("%f / %f / %f\n", point[j].x, point[j].y, fov * 0.5f);
			}
			if(sethide)
			{
//				printf("hide\n");
				continue;
			}
			for(int j = 0; j < 3; ++j)
			{
				MoveToEx(mydc, SCREENW * 0.5f + point[j].x, SCREENH * 0.5f - point[j].y, 0);
				LineTo(mydc, SCREENW * 0.5f + point[j != 2 ? j + 1 : 0].x, SCREENH * 0.5f - point[j != 2 ? j + 1 : 0].y);
			}
		}
	}

	for (int i = 0; i < m.polygon.size(); ++i)
		if (m.polygon[i])
			delete m.polygon[i];
	m.polygon.clear();
	for (int i = 0; i < m.vertex.size(); ++i)
		if (m.vertex[i])
			delete m.vertex[i];
	m.vertex.clear();

	std::cin.ignore();
}