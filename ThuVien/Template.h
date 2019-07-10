#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <ctime>   
#include <cstdlib>
#include <fstream>
#include "ConsoleProcess.h"

using namespace std;

#define foru(i,a,b) for(int i=a; i<=b; i++)
#define ford(i,a,b) for(int i=a; i>=b; i--)
#define reset(a,b) memset(a,b,sizeof(a))
#define ha return 0
typedef long long int64;

/// cac phim bam
#define Normal_Color 15
#define Special_Color 159
#define Control_Enter 13
#define Control_Up 72
#define Control_Down 80
#define Control_Left 75
#define Control_Right 77
#define Control 224
#define Control_Esc 27
#define Control_BackSpace 8
#define Control_Ctrl 17
#define Control_Tab 9
#define CanLe 27
#define databasedocgia "datadocgia.txt"