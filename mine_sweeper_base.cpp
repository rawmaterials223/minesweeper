/* 信息安全 1952889 鲁灵伊 */
/* 内部数组版相关函数的实现*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "mine_sweeper.h"
using namespace std;

/***************************************************************************
函数名称：msb_randommine
功    能：确定扫雷数组内地雷的位置
输入参数：int gx 数组行数
		  int gy 数组列数
		  int cnt 地雷数
		  char arrs[30][30] 扫雷数组
		  char r,c初始打开位置
返 回 值：
说    明：
***************************************************************************/
void msb_randommine(int gx, int gy, int cnt, char arrs[30][30], char r, char c)
{
	int i = 0, j = 0;
	int rp, cp;
	if (r == '*')
		rp = -1;
	if (c == '*')
		cp = -1;
	else
		msb_char_to_int(r, c, &rp, &cp);

	srand((unsigned)time(NULL));
	while (cnt > 0)
	{
		i = rand() % gx;	//i的范围为0~gx-1
		j = rand() % gy;	
		if (((i == rp - 1 || i == rp + 1 || i == rp) && 
			(j == cp - 1 || j == cp + 1 || j == cp)) && rp != -1 && cp != -1)
			continue;
		if (arrs[i][j] != '*')	//若该坐标已生成地雷，则重新生成 
		{
			arrs[i][j] = '*';
			cnt--;
		}
	}

	return;
}

/***************************************************************************
函数名称：msb_cntmine
功    能：确定非雷数组坐标周围雷数
输入参数：char marrs[30][30] 内部数组
          int x, y 输入坐标
返 回 值：char型雷数
说    明：
***************************************************************************/
char msb_cntmine(char marrs[30][30], int x, int y)
{
	return (msb_cntnum(marrs[x - 1][y]) + msb_cntnum(marrs[x + 1][y])
		+ msb_cntnum(marrs[x][y - 1]) + msb_cntnum(marrs[x][y + 1])
		+ msb_cntnum(marrs[x - 1][y - 1]) + msb_cntnum(marrs[x - 1][y + 1])
		+ msb_cntnum(marrs[x + 1][y - 1]) + msb_cntnum(marrs[x + 1][y + 1])) + '0';
}

/***************************************************************************
函数名称：msb_cntnum
功    能：确定数组坐标是否有地雷
输入参数：char arrs 
返 回 值：
说    明：
***************************************************************************/
int msb_cntnum(char arrs)
{
	if (arrs == '*')
		return 1;
	else
		return 0;
}

/***************************************************************************
函数名称：msb_marry
功    能：计算非雷位置周围8个位置的雷数，生成扫雷数组
输入参数：int gx 数组行数
		  int gy 数组列数
		  char arrs[30][30] 扫雷数组
返 回 值：
说    明：
***************************************************************************/
void msb_marray(int gx, int gy, char arrs[30][30])
{
	for (int i = 0; i < gx; i++)
	{
		for (int j = 0; j < gy; j++)
		{
			if (arrs[i][j] == '*')
				continue;
			else
				arrs[i][j] = msb_cntmine(arrs, i, j);
		}
	}

	return;
}

