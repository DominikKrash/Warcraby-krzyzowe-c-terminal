#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

const int BOARD_WIDTH = 17;
const int BOARD_HEIGHT = 17;
const int BUFFER_SIZE = 40;
const int LOG_SIZE = 200;
const int FALSE = 0;
const int TRUE = 1;
const int GAMEBOARD[BOARD_HEIGHT][BOARD_WIDTH] = { { 0, 0, 0, 0, -1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 0, 0, 0 }
, { 0, 0, 0, 0, 0, 2, 0, 0, 4, 0, 0, 3, 0, 0, 0, 0, 0 }
, { 0, 0, 0, 0, 0, 0, -1, 1, -1, 1, -1, 0, 0, 0, 0, 0, 0 }
, { 0, 0, 0, 0, 0, 0, 0, 2, 4, 3, 0, 0, 0, 0, 0, 0, 0 }
, { -3, 0, 0, 0, -1, 1, -1, 1, -1, 1, -1, 1, -1, 0, 0, 0, -3 }
, { 4, 2, 0, 0, 4, 2, 4, 3, 4, 2, 4, 3, 4, 0, 0, 3, 4 }
, { 4, 0, -3, 0, -1, 1, -1, 1, -1, 1, -1, 1, -1, 0, -3, 0, 4 }
, { 4, 0, 4, 2, 4, 3, 4, 2, 4, 3, 4, 2, 4, 3, 4, 0, 4 }
, { -3, 1, -3, 1, -3, 1, -3, 1, -3, 1, -3, 1, -3, 1, -3, 1, -3 } // srodek
, { 4, 0, 4, 3, 4, 2, 4, 3, 4, 2, 4, 3, 4, 2, 4, 0, 4 }
, { 4, 0, -3, 0, -2, 1, -2, 1, -2, 1, -2, 1, -2, 0, -3, 0, 4 }
, { 4, 3, 0, 0, 4, 3, 4, 2, 4, 3, 4, 2, 4, 0, 0, 2, 4 }
, { -3, 0, 0, 0, -2, 1, -2, 1, -2, 1, -2, 1, -2, 0, 0, 0, -3 }
, { 0, 0, 0, 0, 0, 0, 0, 3, 4, 2, 0, 0, 0, 0, 0, 0, 0 }
, { 0, 0, 0, 0, 0, 0, -2, 1, -2, 1, -2, 0, 0, 0, 0, 0, 0 }
, { 0, 0, 0, 0, 0, 3, 0, 0, 4, 0, 0, 2, 0, 0, 0, 0, 0 }
, { 0, 0, 0, 0, -2, 1, 1, 1, -2, 1, 1, 1, -2, 0, 0, 0, 0 } };

//rodzaje wygranych
void endLineWin(int tab[][BOARD_WIDTH],bool &game){
	int i = 0;
	while (i < BOARD_WIDTH){
		if (tab[0][i] == -2) game = FALSE;
		i++;
	}
	i = 0;
	while (i < BOARD_WIDTH){
		if (tab[BOARD_HEIGHT - 1][i] == -1) game = FALSE;
		i++;
	}
}
void hitWin(int tab[][BOARD_WIDTH], bool &game){
	int p1 = 0;
	int p2 = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++){
		for (int j = 0; j < BOARD_WIDTH; j++){
			if (tab[i][j] == -1) p1++;
			else if (tab[i][j] == -2) p2++;
		}
	}
	if (p1 == 0 || p2 == 0) game = FALSE;
}
void renderLine() { 
	cout << "  ";
	for (int i = 0; i < (BOARD_WIDTH / 2) + 1; i++) {
		cout << i + 1 << " ";
	}
	cout << " " << endl;;
}

