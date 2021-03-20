/* ��Ϣ��ȫ 1952889 ³���� */
/* αͼ�ν�����غ�����ʵ��*/
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
�������ƣ�msg_char_to_int
��    �ܣ�����֪����ת��Ϊ������
���������char r, int c ����֪����
		  char *cc ����1��2�к�����Ҫ�����ָ꣬�봫��
		  int* rp, *cp ����������
�� �� ֵ��
˵    ����
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
�������ƣ�msg_printgraph
��    �ܣ�����߿�
���������int gx��������
		  int gy��������
�� �� ֵ��
˵    ����
***************************************************************************/
void msg_printgraph(int gx, int gy, char command)
{
	cct_cls();
	cout << endl;

	int num = 0;
	int flag = 0;
	int cap = 0;
	
	/*��ӡ������*/
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
		/*��ӡ������*/
		if (i % 3 == 2)
			cout << char('A' + cap++);

		for (int j = 0; j <= gy * 6; j++)
		{
			/*��ӡ�����Ľ��Ʊ��*/
			if (i == 0 && j == 0)
				cct_showstr(j + 2, i + 2, "�X", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == 0 && j == gy * 6)
				cct_showstr(j + 2, i + 2, "�[", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == gx * 3 && j == 0)
				cct_showstr(j + 2, i + 2, "�^", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else if (i == gx * 3 && j == gy * 6)
				cct_showstr(j + 2, i + 2, "�a", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
			else
			{
				if (i % 3 == 0)
				{
					/*��ӡ����ָ��Ʊ��*/
					if (i == 0)
					{
						if (j % 6 == 0 && j != 0)
							cct_showstr(j + 2, i + 2, "�j", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					else if (i == gx * 3)
					{
						if (j % 6 == 0 && j != 0)
							cct_showstr(j + 2, i + 2, "�m", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					else
					{
						if (j == 0)
							cct_showstr(j + 2, i + 2, "�d", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
						else if (j == gy * 6)
							cct_showstr(j + 2, i + 2, "�g", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
						else if (j % 6 == 0)
							cct_showstr(j + 2, i + 2, "�p", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
					}
					/*��ӡ�߽��Ʊ��*/
					if (j % 6 == 2)
					{
						cct_showstr(j + 2, i + 2, "�T", COLOR_HWHITE, COLOR_HBLACK, 2, -1);
						j = j + 3;
					}
				}//if (i % 3 == 0)
				else
				{
					/*��ӡ�߽��Ʊ�����ڲ���ɫ/�ⲿ��ɫɫ��*/
					if (j % 6 == 0)
						cct_showstr(j + 2, i + 2, "�U", COLOR_HWHITE, COLOR_HBLACK, 1, -1);
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
�������ƣ�msg_printtable
��    �ܣ���ʾ�ڲ�����
���������int gx��������
		  int gy��������
		  char marrs[30][30]�ڲ�����
		  char command'1' �ڲ������ӡ
		              '2' ��ʾ�����ӡ
�� �� ֵ��
˵    ������msb_printtable��ͬ���˺����������궨λ
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
�������ƣ�msg_printtable_withflag
��    �ܣ���ʾ�ڲ�����
���������int gx��������
		  int gy��������
		  char smarrs[30][30]��ʾ����
		  int colorflag[30][30]��ɫ��־ 1���ɫ
										0��ɫ
		  int rp, cp
�� �� ֵ��
˵    ������msb_printtable��ͬ���˺����������궨λ
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
							if (!colorflag[m][n]) //�൱��!�����
							{
								colorflag[m][n] = 1;
								cct_showstr(j + 1, i + 1, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_HRED, COLOR_HWHITE, 4, -1);
								cct_showch(j + 2, i + 2, '#', COLOR_HRED, COLOR_HWHITE, 1);
							}
							else //�൱��#ȡ�����
							{
								colorflag[m][n] = 0;
								cct_showstr(j + 1, i + 1, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
								cct_showstr(j + 1, i + 2, " ", COLOR_YELLOW, COLOR_WHITE, 4, -1);
							}
						}
						else //���ֱ��
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
�������ƣ�msg_getmouse_and_keyboard
��    �ܣ��ƶ����ж���꣬�жϼ���ESC
���������int gx��������
		  int gy��������
		  char*r,*c����֪��������ָ�봫��
�� �� ֵ�����/����ʶ����
˵    ����
***************************************************************************/
int msg_getmouse_and_keyboard(int gx, int gy, char* r, int* c)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int result;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			cct_gotoxy(0, 2 + gx * 3 + 1);
			if (X < 2 || Y < 2 || X >(2 + gy * 6) || Y >(2 + gx * 3)
				|| (Y - 2) % 3 == 0 || (X - 2) % 6 == 0 || (X - 2) % 6 == 2 || (X - 3) % 6 == 0)
			{
				cct_showch(0, 2 + gx * 3 + 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//�����һ�δ�ӡ�Ĳ���
				cct_showstr(0, 2 + gx * 3 + 1, "[��ǰ���] λ�÷Ƿ�", COLOR_BLACK, COLOR_WHITE, 1);
			}
			else
			{
				*r = char((Y / 3 - 1) + 'A');
				*c = (X - 4) / 6;
				cout << "[��ǰ���] " << setw(2) << *r << " ��" << setw(2) << *c << " ��";
			}
			switch (maction)
			{
				case MOUSE_LEFT_BUTTON_CLICK: //�������
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

	cct_disable_mouse();	//�������
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//�򿪹��

	return result;
}

/***************************************************************************
�������ƣ�msg_5
��    �ܣ���5��--�����ڲ����飬����αͼ�ο�ܣ���ʾ�ڲ�����
���������
�� �� ֵ��
˵    ������������5��6���ֹ����ظ��������ͬ���ܲ��ֺϲ�
***************************************************************************/
void msg_ex5(int gx, int gy, int cnt, char arrs[30][30])
{
	msb_ex1(gx, gy, cnt, arrs, '*', '*');
	msg_printgraph(gx, gy, '1');
	msg_printtable(gx, gy, arrs, '1');

	return;
}

/***************************************************************************
�������ƣ�msg_ex7
��    �ܣ���7��--��ӡ��񣬵�����ʼλ�ã������ڲ����飬��ʾ����չ������ӡ
���������
�� �� ֵ��
˵    ������������7��8���ֹ����ظ��������ͬ���ܲ��ֺϲ�
***************************************************************************/
void msg_ex7(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30])
{
	char r, cc;
	int c, rp, cp;
	msg_printgraph(gx, gy, '2');	//�ȴ�ӡ���
	while (msg_getmouse_and_keyboard(gx, gy, &r, &c) != MOUSE_LEFT_BUTTON_CLICK)//���֪�������������
		continue;
	msg_char_to_int(r, c, &cc, &rp, &cp);
	msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //�������ڲ�����
	msg_printtable(gx, gy, sarrs, '2');		//�մ�ӡ��ʾ����

	return;
}

/***************************************************************************
�������ƣ�msg_ex8
��    �ܣ���8��--αͼ�ν��������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void msg_ex8(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, cc;
	int c, rp, cp;
	int loop = 1;
	msg_printgraph(gx, gy, '2');	//�ȴ�ӡ���
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
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //�����ڲ�����
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
					cout << "�����ˣ���Ϸ����" << endl;
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
		cout << "��ϲʤ������Ϸ����" << endl;
	}

	return;
}

/***************************************************************************
�������ƣ�msg_ex9
��    �ܣ���9��--αͼ�ν���������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void msg_ex9(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, cc;
	int c, rp, cp;
	int loop = 1;
	clock_t start, finish;
	long double duration;
	msg_printgraph(gx, gy, '2');	
	cct_showstr(0, 0, "ESC�˳����ո���ʾʱ��", COLOR_BLACK, COLOR_WHITE, 1, -1);
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
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);			//�����ӡ����
				cct_showstr(0, 0, "��ǰʱ�䣺", COLOR_BLACK, COLOR_HYELLOW, 1, -1);	//��Ŀ��ӡ
				cout << setiosflags(ios::fixed) << setprecision(6) << duration << "�룬";
				cct_setcolor();
				cout << "ESC�˳����ո���ʾʱ��";
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				loop = 0;
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, cc, rp, cp); //�������ڲ�����
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);			//�����ӡ����
				cct_showstr(0, 0, "ʣ��������", COLOR_BLACK, COLOR_HYELLOW, 1, -1);	//��Ŀ��ӡ
				cout << cnt - mst_flagedmine(colorflag);
				cct_setcolor();
				cout << " ESC�˳����ո���ʾʱ��";
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
				cct_showstr(0, 0, "��ǰʱ�䣺", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
				cout << setiosflags(ios::fixed) << setprecision(6) << duration << "�룬";
				cct_setcolor();
				cout << "ESC�˳����ո���ʾʱ��";
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				msb_opentable(marrs, sarrs, gx, gy, rp, cp);
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				if (marrs[rp][cp] == '*')
				{
					finish = clock();
					duration = (long double)(finish - start) / CLOCKS_PER_SEC;
					cct_showstr(0, 2 + 3 * gx + 3, "����ʱ��", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
					cout << setiosflags(ios::fixed) << setprecision(6) << duration << "�룬   ";
					cct_setcolor();
					cout << "�����ˣ���Ϸ����" << endl;
					loop = 0;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				msg_printtable_withflag(gx, gy, sarrs, colorflag, rp, cp);
				cct_showstr(0, 0, " ", COLOR_BLACK, COLOR_WHITE, 50, -1);
				cct_showstr(0, 0, "ʣ��������", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
				cout << cnt - mst_flagedmine(colorflag);
				cct_setcolor();
				cout << "ESC�˳����ո���ʾʱ��";
				break;
		}
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)    
	{
		finish = clock();
		duration = (long double)(finish - start) / CLOCKS_PER_SEC;
		cct_showstr(0, 2 + 3 * gx + 3, "����ʱ��", COLOR_BLACK, COLOR_HYELLOW, 1, -1);
		cout << setiosflags(ios::fixed) << setprecision(6) << duration << "�룬   ";
		cct_setcolor();
		cout << "��ϲʤ������Ϸ����" << endl;
	}

	return;
}

/***************************************************************************
�������ƣ�
��    �ܣ�����ѡ��
���������
�� �� ֵ��
˵    ����
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
	/*���û�������С����ʾ����*/
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