/***************************************************************************
函数名称：msb_printtable
功    能：打印坐标列，打印扫雷数组元素
输入参数：int gx 数组行数
		  int gy 数组列数
		  char arrs[30][30] 扫雷数组
		  char command '1' 普通打印
		               '2' 醒目打印
		  const char *prompt 输出提示
返 回 值：
说    明：
***************************************************************************/
void msb_printtable(int gx, int gy, char arrs[30][30], char command, const char *prompt)
{
	cout << prompt << endl;
	cout << "  |";
	for (int i = 1; i <= gy; i++)
	{
		if (i <= 9)
			cout << char(i + '0') << ' ';
		else
			cout << char(i - 10 + 'a') << ' ';
	}
	cout << endl;
	for (int i = 1; i <= (gy + 2) * 2; i++)
	{
		if (i == 3)
			cout << '+';
		else
			cout << '-';
	}
	cout << endl;
	for (int i = 0; i < gx; i++)
	{
		cout << char('A' + i) << " |";
		for (int j = 0; j < gy; j++)
		{
			if(command == '1')
				cout << arrs[i][j] << ' ';
			else if (command == '2')
			{
				if (arrs[i][j] != 'X')
					cct_setcolor(COLOR_HYELLOW, COLOR_HBLACK + arrs[i][j] - '0');
				cout << arrs[i][j];
				cct_setcolor();
				cout << ' ';
			}
		}
		cout << endl;
	}
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msb_printtable_withflag
功    能：打印坐标列，打印扫雷数组元素
输入参数：int gx 数组行数
		  int gy 数组列数
		  char sarrs[30][30] 显示数组
		  int colorflag[30][30]颜色标志 1 保留红白色
										0 黑白色
		  const char *prompt 输出提示
		  char mineflag 标记！/取消标记#/正常打印$
		  int rp, cp //标记/取消标记行列数
返 回 值：
说    明：移植困难，根据子题4重新做数组元素打印
***************************************************************************/
void msb_printtable_withflag(int gx, int gy, char sarrs[30][30], int colorflag[30][30],
	const char* prompt, int mineflag, int rp, int cp)
{
	cout << prompt << endl;
	cout << "  |";
	for (int i = 1; i <= gy; i++)
	{
		if (i <= 9)
			cout << char(i + '0') << ' ';
		else
			cout << char(i - 10 + 'a') << ' ';
	}
	cout << endl;
	for (int i = 1; i <= (gy + 2) * 2; i++)
	{
		if (i == 3)
			cout << '+';
		else
			cout << '-';
	}
	cout << endl;
	for (int i = 0; i < gx; i++)
	{
		cout << char('A' + i) << " |";
		for (int j = 0; j < gy; j++)
		{
			if (sarrs[i][j] == 'X')
			{
				if (i == rp && j == cp)
				{
					if (mineflag == '!')
					{
						colorflag[i][j] = 1;
						cct_setcolor(COLOR_HRED, COLOR_HWHITE);
					}
					else if (mineflag == '#')
						colorflag[i][j] = 0;
				}
				else
					if (colorflag[i][j] == 1)
						cct_setcolor(COLOR_HRED, COLOR_HWHITE);
			}
			else if (sarrs[i][j] != 'X')
				if (sarrs[i][j] != '*')
					cct_setcolor(COLOR_HYELLOW, COLOR_HBLACK + sarrs[i][j] - '0');

			cout << sarrs[i][j];
			cct_setcolor();
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msb_opentable
功    能：以输入坐标为中心，找到相连的0向四周扩散
输入参数：char marrs[30][30] 内部数组
		  char sarrs[30][30] 显示数组
		  int x, y 输入横纵坐标
返 回 值：
说    明：
***************************************************************************/
void msb_opentable(char marrs[30][30], char sarrs[30][30], int gx, int gy, int x, int y)
{
	if (!msb_cntnum(marrs[x][y]))
	{
		if (msb_cntmine(marrs, x, y) == '0')
		{
			sarrs[x][y] = '0';
			if ((x - 1) >= 0 && (x - 1) < gx && (y - 1) >= 0 && (y - 1) < gy 
				&& sarrs[x - 1][y - 1] == 'X' && marrs[x - 1][y - 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x - 1, y - 1);

			if (x >= 0 && x < gx && (y - 1) >= 0 && (y - 1) < gy 
				&& sarrs[x][y - 1] == 'X' && marrs[x][y - 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x, y - 1);

			if ((x + 1) >= 0 && (x + 1) < gx && (y - 1) >= 0 && (y - 1) < gy 
				&& sarrs[x + 1][y - 1] == 'X' && marrs[x + 1][y - 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x + 1, y - 1);

			if ((x - 1) >= 0 && (x - 1) < gx && y >= 0 && y < gy 
				&& sarrs[x - 1][y] == 'X' && marrs[x - 1][y] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x - 1, y);

			if ((x + 1) >= 0 && (x + 1) < gx && y >= 0 && y < gy 
				&& sarrs[x + 1][y] == 'X' && marrs[x + 1][y] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x + 1, y);

			if ((x - 1) >= 0 && (x - 1) < gx && (y + 1) >= 0 && (y + 1) < gy 
				&& sarrs[x - 1][y + 1] == 'X' && marrs[x - 1][y + 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x - 1, y + 1);

			if (x >= 0 && x < gx && (y + 1) >= 0 && (y + 1) < gy 
				&& sarrs[x][y + 1] == 'X' && marrs[x][y + 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x, y + 1);

			if ((x + 1) >= 0 && (x + 1) < gx && (y + 1) >= 0 && (y + 1) < gy 
				&& sarrs[x + 1][y + 1] == 'X' && marrs[x + 1][y + 1] != '*')
				msb_opentable(marrs, sarrs, gx, gy, x + 1, y + 1);
		}
		else
			sarrs[x][y] = msb_cntmine(marrs, x, y);
	}
	else
		sarrs[x][y] = '*';

	return;
}

/***************************************************************************
函数名称：msb_input_xy
功    能：输入非雷位置的行列坐标（包括判定输入错误）
输入参数：int gx, gy 行列最大值，判定输入错误用
          char *r, *c 输入行列坐标，指针传参
返 回 值：
说    明：
***************************************************************************/
void msb_input_xy(int gx, int gy, char *r, char *c)
{
	while (1)
	{
		*r = _getch();
		while (cin.fail())
			cin.clear();
		if (*r == 'Q' || *r == 'q')
		{
			cout << *r;
			cout << endl << endl;
			return;
		}
		if (*r >= 'A' && *r <= 'Z' && *r <= gx + 'A')
		{
			cout << *r;
			break;
		}
	}

	while (1)
	{
		*c = _getch();
		while (cin.fail())
			cin.clear();
		if ((*c >= '1' && *c <= '9') || (*c >= 'a' && *c <= 'u' && *c <= (gy - 10) + 'a'))
		{
			cout << *c;
			break;
		}
	}
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msb_input_cxy
功    能：输入非雷位置的行列坐标（包括判定输入错误）与特殊字符
输入参数：int gx, gy 行列最大值，判定输入错误用
		  char *r, *c 输入行列坐标，指针传参
		  char *mineflag 特殊字符，指针传参
返 回 值：
说    明：
***************************************************************************/
void msb_input_cxy(int gx, int gy, char* r, char* c, char* mineflag)
{
	while (1)
	{
		char ch = _getch();
		while (cin.fail())
			cin.clear();
		if (ch == 'Q' || ch == 'q')
		{
			*mineflag = ch;
			cout << *mineflag << endl << endl;
			return;
		}
		else if (ch == '&')
		{
			*mineflag = ch;
			cout << *mineflag << endl << endl;
			return;
		}
		else if (ch == '!' || ch == '#')
		{
			*mineflag = ch;
			cout << *mineflag;
			break;
		}
		else if (ch >= 'A' && ch <= 'Z' && ch <= gx + 'A')
		{
			*mineflag = '$';
			*r = ch;
			cout << *r;
			while (1)
			{
				*c = _getch();
				while (cin.fail())
					cin.clear();
				if ((*c >= '1' && *c <= '9') || (*c >= 'a' && *c <= 'u' && *c <= (gy - 10) + 'a'))
				{
					cout << *c;
					break;
				}
			}
			return;
		}
	}
	if (*mineflag == '!' || *mineflag == '#')
		msb_input_xy(gx, gy, r, c);

	return;
}

/***************************************************************************
函数名称：msb_char_to_init
功    能：由char型变量转为相应int型数值
输入参数：char r, c 输入行列坐标
		  int *rp, *cp 行列坐标的int型值，指针传参
返 回 值：
说    明：
***************************************************************************/
void msb_char_to_int(char r, char c, int* rp, int* cp)
{
	*rp = r - 'A';
	*cp = c - '1';
	if (c >= '1' && c <= '9')
		*cp = c - '1';
	else if (c >= 'a' && c <= 'u')
		*cp = c - 'a' + 9;

	return;
}

/***************************************************************************
函数名称：msb_ex1
功    能：第1题--生成内部数组，打印内部数组
输入参数：
返 回 值：
说    明：由于子题5、6需要内部数组，功能与子题1重复，因此相同功能部分合并
***************************************************************************/
void msb_ex1(int gx, int gy, int cnt, char marrs[30][30], char r, char c)
{
	msb_randommine(gx, gy, cnt, marrs, r, c);
	msb_marray(gx, gy, marrs);

	return;
}

/***************************************************************************
函数名称：msb_ex2
功    能：第2题--由初始位置生成内部数组，打开显示数组并打印
输入参数：
返 回 值：
说    明：由于子题3、4、7、8、9功能重复，因此合并相同功能部分
***************************************************************************/
void msb_ex2(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], char r, char c, int rp, int cp)
{
	msb_ex1(gx, gy, cnt, marrs, r, c);
	msb_opentable(marrs, sarrs, gx, gy, rp, cp);

	return;
}

/***************************************************************************
函数名称：msb_ex3
功    能：第3题--数组基础版
输入参数：
返 回 值：
说    明：
***************************************************************************/
void msb_ex3(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30])
{
	char r, c;//记录初始行列位置
	int rp = -1, cp = -1;
	msb_printtable(gx, gy, sarrs, '1', "内部数组：");
	msm_showinput();
	msb_input_xy(gx, gy, &r, &c);
	if (r == 'Q' || r == 'q')
		return;
	msb_char_to_int(r, c, &rp, &cp);
	cout << endl;
	msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);
	msb_printtable(gx, gy, sarrs, '2', "当前数组：");
	while (mst_iswin(sarrs, gx, gy) != cnt)//判断输赢--显示数组X个数=雷数
	{
		msm_showinput();
		msb_input_xy(gx, gy, &r, &c);
		if (r == 'Q' || r == 'q')
			return;
		msb_char_to_int(r, c, &rp, &cp);
		cout << endl;
		msb_opentable(marrs, sarrs, gx, gy, rp, cp);
		//msb_printtable(gx, gy, marrs, '1');//辅助debug，快速完成扫雷
		msb_printtable(gx, gy, sarrs, '2', "当前数组：");
		if (marrs[rp][cp] == '*')
		{
			cout << "你输了，游戏结束" << endl;
			break;
		}
		else
			continue;
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)
		cout << "恭喜胜利，游戏结束" << endl;
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msb_ex4
功    能：第4题--数组完整版
输入参数：
返 回 值：
说    明：
***************************************************************************/
void msb_ex4(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, c;//记录初始行列位置
	char mineflag = '$';
	int rp = -1, cp = -1;
	int loop = 1;

	msb_printtable_withflag(gx, gy, sarrs, colorflag, "内部数组：", '$', 999, 999);
	//clock()函数，返回从开始这个进程到程序中调用clock()时CPU时钟计时单元数
	//clock_t长整型
	clock_t start, finish;
	long double duration;
	start = clock();
	while (loop)
	{
		msm_shownote(); //输入提示
		msm_showinput();//输入提示
		msb_input_cxy(gx, gy, &r, &c, &mineflag);
		msb_char_to_int(r, c, &rp, &cp);
		switch (mineflag)
		{
			case 'Q'://退出
			case 'q':
				loop = 0;
				return;
				break;
			case '&'://取时间函数
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cout << "已运行时间：" << setiosflags(ios::fixed) << setprecision(2) << duration << "秒" << endl;
				break;
			case '!':
			case '#':
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "内部数组：", mineflag, rp, cp);
				break;
			case '$':
				loop = 0;
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);//由初始位置生成内部数组并展开
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "点开后的数组：", '$', 999, 999);
				break;
		}
	}
	loop = 1;
	while (loop && mst_iswin(sarrs, gx, gy) != cnt)
	{
		msm_shownote(); //输入提示
		msm_showinput();//输入提示
		msb_input_cxy(gx, gy, &r, &c, &mineflag);
		msb_char_to_int(r, c, &rp, &cp);
		switch (mineflag)
		{
			case 'Q':
			case 'q':
				loop = 0;
				return;
				break;
			case '&'://取时间函数
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cout << "已运行时间：" << setiosflags(ios::fixed) << setprecision(2) << duration << "秒" << endl;
				break;
			case '!':
			case '#':
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "内部数组：", mineflag, rp, cp);
				break;
			case '$':
				msb_opentable(marrs, sarrs, gx, gy, rp, cp);
				//msb_printtable(gx, gy, marrs, '1');//辅助debug，快速完成扫雷
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "内部数组：", '$', 999, 999);
				if (marrs[rp][cp] == '*')
				{
					loop = 0;
					cout << "你输了，游戏结束" << endl;
				}
				break;
		}
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)
		cout << "恭喜胜利，游戏结束" << endl;
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msb_arrymine
功    能：根据选择难度，确定数组大小和地雷数量
输入参数：char mode 选择难度
          char command 选择功能
返 回 值：
说    明：
***************************************************************************/
void msb_arraymine(char command, char mode)
{
	int gx, gy;
	int cnt;
	char marrs[30][30];
	char sarrs[30][30] = { 'X' };
	int colorflag[30][30];
	char r, c;//记录初始行列位置
	int rp = -1, cp = -1;
	if (command != '1')
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				sarrs[i][j] = 'X';
		if (command == '4')
			for (int i = 0; i < 30; i++)
				for (int j = 0; j < 30; j++)
					colorflag[i][j] = 0;
	}
	switch (mode)
	{
		case '1':
			gx = graph_value1;
			gy = graph_value1;
			cnt = mode_easy_mine;
			break;
		case '2':
			gx = graph_value2;
			gy = graph_value2;
			cnt = mode_mid_mine;
			break;
		case '3':
			gx = graph_value2;
			gy = graph_value3;
			cnt = mode_hard_mine;
			break;
	}
	cct_cls();
	switch (command)
	{
		case '1':
			msb_ex1(gx, gy, cnt, marrs, '*', '*');
			msb_printtable(gx, gy, marrs, '1', "内部数组：");
			break;
		case '2':
			msb_printtable(gx, gy, sarrs, '1', "内部数组：");
			msm_showinput();
			msb_input_xy(gx, gy, &r, &c);
			if (r == 'Q' || r == 'q')
				return;
			msb_char_to_int(r, c, &rp, &cp);
			cout << endl;
			msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);
			msb_printtable(gx, gy, sarrs, '2', "点开后的数组：");
			break;
		case '3':
			msb_ex3(gx, gy, cnt, marrs, sarrs);
			break;
		case '4':
			msb_ex4(gx, gy, cnt, marrs, sarrs, colorflag);
			break;
	}

	return;
}