/*
" " = -3 // RUCHOME MIEJSCE
" " = 0 // PUSTE POLE
x = -1
o = -2
- = 1
\ = 2
/ = 3
| = 4
*/
//rysuje zaleznie od znaku
void renderSign(int tab[][BOARD_WIDTH], int x, int y,char p1,char p2) {//wypisz znak
	if (tab[y][x] == -2) {
		cout << p2;
	}

	else if (tab[y][x] == -1) {
		cout << p1;
	}
	else if (tab[y][x] == 0 || tab[y][x] == -3) {
		cout << " ";
	}
	else if (tab[y][x] == 1) {
		cout << "-";
	}
	else if (tab[y][x] == 2) {
		cout << "\\";
	}
	else if (tab[y][x] == 3) {
		cout << "/";
	}
	else if (tab[y][x] == 4) {

		cout << "|";
	}
}
//rysuje cala tablice i mmiejsce z gra 
void renderBoard(int tab[][BOARD_WIDTH],char p1, char p2) {
	char indeks = 73;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		if (i % 2 == 0) {
			cout << indeks << " ";
		}
		else {
			cout << "  ";
		}
		for (int j = 0; j < BOARD_WIDTH; j++) {
			renderSign(tab, j, i,p1,p2);
		}
		if (i % 2 == 0) {
			cout << " " << indeks;
			indeks--;
		}
		cout << endl;
	}
}
void checkDirection(int xSrc, int ySrc, int xTo, int yTo, int &xVec, int &yVec){
	xVec = xTo - xSrc;
	yVec = yTo - ySrc;
}
void playerText(bool player){
	if (player) cout << "Player 2 turn: " << endl;
	else cout << "Player 1 turn: " << endl << endl;
}

//wypisywanie gry
void render(int board[][BOARD_WIDTH],bool player,char p1, char p2) {
	renderLine();
	renderBoard(board,p1,p2);
	renderLine();
	playerText(player);
}

void initializeBoard(int tab[][BOARD_WIDTH]) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			tab[i][j] = GAMEBOARD[i][j];
		}
	}
}
//czy mozemy ruszycz do danego pola 
bool canMove(int xVec, int yVec, int tab[][BOARD_WIDTH], int x, int y) {
	if (xVec != 0 && yVec == 0 && tab[y][x] == 1) return TRUE;
	else if (xVec == 0 && yVec != 0 && tab[y][x] == 4) return TRUE;
	else if (((xVec > 0 && yVec < 0) || (xVec < 0 && yVec >0)) && tab[y][x] == 3) return TRUE;
	else if (((xVec > 0 && yVec > 0) || (xVec < 0 && yVec <0)) && tab[y][x] == 2) return TRUE;
	return FALSE;
}
bool checkMove(int tab[][BOARD_WIDTH], int x, int y) {//JAK MOZEMY ISC ZWRACA TRUE
	bool hit = FALSE;
	for (int i = -2; i <= 2; i += 2) {
		for (int j = -2; j <= 2; j += 2) {
			if (y + i<BOARD_HEIGHT && y +  i >= 0 && x +  j < BOARD_WIDTH && x + j >= 0){
				if (tab[y + i][x + j] == -3  && canMove(j, i, tab, x + (j / 2), y + (i / 2))) {
					hit = TRUE;
				}
			}
		}
	}
	return hit;
}
bool checkHit(int tab[][BOARD_WIDTH], int x, int y, bool player) {//JAK MOZEMY BIC ZWRACA TRUE
	bool hit = FALSE;
	for (int i = -2; i <= 2; i += 2) {
		for (int j = -2; j <= 2; j += 2) {
			if (y + 2*i<BOARD_HEIGHT  && y + 2*i >= 0 && x + 2*j < BOARD_WIDTH && x + 2*j >= 0){
				if (tab[y + i][x + j] == -2 && player == FALSE && tab[y + 2 * i][x + 2 * j] == -3 && canMove(j, i, tab, x + j / 2, y + i / 2) && canMove(j, i, tab, x + 3 * j / 2, y + 3 * i / 2)) {
					hit = TRUE;
		
					
				}
				else if (tab[y + i][x + j] == -1 && player == TRUE && tab[y + 2 * i][x + 2 * j] == -3 && canMove(j, i, tab, x + j / 2, y + i / 2) && canMove(j, i, tab, x + 3*j / 2, y + 3*i / 2)) {
					hit = TRUE;
				
				}
			}
		}
	}
	return hit;
}
//sprawdza czy moze sie ruszyc
bool canMoveNearby(int tab[][BOARD_WIDTH], bool player){
	bool hit = FALSE;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (player == FALSE && tab[i][j] == -1) {
				if (checkMove(tab,i,j)) hit = TRUE;
			}
			else if (player == TRUE && tab[i][j] == -2){
				if (checkMove(tab, i, j)) hit = TRUE;
			}
		}
	}
	return hit;
}

