#define _CRT_SECURE_NO_WARNINGS
//利用宏定义行和列
#define MAX_ROW 3
#define MAX_COL 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//  将初始化行和列的 '0' 变为空格 ' '
void init(char board[MAX_ROW][MAX_COL]) {
	//行初始化，将数组 0-2输出为' '  
	for (int row = 0; row < MAX_ROW; row++) {
		//列初始化
		for (int col = 0; col < MAX_COL; col++) {
			board[row][col] = ' ';
		}
	}
	//设置随机数种子，为电脑落子
	//只要程序启动时，设置一次即可
	srand((unsigned int)time(0));
}

//  打印棋盘，定义printBoard，以二维数组的方式进行循环打印
void printBoard(char board[MAX_ROW][MAX_COL]) {
	//每次打印之前先清屏
	system("cls");
	for (int row = 0; row < MAX_ROW; row++) {
		//在打印每一行之前加入横线
		printf("+--+--+--+\n");
		for (int col = 0; col < MAX_COL; col++) {
			// 打印字符，使用 %c
			// 每打印一列，在打印之前加入|
			printf("| %c", board[row][col]);
		}
		//打印之后加入|，形成 3 列。
		printf("|");
		//每次打印完一行，进行换行操作，变成3×3的数组形成的纵线棋盘
		printf("\n");
	}//打印完所有行之后在加入横线，形成横线棋盘
	printf("+--+--+--+\n");
}

//  玩家落子
void playerMove(char board[MAX_ROW][MAX_COL]) {
	printf("轮到玩家落子！\n");
	//加入while循环，保证用户输入错误时返回重新输入
	while (1) {
		printf("请输入落子位置的坐标(row col)：");
		//添加屏幕输入模块，输入行和列坐标
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//输入完了之后，一定要验证输入的内容，防止输入例如（10，20）超过棋盘坐标
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("您输入的坐标有误，请重新输入！\n");
			continue;//重新输入，继续循环
		}
		// 当前位置不为 ' ' ，说明有子了，也需要重新输入
		if (board[row][col] != ' ') {
			printf("当前位置有子，无法落子\n");
			continue;
		}
		//玩家落子为 X ，结束当前循环
		board[row][col] = 'X';
		break;
	}
}

// 电脑落子
void computerMove(char board[MAX_ROW][MAX_COL]) {
	printf("轮到电脑落子!\n");
	while (1) {
		//电脑落子时，产生随机位置，用到随机数种子,使随机数范围在棋盘坐标以内
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (board[row][col] != ' ') {
			// 如果行列不是空格，说明有子了,就随机生成随机数
			continue;
		}
		board[row][col] = 'O';
		break;
	}
}


//判断和棋的函数
int isFull(char board[MAX_ROW][MAX_COL]) {
	//如果在棋盘中找不到 ' ' ，就说明棋盘满了，只要找到 ' ' 说明没满
	//约定满了返回1，没满返回0
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			if (board[row][col] == ' ') {
				//没满
				return 0;
			}
		}
	}return 1;
}

// 判定胜负,由于要返回胜负，使用char定义
// 如果是玩家赢返回 X ，电脑赢返回 O，平局返回 P，胜负未分返回 ' '
char checkwinner(char board[MAX_ROW][MAX_COL]) {
	//1.检测所有行
	for (int row = 0; row < MAX_ROW; row++) {
		if (board[row][0] != ' '
			&& board[row][0] == board[row][1]
			&& board[row][0] == board[row][2]) {
			return board[row][0];
		}
	}
	//2.检测所有列
	for (int col = 0; col < MAX_ROW; col++) {
		if (board[0][col] != ' '
			&& board[0][col] == board[1][col]
			&& board[0][col] == board[2][col]) {
			return board[0][col];
		}
	}
	//3.检测所有对角线
	if (board[0][0] != ' ' &&
		board[0][0] == board[1][1]
		&& board[0][0] == board[2][2]) {
		return board[0][0];
	}
	if (board[2][0] != ' ' &&
		board[2][0] == board[1][1]
		&& board[0][0] == board[0][2]) {
		return board[2][0];
	}
	// 判定和棋
	if (isFull(board)) {
		return 'p';
	}return ' ';

}

int main() {
	//  首先创建棋盘并初始化
	//  这里不要用board[3][3],防止后面 3 与 3 搞混，可以利用宏定义
	char board[MAX_ROW][MAX_COL] = { 0 };
	//  使用 init 函数 初始化二维数组{0}应当变成空格  ' '
	//  此处也可以将 init函数定义中的双重 for 循环直接输入
	//  但将二维数组初始化为 ' '，表示了一个固定功能的逻辑，比较适合用函数定义的方法完成
	init(board);
	char winner = ' ';
	//  使用while循环，进行轮流落子
	while (1) {
		//1.先打印棋盘内容
		printBoard(board);
		//2.玩家落子
		playerMove(board);
		winner = checkwinner(board);
		if (winner != ' ') {
			//胜负已分，结束循环
			break;
		}
		//3.电脑落子
		computerMove(board);
		//4.判定胜负
		winner = checkwinner(board);
		if (winner != ' ') {
			//胜负已分，结束循环
			break;
		}
	}
	if (winner = 'X') {
		printf("恭喜你，获胜了!\n");
	}
	else if (winner = 'O') {
		printf("很遗憾，你有点菜呀!\n");
	}
	else {
		printf("你和电脑五五开!\n");
	}
	system("pause");
	return 0;
}
