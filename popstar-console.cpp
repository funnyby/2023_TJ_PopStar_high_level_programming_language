/* ��16 2251654 ����Ө */
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
  �������ƣ�mention_print
  ��    �ܣ���ʾ������
  ���������casion���
  �� �� ֵ����
  ˵    ����
***************************************************************************/
void mention_print(int casion) {
	switch (casion) {
		case 0:
			cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
			break;
		case 1:
			cout << "��ͷ��/����ƶ����س���/�������ѡ��,Q/�����Ҽ�����";
			break;
		case 2:
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
			break;
		case 3:
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳɣ�Q/�����Ҽ��˳�";
			break;
	}
}
/***************************************************************************
  �������ƣ�mouse_show
  ��    �ܣ��ж�����Լ������ƶ�
  ����������������������������顢������顢code�Ƿ��зָ��ߡ��˵�ֵ��ջ�����顢ѡ�������С�ѡ��������
  �� �� ֵ��1/0��������or�����˲˵���
  ˵    �����ú���ʵ�ֹ��ܰ�������ʾ��ꡢ������������/�Ƿ�Ϸ����Ƿ�ѡ�С�ѡ��λ�á�ѡ���Ƿ�Ϸ���ѡ�к���ɫ�仯���ƿ�����ɫ�仯����
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
								cout << "ѡ����" << row << "��" << col << "��                                                     " << endl;
								loop = 0;
								ret_this = 0;
								search[int(row) - 'A'][col] = 1;
							}
							else {
								seek_for_same(xing[int(row) - 'A'][col], xing, search, int(row) - 'A', col, hang, lie);
								count = count_xing(hang, lie, search);
								if (count == 1) {
									cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
									cout << "��Χ����ֵͬ��";
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
						cout << "[��ǰ���] ";
						if ((X < 5) || (X > COL_BOARDER - 1 + (lie - 1) * 2 * code) || (Y < 3) || (Y > 2 + 3 * hang + (hang - 1) * code)) {
							cout << "λ�÷Ƿ�                                  ";
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
								cout << "λ�÷Ƿ�                                  ";
								pos = 0;
							}
							else {
								row = char(((Y - 3) / (3 + code)) + 'A');
								col = (X - 4) / (6 + 2 * code);
								pos = 1;
								if (xing[int(row) - 'A'][col] == 0){
									cout << "λ�÷Ƿ�                                  ";
									pos = 0;
									xing_pic(int(row) - 'A', col, xing[int(row) - 'A'][col], code, COLOR_WHITE, 1);
								}
								else{
									cout << row << "��" << col << "��                                                                               ";
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
						cout << "[��ǰ����] ";
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
						cout << row << "��" << col << "��                                                                                                ";
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
								cout << "ѡ����" << row << "��" << col << "��                                                                " << endl;
								loop = 0;
								ret_this = 0;
								search[int(row) - 'A'][col] = 1;
							}
							else{
								seek_for_same(xing[int(row) - 'A'][col], xing, search, int(row) - 'A', col, hang, lie);
								count = count_xing(hang, lie, search);
								if (count == 1) {
									cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
									cout << "��Χ����ֵͬ��";
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
  �������ƣ�xing_pic
  ��    �ܣ���������Ĳ�����ָ��λ�û����ǻ򲹿հ׵ĺ���
  ������������ڵ��С��С�������ɫ����λ�ö�Ӧ�������Ԫ��ֵ�������ޱ߿򡢱�����ɫ��ѡ�м���δѡ���ڣ���white�Ƿ�ȫ��ɫ
  �� �� ֵ����
  ˵    �����ú����ȿ����Ԫ��ֵΪ0���İ�ɫ��Ҳ�ɻ���ѡ��/δѡ�еĶ�Ӧ��ɫ����
***************************************************************************/
void xing_pic(int hang_now, int lie_now, int color, int code,int back,int white) {
    int prim_x = 5 + lie_now * (6+2*code)-1;//��ʼxλ��
	int prim_y = 4 + hang_now * (3+code)-1;//��ʼyλ��
	if (white == 1) {//��ʱ��հף���һ������Է�ֵֹΪ0��λ�ñ�������ɫ����
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cct_gotoxy(prim_x, prim_y);
		cout << "      ";
		cct_gotoxy(prim_x, prim_y + 1);
		cout << "      ";
		cct_gotoxy(prim_x, prim_y + 2);
		cout << "      ";
	}
	else if(color!=0){//��ʱ��������ɫ����
		cct_setcolor(color + 8, back);//colorΪ����Ԫ��ֵ��backΪ0/7��0�ͻ�����ɫ�����ǣ�7Ϊ��ɫ������
		cct_gotoxy(prim_x, prim_y);
		cout << "������";
		cct_gotoxy(prim_x, prim_y + 1);
		cout << "���逸";
		cct_gotoxy(prim_x, prim_y + 2);
		cout << "������";
	}
}
/***************************************************************************
  �������ƣ�back_pic
  ��    �ܣ������ڵװ�ɫ������������������ж��Ƿ��зָ��ߣ��Լ������ĳ���
  ���������hang_set\lie_set�趨����codeӰ���XY���ֵ��hang/lie����������code���޷ָ��ߡ��˵���
  �� �� ֵ����
  ˵    �������ݲ�����ͬ�����޷ָ��ߵİ�ɫ����
***************************************************************************/
void back_pic(int hang_set, int lie_set, int hang, int lie,int code,int menu_case) {
	cct_gotoxy(0, 1);
	int i = 0, j = 0, k = 0, loop = 0;
	for (i = 0; i < lie; i++) {//�˲�Ϊ�����������������
		if (i == 0)
			cout << ' ';
		else if (code == 1)
			cout << "  ";
		cout << setw(6) << i;
	}
	cout << endl;
	for (i = 0; i < hang; i++) {//���Ʒָ��ߵ����
		for (k = 0; k < 3; k++) {
			cct_setcolor(0, COLOR_HWHITE);
			if (i == 0 && k == 0) {
				cout << "  ";//��һ�б߿�Ŀ�λ
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "��";
				for (j = 0; j < lie; j++) {
					cout << "������";
					if (code == 1 && j < lie - 1)
						cout << "��";//�ָ���
					Sleep(10);
				}
				cout << "��";
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << endl;
			}
			if (k == 1)
				cout << char('A' + i) << ' ';//����ĸ
			else
				cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "��";
			for (j = 0; j < lie; j++) {
				cout << "      ";
				if (code == 1 && j < lie - 1)
					cout << "��";//�ָ���
				Sleep(10);
			}
			cout << "��";
			cct_setcolor(0, 7);
			cout << endl;
			if (i == hang - 1 && k == 2) {
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "��";
				for (j = 0; j < lie; j++) {
					cout << "������";
					if (code == 1 && j < lie - 1)
						cout << "��";//�ָ���
					Sleep(10);
				}
				cout << "��"; 
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << endl;
				
			}
		}
		if (code == 1&&i<hang-1) {//�м�ָ���
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "��";
			for (j = 0; j < lie; j++) {
				cout << "������";
				if ( j < lie - 1)
					cout << "��";
				Sleep(10);
			}
			cout << "��";
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
  �������ƣ�pic_white
  ��    �ܣ�����0ֵ���׿�
  ���������hang/lie/�������顢������顢code�ж��Ƿ��зָ��ߡ��˵���
  �� �� ֵ��count����
  ˵    ����
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
  �������ƣ�down_moving
  ��    �ܣ��������ơ���������
  ���������hang/lie/�������顢������顢ջ���顢code�ж��Ƿ��зָ���
  �� �� ֵ����
  ˵    ����
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
							cout << "������";//�ָ���
						else
							cout << "      ";
						cct_setcolor(shuzu[k][j] + 8, COLOR_BLACK);
						cct_gotoxy(prim_x, prim_y+1);
						cout << "������";
						cct_gotoxy(prim_x, prim_y + 2);
						cout << "���逸";
						cct_gotoxy(prim_x, prim_y + 3);
						cout << "������";
					}
					Sleep(15);
				}
				top[j]++;
			}
		}
}
/***************************************************************************
  �������ƣ�left_moving
  ��    �ܣ��������ơ���������
  ���������hang/lie/�������顢������顢ջ���顢code�ж��Ƿ��зָ���
  �� �� ֵ����
  ˵    ����
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
						cout << "������";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x -4) % 8) == 0)
							cout << "��";
						else
							cout << "  ";
						if (shuzu[i][k] != 0)
							cct_setcolor(shuzu[i][k] + 8, COLOR_BLACK);
						else
							cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
						cct_gotoxy(prim_x, prim_y + 1);
						cout << "���逸";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x - 4) % 8) == 0)
							cout << "��";
						else
							cout << "  ";
						if (shuzu[i][k] != 0)
							cct_setcolor(shuzu[i][k] + 8, COLOR_BLACK);
						else
							cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
						cct_gotoxy(prim_x, prim_y + 2);
						cout << "������";
						cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
						if (code == 1 && ((prim_x - 4) % 8) == 0)
							cout << "��";
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
  �������ƣ�wait_for_falling
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������ȡ������ӣ�����menu��������˵�����ѡ�˵�������Ӧ����
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
		cout << "�ϳ���ɣ��س���/�����������0                                                                   ";
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
	down_moving(hang, lie, xing, search, top,code);//����
	left_moving(hang, lie, xing, search, top,code);//����
	int i = 0, j = 0;
	for (i = 0; i < hang; i++)
		for (j = 0; j < lie; j++)
			if (xing[i][j] == 0)
				search[i][j] = 1;
	if(menu_case==6){
		cct_gotoxy(0, hang_set - 4);
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "���κϳ���ɣ���C/�������������һ�εĺϳ�                                                                   ";
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
  �������ƣ�clear_color
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������ȡ������ӣ�����menu��������˵�����ѡ�˵�������Ӧ����
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
  �������ƣ�judge_xiao
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������ȡ������ӣ�����menu��������˵�����ѡ�˵�������Ӧ����
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
							cout << "[��ǰ���] ";
							if ((X < 5) || (X > COL_BOARDER - 1 + (lie - 1) * 2 * code) || (Y < 3) || (Y > 2 + 3 * hang + (hang - 1) * code)) {
								cout << "λ�÷Ƿ�                                  ";
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
									cout << "λ�÷Ƿ�                                  ";
									pos = 0;
								}
								else {
									row = char(((Y - 3) / (3 + code)) + 'A');
									col = (X - 4) / (6 + 2 * code);
									pos = 1;
									cout << row << "��" << col << "��                                                                               ";
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
						cout << "[��ǰ����] ";
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
						cout << row << "��" << col << "��                                       ";
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
  �������ƣ�pic_basic
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
	cout << "��Ļ��ǰ����Ϊ��" << hang_set << "��" << lie_set << "��";
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
				cout << "���ε÷�:" << count << "�ܷ�:" << sum<<"                ";
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
						cout << "���ε÷�:" << count << "�ܷ�:" << sum << "                ";
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