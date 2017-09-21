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

struct vec3			//좌표
{ 
	float x, y, z;

	vec3(double _x = 0, double _y = 0, double _z = 0){ x = _x; y = _y; z = _z; }
	vec3 operator +(vec3 inV){ vec3 t(0, 0, 0); t.x = x + inV.x; t.y = y + inV.y; t.z = z + inV.z; return t; }
	vec3 operator -(vec3 inV){ vec3 t(0, 0, 0); t.x = x - inV.x; t.y = y - inV.y; t.z = z - inV.z; return t; }
	vec3 operator *(vec3 inV){ vec3 t(0, 0, 0); t.x = x * inV.x; t.y = y * inV.y; t.z = z * inV.z; return t; }
	vec3 operator /(vec3 inV){ vec3 t(0, 0, 0); t.x = x / inV.x; t.y = y / inV.y; t.z = z / inV.z; return t; }

	void operator +=(vec3 inV){ x += inV.x; y += inV.y; z += inV.z; }
	void operator -=(vec3 inV){ x -= inV.x; y -= inV.y; z -= inV.z; }
	void operator *=(vec3 inV){ x *= inV.x; y *= inV.y; z *= inV.z; }
	void operator /=(vec3 inV){ x /= inV.x; y /= inV.y; z /= inV.z; }

	vec3 operator +(double inV){ vec3 t(0, 0, 0); t.x = x + inV; t.y = y + inV; t.z = z + inV; return t; }
	vec3 operator -(double inV){ vec3 t(0, 0, 0); t.x = x - inV; t.y = y - inV; t.z = z - inV; return t; }
	vec3 operator *(double inV){ vec3 t(0, 0, 0); t.x = x * inV; t.y = y * inV; t.z = z * inV; return t; }
	vec3 operator /(double inV){ vec3 t(0, 0, 0); t.x = x / inV; t.y = y / inV; t.z = z / inV; return t; }

	void operator +=(double inV){ x += inV; y += inV; z += inV; }
	void operator -=(double inV){ x -= inV; y -= inV; z -= inV; }
	void operator *=(double inV){ x *= inV; y *= inV; z *= inV; }
	void operator /=(double inV){ x /= inV; y /= inV; z /= inV; }
};
struct poly			//면
{
	int idx[3];
//	vec3 norm;
	poly(int _x = 0, int _y = 0, int _z = 0){ idx[0] = _x; idx[1] = _y; idx[2] = _z; }
};				

struct mesh								//매쉬 정보
{
	std::vector<vec3> vertex;			//점 정보
	std::vector<poly> polygon;			//면 정보
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

	fov = 60.f * D2R;
	
	camPos.x = 0;
	camPos.y = 0;
	camPos.z = -10;

	mesh* tm = new mesh;
	tm->position = vec3(0, 0, 5);

	//점 추가
	tm->vertex.insert(tm->vertex.end(), vec3(-1, 1, -1));
	tm->vertex.insert(tm->vertex.end(), vec3(1, 1, -1));
	tm->vertex.insert(tm->vertex.end(), vec3(-1, -1, -1));
	tm->vertex.insert(tm->vertex.end(), vec3(1, -1, -1));
	tm->vertex.insert(tm->vertex.end(), vec3(-1, 1, 1));
	tm->vertex.insert(tm->vertex.end(), vec3(1, 1, 1));
	tm->vertex.insert(tm->vertex.end(), vec3(-1, -1, 1));
	tm->vertex.insert(tm->vertex.end(), vec3(1, -1, 1));

	//면 생성
	tm->polygon.insert(tm->polygon.end(), poly(0, 1, 2));
	tm->polygon.insert(tm->polygon.end(), poly(1, 3, 2));
	tm->polygon.insert(tm->polygon.end(), poly(4, 0, 6));
	tm->polygon.insert(tm->polygon.end(), poly(0, 2, 6));
	tm->polygon.insert(tm->polygon.end(), poly(5, 4, 6));
	tm->polygon.insert(tm->polygon.end(), poly(7, 5, 6));
	tm->polygon.insert(tm->polygon.end(), poly(1, 5, 3));
	tm->polygon.insert(tm->polygon.end(), poly(5, 7, 3));
	tm->polygon.insert(tm->polygon.end(), poly(4, 5, 0));
	tm->polygon.insert(tm->polygon.end(), poly(5, 1, 0));
	tm->polygon.insert(tm->polygon.end(), poly(7, 6, 2));
	tm->polygon.insert(tm->polygon.end(), poly(3, 7, 2));
	m.insert(m.end(), tm);

	//물체 복제
//	for(int i = 0; i < 1; ++i)
//	{
//		for(int j = 0; j < 2; ++j)
//		{
//			tm = new mesh;
//			memcpy(tm, m.back(), sizeof(mesh));
//			tm->position.x = j * 3;
//			tm->position.z = i * 2;
//			m.insert(m.end(), tm);
//		}
//	}

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
			vec3* point = new vec3[m[c]->vertex.size()];

			//면 노말값 구하기
			//for(int i = 0; i < m[c]->polygon.size(); ++i)
			//{
			//	vec3 tx = m[c]->vertex[m[c]->polygon[i].idx[1]] - m[c]->vertex[m[c]->polygon[i].idx[0]];
			//	vec3 ty = m[c]->vertex[m[c]->polygon[i].idx[2]] - m[c]->vertex[m[c]->polygon[i].idx[0]];
			//	tx = vec3(tx.y * ty.z -tx.z * ty.y, tx.z * ty.x - tx.x * ty.z, tx.x * ty.y - tx.y * ty.x);
			//	m[c]->polygon[i].norm = tx / sqrt(pow(tx.x, 2) + pow(tx.y, 2) + pow(tx.z, 2));
			//}

			for (int i = 0; i < m[c]->vertex.size(); ++i)
			{
				point[i].x = atan((m[c]->vertex[i].x + m[c]->position.x - camPos.x) / (m[c]->vertex[i].z + m[c]->position.z - camPos.z));
				point[i].y = atan((m[c]->vertex[i].y + m[c]->position.y - camPos.y) / (m[c]->vertex[i].z + m[c]->position.z - camPos.z));
				printf("%f / %f\n", point[i].x * R2D, fov * R2D);
				point[i] /= fov / SCREENW;
			}
			//계산된 점 위치 기반으로 투영
			for (int i = 0; i < m[c]->polygon.size(); ++i)
			{
				vec3 f, t;
				//노말 판단한다음 그릴지 말지 정하게 해야됨

				for (int j = 0; j < 3; ++j)
				{

					f = point[m[c]->polygon[i].idx[j]];
					t = point[m[c]->polygon[i].idx[j == 2 ? 0 : j + 1]];
					MoveToEx(mydc, SCREENW * 0.5f + f.x, SCREENH * 0.5f - f.y, 0);
					LineTo(mydc, SCREENW * 0.5f + t.x, SCREENH * 0.5f - t.y);
					
//					Sleep(1);
//					printf("%f / %f / %f / %f / %f / %f / %f\n", camPos.x, camPos.y, camPos.z, f.x, f.y, t.x, t.y);
				}
			}
			delete point;
		}
	}
	for(int i = 0; i < m.size(); ++i)
	{
		delete m[i];
	}
	std::cin.ignore();
}