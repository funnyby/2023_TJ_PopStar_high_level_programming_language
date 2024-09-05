/* 信16 2251654 付宝莹 */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  函数名称：wait_for_End
  功    能：每个菜单栏完成后进行end输入再返回菜单栏
  输入参数：无
  返 回 值：无
  说    明：该过程返回的是输入菜单项部分，G菜单项的进行下一关则不可以进行到此步
***************************************************************************/
void wait_for_End() {
	char wait[3] = { '\0' };
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	while (1) {
		cout << "本小题结束，请输入End继续...";
		int i = 0;
		for (i = 0; i < 3; i++)
			cin >> wait[i];
		while (getchar() != '\n')
			;
		for (i = 0; i < 3; i++){
			if (wait[i] >= 'a' && wait[i] <= 'z')
				wait[i] = wait[i] - 32;
		}
		if (wait[0] == 'E' && wait[1] == 'N' && wait[2] == 'D')
			break;
		else
			cout << endl<<endl;
	}
}
/***************************************************************************
  函数名称：wait_for_enter
  功    能：等待回车
  输入参数：无
  返 回 值：无
  说    明：
***************************************************************************/
void wait_for_enter() {
	cout << "本次消除结束，按回车键继续新一次的消除..." << endl;
	while (_getch() != '\r')
		;
}
/***************************************************************************
  函数名称：seek_end
  功    能：判断是否能够结束
  输入参数：hang\lie\星星数组\菜单选项
  返 回 值：1/0表示是否结束
  说    明：判断结束和是否进行下一关
***************************************************************************/
int seek_end(int hang, int lie, int shuzu[][11],int menu_case) {
	int i = 0, j = 0,count=0;
	for(i=0;i<hang;i++)
		for (j = 0; j < lie; j++) 
			if (shuzu[i][j] != 0) {
				if (j < lie - 1)
					if (shuzu[i][j + 1] == shuzu[i][j])
						return 0;
				if (j > 1)
					if (shuzu[i][j - 1] == shuzu[i][j])
						return 0;
				if (i < hang - 1)
					if (shuzu[i + 1][j] == shuzu[i][j])
						return 0;
				if (i > 1)
					if (shuzu[i - 1][j] == shuzu[i][j])
						return 0;
				count++;
			}
	cct_setcolor(COLOR_HYELLOW, COLOR_RED);
	if (menu_case == 7)
		cout << "剩余" << count << "个星星，无可消除项，本关结束!";
	else
		cout << "剩余" << count << "个不可消除项，本关结束！";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	if (menu_case == 7){
		cout << "回车继续下一关";
	}
	cout << endl << endl;
	return count;
}
/***************************************************************************
  函数名称：shuru
  功    能：在菜单栏之后进行行和列的输入，影响到后续所有函数
  输入参数：&hang,&lie
  返 回 值：无
  说    明：
***************************************************************************/
void shuru(int& hang, int& lie) {
	while (1) {
		cout << "请输入行数(8-10):" << endl;
		cin >> hang;
		cin.clear();
		while (getchar() != '\n')
			;
		if (cin.good() && (hang >= 8) && (hang <= 10))
			break;
	}
	cin.clear();
	while (1) {
		cout << "请输入列数(8-10):" << endl;
		cin >> lie;
		cin.clear();
		while (getchar() != '\n')
			;
		if (cin.good() && (lie >= 8) && (lie <= 10))
			break;
	}
	cin.clear();
}
/***************************************************************************
  函数名称：seek_for_same
  功    能：寻找所选择的位置周围是否有与之相同的数字/星星，对其进行标记
  输入参数：目标值、星星数组、标记数组、目前所在行、目前所在列、行数、列数
  返 回 值：无
  说    明：递归函数，进行一个方向的穷尽寻找之后再次换方向寻找，最终找到全部的相同值
***************************************************************************/
void seek_for_same(int mubiao, int yuan_shuzu[][11], int search[][11], int hang_now, int lie_now,int hang,int lie) {
	search[hang_now][lie_now] = 1;
	if (hang_now >= 0 && hang_now <= hang-1) {
		if (hang_now > 0) {
			if (yuan_shuzu[hang_now - 1][lie_now] == mubiao) {
				search[hang_now - 1][lie_now] = 1;
				yuan_shuzu[hang_now - 1][lie_now] = 0;
				seek_for_same(mubiao, yuan_shuzu, search, hang_now - 1, lie_now, hang, lie);
				yuan_shuzu[hang_now - 1][lie_now] = mubiao;
			}
		}
		if (hang_now < hang - 1) {
			if (yuan_shuzu[hang_now + 1][lie_now] == mubiao) {
				search[hang_now + 1][lie_now] = 1;
				yuan_shuzu[hang_now + 1][lie_now] = 0;
				seek_for_same(mubiao, yuan_shuzu, search, hang_now + 1, lie_now, hang, lie);
				yuan_shuzu[hang_now + 1][lie_now] = mubiao;
			}
		}
	}
	if (lie_now >= 0 && lie_now < lie - 1) {
		if (lie_now > 0) {
			if (yuan_shuzu[hang_now][lie_now-1] == mubiao) {
				search[hang_now][lie_now-1] = 1;
				yuan_shuzu[hang_now][lie_now-1] = 0;
				seek_for_same(mubiao, yuan_shuzu, search, hang_now , lie_now-1, hang, lie);
				yuan_shuzu[hang_now][lie_now-1] = mubiao;
			}
		}
		if (lie_now < lie - 1) {
			if (yuan_shuzu[hang_now][lie_now+1] == mubiao) {
				search[hang_now][lie_now + 1] = 1;
				yuan_shuzu[hang_now][lie_now + 1] = 0;
				seek_for_same(mubiao, yuan_shuzu, search, hang_now, lie_now + 1, hang, lie);
				yuan_shuzu[hang_now][lie_now + 1] = mubiao;
			}
		}
	}
}
/***************************************************************************
  函数名称：count_xing
  功    能：对星星计数
  输入参数：hang、lie、标记数组
  返 回 值：count星星数目
  说    明：返回星星数目，调用它的函数由此进行决定后一步动作
***************************************************************************/
int count_xing(int hang, int lie, int search[][11]) {
	int count = 0;
	for(int i=0;i<hang;i++)
		for (int j = 0; j < lie; j++) {
			if (search[i][j] == 1)
				count++;
		}
	return count;
}