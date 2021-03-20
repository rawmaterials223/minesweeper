/* 信息安全 1952889 鲁灵伊 */
/* 伪图形界面相关函数的实现*/
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
函数名称：msg_char_to_int
功    能：鼠标感知坐标转换为行列数
输入参数：char r, int c 鼠标感知坐标
		  char *cc 子题1、2中函数需要列坐标，指针传参
		  int* rp, *cp 数组行列数
返 回 值：
说    明：
***************************************************************************/
void msg_char_to_int(char r, int c, char* cc, int* rp, int* cp)
{
	if (c <= 8)
		*cc = c + '1';
	else if (c >= 9)
		*cc = c - 9 + 'a';
	*rp = r - 'A';
	*cp = c;

	return;
}

/***************************************************************************
函数名称：msg_printgraph
功    能：输出边框
输入参数：int gx数组行数
		  int gy数组列数
返 回 值：
说    明：
***************************************************************************/
void msg_printgraph(int gx, int gy, char command)
{
	cct_cls();
	cout << endl;

	int num = 0;
	int flag = 0;
	int cap = 0;
	
	/*打印列坐标*/
	for (int i = 0; i < 2 * (3 * gy + 1); i++)
	{
		if (num < gy)
		{
			if ((flag == 5 && num <= 10) || (flag == 4 && num >= 11))
			{
				flag = 0;
				cout << num++;
			}
			else
			{
				flag++;
				cout << ' ';
			}
		}
	}
	cout << endl;

	for (int i = 0; i <= gx * 3; i++)
	{
		/*打印行坐标*/
		if (i % 3 == 2)
			cout << char('A' + cap++);

		for (int j = 0; j <= gy * 6; j++)
		{
			/*打印特殊四角制表符*/
			if (i == 0 && j == 0)
				cct_showstr(j + 2, i + 2, "╔", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == 0 && j == gy * 6)
				cct_showstr(j + 2, i + 2, "╗", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == gx * 3 && j == 0)
				cct_showstr(j + 2, i + 2, "╚", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == gx * 3 && j == gy * 6)
				cct_showstr(j + 2, i + 2, "╝", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else
			{
				if (i % 3 == 0)
				{
					/*打印特殊分割制表符*/
					if (i == 0)
					{
						if (j % 6 == 0 && j != 0)
							cct_showstr(j + 2, i + 2, "╦", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					else if (i == gx * 3)
					{
						if (j % 6 == 0 && j != 0)
							cct_showstr(j + 2, i + 2, "╩", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					else
					{
						if (j == 0)
							cct_showstr(j + 2, i + 2, "╠", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
						else if (j == gy * 6)
							cct_showstr(j + 2, i + 2, "╣", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
						else if (j % 6 == 0)
							cct_showstr(j + 2, i + 2, "╬", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					/*打印边界制表符*/
					if (j % 6 == 2)
					{
						cct_showstr(j + 2, i + 2, "═", COLOR_HWHITE, COLOR_HBLACK, 2, -1);
						j = j + 3;
					}
				}//if (i % 3 == 0)
				else
				{
					/*打印边界制表符与内部灰色/外部黄色色块*/
					if (j % 6 == 0)
						cct_showstr(j + 2, i + 2, "║", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					else if (j % 6 == 2)
					{
						if (command == '1')
							cct_showstr(j + 2, i + 2, " ", COLOR_WHITE, COLOR_BLACK, 4, -1);
						else
							cct_showstr(j + 2, i + 2, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
						
						j = j + 3;
					}
				}
			}
		}
		cct_setcolor();
		cout << endl;
	}
	cout << endl;

	return;
}

/***************************************************************************
函数名称：msg_printtable
功    能：显示内部数组
输入参数：int gx数组行数
		  int gy数组列数
		  char marrs[30][30]内部数组
		  char command'1' 内部数组打印
		              '2' 显示数组打印
返 回 值：
说    明：与msb_printtable不同，此函数包括坐标定位
***************************************************************************/
void msg_printtable(int gx, int gy, char arrs[30][30], char command)
{
	int m = 0, n = 0;
	for (int i = 0; i <= 3 * gx; i++)
	{
		if (i % 3 == 2)
		{
			n = 0;//important!!!
			for (int j = 0; j <= 6 * gy; j++)
			{
				if (j % 6 == 3)
				{
					switch (command)
					{
						case '1':
							if (arrs[m][n] != '*' && arrs[m][n] != '0')
								cct_showch(j + 2, i + 2, arrs[m][n], COLOR_WHITE, 8 + arrs[m][n] - '0', 1);

							else if (arrs[m][n] == '*')
								cct_showch(j + 2, i + 2, arrs[m][n], COLOR_WHITE, COLOR_BLACK, 1);
							break;
						case '2':
							if (arrs[m][n] != 'X')
							{
								cct_showstr(j + 1, i + 1, " ", COLOR_WHITE, COLOR_BLACK, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_WHITE, COLOR_BLACK, 4, -1);
								if (arrs[m][n] != '0')
									cct_showch(j + 2, i + 2, arrs[m][n], COLOR_WHITE, 8 + arrs[m][n] - '0', 1);
								else if (arrs[m][n] == '*')
									cct_showch(j + 2, i + 2, arrs[m][n], COLOR_WHITE, COLOR_BLACK, 1);
							}
					}
					cct_setcolor();
					n++;
				}
			}
			m++;//important!
		}
	}

	cout << endl << endl;

	return;
}

/***************************************************************************
函数名称：msg_printtable_withflag
功    能：显示内部数组
输入参数：int gx数组行数
		  int gy数组列数
		  char smarrs[30][30]显示数组
		  int colorflag[30][30]颜色标志 1红白色
										0褐色
		  int rp, cp
返 回 值：
说    明：与msb_printtable不同，此函数包括坐标定位
***************************************************************************/
void msg_printtable_withflag(int gx, int gy, char sarrs[30][30], int colorflag[30][30], int rp, int cp)
{
	int m = 0, n = 0;
	for (int i = 0; i <= 3 * gx; i++)
	{
		if (i % 3 == 2)
		{
			n = 0;//important!!!
			for (int j = 0; j <= 6 * gy; j++)
			{
				if (j % 6 == 3)
				{
					if (sarrs[m][n] == 'X')
					{
						if (m == rp && n == cp)
						{
							if (!colorflag[m][n]) //相当于!标记雷
							{
								colorflag[m][n] = 1;
								cct_showstr(j + 1, i + 1, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showch(j + 2, i + 2, '#', COLOR_HRED, COLOR_HWHITE, 1);
							}
							else //相当于#取消标记
							{
								colorflag[m][n] = 0;
								cct_showstr(j + 1, i + 1, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
							}
						}
						else //保持标记
						{
							if (!colorflag[m][n])
							{
								cct_showstr(j + 1, i + 1, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
							}
							else
							{
								cct_showstr(j + 1, i + 1, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showch(j + 2, i + 2, '#', COLOR_HRED, COLOR_HWHITE, 1);
							}
						}
					}
					else if (sarrs[m][n] != 'X')
					{
						cct_showstr(j + 1, i + 1, " ", COLOR_WHITE, COLOR_BLACK, 4, -1);
						cct_showstr(j + 1, i + 2, " ", COLOR_WHITE, COLOR_BLACK, 4, -1);
						if (sarrs[m][n] != '0')
							cct_showch(j + 2, i + 2, sarrs[m][n], COLOR_WHITE, COLOR_BLACK + sarrs[m][n] - '0', 1);
						else if(sarrs[m][n]=='*')
							cct_showch(j + 2, i + 2, sarrs[m][n], COLOR_WHITE, COLOR_BLACK, 1);
					}
					cct_setcolor();
					n++;
				}
			}
			m++;//important!
		}
	}

	cout << endl << endl;

	return;
}

/***************************************************************************
函数名称：msg_getmouse_and_keyboard
功    能：移动并判断鼠标，判断键盘ESC
输入参数：int gx数组行数
		  int gy数组列数
		  char*r,*c鼠标感知行列数，指针传参
返 回 值：鼠标/键盘识别结果
说    明：
***************************************************************************/
int msg_getmouse_and_keyboard(int gx, int gy, char* r, int* c)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int result;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			cct_gotoxy(0, 2 + gx * 3 + 1);
			if (X < 2 || Y < 2 || X >(2 + gy * 6) || Y >(2 + gx * 3)
				|| (Y - 2) % 3 == 0 || (X - 2) % 6 == 0 || (X - 2) % 6 == 2 || (X - 3) % 6 == 0)
			{
				cct_showch(0, 2 + gx * 3 + 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//清除上一次打印的残留
				cct_showstr(0, 2 + gx * 3 + 1, "[当前光标] 位置非法", COLOR_BLACK, COLOR_WHITE, 1);
			}
			else
			{
				*r = char((Y / 3 - 1) + 'A');
				*c = (X - 4) / 6;
				cout << "[当前光标] " << setw(2) << *r << " 行" << setw(2) << *c << " 列";
			}
			switch (maction)
			{
				case MOUSE_LEFT_BUTTON_CLICK: //按下左键
					loop = 0;
					cct_gotoxy(0, 2 + gx * 3 + 3);
					result = MOUSE_LEFT_BUTTON_CLICK;
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:
					loop = 0;
					result = MOUSE_RIGHT_BUTTON_CLICK;
					break;
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			loop = 0;
			result = keycode1; //case 1:ESC
							   //case 2:SPACE
		}
	}

	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标

	return result;
}

/***************************************************************************
函数名称：msg_5
功    能：第5题--生成内部数组，画出伪图形框架，显示内部数据
输入参数：
返 回 值：
说    明：由于子题5、6部分功能重复，因此相同功能部分合并
***************************************************************************/
void msg_ex5(int gx, int gy, int cnt, char arrs[30][30])
{
	msb_ex1(gx, gy, cnt, arrs, '*', '*');
	msg_printgraph(gx, gy, '1');
	msg_printtable(gx, gy, arrs, '1');

	return;
}

/***************************************************************************
函数名称：msg_ex7
功    能：第7题--打印表格，单击初始位置，生成内部数组，显示数组展开并打印
输入参数：
返 回 值：
说    明：由于子题7、8部分功能重复，因此相同功能部分合并
***************************************************************************/
void msg_ex7(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30])
{
	char r, cc;
	int c, rp, cp;
	msg_printgraph(gx, gy, '2');	//先打印表格
	while (msg_getmouse_and_keyboard(gx, gy, &r, &c) != MOUSE_LEFT_BUTTON_CLICK)//后感知鼠标左键点击坐标
		continue;
	msg_char_to_int(r, c, &cc, &rp, &cp);
	msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //再生成内部数组
	msg_printtable(gx, gy, sarrs, '2');		//终打印显示数组

	return;
}

/***************************************************************************
函数名称：msg_ex8
功    能：第8题--伪图形界面基础版
输入参数：
返 回 值：
说    明：
***************************************************************************/
void msg_ex8(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, cc;
	int c, rp, cp;
	int loop = 1;
	msg_printgraph(gx, gy, '2');	//先打印表格
	while (loop)
	{
		int action = msg_getmouse_and_keyboard(gx, gy, &r, &c);
		msg_char_to_int(r, c, &cc, &rp, &cp);
		switch (action)
		{
			case ESC:
				loop = 0;
				return;
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				loop = 0;
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //生成内部数组
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				break;
		}
	}
	loop = 1;
	while (loop && mst_iswin(sarrs, gx, gy) != cnt)
	{
		int action = msg_getmouse_and_keyboard(gx, gy, &r, &c);
		msg_char_to_int(r, c, &cc, &rp, &cp);
		switch (action)
		{
			case ESC:
				loop = 0;
				return;
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				msb_opentable(marrs, sarrs, gx, gy, rp, cp);
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				if (marrs[rp][cp] == '*')
				{
					cct_gotoxy(0, 2 + 3 * gx + 3);
					cout << "你输了，游戏结束" << endl;
					loop = 0;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				break;
		}
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)
	{
		cct_gotoxy(0, 2 + 3 * gx + 3);
		cout << "恭喜胜利，游戏结束" << endl;
	}

	return;
}

/***************************************************************************
函数名称：msg_ex9
功    能：第9题--伪图形界面完整版
输入参数：
返 回 值：
说    明：
***************************************************************************/
void msg_ex9(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, cc;
	int c, rp, cp;
	int loop = 1;
	clock_t start, finish;
	long double duration;
	msg_printgraph(gx, gy, '2');	
	cct_showstr(0, 0, "ESC退出，空格显示时间", COLOR_BLACK, COLOR_WHITE, 1, -1);
	start = clock();
	while (loop)
	{
		int action = msg_getmouse_and_keyboard(gx, gy, &r, &c);
		msg_char_to_int(r, c, &cc, &rp, &cp);
		switch (action)
		{
			case ESC:
				loop = 0;
				return;
				break;
			case SPACE:
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);			//清除打印残余
				cct_showstr(0, 0, "当前时间：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);	//醒目打印
				cout << setiosflags(ios::fixed) << setprecision(6) << duration << "秒，";
				cct_setcolor();
				cout << "ESC退出，空格显示时间";
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				loop = 0;
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //再生成内部数组
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);			//清除打印残余
				cct_showstr(0, 0, "剩余雷数：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);	//醒目打印
				cout << cnt - mst_flagedmine(colorflag);
				cct_setcolor();
				cout << " ESC退出，空格显示时间";
				break;
		}
	}
	loop = 1;
	while (loop && mst_iswin(sarrs, gx, gy) != cnt)
	{
		int action = msg_getmouse_and_keyboard(gx, gy, &r, &c);
		msg_char_to_int(r, c, &cc, &rp, &cp);
		switch (action)
		{
			case ESC:
				loop = 0;
				return;
				break;
			case SPACE:
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);
				cct_showstr(0, 0, "当前时间：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
				cout << setiosflags(ios::fixed) << setprecision(6) << duration << "秒，";
				cct_setcolor();
				cout << "ESC退出，空格显示时间";
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				msb_opentable(marrs, sarrs, gx, gy, rp, cp);
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				if (marrs[rp][cp] == '*')
				{
					finish = clock();
					duration = (long double)(finish - start) / CLOCKS_PER_SEC;
					cct_showstr(0, 2 + 3 * gx + 3, "共用时：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
					cout << setiosflags(ios::fixed) << setprecision(6) << duration << "秒，   ";
					cct_setcolor();
					cout << "你输了，游戏结束" << endl;
					loop = 0;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);
				cct_showstr(0, 0, "剩余雷数：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
				cout << cnt - mst_flagedmine(colorflag);
				cct_setcolor();
				cout << "ESC退出，空格显示时间";
				break;
		}
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)    
	{
		finish = clock();
		duration = (long double)(finish - start) / CLOCKS_PER_SEC;
		cct_showstr(0, 2 + 3 * gx + 3, "共用时：", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
		cout << setiosflags(ios::fixed) << setprecision(6) << duration << "秒，   ";
		cct_setcolor();
		cout << "恭喜胜利，游戏结束" << endl;
	}

	return;
}

/***************************************************************************
函数名称：
功    能：功能选择
输入参数：
返 回 值：
说    明：
***************************************************************************/
void msg_graphmine(char command, char mode)
{
	int gx, gy;
	int cnt;
	int cols, lines;
	char marrs[30][30];
	char sarrs[30][30] = { 'X' };
	int colorflag[30][30];
	char r;
	int c;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			sarrs[i][j] = 'X';
			colorflag[i][j] = 0;
		}
	}
	switch (mode)
	{
		case '1':
			gx = graph_value1;
			gy = graph_value1;
			cnt = mode_easy_mine;
			cols = border_value1;
			lines = border_value2;
			break;
		case '2':
			gx = graph_value2;
			gy = graph_value2;
			cnt = mode_mid_mine;
			cols = border_value3;
			lines = border_value4;
			break;
		case '3':
			gx = graph_value2;
			gy = graph_value3;
			cnt = mode_hard_mine;
			cols = border_value5;
			lines = border_value4;
			break;
	}
	/*设置缓冲区大小及显示字体*/
	cct_setfontsize("Terminal", 16, 8);
	cct_setconsoleborder(cols, lines);

	switch (command)
	{
		case '5':
			msg_ex5(gx, gy, cnt, marrs);
			cout << endl;
			break;
		case '6':
			msg_ex5(gx, gy, cnt, marrs);
			while (msg_getmouse_and_keyboard(gx, gy, &r, &c) != MOUSE_LEFT_BUTTON_CLICK)
				continue;
			break;
		case '7':
			msg_ex7(gx, gy, cnt, marrs, sarrs);
			cct_gotoxy(0, 2 + 3 * gx + 3);
			break;
		case '8':
			msg_ex8(gx, gy, cnt, marrs, sarrs, colorflag);
			cct_gotoxy(0, 2 + 3 * gx + 4);
			break;
		case '9':
			msg_ex9(gx, gy, cnt, marrs, sarrs, colorflag);
			cct_gotoxy(0, 2 + 3 * gx + 4);
			break;
	}

	return;
}