#define _CRT_SECURE_NO_WARNINGS
//���ú궨���к���
#define MAX_ROW 3
#define MAX_COL 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//  ����ʼ���к��е� '0' ��Ϊ�ո� ' '
void init(char board[MAX_ROW][MAX_COL]) {
	//�г�ʼ���������� 0-2���Ϊ' '  
	for (int row = 0; row < MAX_ROW; row++) {
		//�г�ʼ��
		for (int col = 0; col < MAX_COL; col++) {
			board[row][col] = ' ';
		}
	}
	//������������ӣ�Ϊ��������
	//ֻҪ��������ʱ������һ�μ���
	srand((unsigned int)time(0));
}

//  ��ӡ���̣�����printBoard���Զ�ά����ķ�ʽ����ѭ����ӡ
void printBoard(char board[MAX_ROW][MAX_COL]) {
	//ÿ�δ�ӡ֮ǰ������
	system("cls");
	for (int row = 0; row < MAX_ROW; row++) {
		//�ڴ�ӡÿһ��֮ǰ�������
		printf("+--+--+--+\n");
		for (int col = 0; col < MAX_COL; col++) {
			// ��ӡ�ַ���ʹ�� %c
			// ÿ��ӡһ�У��ڴ�ӡ֮ǰ����|
			printf("| %c", board[row][col]);
		}
		//��ӡ֮�����|���γ� 3 �С�
		printf("|");
		//ÿ�δ�ӡ��һ�У����л��в��������3��3�������γɵ���������
		printf("\n");
	}//��ӡ��������֮���ڼ�����ߣ��γɺ�������
	printf("+--+--+--+\n");
}

//  �������
void playerMove(char board[MAX_ROW][MAX_COL]) {
	printf("�ֵ�������ӣ�\n");
	//����whileѭ������֤�û��������ʱ������������
	while (1) {
		printf("����������λ�õ�����(row col)��");
		//�����Ļ����ģ�飬�����к�������
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//��������֮��һ��Ҫ��֤��������ݣ���ֹ�������磨10��20��������������
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("������������������������룡\n");
			continue;//�������룬����ѭ��
		}
		// ��ǰλ�ò�Ϊ ' ' ��˵�������ˣ�Ҳ��Ҫ��������
		if (board[row][col] != ' ') {
			printf("��ǰλ�����ӣ��޷�����\n");
			continue;
		}
		//�������Ϊ X ��������ǰѭ��
		board[row][col] = 'X';
		break;
	}
}

// ��������
void computerMove(char board[MAX_ROW][MAX_COL]) {
	printf("�ֵ���������!\n");
	while (1) {
		//��������ʱ���������λ�ã��õ����������,ʹ�������Χ��������������
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (board[row][col] != ' ') {
			// ������в��ǿո�˵��������,��������������
			continue;
		}
		board[row][col] = 'O';
		break;
	}
}


//�жϺ���ĺ���
int isFull(char board[MAX_ROW][MAX_COL]) {
	//������������Ҳ��� ' ' ����˵���������ˣ�ֻҪ�ҵ� ' ' ˵��û��
	//Լ�����˷���1��û������0
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			if (board[row][col] == ' ') {
				//û��
				return 0;
			}
		}
	}return 1;
}

// �ж�ʤ��,����Ҫ����ʤ����ʹ��char����
// ��������Ӯ���� X ������Ӯ���� O��ƽ�ַ��� P��ʤ��δ�ַ��� ' '
char checkwinner(char board[MAX_ROW][MAX_COL]) {
	//1.���������
	for (int row = 0; row < MAX_ROW; row++) {
		if (board[row][0] != ' '
			&& board[row][0] == board[row][1]
			&& board[row][0] == board[row][2]) {
			return board[row][0];
		}
	}
	//2.���������
	for (int col = 0; col < MAX_ROW; col++) {
		if (board[0][col] != ' '
			&& board[0][col] == board[1][col]
			&& board[0][col] == board[2][col]) {
			return board[0][col];
		}
	}
	//3.������жԽ���
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
	// �ж�����
	if (isFull(board)) {
		return 'p';
	}return ' ';

}

int main() {
	//  ���ȴ������̲���ʼ��
	//  ���ﲻҪ��board[3][3],��ֹ���� 3 �� 3 ��죬�������ú궨��
	char board[MAX_ROW][MAX_COL] = { 0 };
	//  ʹ�� init ���� ��ʼ����ά����{0}Ӧ����ɿո�  ' '
	//  �˴�Ҳ���Խ� init���������е�˫�� for ѭ��ֱ������
	//  ������ά�����ʼ��Ϊ ' '����ʾ��һ���̶����ܵ��߼����Ƚ��ʺ��ú�������ķ������
	init(board);
	char winner = ' ';
	//  ʹ��whileѭ����������������
	while (1) {
		//1.�ȴ�ӡ��������
		printBoard(board);
		//2.�������
		playerMove(board);
		winner = checkwinner(board);
		if (winner != ' ') {
			//ʤ���ѷ֣�����ѭ��
			break;
		}
		//3.��������
		computerMove(board);
		//4.�ж�ʤ��
		winner = checkwinner(board);
		if (winner != ' ') {
			//ʤ���ѷ֣�����ѭ��
			break;
		}
	}
	if (winner = 'X') {
		printf("��ϲ�㣬��ʤ��!\n");
	}
	else if (winner = 'O') {
		printf("���ź������е��ѽ!\n");
	}
	else {
		printf("��͵������忪!\n");
	}
	system("pause");
	return 0;
}
