/* 信息安全 1952889 鲁灵伊 */
#pragma once

#define mode_easy 1
#define mode_mid 2
#define mode_hard 3
#define mode_easy_mine 10
#define mode_mid_mine 40
#define mode_hard_mine 99
#define graph_value1 9
#define graph_value2 16
#define graph_value3 30
#define border_value1 60
#define border_value2 35
#define border_value3 101
#define border_value4 56
#define border_value5 185

#define CLOCKS_PER_SEC ((clock_t)1000) 
#define ESC 27
#define SPACE 32

/*与menu相关的函数*/
void msm_showmenu();
void msm_showsub_menu();
void msm_showinput();
void msm_shownote();
char msm_choosemenu(char move);

/*与内部数组相关的函数*/
void msb_arraymine(char command, char mode);
void msb_ex1(int gx, int gy, int cnt, char marrs[30][30], char r, char c);
void msb_ex2(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], char r, char c, int rp, int cp);
void msb_ex3(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30]);
void msb_ex4(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30]);
void msb_randommine(int gx, int gy, int cnt, char arrs[30][30], char r, char c);
void msb_marray(int gx, int gy, char arrs[30][30]);
void msb_opentable(char marrs[30][30], char sarrs[30][30], int gx, int gy, int x, int y);
int  msb_cntnum(char arrs);
char msb_cntmine(char marrs[30][30], int x, int y);
void msb_printtable(int gx, int gy, char arrs[30][30], char command, const char *prompt);
void msb_printtable_withflag(int gx, int gy, char sarrs[30][30], int colorflag[30][30],
	const char* prompt, int mineflag, int rp, int cp);
void msb_input_xy(int gx, int gy, char* r, char* c);
void msb_input_cxy(int gx, int gy, char* r, char* c, char* mineflag);
void msb_char_to_int(char r, char c, int* rp, int* cp);

/*工具函数*/
void mst_to_be_continued();
int  mst_iswin(char sarrs[30][30], int gx, int gy);
int  mst_flagedmine(int colorflag[30][30]);

/*与伪图形界面相关的函数*/
void msg_graphmine(char command, char mode);
void msg_printgraph(int gx, int gy, char command);
void msg_printtable(int gx, int gy, char arrs[30][30], char command);
void msg_printtable_withflag(int gx, int gy, char sarrs[30][30], int colorflag[30][30], int rp, int cp);
int  msg_getmouse_and_keyboard(int gx, int gy, char* r, int* c);
void msg_ex5(int gx, int gy, int cnt, char arrs[30][30]);
void msg_ex7(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30]);
void msg_ex8(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30]);
void msg_ex9(int gx, int gy, int cnt, char marrs[30][30], char sarrs[30][30], int colorflag[30][30]);
void msg_char_to_int(char r, int c, char* cc, int* rp, int* cp);