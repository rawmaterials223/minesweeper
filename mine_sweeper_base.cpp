/* ��Ϣ��ȫ 1952889 ³���� */
/* �ڲ��������غ�����ʵ��*/
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
�������ƣ�msb_randommine
��    �ܣ�ȷ��ɨ�������ڵ��׵�λ��
���������int gx ��������
		  int gy ��������
		  int cnt ������
		  char arrs[30][30] ɨ������
		  char r,c��ʼ��λ��
�� �� ֵ��
˵    ����
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
		i = rand() % gx;	//i�ķ�ΧΪ0~gx-1
		j = rand() % gy;	
		if (((i == rp - 1 || i == rp + 1 || i == rp) && 
			(j == cp - 1 || j == cp + 1 || j == cp)) && rp != -1 && cp != -1)
			continue;
		if (arrs[i][j] != '*')	//�������������ɵ��ף����������� 
		{
			arrs[i][j] = '*';
			cnt--;
		}
	}

	return;
}

/***************************************************************************
�������ƣ�msb_cntmine
��    �ܣ�ȷ����������������Χ����
���������char marrs[30][30] �ڲ�����
          int x, y ��������
�� �� ֵ��char������
˵    ����
***************************************************************************/
char msb_cntmine(char marrs[30][30], int x, int y)
{
	return (msb_cntnum(marrs[x - 1][y]) + msb_cntnum(marrs[x + 1][y])
		+ msb_cntnum(marrs[x][y - 1]) + msb_cntnum(marrs[x][y + 1])
		+ msb_cntnum(marrs[x - 1][y - 1]) + msb_cntnum(marrs[x - 1][y + 1])
		+ msb_cntnum(marrs[x + 1][y - 1]) + msb_cntnum(marrs[x + 1][y + 1])) + '0';
}

/***************************************************************************
�������ƣ�msb_cntnum
��    �ܣ�ȷ�����������Ƿ��е���
���������char arrs 
�� �� ֵ��
˵    ����
***************************************************************************/
int msb_cntnum(char arrs)
{
	if (arrs == '*')
		return 1;
	else
		return 0;
}

/***************************************************************************
�������ƣ�msb_marry
��    �ܣ��������λ����Χ8��λ�õ�����������ɨ������
���������int gx ��������
		  int gy ��������
		  char arrs[30][30] ɨ������
�� �� ֵ��
˵    ����
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
�������ƣ�msb_printtable
��    �ܣ���ӡ�����У���ӡɨ������Ԫ��
���������int gx ��������
		  int gy ��������
		  char arrs[30][30] ɨ������
		  char command '1' ��ͨ��ӡ
		               '2' ��Ŀ��ӡ
		  const char *prompt �����ʾ
�� �� ֵ��
˵    ����
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
�������ƣ�msb_printtable_withflag
��    �ܣ���ӡ�����У���ӡɨ������Ԫ��
���������int gx ��������
		  int gy ��������
		  char sarrs[30][30] ��ʾ����
		  int colorflag[30][30]��ɫ��־ 1 �������ɫ
										0 �ڰ�ɫ
		  const char *prompt �����ʾ
		  char mineflag ��ǣ�/ȡ�����#/������ӡ$
		  int rp, cp //���/ȡ�����������
�� �� ֵ��
˵    ������ֲ���ѣ���������4����������Ԫ�ش�ӡ
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
�������ƣ�msb_opentable
��    �ܣ�����������Ϊ���ģ��ҵ�������0��������ɢ
���������char marrs[30][30] �ڲ�����
		  char sarrs[30][30] ��ʾ����
		  int x, y �����������
�� �� ֵ��
˵    ����
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
�������ƣ�msb_input_xy
��    �ܣ��������λ�õ��������꣨�����ж��������
���������int gx, gy �������ֵ���ж����������
          char *r, *c �����������ָ꣬�봫��
�� �� ֵ��
˵    ����
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
�������ƣ�msb_input_cxy
��    �ܣ��������λ�õ��������꣨�����ж���������������ַ�
���������int gx, gy �������ֵ���ж����������
		  char *r, *c �����������ָ꣬�봫��
		  char *mineflag �����ַ���ָ�봫��
�� �� ֵ��
˵    ����
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
�������ƣ�msb_char_to_init
��    �ܣ���char�ͱ���תΪ��Ӧint����ֵ
���������char r, c ������������
		  int *rp, *cp ���������int��ֵ��ָ�봫��
�� �� ֵ��
˵    ����
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
�������ƣ�msb_ex1
��    �ܣ���1��--�����ڲ����飬��ӡ�ڲ�����
���������
�� �� ֵ��
˵    ������������5��6��Ҫ�ڲ����飬����������1�ظ��������ͬ���ܲ��ֺϲ�
***************************************************************************/
void msb_ex1(int gx, int gy, int cnt, char marrs[30][30], char r, char c)
{
	msb_randommine(gx, gy, cnt, marrs, r, c);
	msb_marray(gx, gy, marrs);

	return;
}

/***************************************************************************
�������ƣ�msb_ex2
��    �ܣ���2��--�ɳ�ʼλ�������ڲ����飬����ʾ���鲢��ӡ
���������
�� �� ֵ��
˵    ������������3��4��7��8��9�����ظ�����˺ϲ���ͬ���ܲ���
***************************************************************************/
void msb_ex2(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], char r, char c, int rp, int cp)
{
	msb_ex1(gx, gy, cnt, marrs, r, c);
	msb_opentable(marrs, sarrs, gx, gy, rp, cp);

	return;
}

