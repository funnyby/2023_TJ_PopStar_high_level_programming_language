/* ��16 2251654 ����Ө */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  �������ƣ�wait_for_End
  ��    �ܣ�ÿ���˵�����ɺ����end�����ٷ��ز˵���
  �����������
  �� �� ֵ����
  ˵    �����ù��̷��ص�������˵���֣�G�˵���Ľ�����һ���򲻿��Խ��е��˲�
***************************************************************************/
void wait_for_End() {
	char wait[3] = { '\0' };
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	while (1) {
		cout << "��С�������������End����...";
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
  �������ƣ�wait_for_enter
  ��    �ܣ��ȴ��س�
  �����������
  �� �� ֵ����
  ˵    ����
***************************************************************************/
void wait_for_enter() {
	cout << "�����������������س���������һ�ε�����..." << endl;
	while (_getch() != '\r')
		;
}
/***************************************************************************
  �������ƣ�seek_end
  ��    �ܣ��ж��Ƿ��ܹ�����
  ���������hang\lie\��������\�˵�ѡ��
  �� �� ֵ��1/0��ʾ�Ƿ����
  ˵    �����жϽ������Ƿ������һ��
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
		cout << "ʣ��" << count << "�����ǣ��޿���������ؽ���!";
	else
		cout << "ʣ��" << count << "��������������ؽ�����";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	if (menu_case == 7){
		cout << "�س�������һ��";
	}
	cout << endl << endl;
	return count;
}
/***************************************************************************
  �������ƣ�shuru
  ��    �ܣ��ڲ˵���֮������к��е����룬Ӱ�쵽�������к���
  ���������&hang,&lie
  �� �� ֵ����
  ˵    ����
***************************************************************************/
void shuru(int& hang, int& lie) {
	while (1) {
		cout << "����������(8-10):" << endl;
		cin >> hang;
		cin.clear();
		while (getchar() != '\n')
			;
		if (cin.good() && (hang >= 8) && (hang <= 10))
			break;
	}
	cin.clear();
	while (1) {
		cout << "����������(8-10):" << endl;
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
  �������ƣ�seek_for_same
  ��    �ܣ�Ѱ����ѡ���λ����Χ�Ƿ�����֮��ͬ������/���ǣ�������б��
  ���������Ŀ��ֵ���������顢������顢Ŀǰ�����С�Ŀǰ�����С�����������
  �� �� ֵ����
  ˵    �����ݹ麯��������һ��������Ѱ��֮���ٴλ�����Ѱ�ң������ҵ�ȫ������ֵͬ
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
  �������ƣ�count_xing
  ��    �ܣ������Ǽ���
  ���������hang��lie���������
  �� �� ֵ��count������Ŀ
  ˵    ��������������Ŀ���������ĺ����ɴ˽��о�����һ������
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