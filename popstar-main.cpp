/* ��16 2251654 ����Ө */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  �������ƣ�menu
  ��    �ܣ�����˵�����ѡ��˵���
  �����������
  �� �� ֵ��choice��ѡ��
  ˵    ����
***************************************************************************/
int menu(){
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "--------------------------------------------" << endl;
	cout << "A.�������ҳ����������ʶ" << endl;
	cout << "B.���������һ���������ֲ�����ʾ��" << endl;
	cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
	cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
	cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
	cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
	cout << "G.αͼ�ν���������" << endl;
	cout << "Q.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��:] ";
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
  �������ƣ�task����
  ��    �ܣ�����������ͱ�������ʼ����ֵ�����������
  ���������menu_case��hang��lie��mark���ܷ�����
  �� �� ֵ����
  ˵    �����ֱ����������ֺ�ͼ�񲿷ֵĻ�������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������ȡ������ӣ�����menu��������˵�����ѡ�˵�������Ӧ����
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