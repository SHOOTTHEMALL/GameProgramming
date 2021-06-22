#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Console.h"

using namespace std;

//Ű �Է�
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77


//��������
int currentX = 1;
int currentY = 1;
int randomX;
int randomY;
int asdfx[2]={0,};
int asdfy[2] = {0,};

//ȭ�� ����
void SetConsoleView()
{
	system("mode con:cols=120 lines=30");
	system("title MY WORK");
}

//�÷��̾� �̵�
void move(int dir)
{
	int dir_x = 0, dir_y = 0; //�ʱ�ȭ 

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

	if (ShowMap[currentY + dir_y][currentX + dir_x] != '-' && ShowMap[currentY + dir_y][currentX + dir_x] != '|' && ShowMap[currentY + dir_y][currentX + dir_x] != '+') //�浹üũ �÷��̾�� ��
	{
		if (ShowMap[currentY + dir_y][currentX + dir_x] == '$')
		{
			backgroundMap[currentY + dir_y][currentX + dir_x] = '$';
		}
		currentX += dir_x;//���� x��ġ
		currentY += dir_y;//���� y��ġ 
	}
	
}

//ù ��ŸƮ ȭ�� 
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
	cout << "�����Ϸ��� 'a'�� ��������";
	gotoXY(45, 15);
	cout << "���۹�";
	gotoXY(45, 17);
	cout << "fŰ : ��(+)�νñ� rŰ : �ٽý���";
	gotoXY(45, 18);
	cout << "���� 15���� �ν� �� �ֽ��� :3";
}

//����Ű�� �����¤���? üũ�սô�
bool ReadyGame()
{
	DrawReadyGame(); //�޴��� �׸��ϴ�

	playMusic(); //������ ����մϴ�

	while (true)
	{
		int key = GetKeyDown(); //Ű���� �޽��ϴ�
		key = tolower(key);

		if (key == 'a') //a�� ��������
		{
			return true;
		}
	}

	return false;
}
//Ŭ��� �Ͽ���!
void Clear()
{
	system("cls");
	gotoXY(45, 12);
	cout << "����� #�� �����Ͽ���.";
	exit(0);
}

//������ �����غ��ô�.
int StartGame()
{
	int ch; //Ű�� �޽��ϴ�.
	int color = 15; //���� �ν� �� �ִ� �����Դϴ�.


	Beep(1046.50, 1000); //���� ���� ����ϸ� �����մϴ�.

	while (true)
	{
		Sleep(10);
		system("cls");//ȭ���� ������

		displayScreen(currentX, currentY);
		int ax = 0;


		if (ShowMap[currentY][currentX] == '#') //#�� �����߾��
		{
			Clear(); //Ŭ���� ��
		}
		
		ch = _getch();
		if (ch == 0xE0 || ch == 0)//���ӵ�
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

			if (ch == 'f')//f�� ��������
			{
				if (color != 0)//0�̸� �۵��ϸ� �ȴ뿩
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
					}//���� �νŴ�. 
				}
			}
			else if (ch == 'r') //rŰ�� ������ �ٽ� ���� �����.
			{
				system("cls"); //�������
				currentX = 1;
				currentY = 1; //1,1�� �ʱ�ȭ
				createMaze(randomX, randomY);

				if (ReadyGame()) //�غ��ٸ�
				{
					StartGame(); //���!!
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



//�� ��
int main()
{

	SetConsoleView(); //ȭ�� ����

	createMaze(randomX, randomY); //���� �̷� ����



	while (true)
	{

		if (ReadyGame()) //����?
		{
			StartGame(); //��!
		}
	}

	return 0;
}