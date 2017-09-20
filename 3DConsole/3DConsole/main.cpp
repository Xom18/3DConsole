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

struct vec3{ float x, y, z; };			//좌표
struct poly{int idx[3];};				//면

struct mesh								//매쉬 정보
{
	std::vector<vec3*> vertex;			//점 정보
	std::vector<poly*> polygon;			//면 정보
	vec3 position;						//위치
	vec3 rotation;						//회전값
};

std::vector<mesh*> m;					//물체
vec3 camPos;							//카메라 위치
float fov;								//카메라 FOV

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

	//점 추가
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

	//물체 생성
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

	//물체 복제
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
		//조작 및 화면 초기화
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
		
		//투영
		for(int c = 0; c < m.size(); ++c)
		{
			for (int i = 0; i < m[c]->polygon.size(); ++i)
			{
				//화면상의 점 위치 계산
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
				//화면 바깥으로 나가면 안그림
				if(sethide)
					continue;
				//계산된 점 위치 기반으로 투영
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