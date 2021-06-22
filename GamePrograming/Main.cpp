#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Console.h"

using namespace std;

//키 입력
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77


//전역변수
int currentX = 1;
int currentY = 1;
int randomX;
int randomY;
int asdfx[2]={0,};
int asdfy[2] = {0,};

//화면 구성
void SetConsoleView()
{
	system("mode con:cols=120 lines=30");
	system("title MY WORK");
}

//플레이어 이동
void move(int dir)
{
	int dir_x = 0, dir_y = 0; //초기화 

	switch (dir)
	{
	case LEFT:	
		dir_x = -1;
		break;
	case RIGHT:
		dir_x = 1;
		break;
	case UP:
		dir_y = -1;
		break;
	case DOWN:
		dir_y = 1;
		break;
	}

	if (ShowMap[currentY + dir_y][currentX + dir_x] != '-' && ShowMap[currentY + dir_y][currentX + dir_x] != '|' && ShowMap[currentY + dir_y][currentX + dir_x] != '+') //충돌체크 플레이어와 벽
	{
		if (ShowMap[currentY + dir_y][currentX + dir_x] == '$')
		{
			backgroundMap[currentY + dir_y][currentX + dir_x] = '$';
		}
		currentX += dir_x;//현재 x위치
		currentY += dir_y;//현재 y위치 
	}
	
}

//첫 스타트 화면 
void DrawReadyGame()
{
	system("cls");
	gotoXY(45, 10);
	cout << "==============================";
	gotoXY(45, 11);
	cout << "=========== GO To # ==========";
	gotoXY(45, 12);
	cout << "==============================";
	gotoXY(45, 13);
	cout << "시작하려면 'a'를 누르세요";
	gotoXY(45, 15);
	cout << "조작법";
	gotoXY(45, 17);
	cout << "f키 : 벽(+)부시기 r키 : 다시시작";
	gotoXY(45, 18);
	cout << "벽은 15번만 부실 수 있숴요 :3";
}

//시작키를 눌렀는ㄱ가? 체크합시다
bool ReadyGame()
{
	DrawReadyGame(); //메뉴를 그립니다

	playMusic(); //음악을 재생합니다

	while (true)
	{
		int key = GetKeyDown(); //키값을 받습니다
		key = tolower(key);

		if (key == 'a') //a를 누르세요
		{
			return true;
		}
	}

	return false;
}
//클리어를 하였다!
void Clear()
{
	system("cls");
	gotoXY(45, 12);
	cout << "당신은 #에 도달하였다.";
	exit(0);
}

//게임을 시작해봅시다.
int StartGame()
{
	int ch; //키를 받습니다.
	int color = 15; //벽을 부쉴 수 있는 갯수입니다.


	Beep(1046.50, 1000); //높은 도를 출력하며 시작합니다.

	while (true)
	{
		Sleep(10);
		system("cls");//화면을 지워요

		displayScreen(currentX, currentY);
		int ax = 0;


		if (ShowMap[currentY][currentX] == '#') //#에 도달했어요
		{
			Clear(); //클리어 ♥
		}
		
		ch = _getch();
		if (ch == 0xE0 || ch == 0)//ㅇㅣ동
		{
			ch = _getch();
			switch (ch)
			{
			case LEFT:
			case RIGHT:
			case UP:
			case DOWN:
				move(ch);
				break;
			}
		}

		else
		{
			ch = tolower(ch);

			if (ch == 'f')//f를 누르세요
			{
				if (color != 0)//0이면 작동하면 안대여
				{
					if (ShowMap[currentY - 1][currentX] == '+')
					{
						ShowMap[currentY - 1][currentX] = '.';
						color--;
					}
					else if (ShowMap[currentY + 1][currentX] == '+')
					{
						ShowMap[currentY + 1][currentX] = '.';
						color--;
					}
					else if (ShowMap[currentY][currentX - 1] == '+')
					{
						ShowMap[currentY][currentX - 1] = '.';
						color--;
					}
					else if (ShowMap[currentY][currentX + 1] == '+')
					{
						ShowMap[currentY][currentX + 1] = '.';
						color--;
					}//벽을 부신다. 
				}
			}
			else if (ch == 'r') //r키를 누르면 다시 맵을 만든다.
			{
				system("cls"); //다지운다
				currentX = 1;
				currentY = 1; //1,1로 초기화
				createMaze(randomX, randomY);

				if (ReadyGame()) //준비됬다면
				{
					StartGame(); //쏘세요!!
				}

			}
		}
		
		for (int y = 0; y < 121; y++)
		{
			for (int x = 0; x < 107; x++)
			{
				if (ShowMap[y][x] == '$')
				{
					asdfx[ax] = x;
					asdfy[ax] = y;
					ax++;
					if (asdfx[0] == currentX && asdfy[0] == currentY)
					{
						currentX = asdfx[1];
						currentY = asdfy[1];
					}
					else if (asdfx[1] == currentX && asdfy[1] == currentY)
					{
						currentX = asdfx[0];
						currentY = asdfy[0];
					}
				}
			}
		}
	}
	return 0;
}



//실 행
int main()
{

	SetConsoleView(); //화면 조정

	createMaze(randomX, randomY); //랜덤 미로 생성



	while (true)
	{

		if (ReadyGame()) //레디?
		{
			StartGame(); //고!
		}
	}

	return 0;
}