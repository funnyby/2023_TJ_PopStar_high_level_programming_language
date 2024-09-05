/* 信16 2251654 付宝莹 */
#pragma once

void pic_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case,int mark);
void xing_pic(int hang_now, int lie_now, int color, int code, int back, int white);
int clear_color(int hang, int lie, int xing[][11], int search[][11], int code);

/*--------------------主程序函数-----------------------*/
int menu();
void task(int menu_case, int hang, int lie, int mark);


/*--------------------基础部分函数-----------------------*/
void shuzu_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case);//数组部分基础函数

//输出系列函数
void print_basic(int n);//基础语句输出
void print_kuang(int hang, int lie, int shuzu[][11], int search[][11], int casion);//打印框架函数，实际调用其他打印函数，可以打印所有
void print_shuzu(int hang, int lie, int shuzu[][11], int search[][11], int casion);//打印数组数字或*

//判断系列函数
int pos_shuru(char* hang_pos, int* lie_pos);//输入消除位置
char wait_for_YNQ(int hang, int lie, char* hang_pos, int* lie_pos, int shuzu[][11], int search[][11], int top[]);//判断是否消除
void seek(int hang, int lie, int shuzu[][11], int search[][11], char* hang_pos, int* lie_pos);//输入位置判断能否消除

//移动系列函数
int xiaochu_xing(int hang, int lie, int shuzu[][11], int search[][11]);//给被消灭星星赋0、计分
void down_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//数组下落函数
void left_move(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//数组左移函数
void wait_for_fall(int hang, int lie, int shuzu[][11], int search[][11], int top[]);//准备下落函数


/*--------------------共用部分函数-----------------------*/
//等待系列函数
void wait_for_End();//输入end后返回菜单
void wait_for_enter();//等待回车

//输入函数
void shuru(int& hang, int& lie);//输入行和列总数

//判断系列函数
int seek_end(int hang, int lie, int shuzu[][11], int menu_case);//判断是否再无相同值
void seek_for_same(int mubiao, int yuan_shuzu[][11], int search[][11], int hang_now, int lie_now, int hang, int lie);//找寻是否有相同值
int count_xing(int hang, int lie, int search[][11]);//判断星星个数


/*--------------------图形部分函数-----------------------*/
void mention_print(int casion);//提示语句输出
int mouse_show(int hang, int lie, int xing[][11], int search[][11], int code, int menu_case, int top[], char& row, int& col);//鼠标键盘判断
void xing_pic(int hang_now, int lie_now, int color, int code, int back, int white);//画星星函数
void back_pic(int hang_set, int lie_set, int hang, int lie, int code, int menu_case);
int pic_white(int hang, int lie, int xing[][11], int search[][11], int code);
void down_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[], int code);
void left_moving(int hang, int lie, int shuzu[][11], int search[][11], int top[], int code);
void wait_for_falling(int hang, int lie, int xing[][11], int search[][11], int top[], int hang_set, int code, int menu_case);
int clear_color(int hang, int lie, int xing[][11], int search[][11], int code);
int judge_xiao(int hang, int lie, int xing[][11], int search[][11], int code, char& row, int& col);
void pic_basic(int hang, int lie, int xing[][11], int search[][11], int menu_case, int mark);