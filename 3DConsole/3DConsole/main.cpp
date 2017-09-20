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

struct vec3{ float x, y, z; };			//��ǥ
struct poly{int idx[3];};				//��

struct mesh								//�Ž� ����
{
	std::vector<vec3*> vertex;			//�� ����
	std::vector<poly*> polygon;			//�� ����
	vec3 position;						//��ġ
	vec3 rotation;						//ȸ����
};

std::vector<mesh*> m;					//��ü
vec3 camPos;							//ī�޶� ��ġ
float fov;								//ī�޶� FOV

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

	mesh* tm = new mesh;
	tm->position.x = 0;
	tm->position.y = 0;
	tm->position.z = 5;

	//�� �߰�
	vec3* ve;
	ve = new vec3;
	ve->x = -1;
	ve->y = 1;
	ve->z = -1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = 1;
	ve->z = -1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = -1;
	ve->z = -1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = -1;
	ve->z = -1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = 1;
	ve->z = 1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = 1;
	ve->z = 1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = -1;
	ve->y = -1;
	ve->z = 1;
	tm->vertex.insert(tm->vertex.end(), ve);
	ve = new vec3;
	ve->x = 1;
	ve->y = -1;
	ve->z = 1;
	tm->vertex.insert(tm->vertex.end(), ve);

	//��ü ����
	poly* po;
	po = new poly;
	po->idx[0] = 0;
	po->idx[1] = 1;
	po->idx[2] = 2;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 1;
	po->idx[1] = 3;
	po->idx[2] = 2;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 4;
	po->idx[1] = 0;
	po->idx[2] = 6;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 0;
	po->idx[1] = 2;
	po->idx[2] = 6;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 4;
	po->idx[2] = 6;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 7;
	po->idx[1] = 5;
	po->idx[2] = 6;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 1;
	po->idx[1] = 5;
	po->idx[2] = 3;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 7;
	po->idx[2] = 3;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 4;
	po->idx[1] = 5;
	po->idx[2] = 0;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 5;
	po->idx[1] = 1;
	po->idx[2] = 0;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 7;
	po->idx[1] = 6;
	po->idx[2] = 2;
	tm->polygon.insert(tm->polygon.end(), po);
	po = new poly;
	po->idx[0] = 3;
	po->idx[1] = 7;
	po->idx[2] = 2;
	tm->polygon.insert(tm->polygon.end(), po);
	m.insert(m.end(), tm);

	//��ü ����
	for(int i = 0; i < 30; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			tm = new mesh;
			memcpy(tm, m.back(), sizeof(mesh));
			tm->position.x = j * 3;
			tm->position.z = i * 2;
			m.insert(m.end(), tm);
		}
	}

//	printf("%d / %f / %f\n", m.size(), m[0]->position.x, m[1]->position.x);

	char inT;
	while(true)
	{
		//���� �� ȭ�� �ʱ�ȭ
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
		
		//����
		for(int c = 0; c < m.size(); ++c)
		{
			for (int i = 0; i < m[c]->polygon.size(); ++i)
			{
				//ȭ����� �� ��ġ ���
				vec3 point[3];
				bool sethide = true;
			
				for(int j = 0; j < 3; ++j)
				{
					point[j].x = atan((m[c]->vertex[m[c]->polygon[i]->idx[j]]->x + m[c]->position.x - camPos.x) / (m[c]->vertex[m[c]->polygon[i]->idx[j]]->z + m[c]->position.z - camPos.z));
					point[j].y = atan((m[c]->vertex[m[c]->polygon[i]->idx[j]]->y + m[c]->position.y - camPos.y) / (m[c]->vertex[m[c]->polygon[i]->idx[j]]->z + m[c]->position.z - camPos.z));
					if(!(point[j].x > fov * 0.5f || point[j].x < -fov * 0.5f) && !(point[j].y > fov * 0.5f || point[j].y < -fov * 0.5f))
						sethide = false;
					point[j].x /= fov / SCREENW;
					point[j].y /= fov / SCREENW;
				}
				//ȭ�� �ٱ����� ������ �ȱ׸�
				if(sethide)
					continue;
				//���� �� ��ġ ������� ����
				for(int j = 0; j < 3; ++j)
				{
					MoveToEx(mydc, SCREENW * 0.5f + point[j].x, SCREENH * 0.5f - point[j].y, 0);
					LineTo(mydc, SCREENW * 0.5f + point[j != 2 ? j + 1 : 0].x, SCREENH * 0.5f - point[j != 2 ? j + 1 : 0].y);
				}
			}
		}
	}
	std::cin.ignore();
}