//czy moze uderzyc w okolicy
bool checkHitNearby(int tab[][BOARD_WIDTH], bool player) {
	bool hit = FALSE;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (player == FALSE && tab[i][j] == -1) {
				if (checkHit(tab, j, i, player)) hit = TRUE;
			}
			else if (player == TRUE && tab[i][j] == -2){
				if (checkHit(tab, j, i, player)) hit = TRUE;
			}
		}
	}
	return hit;
}
//zamienia podane wspolrzedne na wspolrzedne ktorej uzywa nasza logika programu czyli tablica int
void coordinatesInput(char tab[], int &wspx, int &wspy) { //ustalamy wspolrzedne
	if (toupper(tab[0]) < 74 && toupper(tab[0]) > 64) {
		wspy = abs(toupper(tab[0]) - 73);
		wspx = tab[1] - 48;
		if (wspx != 0)wspx = wspx * 2 - 2; 
		if (wspy != 0)wspy = wspy * 2;
	}

	else if (tab[0] > 47 && tab[0] < 58) {
		wspx = abs(toupper(tab[0]) - 73);
		wspy = tab[1] - 48;
		if (wspx != 0) wspx = wspx * 2 - 2;
		if (wspy != 0)wspy = wspy * 2;
	}
}
//zamiana miejscami
void swap(int tab[][BOARD_WIDTH], int xSrc, int ySrc, int xTo, int yTo) {
	int temp = tab[ySrc][xSrc];
	tab[ySrc][xSrc] = tab[yTo][xTo];
	tab[yTo][xTo] = temp;
}


/*
" " = -3 // RUCHOME MIEJSCE
" " = 0 // PUSTE POLE
x = -1
o = -2
- = 1
\ = 2
/ = 3
| = 4
*/
void moveWin(int tab[][BOARD_WIDTH], bool &game, bool player){
	if (!canMoveNearby(tab, player) && !checkHitNearby(tab, player))game = FALSE;
}

bool movePionek(int tab[][BOARD_WIDTH], int xSrc, int ySrc, int xTo, int yTo, bool &turn) {
	int xSro, ySro; // sprawdzamy czy mozna przejsc
	int xVec, yVec; // kierunek bicia
	checkDirection(xSrc, ySrc, xTo, yTo, xVec, yVec);
	xSro = (xSrc + xTo) / 2;
	ySro = (ySrc + yTo) / 2;
	if (tab[yTo][xTo] == -3 && !checkHitNearby(tab, turn)) {
		if (canMove(xVec, yVec, tab, xSro, ySro)) {
			swap(tab, xSrc, ySrc, xTo, yTo);
			turn = !turn;
			return TRUE;
		}
	}
	else if (tab[yTo][xTo] == -2 && turn == FALSE) {
		if (tab[yTo + yVec][xTo + xVec] == -3 && canMove(xVec,yVec,tab,xSro,ySro)) {
			swap(tab, xSrc, ySrc, xTo + xVec, yTo + yVec);
			tab[yTo][xTo] = -3;
			if (checkHit(tab, xTo + xVec, yTo + yVec, turn)) return TRUE;
			turn = !turn;
			return TRUE;
		}
	}
	else if (tab[yTo][xTo] == -1 && turn == TRUE) {
		if (tab[yTo + yVec][xTo + xVec] == -3 && canMove(xVec, yVec, tab, xSro, ySro)) {
			swap(tab, xSrc, ySrc, xTo + xVec, yTo + yVec);
			tab[yTo][xTo] = -3;
			if (checkHit(tab, xTo + xVec, yTo + yVec, turn)) return TRUE;
			turn = !turn;
			return TRUE;
		}
	}
	return FALSE;
}

