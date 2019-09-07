#include <iostream>
#include<windows.h>
#include<conio.h>
int player1_point;
int player2_point;
int dir = -1;

int ball_x=3;
int ball_y=57;

int boule_delta = 0;

bool t11=true;
bool t22=false;
bool t33=false;

short tx = 2;


COORD p = { 0, 0 };
auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x, int y)
{
	p.X = x;
	p.Y = y;
	SetConsoleCursorPosition(handle, p);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
using namespace std;
void init_game();
int game_board[61][20];

bool keyuppressed=false;
bool keydownpressed=false;
bool keyuppressed2=false;
bool keydownpressed2=false;

bool isBoardDirty = true;
bool isScoreDirty = true;
bool isBallDirty = true;
bool isPlateformDirty = true;


int platform1_y = 2;
int plateform2_y = 2;

void checkdir() {
	if (dir == 1 && ball_x == 57) {
		dir = -1;
	}
	if (dir == -1 && ball_x == 3) {
		dir = 1;
	}
}

void t1() {
	ball_x+=dir;
	ball_y--;
}

void t2(){
	ball_x+= 2*dir;
}
void t3() {
	ball_y++;
	ball_x+=dir;

}

void checkplatecoll() {
	if ((game_board[ball_x + 1][ball_y] == 2) || (game_board[ball_x-1][ball_y] == 2)) {
		tx = 1;
	}
	if ((game_board[ball_x + 1][ball_y] == 3) || (game_board[ball_x - 1][ball_y] == 3)) {
		tx = 2;
	}
	if ((game_board[ball_x + 1][ball_y] == 4) || (game_board[ball_x - 1][ball_y] == 4)) {
		tx = 3;
	}
	if (ball_x == 3) {
		if (game_board[ball_x - 1][ball_y] == 0) {
			player2_point++;
			isScoreDirty = true;
			tx = 4;
		}
	}
	if (ball_x==57) {
		//cout << "dowg";
		//Sleep(1000);
			if (game_board[ball_x+1][ball_y] == 0) {
				player1_point++;
				tx = 5;
				isScoreDirty = true;
				//cout << "dowg";
				//Sleep(1000);
			}
		
	}
}

void initplate() {
	for (int y = 1; y < 19; y++) {
		game_board[2][y] = 0;
		game_board[58][y] = 0;
	}
	for (int p = 0; p < 3; p++) {
		game_board[2][2 + p] = p + 2;
	}
	for (int p = 0; p < 3; p++) {
		game_board[58][2 + p] = p + 2;
	}
	plateform2_y = 2;
	platform1_y = 2;
}

void boulelogic() {

	
	boule_delta +=16.66;
	if (boule_delta < 100)
		return;

	boule_delta = 0;

		//inverse direction and check for left right collision
		checkdir();

		//colision up and down
		if (ball_x == 57) {
			//cout << "lets gooo";
			//Sleep(1000);
			checkplatecoll();
		}
		if (ball_x == 3) {
			//cout << "bruh";
			checkplatecoll();
		}


		switch (tx) {
		case 1:
			t1();
			if (game_board[ball_x][ball_y] == 8) {
				tx = 3;
				ball_x -= dir;
				ball_y++;
			}
			break;
		case 2:
			t2();
			if (game_board[ball_x+1][ball_y] != 8) {
				ball_x -= dir;
			}

			tx = 2;
			break;
		case 3:
			t3();
			if (game_board[ball_x][ball_y] == 8) {
				tx = 1;
				ball_y--;
				ball_x -= dir;
			}
			break;
		case 4:
			ball_x = 57;
			ball_y = 3;
			tx = 2;
			initplate();
			//isScoreDirty = true;
			break;
		case 5:
			ball_x = 10;
			ball_y = 3;
			initplate();
			tx = 2;
			//Sleep(1000);
			//cout << "hey";
			//isScoreDirty = true;
			break;
		}
		

		isBallDirty = true;
}

void moveup() {
	platform1_y--;
	isPlateformDirty = true;
}
void movedown() {
	platform1_y++;
	isPlateformDirty = true;
}
void moveup1() {
	plateform2_y--;
	isPlateformDirty = true;
}
void movedown1(){
	plateform2_y++;
	isPlateformDirty = true;
}


void init_game(){

	ball_x = 57;
	ball_y = 3;

	/*for (int x = 0; x < 61; x++) {
		for (int y = 0; y < 20; y++) {
			game_board[x][y] = 0;
		}
	}*/
	for (int x = 0; x < 61; x++) {
		game_board[x][19] = 8;
		game_board[x][0] = 8;

	}
	for (int y = 1; y < 19; y++) {
		game_board[0][y] = 8;
		game_board[60][y] = 8;
	}

	game_board[ball_x][ball_y] = 5;
}

int last_ball_x;
int last_ball_y;
void render() {
	
	
	//Board
	if (isBoardDirty) {
		gotoxy(0, 0);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 61; x++) {
				gotoxy(x, y);
				if (game_board[x][y] == 8)
					cout << "#";
			}
		}
		isBoardDirty = false;
	}

	//Balls
	if (isBallDirty) {

		gotoxy(last_ball_x, last_ball_y);
		cout << " ";

		gotoxy(ball_x, ball_y);
		cout << "O";
		isBallDirty = false;

		last_ball_x = ball_x;
		last_ball_y = ball_y;

		gotoxy(22, 22);
		cout << "last x:" << last_ball_x;
		cout << "x:" << ball_x;

	}
	
	if (isPlateformDirty) {

		for (int y = 1; y < 19; y++) {
			gotoxy(2, y);
			if (y >= platform1_y && y < platform1_y + 3)
				cout << "|";
			else
				cout << " ";
			gotoxy(58, y);
			if (y >= plateform2_y && y < plateform2_y + 3)
				cout << "|";
			else
				cout << " ";
		}

		isPlateformDirty = false;
	}
	
	//Score Panel
	if (isScoreDirty) {
		gotoxy(10, 0);
		cout << "player1 score: " << player1_point << "  player2 score: " << player2_point;
		isScoreDirty = false;
	}
}
	

void updategamelogic() {

	for (int y = 1; y < 19; y++) {
		game_board[2][y]=0;
		game_board[58][y]=0;
	}

		if ((keyuppressed) &&(game_board[2][platform1_y - 1] != 8))
			moveup();
		if ((keydownpressed) && (game_board[2][platform1_y + 3] != 8))
			movedown();
		if ((keyuppressed2) && (game_board[58][plateform2_y - 1] != 8))
			moveup1();
		if ((keydownpressed2) && (game_board[58][plateform2_y + 3] != 8))
			movedown1();

		
		for (int p = 0; p < 3; p++) {
			game_board[2][platform1_y + p] = p+2;
		}
		for (int p = 0; p < 3; p++) {
			game_board[58][plateform2_y + p] = p+2;
		}
		boulelogic();

}

void update_input() {
		keyuppressed =
		keydownpressed =
		keyuppressed2 =
		keydownpressed2 = false;
	if (_kbhit()) {
		switch (_getch()) {
		case 'q': {
			keyuppressed = true;
			break;
		}
		case 'a': {
			keydownpressed = true;
			break;
		}
		case 'i':{
			keyuppressed2 = true;
			break;
		}
		case 'k':{
			 keydownpressed2 = true;
			 break;
		}
		}

	}
}

int main()
{
	ShowConsoleCursor(false);
		init_game();
		while (true) {
			update_input();
			updategamelogic();
			render();
			Sleep(16);
		}

}
