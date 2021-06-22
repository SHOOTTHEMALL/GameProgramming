#pragma once

#include <Windows.h>
#include <conio.h>

//맵 그리기
extern char ShowMap[21][108];
//이동키 핸들

extern char backgroundMap[21][108];
extern void gotoXY(int x, int y);
//키값 받기
extern int GetKeyDown();
//맵 그리기
extern void displayScreen(int x, int y);
//랜덤으로 맵에 + 생성
extern void createMaze(int& randomX, int& randomY);
//음악 재생
extern void playMusic();
//게임 시작시 나오는 멜로디
extern char Mycurse[10];