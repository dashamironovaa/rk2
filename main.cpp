#include <iostream>
#include <iostream>
#include <windows.h>
#include <locale>
#include <conio.h>
#include <limits>
#include "source.h"

/* ����� ���������� �� ���� */
class Coord {
public:
	int x_;
	int y_;
	int fox_count;

	Coord() {
		//std::cout << "h";
		x_ = 0;
		y_ = 0;
		fox_count = 0;
	}
	/* �������� ���������� */
	void get_coord() {
		std::cout << x_ << ' ' << y_;
	}
	/* �������� ���������� ��� � ���� ���������� */
	void get_fox() {
		std::cout << fox_count;
	}
};

/* ����� �������� ����, ������� ������� �� �������-�������� ��������� */
class Board {
public:
	/* �������� ������� - ���� */
	Coord** board = new Coord * [10];
	Board() {
		char fox = 253, user = 1;
		std::cout << fox << "- Fox  " << user << "- User's position" << std::endl;
		for (int j = 0; j < 10; j++) {
			board[j] = new Coord[10];
		}
		/* ������ ���������� */
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				board[i][j].x_ = i;
				board[i][j].y_ = j;
			}
		}
	}
};

/* ��������� �������� ���� */
class DrawBoard {
public:
	int x_new = 0;
	int y_new = 0;
	int delta = 1;
	char fox = 253;
	char empty_cell = 254;
	int x_user = 0;
	int y_user = 14;
	char user_face = 1;
	DrawBoard() {
		x_new = 6; y_new = 12;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				DrawCell(x_new, y_new);
				x_new = x_new + 2;
			}
			x_new = 6;
			y_new--;
		}
		std::cout << std::endl;
		console_gotoxy(x_user, y_user);
		x_user = 0;
		y_user = y_user + 1;
	}

	void DrawCell(int x_, int y_) {
		console_gotoxy(x_, y_);
		std::cout << empty_cell;
	}

	void DrawFox(int x, int y) {
		int x_ = 6 + 2 * x;
		int y_ = 12 - y;
		console_gotoxy(x_, y_);
		std::cout << fox;
	}

	void DrawUser(int x, int y) {
		int x_ = 6 + 2 * x;
		int y_ = 12 - y;
		console_gotoxy(x_, y_);
		std::cout << user_face;
		y_user = y_user + 3;
		x_user = 0;
		console_gotoxy(x_user, y_user);
	}

};

/* ���������� ���� */
class Game {
public:								// ������ ���������� ������������ ��� �������� ���������� ������� ������
	int x_old = 6, y_old = 12;		// ��������� ��������� �������� ���������, ����� �� ���������� ������
	Board* brd = nullptr;
	DrawBoard* dr_brd = nullptr;
	Game(Board* ptr, DrawBoard *d_ptr) {
		brd = ptr;
		dr_brd = d_ptr;
		/* �������� �������� ��������� */
		int foxes = 8;
		while (foxes > 0) {
			int x = rand() % 10;	// � ������ ������ rand ���� ��� ��������� ���������
			int y = rand() % 10;	// ������� � ��� ��� �����������
			brd->board[x][y].fox_count++;
			//std::cout << "rand: " << x << ' ' << y << std::endl;
			// ��� "���������" ���������� ������ ����������, ��� �������� ����
			foxes--;
		}

		bool isFinish = false;
		int fox_num = 0;		// ��������� ����
		std::cout << "Enter coordinates [0-9]" << std::endl;
		while (!isFinish) {
			int fox_middle = 0;		// ���������� ��� � ��������� ����������
			int x_in, y_in;
			std::cout << "Enter X: ";
			std::cin >> x_in;
			std::cout << "Enter Y: ";
			std::cin >> y_in;
			fox_middle = CheckFox(x_in, y_in, brd);
			std::cout << "Fox count is: " << fox_middle << std::endl;
			fox_num = fox_num + fox_middle;		// ����� ���������� ��������� ���
			if (fox_num == 8) {
				std::cout << "All foxes have been founded" << std::endl;
				isFinish = true;
			}
		}
	}
	/* ������� �������� ��� � �������� ���������� */
	int CheckFox(int x, int y, Board* ptr) {
		int x_new = x; int y_new = y;	// ���������� ���������� ���������
		int fox = 0;		// ����� ���������� ���

		dr_brd->DrawCell(x_old, y_old);

		//�������� ������ �������
		while (x_new < 10) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;		// ��������� ���� ���
			ptr->board[x_new][y_new].fox_count = 0;			// ��������, �.�. �����
			x_new++;
		}
		x_new = x;	y_new = y;
		//�������� �� ����� �������
		while (x_new >= 0) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			x_new--;
		}
		x_new = x; y_new = y;
		//�������� ����������� �����
		while (y_new < 10) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			y_new++;
		}
		x_new = x; y_new = y;
		//�������� ����������� ����
		while (y_new >= 0) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			y_new--;
		}
		x_new = x; y_new = y;
		//�������� �� ��������� ������-�����
		while (x_new < 10 && y_new < 10) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			x_new++; y_new++;
		}
		x_new = x; y_new = y;
		//�������� �� ��������� �����-�����
		while (x_new >= 0 && y_new < 10) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			x_new--; y_new++;
		}
		x_new = x; y_new = y;
		//�������� �� ��������� ������-����
		while (x_new < 10 && y_new >= 0) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			x_new++; y_new--;
		}
		x_new = x; y_new = y;
		//�������� �� ��������� �����-����
		while (x_new >= 0 && y_new >= 0) {
			if (ptr->board[x_new][y_new].fox_count > 0) {
				dr_brd->DrawFox(x_new, y_new);
			}
			fox = fox + ptr->board[x_new][y_new].fox_count;
			ptr->board[x_new][y_new].fox_count = 0;
			x_new--; y_new--;
		}

		dr_brd->DrawUser(x, y);			// ���� �������� �� �������, ��� ���� ���, �� �� ����������� ����
		x_old = 6 + 2*x; y_old = 12-y;		// ������ "�����" ���������� ����� "�������"

		return fox;
	}
};

int main() {
	Board* board = new Board;		// �������� ����
	DrawBoard *draw = new DrawBoard;
	std::cout << std::endl;
	Game gm(board, draw);			// ������ ����
	return 0;
}
