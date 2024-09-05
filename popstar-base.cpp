/* ��16 2251654 ����Ө */
#include<iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;
/***************************************************************************
  �������ƣ�print_basic
  ��    �ܣ�һЩ�������������ѡ��
  ���������n
  �� �� ֵ��
  ˵    �����������������ͬ�����Ӧ����
***************************************************************************/
void print_basic(int n){
	switch (n) {
		case 0:
			cout << "��ǰ���飺" << endl;
			break;
		case 1:
			cout << "���ҽ�����飺" << endl;
			break;
		case 2:
			cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
			break;
		case 3:
			cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
			break;
		case 4:
			cout << "���������飺" << endl;
			break;
		default:
			break;
	}
}
/***************************************************************************
  �������ƣ�pos_shuru
  ��    �ܣ���������Ҫ������λ��
  ���������char *hang_pos, int *lie_pos
  �� �� ֵ��loop-1
  ˵    ��������ֵ�����жϣ�����������Ƿ���ȷ�����ڵ������ĺ��������ж�
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
  �������ƣ�xiaochu_xing
  ��    �ܣ����Ѿ�����������Ǹ�0�����㱻��������ǹ����ٷ�
  ���������hang��lie���������飬�������
  �� �� ֵ��count����
  ˵    ����
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
  �������ƣ�wait_for_YNQ
  ��    �ܣ����Ƿ�����������жϵ������ж�
  ���������hang��lie�����ڵġ�������ĵ�ǰ�С��У��������飬������飬���е�ջ������
  �� �� ֵ��YNQ
  ˵    ����
***************************************************************************/
char wait_for_YNQ(int hang, int lie,char *hang_pos,int*lie_pos, int shuzu[][11], int search[][11],int top[]) {
	cout << "��ȷ���Ƿ��"<<*hang_pos<<*lie_pos<<"����Χ����ֵͬ����(Y / N / Q)��";
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
  �������ƣ�down_move
  ��    �ܣ��������������������
  ���������hang��lie���������飬������飬���е�ջ������
  �� �� ֵ����
  ˵    ����
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
  �������ƣ�left_move
  ��    �ܣ����������������
  ���������hang��lie���������飬������飬���е�ջ������
  �� �� ֵ����
  ˵    ����j--�����ڣ�����һ������ͬʱ����գ���ʱ����һ�κ���������һ�пյ���������ٽ���һ�α���ѭ��
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
  �������ƣ�wait_for_fall
  ��    �ܣ������������������down_move��left_move�����������ָı䣬�ٶԿ�λ�ý��б�ǣ����ô�ӡ�������д�ӡ��
  ���������hang��lie���������飬������飬���е�ջ������
  �� �� ֵ����
  ˵    �����Կ�λ���ٱ�ǿ�ʹ�������ɫ���ⲻ�����bug
***************************************************************************/
void wait_for_fall(int hang, int lie, int shuzu[][11], int search[][11], int top[]) {
	cout << "���س������������������...";
	while (getchar() != '\n')
		;
	down_move(hang, lie, shuzu, search, top);//����
	left_move(hang, lie, shuzu, search, top);//����
	int i = 0, j = 0;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			if (shuzu[i][j] == 0)
				search[i][j] = 1;
	print_kuang(hang, lie, shuzu, search, 4);
}
/***************************************************************************
  �������ƣ�seek
  ��    �ܣ�����pos_shuru����������꣬�ٽ����жϣ�����ȷ������seek_for_same������Ѱ��ͬ������ֵ���������ж�
  ���������hang��lie�����ڵġ�������ĵ�ǰ�С��У��������飬������飬���е�ջ������
  �� �� ֵ����
  ˵    ����
***************************************************************************/
void seek(int hang, int lie, int shuzu[][11], int search[][11],char*hang_pos,int*lie_pos) {
	int x, y, count = 0, ret = 0;
	while (1) {
		cout << "������ĸ*������ʽ[����c2]����������꣺";
		cct_getxy(x, y);
		ret = pos_shuru(hang_pos, lie_pos);
		cout << endl;
		if (*hang_pos >= 'a' && *hang_pos <= 'z')
			*hang_pos -= 32;
		if (ret == 2 && *hang_pos >= 'A' && *hang_pos <= ('A' + hang - 1)&&*lie_pos>=0&&*lie_pos<lie) {
			cout << "����Ϊ" << *hang_pos <<"��" << *lie_pos << "��        " << endl;
			if (shuzu[int(*hang_pos)-'A'][*lie_pos] == 0) {
				cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������" << endl;
				continue;
			}
			else {
				seek_for_same(shuzu[int(*hang_pos) - 'A'][*lie_pos], shuzu, search, int(*hang_pos) - 'A', *lie_pos, hang, lie);
				int count = count_xing(hang, lie, search);
				if (count == 1) {
					cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
					continue;
				}
				else
					break;
			}
		}
		else {
			cout << "�����������������";
			cct_gotoxy(x, y);
			cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(0, y);
		}
	}
}
/***************************************************************************
  �������ƣ�print_kuang
  ��    �ܣ����û��������������ӡ��ܡ�������������������������������ɶ�Ӧ�����ȫ�������
  ���������hang��lie���������飬������飬��Ӧ���
  �� �� ֵ����
  ˵    ����
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
  �������ƣ�print_shuzu
  ��    �ܣ����������������ӡ��Ӧ��ɫ����ʽ������Ԫ��
  ���������hang��lie���������飬������飬��Ӧ���
  �� �� ֵ����
  ˵    ����
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
  �������ƣ�shuzu_basic
  ��    �ܣ���ʼ��ջ�����顢ͨ��ѭ�������print_kuang��seek������ɲ�ͬ��������
  ���������hang��lie���������飬������飬menu_case
  �� �� ֵ����
  ˵    ����main������ȡ������ӣ�����menu��������˵�����ѡ�˵�������Ӧ����
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
					cout << "���ε÷֣�" << ret << " �ܵ÷֣�" << count << endl << endl;
					wait_for_fall(hang, lie, xing, search, top);
					if (menu_case == 2)
						break;
					wait_for_enter();
				}
			}
		}
	}
}