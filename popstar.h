/* ��16 2251654 ����Ө */
#pragma once

void pic_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case,int mark);
void xing_pic(int hang_now, int lie_now, int color, int code, int back, int white);
int clear_color(int hang, int lie, int xing[][11], int search[][11], int code);

/*--------------------��������-----------------------*/
int menu();
void task(int menu_case, int hang, int lie, int mark);


/*--------------------�������ֺ���-----------------------*/
void shuzu_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case);//���鲿�ֻ�������

//���ϵ�к���
void print_basic(int n);//����������
void print_kuang(int hang, int lie, int shuzu[][11], int search[][11], int casion);//��ӡ��ܺ�����ʵ�ʵ���������ӡ���������Դ�ӡ����
void print_shuzu(int hang, int lie, int shuzu[][11], int search[][11], int casion);//��ӡ�������ֻ�*

//�ж�ϵ�к���
int pos_shuru(char* hang_pos, int* lie_pos);//��������λ��
char wait_for_YNQ(int hang, int lie, char* hang_pos, int* lie_pos, int shuzu[][11], int search[][11], int top[]);//�ж��Ƿ�����
void seek(int hang, int lie, int shuzu[][11], int search[][11], char* hang_pos, int* lie_pos);//����λ���ж��ܷ�����

//�ƶ�ϵ�к���
int xiaochu_xing(int hang, int lie, int shuzu[][11], int search[][11]);//�����������Ǹ�0���Ʒ�
void down_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//�������亯��
void left_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//�������ƺ���
void wait_for_fall(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//׼�����亯��


/*--------------------���ò��ֺ���-----------------------*/
//�ȴ�ϵ�к���
void wait_for_End();//����end�󷵻ز˵�
void wait_for_enter();//�ȴ��س�

//���뺯��
void shuru(int& hang, int& lie);//�����к�������

//�ж�ϵ�к���
int seek_end(int hang, int lie, int shuzu[][11], int menu_case);//�ж��Ƿ�������ֵͬ
void seek_for_same(int mubiao, int yuan_shuzu[][11], int search[][11], int hang_now, int lie_now, int hang, int lie);//��Ѱ�Ƿ�����ֵͬ
int count_xing(int hang, int lie, int search[][11]);//�ж����Ǹ���


/*--------------------ͼ�β��ֺ���-----------------------*/
void mention_print(int casion);//��ʾ������
int mouse_show(int hang, int lie, int xing[][11], int search[][11], int code, int menu_case, int top[], char& row, int& col);//�������ж�
void xing_pic(int hang_now, int lie_now, int color, int code, int back, int white);//�����Ǻ���
void back_pic(int hang_set, int lie_set, int hang, int lie, int code, int menu_case);
int pic_white(int hang, int lie, int xing[][11], int search[][11], int code);
void down_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[], int code);
void left_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[], int code);
void wait_for_falling(int hang, int lie, int xing[][11], int search[][11], int top[], int hang_set, int code, int menu_case);
int clear_color(int hang, int lie, int xing[][11], int search[][11], int code);
int judge_xiao(int hang, int lie, int xing[][11], int search[][11], int code, char& row, int& col);
void pic_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case, int mark);