/***************************************************************************
�������ƣ�msb_ex3
��    �ܣ���3��--���������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void msb_ex3(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30])
{
	char r, c;//��¼��ʼ����λ��
	int rp = -1, cp = -1;
	msb_printtable(gx, gy, sarrs, '1', "�ڲ����飺");
	msm_showinput();
	msb_input_xy(gx, gy, &r, &c);
	if (r == 'Q' || r == 'q')
		return;
	msb_char_to_int(r, c, &rp, &cp);
	cout << endl;
	msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);
	msb_printtable(gx, gy, sarrs, '2', "��ǰ���飺");
	while (mst_iswin(sarrs, gx, gy) != cnt)//�ж���Ӯ--��ʾ����X����=����
	{
		msm_showinput();
		msb_input_xy(gx, gy, &r, &c);
		if (r == 'Q' || r == 'q')
			return;
		msb_char_to_int(r, c, &rp, &cp);
		cout << endl;
		msb_opentable(marrs, sarrs, gx, gy, rp, cp);
		//msb_printtable(gx, gy, marrs, '1');//����debug���������ɨ��
		msb_printtable(gx, gy, sarrs, '2', "��ǰ���飺");
		if (marrs[rp][cp] == '*')
		{
			cout << "�����ˣ���Ϸ����" << endl;
			break;
		}
		else
			continue;
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)
		cout << "��ϲʤ������Ϸ����" << endl;
	cout << endl;

	return;
}

/***************************************************************************
�������ƣ�msb_ex4
��    �ܣ���4��--����������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void msb_ex4(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30])
{
	char r, c;//��¼��ʼ����λ��
	char mineflag = '$';
	int rp = -1, cp = -1;
	int loop = 1;

	msb_printtable_withflag(gx, gy, sarrs, colorflag, "�ڲ����飺", '$', 999, 999);
	//clock()���������شӿ�ʼ������̵������е���clock()ʱCPUʱ�Ӽ�ʱ��Ԫ��
	//clock_t������
	clock_t start, finish;
	long double duration;
	start = clock();
	while (loop)
	{
		msm_shownote(); //������ʾ
		msm_showinput();//������ʾ
		msb_input_cxy(gx, gy, &r, &c, &mineflag);
		msb_char_to_int(r, c, &rp, &cp);
		switch (mineflag)
		{
			case 'Q'://�˳�
			case 'q':
				loop = 0;
				return;
				break;
			case '&'://ȡʱ�亯��
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cout << "������ʱ�䣺" << setiosflags(ios::fixed) << setprecision(2) << duration << "��" << endl;
				break;
			case '!':
			case '#':
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "�ڲ����飺", mineflag, rp, cp);
				break;
			case '$':
				loop = 0;
				msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);//�ɳ�ʼλ�������ڲ����鲢չ��
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "�㿪������飺", '$', 999, 999);
				break;
		}
	}
	loop = 1;
	while (loop && mst_iswin(sarrs, gx, gy) != cnt)
	{
		msm_shownote(); //������ʾ
		msm_showinput();//������ʾ
		msb_input_cxy(gx, gy, &r, &c, &mineflag);
		msb_char_to_int(r, c, &rp, &cp);
		switch (mineflag)
		{
			case 'Q':
			case 'q':
				loop = 0;
				return;
				break;
			case '&'://ȡʱ�亯��
				finish = clock();
				duration = (long double)(finish - start) / CLOCKS_PER_SEC;
				cout << "������ʱ�䣺" << setiosflags(ios::fixed) << setprecision(2) << duration << "��" << endl;
				break;
			case '!':
			case '#':
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "�ڲ����飺", mineflag, rp, cp);
				break;
			case '$':
				msb_opentable(marrs, sarrs, gx, gy, rp, cp);
				//msb_printtable(gx, gy, marrs, '1');//����debug���������ɨ��
				msb_printtable_withflag(gx, gy, sarrs, colorflag, "�ڲ����飺", '$', 999, 999);
				if (marrs[rp][cp] == '*')
				{
					loop = 0;
					cout << "�����ˣ���Ϸ����" << endl;
				}
				break;
		}
	}
	if (mst_iswin(sarrs, gx, gy) == cnt)
		cout << "��ϲʤ������Ϸ����" << endl;
	cout << endl;

	return;
}

/***************************************************************************
�������ƣ�msb_arrymine
��    �ܣ�����ѡ���Ѷȣ�ȷ�������С�͵�������
���������char mode ѡ���Ѷ�
          char command ѡ����
�� �� ֵ��
˵    ����
***************************************************************************/
void msb_arraymine(char command, char mode)
{
	int gx, gy;
	int cnt;
	char marrs[30][30];
	char sarrs[30][30] = { 'X' };
	int colorflag[30][30];
	char r, c;//��¼��ʼ����λ��
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
			msb_printtable(gx, gy, marrs, '1', "�ڲ����飺");
			break;
		case '2':
			msb_printtable(gx, gy, sarrs, '1', "�ڲ����飺");
			msm_showinput();
			msb_input_xy(gx, gy, &r, &c);
			if (r == 'Q' || r == 'q')
				return;
			msb_char_to_int(r, c, &rp, &cp);
			cout << endl;
			msb_ex2(gx, gy, cnt, marrs, sarrs, r, c, rp, cp);
			msb_printtable(gx, gy, sarrs, '2', "�㿪������飺");
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