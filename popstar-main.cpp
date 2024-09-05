/* 信16 2251654 付宝莹 */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  函数名称：menu
  功    能：输出菜单栏，选择菜单项
  输入参数：无
  返 回 值：choice，选项
  说    明：
***************************************************************************/
int menu(){
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "--------------------------------------------" << endl;
	cout << "A.命令行找出可消除项并标识" << endl;
	cout << "B.命令行完成一次消除（分步骤显示）" << endl;
	cout << "C.命令行完成一关（分步骤显示）" << endl;
	cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
	cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
	cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
	cout << "G.伪图形界面完整版" << endl;
	cout << "Q.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:] ";
	char choice;
	while (1){
		choice = _getch();
		if ((choice >= 'a' && choice <= 'g')||(choice>='A'&&choice<='G')||(choice=='q')||(choice=='Q')){
			cout << choice;
			if (choice >= 'a' && choice <= 'g')
				choice = choice - 32;
			break;
		}
	}
	return int(choice);
}
/***************************************************************************
  函数名称：task函数
  功    能：对星星数组和标记数组初始化赋值进入后续函数
  输入参数：menu_case，hang，lie，mark（总分数）
  返 回 值：无
  说    明：分别进入基础部分和图像部分的基本函数
***************************************************************************/
void task(int menu_case,int hang,int lie,int mark) {
	int xing[11][11] = { 0 };
	int i = 0, j = 0;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			xing[i][j] = rand() % 5 + 1; 
	int search[11][11] = { 0 };
	switch (menu_case) {
		case 1:
		case 2:
		case 3:
			shuzu_basic(hang, lie, xing, search, menu_case);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			pic_basic(hang, lie, xing, search, menu_case,mark);
			break;
	}
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，取随机种子，调用menu函数输出菜单栏，选菜单项进入对应函数
***************************************************************************/
int main() {
	cct_setconsoleborder(74, 41,256 , 62);
	srand((unsigned int)(time(0)));
	while (1){
		cct_setconsoleborder(74, 41, 256, 62);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		int memu_case;
		memu_case = menu();
		if (memu_case == 'q'|| memu_case == 'Q')
			break;
		else{
			cout << endl;
			cct_cls();
			int hang = 0, lie = 0;
			shuru(hang, lie);
			int mark = 0;
			task(memu_case-'A'+1,hang,lie,mark);
		}
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		wait_for_End();
	}
	cct_gotoxy(0, 23);
	return 0;
}