#pragma once

#include <Windows.h>
#include <conio.h>

//�� �׸���
extern char ShowMap[21][108];
//�̵�Ű �ڵ�

extern char backgroundMap[21][108];
extern void gotoXY(int x, int y);
//Ű�� �ޱ�
extern int GetKeyDown();
//�� �׸���
extern void displayScreen(int x, int y);
//�������� �ʿ� + ����
extern void createMaze(int& randomX, int& randomY);
//���� ���
extern void playMusic();
//���� ���۽� ������ ��ε�
extern char Mycurse[10];