/* 信息安全 1952889 鲁灵伊 */
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
int main()
{
	cct_setfontsize("新宋体", 24);
	cct_setconsoleborder(100, 30, 100, 30);
	
	while (1)
	{
		msm_showmenu();
		char command = msm_choosemenu('1');
		char mode = '1';
		switch (command)
		{
			case '0':
				return 0;
			case '1':
			case '2':
			case '3':
			case '4':
				msm_showsub_menu();
				mode = msm_choosemenu('2');
				msb_arraymine(command, mode);
				break;

			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				msm_showsub_menu();
				mode = msm_choosemenu('2');
				msg_graphmine(command, mode);
				break;
		}

		mst_to_be_continued();
	}

	return 0;
}