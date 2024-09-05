/* 信16 2251654 付宝莹 */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std; 
#define ROW_BOARDER 32
#define COL_BOARDER 55
/***************************************************************************
  函数名称：mention_print
  功    能：提示语句输出
  输入参数：casion情况
  返 回 值：无
  说    明：
***************************************************************************/
void mention_print(int casion) {
	switch (casion) {
		case 0:
			cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
			break;
		case 1:
			cout << "箭头键/鼠标移动，回车键/单击左键选择,Q/单击右键结束";
			break;
		case 2:
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
			break;
		case 3:
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成，Q/单击右键退出";
			break;
	}
}
/***************************************************************************
  函数名称：mouse_show
  功    能：判断鼠标以及键盘移动
  输入参数：行数、列数、星星数组、标记数组、code是否有分割线、菜单值、栈顶数组、选择所在行、选择所在列
  返 回 值：1/0继续进行or结束此菜单项
  说    明：该函数实现功能包括：显示鼠标、键盘所在行列/是否合法、是否选中、选中位置、选中是否合法、选中后颜色变化、移开后颜色变化……
***************************************************************************/
int mouse_show(int hang, int lie,int xing[][11],int search[][11],int code,int menu_case,int top[],char&row,int&col) {
	int Y_print = 3 * hang + (hang - 1) * code + 3;
	int ret_this = 0;
	if (1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;
		int pos = 0;
		int straight_kuang[10] = {0};
		for (int k = 0; k < lie - 1; k++) 
			straight_kuang[k] = 2 + 8 * (k + 1);
		
		cct_enable_mouse();
		while (loop) {
			clear_color(hang, lie, xing, search, code);
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				clear_color(hang, lie, xing, search, code);
				if(pos!=0)
					xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_BLACK,0);
				cct_gotoxy(0, Y_print+1);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				switch (maction) {
					case MOUSE_LEFT_BUTTON_CLICK:
						if (pos != 0) {
							int count = 0;
							if (menu_case < 6) {
								cout << "选中了" << row << "行" << col << "列                                                     " << endl;
								loop = 0;
								ret_this = 0;
								search[int(row) - 'A'][col] = 1;
							}
							else {
								seek_for_same(xing[int(row) - 'A'][col], xing, search, int(row) - 'A', col, hang, lie);
								count = count_xing(hang, lie, search);
								if (count == 1) {
									cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
									cout << "周围无相同值，";
									cct_setcolor(COLOR_BLACK, COLOR_WHITE);
									mention_print(3);
									ret_this = 0;
									search[int(row) - 'A'][col] = 1;
								}
								else
									mention_print(2);
							}
							for (int i = 0; i < hang; i++)
								for (int j = 0; j < lie; j++) {
									if (search[i][j] == 1) {
										xing_pic(i, j, xing[i][j], code, COLOR_WHITE,0);
									}
								}
							if (count > 1) {
								ret_this = 1;
								loop = 0;
								cct_disable_mouse();
								return 1;
							}
						}
						break;
					case MOUSE_ONLY_MOVED:
						cout << "[当前鼠标] ";
						if ((X < 5) || (X > COL_BOARDER - 1 + (lie - 1) * 2 * code) || (Y < 3) || (Y > 2 + 3 * hang + (hang - 1) * code)) {
							cout << "位置非法                                  ";
							pos = 0;
						}
						else {
							int kuang = 0;
							for (int i = 0; i < hang - 1; i++) {
								if (X == straight_kuang[i] || X == straight_kuang[i] + 1) {
									kuang = 1;
									break;
								}
							}
							if ((code == 1) && (((Y - 2) % 4 == 0) || kuang == 1)) {
								cout << "位置非法                                  ";
								pos = 0;
							}
							else {
								row = char(((Y - 3) / (3 + code)) + 'A');
								col = (X - 4) / (6 + 2 * code);
								pos = 1;
								if (xing[int(row) - 'A'][col] == 0){
									cout << "位置非法                                  ";
									pos = 0;
									xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE, 1);
								}
								else{
									cout << row << "行" << col << "列                                                                               ";
									xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE, 0);
								}
							}
						}
						break;
					default:
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						loop = 0;
						ret_this = 0;
						break;
					
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (pos != 0)
					xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_BLACK,0);
				cct_gotoxy(0, Y_print + 1);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				switch (keycode1) {
					case 224:
						cout << "[当前键盘] ";
						pos = 1;
						ret_this = 0;
						switch (keycode2) {
							case KB_ARROW_UP:
								if (row == 'A'+top[col])
									row = 'A' + lie - 1;
								else
									row--;
								break;
							case KB_ARROW_DOWN:
								if (row == 'A' + lie - 1)
									row = 'A'+top[col];
								else
									row++;
								break;
							case KB_ARROW_LEFT:
								if (col == 0)
								{
									col = lie - 1;
									while(1){
										if (xing[int(row) - 'A'][col] == 0)
											col--;
										else 
											break;
									}
								}
								else{
									col--;
									while (1) {
										if (xing[int(row) - 'A'][col] == 0)
											col--;
										else
											break;
									}
								}
								break;
							case KB_ARROW_RIGHT:
								if (col == lie - 1)
									col = 0;
								else
									col++;
								while (1) {
									if (xing[int(row) - 'A'][col] == 0)
										col++;
									else
										break;
								}
								break;
						}
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << row << "行" << col << "列                                                                                                ";
						xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE,0);
						break;
					case 81:
					case 113:
						loop = 0;
						ret_this = 0;
						break;
					case '\r':
						if (pos != 0) {
							int count = 0;
							if (menu_case < 6) {
								cout << "选中了" << row << "行" << col << "列                                                                " << endl;
								loop = 0;
								ret_this = 0;
								search[int(row) - 'A'][col] = 1;
							}
							else{
								seek_for_same(xing[int(row) - 'A'][col], xing, search, int(row) - 'A', col, hang, lie);
								count = count_xing(hang, lie, search);
								if (count == 1) {
									cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
									cout << "周围无相同值，";
									cct_setcolor(COLOR_BLACK, COLOR_WHITE);
									mention_print(3);
									ret_this = 0;
									search[int(row) - 'A'][col] = 1;
								}
								else
									mention_print(2);
							}
							for (int i = 0; i < hang; i++)
								for (int j = 0; j < lie; j++) {
									if (search[i][j] == 1) {
										xing_pic(i, j, xing[i][j], code, COLOR_WHITE,0);
									}
								}
							if (count > 1) {
								ret_this = 1;
								loop = 0;
							}
						}
						break;
				}
			}
		}
	}
	return ret_this;
}
/***************************************************************************
  函数名称：xing_pic
  功    能：按照输入的参数在指定位置画星星或补空白的函数
  输入参数：现在的行、列、星星颜色（该位置对应的数组的元素值）、有无边框、背景颜色（选中即白未选即黑）、white是否补全白色
  返 回 值：无
  说    明：该函数既可以填补元素值为0处的白色、也可画出选中/未选中的对应颜色星星
***************************************************************************/
void xing_pic(int hang_now, int lie_now, int color, int code,int back,int white) {
    int prim_x = 5 + lie_now * (6+2*code)-1;//初始x位置
	int prim_y = 4 + hang_now * (3+code)-1;//初始y位置
	if (white == 1) {//此时填补空白，这一步骤可以防止值为0的位置被画出灰色星星
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cct_gotoxy(prim_x, prim_y);
		cout << "      ";
		cct_gotoxy(prim_x, prim_y + 1);
		cout << "      ";
		cct_gotoxy(prim_x, prim_y + 2);
		cout << "      ";
	}
	else if(color!=0){//此时画出带颜色星星
		cct_setcolor(color + 8, back);//color为数组元素值，back为0/7，0就画出黑色框星星，7为白色框星星
		cct_gotoxy(prim_x, prim_y);
		cout << "┏━┓";
		cct_gotoxy(prim_x, prim_y + 1);
		cout << "┃★┃";
		cct_gotoxy(prim_x, prim_y + 2);
		cout << "┗━┛";
	}
}
/***************************************************************************
  函数名称：back_pic
  功    能：画出黑底白色背景，根据输入参数判断是否有分割线，以及背景的长宽
  输入参数：hang_set\lie_set设定的由code影响的XY最大值、hang/lie行数列数、code有无分割线、菜单项
  返 回 值：无
  说    明：根据参数不同画有无分割线的白色背景
***************************************************************************/
void back_pic(int hang_set, int lie_set, int hang, int lie,int code,int menu_case) {
	cct_gotoxy(0, 1);
	int i = 0, j = 0, k = 0, loop = 0;
	for (i = 0; i < lie; i++) {//此步为输出代表列数的数字
		if (i == 0)
			cout << ' ';
		else if (code == 1)
			cout << "  ";
		cout << setw(6) << i;
	}
	cout << endl;
	for (i = 0; i < hang; i++) {//控制分割线的输出
		for (k = 0; k < 3; k++) {
			cct_setcolor(0, COLOR_HWHITE);
			if (i == 0 && k == 0) {
				cout << "  ";//第一行边框的空位
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "┏";
				for (j = 0; j < lie; j++) {
					cout << "━━━";
					if (code == 1 && j < lie - 1)
						cout << "┳";//分割线
					Sleep(10);
				}
				cout << "┓";
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << endl;
			}
			if (k == 1)
				cout << char('A' + i) << ' ';//行字母
			else
				cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "┃";
			for (j = 0; j < lie; j++) {
				cout << "      ";
				if (code == 1 && j < lie - 1)
					cout << "┃";//分割线
				Sleep(10);
			}
			cout << "┃";
			cct_setcolor(0, 7);
			cout << endl;
			if (i == hang - 1 && k == 2) {
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "┗";
				for (j = 0; j < lie; j++) {
					cout << "━━━";
					if (code == 1 && j < lie - 1)
						cout << "┻";//分割线
					Sleep(10);
				}
				cout << "┛"; 
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << endl;
				
			}
		}
		if (code == 1&&i<hang-1) {//中间分割线
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "┣";
			for (j = 0; j < lie; j++) {
				cout << "━━━";
				if ( j < lie - 1)
					cout << "╋";
				Sleep(10);
			}
			cout << "┫";
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << endl;
		}
	}
	if (menu_case < 6)
		mention_print(0);
	else
		mention_print(1);
}
/***************************************************************************
  函数名称：pic_white
  功    能：对于0值画白块
  输入参数：hang/lie/星星数组、标记数组、code判断是否有分割线、菜单项
  返 回 值：count分数
  说    明：
***************************************************************************/
int pic_white(int hang, int lie, int xing[][11], int search[][11],int code) {
	int num = 0, tmp = 0, count = 0;
	for(int i=0;i<hang;i++)
		for (int j = 0; j < lie; j++) {
			if (search[i][j] == 1) {
				tmp = xing[i][j];
				num++;
				xing[i][j] = 0;
				xing_pic(i, j, 0, code, 0, 1);
			}
		}
	count = tmp * tmp * num;
	return count;
}
/***************************************************************************
  函数名称：down_moving
  功    能：数组下移、函数下移
  输入参数：hang/lie/星星数组、标记数组、栈数组、code判断是否有分割线
  返 回 值：无
  说    明：
***************************************************************************/
void down_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[],int code) {
	int i, j, k;
	int prim_x,prim_y;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++) {
			if (search[i][j] == 1) {
				for (k = i; k > top[j]; k--) {
					prim_x = 4 + j * (6 + 2 * code);
					prim_y = 3+ (k-1) * 3+(k-2)*code;
					shuzu[k][j] = shuzu[k - 1][j];
					shuzu[k - 1][j] = 0;
					search[k][j] = search[k - 1][j];
					search[k - 1][j] = 1;
					for (int loop=0; loop < 3 + code*2; loop++, prim_y++) {
						cct_gotoxy(prim_x, prim_y);
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && (prim_y-2)%4 ==0)
							cout << "━━━";//分割线
						else
							cout << "      ";
						cct_setcolor(shuzu[k][j] + 8, COLOR_BLACK);
						cct_gotoxy(prim_x, prim_y+1);
						cout << "┏━┓";
						cct_gotoxy(prim_x, prim_y + 2);
						cout << "┃★┃";
						cct_gotoxy(prim_x, prim_y + 3);
						cout << "┗━┛";
					}
					Sleep(15);
				}
				top[j]++;
			}
		}
}
/***************************************************************************
  函数名称：left_moving
  功    能：数组左移、函数左移
  输入参数：hang/lie/星星数组、标记数组、栈数组、code判断是否有分割线
  返 回 值：无
  说    明：
***************************************************************************/
void left_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[], int code) {
	int i, j, k;
	int prim_x, prim_y;
	for (j = 0; j < lie; j++) {
		if (top[j] == hang) {
			for (k = j; k < lie-1 ; k++) {
				for (i = hang - 1; i >= 0; i--) {
					prim_x = 4 + (k+1)*6+k*2*code;
					prim_y = 3 + (i * (3 + code));
					shuzu[i][k] = shuzu[i][k + 1];
					search[i][k] = search[i][k + 1];
					shuzu[i][k + 1] = 0;
					search[i][k + 1] = 1;
					for (int loop=0; loop < 3 + code; loop++, prim_x-=2) {
						cct_gotoxy(prim_x, prim_y);
						if (shuzu[i][k] != 0)
							cct_setcolor(shuzu[i][k] + 8, COLOR_BLACK);
						else
							cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
						cct_gotoxy(prim_x, prim_y);
						cout << "┏━┓";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x -4) % 8) == 0)
							cout << "┃";
						else
							cout << "  ";
						if (shuzu[i][k] != 0)
							cct_setcolor(shuzu[i][k] + 8, COLOR_BLACK);
						else
							cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
						cct_gotoxy(prim_x, prim_y + 1);
						cout << "┃★┃";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x - 4) % 8) == 0)
							cout << "┃";
						else
							cout << "  ";
						if (shuzu[i][k] != 0)
							cct_setcolor(shuzu[i][k] + 8, COLOR_BLACK);
						else
							cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
						cct_gotoxy(prim_x, prim_y + 2);
						cout << "┗━┛";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x - 4) % 8) == 0)
							cout << "┃";
						else
							cout << "  ";
					}
					Sleep(15);
				}
				top[k] = top[k + 1];
			}
			if (top[j] == hang)
				j--;
		}
	}
}
/***************************************************************************
  函数名称：wait_for_falling
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，取随机种子，调用menu函数输出菜单栏，选菜单项进入对应函数
***************************************************************************/
void wait_for_falling(int hang, int lie, int xing[][11], int search[][11], int top[],int hang_set,int code,int menu_case) {
	cct_gotoxy(0, hang_set - 4);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	int loop = 1;
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	cct_enable_mouse();
	if(menu_case==6){
		cout << "合成完成，回车键/单击左键下落0                                                                   ";
		while (loop) {
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK)
					break;
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (keycode1 == '\r')
					break;
			}
		}
	}
	down_moving(hang, lie, xing, search, top,code);//下移
	left_moving(hang, lie, xing, search, top,code);//左移
	int i = 0, j = 0;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			if (xing[i][j] == 0)
				search[i][j] = 1;
	if(menu_case==6){
		cct_gotoxy(0, hang_set - 4);
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "本次合成完成，按C/单击左键继续新一次的合成                                                                   ";
		while (loop) {
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK)
					break;
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (keycode1 == 'c' || keycode1 == 'C')
					loop = 0;
			}
		}
	}
}
/***************************************************************************
  函数名称：clear_color
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，取随机种子，调用menu函数输出菜单栏，选菜单项进入对应函数
***************************************************************************/
int clear_color(int hang, int lie, int xing[][11], int search[][11],int code) {
	for (int i = 0; i < hang; i++)
		for (int j = 0; j < lie; j++) {
			if (search[i][j] == 1) {
				xing_pic(i, j, xing[i][j], code, COLOR_BLACK, 0);
				search[i][j] = 0;
			}
		}
	return 0;
}
/***************************************************************************
  函数名称：judge_xiao
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，取随机种子，调用menu函数输出菜单栏，选菜单项进入对应函数
***************************************************************************/
int judge_xiao(int hang, int lie, int xing[][11], int search[][11], int code,char&row,int&col) {
	int Y_print = 3 * hang + (hang - 1) * code + 3;
	int ret_this = 0;
	if (1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;
		int pos = 0;
		int straight_kuang[10] = { 0 };
		for (int k = 0; k < lie - 1; k++) {
			straight_kuang[k] = 2 + 8 * (k + 1);
		}
		cct_enable_mouse();
		while (loop) {
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				switch (maction) {
					case MOUSE_LEFT_BUTTON_CLICK:
					case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
						ret_this = 1;
						cct_disable_mouse();
						break;
					case MOUSE_ONLY_MOVED:
						if((col!=(X-4)/(6+2*code))||(row!=char(((Y-3)/(3+code)))+'A'))
						{
							clear_color(hang, lie, xing, search, code);
							cct_gotoxy(0, Y_print + 1);
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cout << "[当前鼠标] ";
							if ((X < 5) || (X > COL_BOARDER - 1 + (lie - 1) * 2 * code) || (Y < 3) || (Y > 2 + 3 * hang + (hang - 1) * code)) {
								cout << "位置非法                                  ";
								pos = 0;
							}
							else {
								int kuang = 0;
								for (int i = 0; i < hang - 1; i++) {
									if (X == straight_kuang[i] || X == straight_kuang[i] + 1) {
										kuang = 1;
										break;
									}
								}
								if ((code == 1) && (((Y - 2) % 4 == 0) || kuang == 1)) {
									cout << "位置非法                                  ";
									pos = 0;
								}
								else {
									row = char(((Y - 3) / (3 + code)) + 'A');
									col = (X - 4) / (6 + 2 * code);
									pos = 1;
									cout << row << "行" << col << "列                                                                               ";
									xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE, 0);
								}
							}
							loop = 0;
						}
						ret_this = 0;
						break;
					default:
						loop = 0;
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						ret_this = -1;
						loop = 0;
						break;

				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				switch (keycode1) {
					case 224:
						clear_color(hang, lie, xing, search, code);
						cct_gotoxy(0, Y_print + 1);
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << "[当前键盘] ";
						pos = 1;
						ret_this = 0;
						switch (keycode2) {
							case KB_ARROW_UP:
								if (row == 'A')
									row = 'A' + lie - 1;
								else
									row--;
								break;
							case KB_ARROW_DOWN:
								if (row == 'A' + lie - 1)
									row = 'A';
								else
									row++;
								break;
							case KB_ARROW_LEFT:
								if (col == 0)
									col = lie - 1;
								else
									col--;
								break;
							case KB_ARROW_RIGHT:
								if (col == lie - 1)
									col = 0;
								else
									col++;
								break;
						}
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << row << "行" << col << "列                                       ";
						xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE, 0);
						break;
					case 81:
					case 113:
						ret_this = -1;
						loop = 0;
						break;
					case '\r':
						ret_this = 1;
						break;
				}
			}
			if (ret_this != 0) {
				break;
			}
		}
	}
	cct_disable_mouse();
	return ret_this;
}
/***************************************************************************
  函数名称：pic_basic
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void pic_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case,int mark) {
	int i = 0, j = 0, k = 0,loop=0;
	int hang_set=0, lie_set=0;
	int code = 0;
	int sum = mark;
	int count = 0;
	int top[11] = { 0 };
	int ret_end=0;
	char row = 'A';
	int col = 0;
	if(menu_case==4||menu_case==6){
		hang_set = ROW_BOARDER + (hang - 8) * 3;
		lie_set = COL_BOARDER + (lie - 8) * 6;
		code = 0;
	}
	else if (menu_case == 5 || menu_case == 7) {
		hang_set = ROW_BOARDER + 7 + (hang - 8) * 4;
		lie_set = COL_BOARDER + 14 + (lie - 8) * 8;
		code = 1;
	}
	cct_setconsoleborder(lie_set, hang_set);
	cct_setcursor(CURSOR_INVISIBLE);
	back_pic(hang_set, lie_set, hang, lie, code,menu_case);
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			xing_pic(i, j, xing[i][j], code,COLOR_BLACK,0);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << hang_set << "行" << lie_set << "列";
	while (1) {
		int ret = mouse_show(hang, lie, xing, search, code, menu_case,top,row,col);
		if (ret == 0)
			break;
		else
		{
			int ret1 = judge_xiao(hang, lie, xing, search, code,row,col);
			if (ret1 == 0)
			{
				clear_color(hang, lie, xing, search, code);
				continue;
			}
			else if (ret1 == -1)
				break;
			else {
				count = pic_white(hang, lie, xing, search, code);
				sum += count;
				cct_gotoxy(0, 0);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "本次得分:" << count << "总分:" << sum<<"                ";
				wait_for_falling(hang,lie,xing, search, top,hang_set,code,menu_case);
				if (menu_case == 6)
					break;
				clear_color(hang, lie, xing, search, code);
				cct_gotoxy(0, hang_set - 4);
				ret_end = seek_end(hang, lie, xing, menu_case);
				if (ret_end != 0)
				{
					while (getchar() != '\n')
						;
					if (ret_end < 10){
						count = count + (10 - ret_end) * 180;
						cct_gotoxy(0, 0);
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << "本次得分:" << count << "总分:" << sum << "                ";
					}
					break;
				}
			}
		}
	}
	if (ret_end != 0)
		task(7,hang,lie,sum);
	cct_gotoxy(0, hang_set-2);
}