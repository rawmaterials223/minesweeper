/* ��Ϣ��ȫ 1952889 ³���� */
/*��Ҫ�Ĺ��ߺ�����������չ�����ж���Ϸ�Ƿ�ɹ�*/
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
�������ƣ�mst_to_be_continued
��    �ܣ������ʾ����������ʼ��
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void mst_to_be_continued()
{
	cout << "���س�������";
	while (char c = _getch() != '\r')
		continue;
	cct_cls();
	//init border
	cct_setfontsize("������", 24);
	cct_setconsoleborder(100, 30, 100, 30);
	return;
}

/***************************************************************************
�������ƣ�
��    �ܣ��ж���Ӯ
���������
�� �� ֵ��
˵    ����
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
�������ƣ�
��    �ܣ���¼����ǵ�����
���������
�� �� ֵ��
˵    ����
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