void input(bool &turn, int &wspx, int &wspy, int tab[][BOARD_WIDTH], char log[][BUFFER_SIZE], char log2[][BUFFER_SIZE], int &dl, int &dl2) {
	int nextX, nextY;
	char buffer[BUFFER_SIZE];
	cin >> buffer;
	char temp[BUFFER_SIZE];
	strcpy_s(temp, buffer);
	coordinatesInput(buffer, wspx, wspy);
	if (tab[wspy][wspx] == -1 && turn == FALSE) {
		cin >> buffer;
		coordinatesInput(buffer, nextX, nextY);
		if (movePionek(tab, wspx, wspy, nextX, nextY, turn)){
			strcat_s(temp, buffer);
			strcpy_s(log[dl], temp);
			dl++;
		}
	}
	else if (tab[wspy][wspx] == -2 && turn == TRUE) {
		cin >> buffer;
		coordinatesInput(buffer, nextX, nextY);
		if (movePionek(tab, wspx, wspy, nextX, nextY, turn)){
			strcat_s(temp, buffer);
			strcpy_s(log2[dl2], temp);
			dl2++;
		}
	}
}
//wypisujemy info o grze 
void read_Log(char log[][BUFFER_SIZE], char log2[][BUFFER_SIZE], int l1, int l2){
	cout << "MOVES LIST" << endl;
	cout << "Player 1     Player 2" << endl;
	int dl = l1 >= l2 ? l1 : l2;
	for (int i = 0; i < dl; i++){
		if (i < l1) cout << log[i];
		cout << "         ";
		if (i < l2) cout << log2[i];
		cout << endl;
	}
	cout << endl;
}
void winCondition(int tab[][BOARD_WIDTH], bool &game,bool player){
	endLineWin(tab, game);
	hitWin(tab, game);
	moveWin(tab, game, player);
}
void instruction(){
	int a;
	while (TRUE){
		cout << "Warcaby" << endl;
		cout << "sterowanie to podanie wspolrzednej wybranej w figury a nastepnie wsplrzednej docelowej" << endl;
		cout << "zbijanie nastepuje po nacelowaniu na zbijana figure" << endl;
		cout << "nacisnij przycisk z klawiatury by zaczac gre" << endl;
		a = getchar();
		if (a){
			system("cls");
			break;
		}
	}
}

void playerInitialize(char &p1, char &p2){
			cout << "Podaj rodzaj pionkow jaki chcesz uzywac ?" << endl;
			cout << "pionek 1:" << endl;
			cin >> p1;
			cout << "pionek 2:" << endl;
			cin >> p2;
	system("cls");
	}
void endGameStatement(bool player){
	system("cls");
	int a;
	if (player){
		cout << "Player 1 WON!";
	}
	else cout << "Player 2 WON!";
	cin >> a;
}
int main() {

	int GameBoard[BOARD_HEIGHT][BOARD_WIDTH];
	int x, y;
	bool Turn = FALSE; // GRACZ NR 1 ZACZYNA
	bool GameTime = TRUE; //CZAS GRY
	char Log_P1[LOG_SIZE][BUFFER_SIZE], Log_P2[LOG_SIZE][BUFFER_SIZE];
	char p1, p2;
	int Log_Length = 0;
	int Log2_Length = 0;
	initializeBoard(GameBoard);
	instruction();
	playerInitialize(p1, p2);
	do {
		render(GameBoard,Turn,p1,p2);
		read_Log(Log_P1, Log_P2, Log_Length, Log2_Length);
		input(Turn, x, y, GameBoard,Log_P1,Log_P2,Log_Length,Log2_Length);
		system("cls");
		winCondition(GameBoard, GameTime,Turn);
		
	} while (GameTime);
	endGameStatement(Turn);
}