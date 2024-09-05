/* 信16 2251654 付宝莹 */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  函数名称：print_basic
  功    能：一些基本的文字输出选项
  输入参数：n
  返 回 值：
  说    明：根据输入参数不同输出相应文字
***************************************************************************/
void print_basic(int n){
	switch (n) {
		case 0:
			cout << "当前数组：" << endl;
			break;
		case 1:
			cout << "查找结果数组：" << endl;
			break;
		case 2:
			cout << "当前数组(不同色标识)：" << endl;
			break;
		case 3:
			cout << "相同值归并后的数组(不同色标识)：" << endl;
			break;
		case 4:
			cout << "下落后的数组：" << endl;
			break;
		default:
			break;
	}
}
/***************************************************************************
  函数名称：pos_shuru
  功    能：输入所需要消除的位置
  输入参数：char *hang_pos, int *lie_pos
  返 回 值：loop-1
  说    明：返回值用于判断，输入的数量是否正确，用于调用它的函数进行判断
***************************************************************************/
int pos_shuru(char *hang_pos, int *lie_pos) {
	int loop = 0;
	char ch;
	while (1) {
		loop++;
		ch = _getche();
		if (ch == '\r')
			break;
		else {
			if (loop == 1)
				*hang_pos = ch;
			else if (loop == 2)
				*lie_pos = int(ch) - '0';
		}
	}
	return (loop - 1);
}
/***************************************************************************
  函数名称：xiaochu_xing
  功    能：对已经被消灭掉星星赋0并计算被消灭的星星共多少分
  输入参数：hang，lie，星星数组，标记数组
  返 回 值：count分数
  说    明：
***************************************************************************/
int xiaochu_xing(int hang, int lie, int shuzu[][11], int search[][11]) {
	int i,j ;
	int num=0, tmp=0,count;
	for(i=0;i<hang;i++)
		for (j = 0; j < lie; j++) 
			if (search[i][j] == 1) 
			{
				tmp = shuzu[i][j];
				num++;
				shuzu[i][j] = 0;
			}
	count = tmp * tmp * num;
	return count;
}
/***************************************************************************
  函数名称：wait_for_YNQ
  功    能：对是否进行消除的判断的输入判断
  输入参数：hang，lie，现在的、被输入的当前行、列，星星数组，标记数组，各列的栈顶数组
  返 回 值：YNQ
  说    明：
***************************************************************************/
char wait_for_YNQ(int hang, int lie,char *hang_pos,int*lie_pos, int shuzu[][11], int search[][11],int top[]) {
	cout << "请确认是否把"<<*hang_pos<<*lie_pos<<"及周围的相同值消除(Y / N / Q)：";
	char YNQ;
	while (1) {
		YNQ = _getch();
		if (YNQ >= 'a' && YNQ <= 'z')
			YNQ = YNQ - 32;
		if (YNQ == 'Q') {
			cout << YNQ << endl<<endl;
			break;
		}
		if (YNQ == 'N') {
			for (int i = 0; i < 11; i++)
				for (int j = 0; j < 11; j++)
					search[i][j] = 0;
			cout << YNQ << endl << endl;
			break;
		}
		if (YNQ == 'Y') {
			cout << YNQ << endl << endl;
			break;
		}
	}
	return YNQ;
}
/***************************************************************************
  函数名称：down_move
  功    能：完成星星数组数字下移
  输入参数：hang，lie，星星数组，标记数组，各列的栈顶数组
  返 回 值：无
  说    明：
***************************************************************************/
void down_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]) {
	int i, j, k;
	for(i=0;i<hang;i++)
		for (j = 0; j < lie; j++) {
			if (search[i][j] == 1) {
				for (k = i; k > top[j]; k--) {
					shuzu[k][j] = shuzu[k - 1][j];
					shuzu[k - 1][j] = 0;
					search[k][j] = search[k - 1][j];
					search[k - 1][j] = 1;
				}
				top[j]++;
			}
		}
}
/***************************************************************************
  函数名称：left_move
  功    能：完成星星数组左移
  输入参数：hang，lie，星星数组，标记数组，各列的栈顶数组
  返 回 值：无
  说    明：j--是由于，若有一列以上同时被清空，此时左移一次后会出现仍有一列空的情况，需再进行一次本轮循环
***************************************************************************/
void left_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]) {
	int i, j, k;
	for (j = 0; j < lie; j++) {
		if (top[j] == hang) {
			for (k = j; k < lie - 1; k++) {
				for (i = hang-1; i >=0; i--) {
					shuzu[i][k] = shuzu[i][k + 1];
					search[i][k] = search[i][k + 1];
					shuzu[i][k + 1] = 0;
					search[i][k + 1] = 1;
				}
				top[k] = top[k + 1];
			}
			if (top[j] == hang)
				j--;
		}
	}
}
/***************************************************************************
  函数名称：wait_for_fall
  功    能：进行下落操作，调用down_move、left_move进行数组数字改变，再对空位置进行标记，调用打印函数进行打印。
  输入参数：hang，lie，星星数组，标记数组，各列的栈顶数组
  返 回 值：无
  说    明：对空位置再标记可使输出的颜色问题不会出现bug
***************************************************************************/
void wait_for_fall(int hang, int lie, int shuzu[][11], int search[][11], int top[]) {
	cout << "按回车键进行数组下落操作...";
	while (getchar() != '\n')
		;
	down_move(hang, lie, shuzu, search, top);//下移
	left_move(hang, lie, shuzu, search, top);//左移
	int i = 0, j = 0;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			if (shuzu[i][j] == 0)
				search[i][j] = 1;
	print_kuang(hang, lie, shuzu, search, 4);
}
/***************************************************************************
  函数名称：seek
  功    能：调用pos_shuru输入矩阵坐标，再进行判断，若正确，调用seek_for_same函数找寻相同的所有值、计数、判断
  输入参数：hang，lie，现在的、被输入的当前行、列，星星数组，标记数组，各列的栈顶数组
  返 回 值：无
  说    明：
***************************************************************************/
void seek(int hang, int lie, int shuzu[][11], int search[][11],char*hang_pos,int*lie_pos) {
	int x, y, count = 0, ret = 0;
	while (1) {
		cout << "请以字母*数字形式[例：c2]输入矩阵坐标：";
		cct_getxy(x, y);
		ret = pos_shuru(hang_pos, lie_pos);
		cout << endl;
		if (*hang_pos >= 'a' && *hang_pos <= 'z')
			*hang_pos -= 32;
		if (ret == 2 && *hang_pos >= 'A' && *hang_pos <= ('A' + hang - 1)&&*lie_pos>=0&&*lie_pos<lie) {
			cout << "输入为" << *hang_pos <<"行" << *lie_pos << "列        " << endl;
			if (shuzu[int(*hang_pos)-'A'][*lie_pos] == 0) {
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
				continue;
			}
			else {
				seek_for_same(shuzu[int(*hang_pos) - 'A'][*lie_pos], shuzu, search, int(*hang_pos) - 'A', *lie_pos, hang, lie);
				int count = count_xing(hang, lie, search);
				if (count == 1) {
					cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
					continue;
				}
				else
					break;
			}
		}
		else {
			cout << "输入错误，请重新输入";
			cct_gotoxy(x, y);
			cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(0, y);
		}
	}
}
/***************************************************************************
  函数名称：print_kuang
  功    能：调用基本输出函数、打印框架、调用数组输出函数，根据输入参数完成对应步骤的全过程输出
  输入参数：hang，lie，星星数组，标记数组，对应情况
  返 回 值：无
  说    明：
***************************************************************************/
void print_kuang(int hang, int lie, int shuzu[][11], int search[][11],int casion) {
	print_basic(casion);
	int i;
	for (i = 0; i < hang + 2; i++) {
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		if (i == 0) {
			cout << "  |";
			for (int loop = 0; loop < lie; loop++)
				cout << setw(3) << loop;
			cout << endl;
		}
		else if (i == 1) {
			cout << "--+";
			for (int loop = 0; loop < lie; loop++)
				cout << "---";
			cout << '-' << endl;
		}
		else {
			cout << char('A' + i - 2) << " |";
			print_shuzu(i-2, lie,shuzu,search, casion);
		}
	}
	cout << endl;
}
/***************************************************************************
  函数名称：print_shuzu
  功    能：根据输入参数，打印对应颜色、形式的数组元素
  输入参数：hang，lie，星星数组，标记数组，对应情况
  返 回 值：无
  说    明：
***************************************************************************/
void print_shuzu(int hang, int lie,int shuzu[][11], int search[][11], int casion) {
	int i = 0;
	if (casion == 0) {
		for (i = 0; i < lie; i++){
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			if (search[hang][i] == 1) {
				cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << shuzu[hang][i];
			}
			else
				cout << setw(3) << shuzu[hang][i];
		}
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;
	}
	else if (casion == 1) {
		for (i = 0; i < lie; i++) {
			if (search[hang][i] == 1)
				cout << setw(3) << '*';
			else
				cout << setw(3) << search[hang][i];
		}
		cout << endl;
	}
	else {
		for (i = 0; i < lie; i++) {
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			if (search[hang][i] == 1){
				cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout<<shuzu[hang][i];
			}
			else
				cout << setw(3) << shuzu[hang][i];
		}
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}
/***************************************************************************
  函数名称：shuzu_basic
  功    能：初始化栈顶数组、通过循环与调用print_kuang、seek函数完成不同步骤的输出
  输入参数：hang，lie，星星数组，标记数组，menu_case
  返 回 值：无
  说    明：main函数，取随机种子，调用menu函数输出菜单栏，选菜单项进入对应函数
***************************************************************************/
void shuzu_basic(int hang, int lie, int xing[][11], int search[][11],int menu_case) {
	int loop = 0;
	char hang_pos,Ywait;
	int lie_pos;
	int top[11] = { 0 };
	int count = 0;
	int ret = 0;
	while (1) {
		for (loop = 0; loop < 3; loop++) {
			cout << endl;
			print_kuang(hang, lie, xing, search, loop);
			if (loop == 0){
				for (int i = 0; i < hang; i++)
					for (int j = 0; j < lie; j++)
						search[i][j] = 0;
				ret = seek_end(hang, lie, xing,menu_case);
				if (ret != 0)
					break;
				seek(hang, lie, xing, search, &hang_pos, &lie_pos);
			}
		}
		if (ret != 0)
			break;
		if (menu_case == 1)
			break;
		else {
			Ywait = wait_for_YNQ(hang, lie, &hang_pos, &lie_pos, xing, search, top);
			if (Ywait == 'Q')
				break;
			else {
				if (Ywait == 'N')
					continue;
				else {
					int ret=xiaochu_xing(hang, lie, xing, search);
					count += ret;
					print_kuang(hang, lie, xing, search,3);
					cout << "本次得分：" << ret << " 总得分：" << count << endl << endl;
					wait_for_fall(hang, lie, xing, search, top);
					if (menu_case == 2)
						break;
					wait_for_enter();
				}
			}
		}
	}
}