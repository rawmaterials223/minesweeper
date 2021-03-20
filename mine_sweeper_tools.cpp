/* 信息安全 1952889 鲁灵伊 */
/*需要的工具函数，例如拓展区域，判断游戏是否成功*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "mine_sweeper.h"
using namespace std;

/***************************************************************************
函数名称：mst_to_be_continued
功    能：输出提示，清屏，初始化
输入参数：
返 回 值：
说    明：
***************************************************************************/
void mst_to_be_continued()
{
	cout << "按回车键继续";
	while (char c = _getch() != '\r')
		continue;
	cct_cls();
	//init border
	cct_setfontsize("新宋体", 24);
	cct_setconsoleborder(100, 30, 100, 30);
	return;
}

/***************************************************************************
函数名称：
功    能：判断输赢
输入参数：
返 回 值：
说    明：
***************************************************************************/
int mst_iswin(char sarrs[30][30], int gx, int gy)
{
	int temp = 0;
	for (int i = 0; i < gx; i++)
	{
		for (int j = 0; j < gy; j++)
			if (sarrs[i][j] == 'X')
				temp++;
	}

	return temp;
}

/***************************************************************************
函数名称：
功    能：记录被标记的雷数
输入参数：
返 回 值：
说    明：
***************************************************************************/
int mst_flagedmine(int colorflag[30][30])
{
	int temp = 0;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
			if (colorflag[i][j] == 1)
				temp++;
	}

	return temp;
}