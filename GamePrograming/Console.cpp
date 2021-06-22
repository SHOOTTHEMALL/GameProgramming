#include "Console.h"
#include <time.h>
//#include "Main.cpp"

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

//���� �׸��ϴ�. 
char ShowMap[21][108] =
{
	" -------------------------------------------------------------------------------------------------------- ",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|........................................................................................................|",
	"|.......................................................................................................#|",
	" -------------------------------------------------------------------------------------------------------- "
};

char backgroundMap[21][108];

//�̵�ó��
void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

//Ű�� �Է� �޽��ϴ�
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;

}

//ȭ���� �׷���
void displayScreen(int x, int y)
{
	{
		srand((unsigned)time(NULL)); //��������

		for (int y = 0; y < 21; y++) //���η� 21���ٱ���
		{
			for (int x = 0; x < 108; x++) // ���η� 108���ٱ���
			{
				gotoXY(x, y);
				//cout << ShowMap[y][x];
				_putch(ShowMap[y][x]);
			}
		}

		gotoXY(x, y); //���� ��ġ
		_putch('@'); //�÷��̾�
	}
}

void Init() // �缳�� �ٽ� �׸���. 
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 106; j++)
		{
			if (ShowMap[i][j] != '|' && ShowMap[i][j] != '-' && ShowMap[i][j] != ' ' && ShowMap[i][j] != '#') //'|'�� '-'�� ' '�� '#'�� �����ϰ�
			{
				ShowMap[i][j] = '.'; //���� ������ �׸���
			}

		}
	}
}

void createMaze(int& randomX, int& randomY) //�̷θ� �������� �����Ѵ�.
{
	Init();
	for (int i = 0; i < 370; i++) // ��� ���� ������. �� ���� < x���� �����ȴ�. 
	{
		randomX = rand() % 21;	//���θ� 21������ ������.
		randomY = rand() % 108; // ���η� 108������ ������

		if (ShowMap[randomX][randomY] == '.') //���� .�̶��
		{
			i--; //�ߺ�ó��
			ShowMap[randomX][randomY] = '+'; // +�� �ٲپ��
			continue;
		}
	}

	for (int i = 0; i < 2; i++) // ��� ���� ������. �� ���� < x���� �����ȴ�. 
	{
		randomX = rand() % 21;	//���θ� 21������ ������.
		randomY = rand() % 108; // ���η� 108������ ������

		if (ShowMap[randomX][randomY] == '.' && ShowMap[randomX][randomY] != '+') //���� .�̶��
		{
			i--; //�ߺ�ó��
			ShowMap[randomX][randomY] = '$'; // +�� �ٲپ��
			continue;
		}
	}
}

//������ �� ������ ����
char Mycurse[10] =
{
	'A', 'c', 'E', 'F', 'E', 'c', 'B', 'C', 'D', 'c',
};

//������ ����ؿ�
void playMusic()
{
	char Tone = 0; //�ʱ�ȭ. 

	//Beep(523.25, 1000);  //��, C
	//Beep(587.33, 1000);  //��, D
	//Beep(659.26, 1000);  //��, E
	//Beep(698.46, 1000);  //��, F
	//Beep(783.99, 1000);  //��, G
	//Beep(880.00, 1000);  //��, A	
	//Beep(987.77, 1000);  //��, B
	//Beep(1046.50, 1000);  //��, C

	for (int i = 0; i < 10; i++) //10���� �ҷ���
	{
		Tone = Mycurse[i];

		switch (Tone) //�濡 ���� �� �����̳� �� ���� �뷡�� �θ���.
		{
		case 'c':
			Beep(523.25, 500);
			break;
		case 'D':
			Beep(587.33, 500);
			break;
		case 'E':
			Beep(659.26, 500);
			break;
		case 'F':
			Beep(698.46, 500);
			break;
		case 'G':
			Beep(783.99, 500);
			break;
		case 'A':
			Beep(880.00, 500);
			break;
		case 'B':
			Beep(987.77, 500);
			break;
		case 'C':
			Beep(1046.50, 500);
			break;
		default:
			break;
		}
	}
}