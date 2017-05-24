// VALDEZ, Jessica Ria B. 2013-51016
// Push Box! (Game for ICS-OS; App-based)
// For mechanics, read README file included in folder :)

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

// PROTOTYPES
void initialize_board(char level);			// sets initial game board after player choice of level
void check_win(char level);					// checks if current board has achieved goal
void draw_board(char level);				// draws and updates playable board depending on player choice of level
void box2(int x, int y, int color);			// draws 15x15 box; used in draw_board fxn
void print_gamemenu();						// prints game controls
void print_header();						// main menu
void print_levels();						// level menu
void erase();								// clears area by covering it with a black rectangle; from lightsout code (Ibay, DeLaVina)


// CONSTANTS
#define WHITE 63
#define BROWN 20
#define PINK 60
#define BLACK 0
#define PURPLE 5
#define GREEN 2
#define BLUE 25
#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define quit 'b'
#define start 'p'
#define quit_game 'e'
#define reset 'r'

// GLOBAL VARIABLES
int setABoard[7][6];		// game board for levels 0-4
int setBBoard[7][7];		// game board for levels 5-9
int xPos;					// stores player's current x position
int yPos;					// stores player's current y position
int wasAtX = 0;				// flag to check if player was from a goal marker
int moves = 0;				// counts player's number of moves
int goal;					// flag to check whether player has achieved goal
char level;					// current level (from player's choice)

int main(){

	char keypress = start; 

	set_graphics(VGA_320X200X256);
	
	do{
		print_header();
		keypress=(char)getch();
		
		if(keypress == start){
			erase(1,1,400,220);
			
			print_levels();
			keypress=(char)getch();
			erase(1,1,400,220);
			level = keypress;
			initialize_board(level);
			draw_board(level);
			moves = 0;
			switch(level){
				case '0': write_text("Level 0", 3, 25, GREEN, 0); break;
				case '1': write_text("Level 1", 3, 25, GREEN, 0); break; 
				case '2': write_text("Level 2", 3, 25, GREEN, 0); break;
				case '3': write_text("Level 3", 3, 25, GREEN, 0); break;
				case '4': write_text("Level 4", 3, 25, GREEN, 0); break;
				case '5': write_text("Level 5", 3, 25, GREEN, 0); break;
				case '6': write_text("Level 6", 3, 25, GREEN, 0); break;
				case '7': write_text("Level 7", 3, 25, GREEN, 0); break;
				case '8': write_text("Level 8", 3, 25, GREEN, 0); break;
				case '9': write_text("Level 9", 3, 25, GREEN, 0); break;
			}
			do{
				check_win(level);
				keypress=(char)getch();

				if(keypress == reset){		// resets current level
					wasAtX = 0;
					moves = 0;
					erase(1,1,400,220);
					initialize_board(level);
					draw_board(level);
				}
				else if(keypress == up_key){		// player pressed 'w'
					if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
						if(setABoard[xPos-1][yPos] == 1){}
						else if(setABoard[xPos-1][yPos] == 0){	// if up position is a SPACE
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 0;
							setABoard[xPos-1][yPos] = 5;
							draw_board(level);
							xPos = xPos-1;
							yPos = yPos;
						}
						else if(setABoard[xPos-1][yPos] == 2 || setABoard[xPos-1][yPos] == 4){	// if up position is a BOX
							if(setABoard[xPos-2][yPos] == 1 || setABoard[xPos-2][yPos] == 2 || setABoard[xPos-2][yPos] == 4){
								// if next up pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setABoard[xPos-2][yPos] == 0){	// if next up pos is a SPACE
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setABoard[xPos-1][yPos] == 4) wasAtX = 1;								
								setABoard[xPos-1][yPos] = 5;
								setABoard[xPos-2][yPos] = 2;
								draw_board(level);
								xPos = xPos-1;
								yPos = yPos;
							}
							else if(setABoard[xPos-2][yPos] == 3){	// if next up pos is a GOAL MARK
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setABoard[xPos-1][yPos] == 4) wasAtX = 1;
								setABoard[xPos-1][yPos] = 5;
								setABoard[xPos-2][yPos] = 4;
								draw_board(level);
								xPos = xPos-1;
								yPos = yPos;
							}
						}
						else if(setABoard[xPos-1][yPos] == 3){	// if up position is a GOAL MARK
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 1;
							setABoard[xPos-1][yPos] = 5;
							draw_board(level);
							xPos = xPos-1;
							yPos = yPos;
						}
					}
					else{
						if(setBBoard[xPos-1][yPos] == 1){}
						else if(setBBoard[xPos-1][yPos] == 0){	// if up position is a SPACE
							// move character to space
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 0;
							setBBoard[xPos-1][yPos] = 5;
							draw_board(level);
							xPos = xPos-1;
							yPos = yPos;
						}
						else if(setBBoard[xPos-1][yPos] == 2 || setBBoard[xPos-1][yPos] == 4){	// if up position is a BOX
							
							if(setBBoard[xPos-2][yPos] == 1 || setBBoard[xPos-2][yPos] == 2 || setBBoard[xPos-2][yPos] == 4){
								// if next up pos is a WALL || BOX || SOLVED BOX
								// do nothing	
							}	
							else if(setBBoard[xPos-2][yPos] == 0){	// if next up pos is a SPACE
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setBBoard[xPos-1][yPos] == 4) wasAtX = 1;
								setBBoard[xPos-1][yPos] = 5;
								setBBoard[xPos-2][yPos] = 2;
								draw_board(level);
								xPos = xPos-1;
								yPos = yPos;
							}
							else if(setBBoard[xPos-2][yPos] == 3){	// if next up pos is a GOAL MARK
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setBBoard[xPos-1][yPos] == 4) wasAtX = 1;
								setBBoard[xPos-1][yPos] = 5;
								setBBoard[xPos-2][yPos] = 4;
								draw_board(level);
								xPos = xPos-1;
								yPos = yPos;
							}
						}
						else if(setBBoard[xPos-1][yPos] == 3){	// if up position is a GOAL MARK
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 1;
							setBBoard[xPos-1][yPos] = 5;
							draw_board(level);
							xPos = xPos-1;
							yPos = yPos;
						}
					}
				}
				else if(keypress == down_key){		// player pressed 's'
					if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
						if(setABoard[xPos+1][yPos] == 1){}
						else if(setABoard[xPos+1][yPos] == 0){	// if down position is a SPACE
							// move character to space
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 0;
							setABoard[xPos+1][yPos] = 5;
							draw_board(level);
							xPos = xPos+1;
							yPos = yPos;
						}
						else if(setABoard[xPos+1][yPos] == 2 || setABoard[xPos+1][yPos] == 4){	// if down position is a BOX
							if(setABoard[xPos+2][yPos] == 1 || setABoard[xPos+2][yPos] == 2 || setABoard[xPos+2][yPos] == 4){
								// if next down pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setABoard[xPos+2][yPos] == 0){	// if next down pos is a SPACE
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setABoard[xPos+1][yPos] == 4) wasAtX = 1;
								setABoard[xPos+1][yPos] = 5;
								setABoard[xPos+2][yPos] = 2;
								draw_board(level);
								xPos = xPos+1;
								yPos = yPos;
							}
							else if(setABoard[xPos+2][yPos] == 3){	// if next down pos is a GOAL MARK
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setABoard[xPos+1][yPos] == 4) wasAtX = 1;
								setABoard[xPos+1][yPos] = 5;
								setABoard[xPos+2][yPos] = 4;
								draw_board(level);
								xPos = xPos+1;
								yPos = yPos;
							}
						}
						else if(setABoard[xPos+1][yPos] == 3){	// if down position is a GOAL MARK
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 1;
							setABoard[xPos+1][yPos] = 5;
							draw_board(level);
							xPos = xPos+1;
							yPos = yPos;
						}
					}
					else{
						if(setBBoard[xPos+1][yPos] == 1){}
						else if(setBBoard[xPos+1][yPos] == 0){	// if down position is a SPACE
							// move character to space
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 0;
							setBBoard[xPos+1][yPos] = 5;
							draw_board(level);
							xPos = xPos+1;
							yPos = yPos;
						}
						else if(setBBoard[xPos+1][yPos] == 2 || setBBoard[xPos+1][yPos] == 4){	// if down position is a BOX
							if(setBBoard[xPos+2][yPos] == 1 || setBBoard[xPos+2][yPos] == 2 || setBBoard[xPos+2][yPos] == 4){
								// if next down pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setBBoard[xPos+2][yPos] == 0){	// if next down pos is a SPACE
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setBBoard[xPos+1][yPos] == 4) wasAtX = 1;
								setBBoard[xPos+1][yPos] = 5;
								setBBoard[xPos+2][yPos] = 2;
								draw_board(level);
								xPos = xPos+1;
								yPos = yPos;
							}
							else if(setBBoard[xPos+2][yPos] == 3){	// if next down pos is a GOAL MARK
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setBBoard[xPos+1][yPos] == 4) wasAtX = 1;
								setBBoard[xPos+1][yPos] = 5;
								setBBoard[xPos+2][yPos] = 4;
								draw_board(level);
								xPos = xPos+1;
								yPos = yPos;
							}
						}
						else if(setBBoard[xPos+1][yPos] == 3){	// if down position is a GOAL MARK
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 1;
							setBBoard[xPos+1][yPos] = 5;
							draw_board(level);
							xPos = xPos+1;
							yPos = yPos;
						}
					}

				}
				else if(keypress == left_key){		// player pressed 'a'
					if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
						if(setABoard[xPos][yPos-1] == 1){}
						else if(setABoard[xPos][yPos-1] == 0){	// if left position is a SPACE
							// move character to space
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 0;
							setABoard[xPos][yPos-1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos-1;
						}
						else if(setABoard[xPos][yPos-1] == 2 || setABoard[xPos][yPos-1] == 4){	// if left position is a BOX
							if(setABoard[xPos][yPos-2] == 1 || setABoard[xPos][yPos-2] == 2 || setABoard[xPos][yPos-2] == 4){
								// if next left pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setABoard[xPos][yPos-2] == 0){	// if left pos is a SPACE
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setABoard[xPos][yPos-1] == 4) wasAtX = 1;
								setABoard[xPos][yPos-1] = 5;
								setABoard[xPos][yPos-2] = 2;
								draw_board(level);
								xPos = xPos;
								yPos = yPos-1;
							}
							else if(setABoard[xPos][yPos-2] == 3){	// if next left pos is a GOAL MARK
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setABoard[xPos][yPos-1] == 4) wasAtX = 1;
								setABoard[xPos][yPos-1] = 5;
								setABoard[xPos][yPos-2] = 4;
								draw_board(level);
								xPos = xPos;
								yPos = yPos-1;
							}
						}
						else if(setABoard[xPos][yPos-1] == 3){	// if left position is a GOAL MARK
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 1;
							setABoard[xPos][yPos-1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos-1;
						}
					}
					else{
						if(setBBoard[xPos][yPos-1] == 1){}
						else if(setBBoard[xPos][yPos-1] == 0){	// if left position is a SPACE
							// move character to space
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 0;
							setBBoard[xPos][yPos-1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos-1;
						}
						else if(setBBoard[xPos][yPos-1] == 2 || setBBoard[xPos][yPos-1] == 4){	// if left position is a BOX
							if(setBBoard[xPos][yPos-2] == 1 || setBBoard[xPos][yPos-2] == 2 || setBBoard[xPos][yPos-2] == 4){
								// if next left pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setBBoard[xPos][yPos-2] == 0){	// if left pos is a SPACE
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setBBoard[xPos][yPos-1] == 4) wasAtX = 1;
								setBBoard[xPos][yPos-1] = 5;
								setBBoard[xPos][yPos-2] = 2;
								draw_board(level);
								xPos = xPos;
								yPos = yPos-1;
							}
							else if(setBBoard[xPos][yPos-2] == 3){	// if next left pos is a GOAL MARK
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setBBoard[xPos][yPos-1] == 4) wasAtX = 1;
								setBBoard[xPos][yPos-1] = 5;
								setBBoard[xPos][yPos-2] = 4;
								draw_board(level);
								xPos = xPos;
								yPos = yPos-1;
							}
						}
						else if(setBBoard[xPos][yPos-1] == 3){	// if left position is a GOAL MARK
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 1;
							setBBoard[xPos][yPos-1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos-1;
						}
					}
				}
				else if(keypress == right_key){		// player pressed 'd'
					if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
						if(setABoard[xPos][yPos+1] == 1){}
						else if(setABoard[xPos][yPos+1] == 0){	// if right position is a SPACE
							// move character to space
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 0;
							setABoard[xPos][yPos+1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos+1;
						}
						else if(setABoard[xPos][yPos+1] == 2 || setABoard[xPos][yPos+1] == 4){	// if right position is a BOX
							if(setABoard[xPos][yPos+2] == 1 || setABoard[xPos][yPos+2] == 2 || setABoard[xPos][yPos+2] == 4){
								// if next right pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setABoard[xPos][yPos+2] == 0){	// if next right pos is a SPACE
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setABoard[xPos][yPos+1] == 4) wasAtX = 1;
								setABoard[xPos][yPos+1] = 5;
								setABoard[xPos][yPos+2] = 2;
								draw_board(level);
								xPos = xPos;
								yPos = yPos+1;
							}
							else if(setABoard[xPos][yPos+2] == 3){	// if next right pos is a GOAL MARK
								if(wasAtX == 1) setABoard[xPos][yPos] = 3;
								else setABoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setABoard[xPos][yPos+1] == 4) wasAtX = 1;
								setABoard[xPos][yPos+1] = 5;
								setABoard[xPos][yPos+2] = 4;
								draw_board(level);
								xPos = xPos;
								yPos = yPos+1;
							}
						}
						else if(setABoard[xPos][yPos+1] == 3){	// if right position is a GOAL MARK
							if(wasAtX == 1) setABoard[xPos][yPos] = 3;
							else setABoard[xPos][yPos] = 0;
							wasAtX = 1;
							setABoard[xPos][yPos+1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos+1;
						}
					}
					else{
						if(setBBoard[xPos][yPos+1] == 1){}
						else if(setBBoard[xPos][yPos+1] == 0){	// if right position is a SPACE
							// move character to space
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 0;
							setBBoard[xPos][yPos+1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos+1;
						}
						else if(setBBoard[xPos][yPos+1] == 2 || setBBoard[xPos][yPos+1] == 4){	// if right position is a BOX
							if(setBBoard[xPos][yPos+2] == 1 || setBBoard[xPos][yPos+2] == 2 || setBBoard[xPos][yPos+2] == 4){
								// if next right pos is a WALL || BOX || SOLVED BOX
								// do nothing
							}	
							else if(setBBoard[xPos][yPos+2] == 0){	// if next right pos is a SPACE
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;

								if(setBBoard[xPos][yPos+1] == 4) wasAtX = 1;
								setBBoard[xPos][yPos+1] = 5;
								setBBoard[xPos][yPos+2] = 2;
								draw_board(level);
								xPos = xPos;
								yPos = yPos+1;
							}
							else if(setBBoard[xPos][yPos+2] == 3){	// if next right pos is a GOAL MARK
								if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
								else setBBoard[xPos][yPos] = 0;
								wasAtX = 0;
								if(setBBoard[xPos][yPos+1] == 4) wasAtX = 1;
								setBBoard[xPos][yPos+1] = 5;
								setBBoard[xPos][yPos+2] = 4;
								draw_board(level);
								xPos = xPos;
								yPos = yPos+1;
							}
						}
						else if(setBBoard[xPos][yPos+1] == 3){	// if right position is a GOAL MARK
							if(wasAtX == 1) setBBoard[xPos][yPos] = 3;
							else setBBoard[xPos][yPos] = 0;
							wasAtX = 1;
							setBBoard[xPos][yPos+1] = 5;
							draw_board(level);
							xPos = xPos;
							yPos = yPos+1;
						}
					}
				}
					
			} while(keypress != quit);		// exit loop if player presses 'b'
				
			erase(1,1,400,220);
			
		}
		
	} while(keypress != quit_game);			// exit game if player presses 'e'
	
	// clear screen after game exit
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void initialize_board(char level){	
	int i=0, j=0;
	
	// initialize boards with 0s
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			setABoard[i][j] = 0;
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			setBBoard[i][j] = 0;
		}
	}

	// 0 - space
	// 1 - wall
	// 2 - box
	// 3 - x mark/goal
	// 4 - properly positioned box
	// 5 - character
	
	// set borders as walls
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			if(j == 0) setABoard[i][j] = 1;
			if(i == 0) setABoard[i][j] = 1;
			if(j == 5) setABoard[i][j] = 1;
			if(i == 6) setABoard[i][j] = 1;
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			if(j == 0) setBBoard[i][j] = 1;
			if(i == 0) setBBoard[i][j] = 1;
			if(j == 6) setBBoard[i][j] = 1;
			if(i == 6) setBBoard[i][j] = 1;
		}
	}
	
	// set up game board depending on user input (level)
	switch(level){
		case '0':			
			setABoard[1][2] = 3;
			setABoard[1][3] = 1;
			setABoard[1][4] = 1;
			setABoard[2][3] = 1;
			setABoard[2][4] = 1;
			setABoard[3][1] = 4;
			setABoard[3][2] = 5;
			setABoard[4][3] = 2;
			setABoard[5][3] = 1;
			setABoard[5][4] = 1;

			goal = 2;
			xPos = 3;
			yPos = 2;
			break;
		case '1':
			setABoard[2][2] = 1;
			setABoard[2][4] = 5;
			setABoard[3][2] = 2;
			setABoard[3][3] = 4;
			setABoard[4][2] = 3;
			setABoard[4][3] = 4;

			goal = 3;
			xPos = 2;
			yPos = 4;
			break;
		case '2':
			setABoard[1][1] = 3;
			setABoard[1][4] = 1;
			setABoard[2][1] = 5;
			setABoard[2][2] = 2;
			setABoard[2][3] = 2;
			setABoard[3][1] = 1;
			setABoard[4][1] = 1;
			setABoard[4][2] = 1;
			setABoard[5][1] = 1;
			setABoard[5][2] = 1;
			setABoard[5][3] = 1;
			setABoard[5][4] = 3;

			goal = 2;
			xPos = 2;
			yPos = 1;
			break;
		case '3':
			setABoard[1][2] = 5;
			setABoard[1][4] = 1;
			setABoard[2][1] = 3;
			setABoard[2][2] = 3;
			setABoard[2][3] = 3;
			setABoard[2][4] = 1;
			setABoard[3][1] = 2;
			setABoard[3][2] = 2;
			setABoard[3][3] = 2;
			setABoard[3][4] = 1;

			goal = 3;
			xPos = 1;
			yPos = 2;
			break;
		case '4':
			setABoard[2][2] = 1;
			setABoard[2][2] = 2;
			setABoard[2][4] = 5;
			setABoard[3][2] = 3;
			setABoard[3][3] = 4;
			setABoard[3][4] = 3;
			setABoard[4][2] = 1;
			setABoard[4][3] = 2;

			goal = 3;
			xPos = 2;
			yPos = 4;
			break;
		case '5':
			setBBoard[1][1] = 1;
			setBBoard[1][2] = 1;
			setBBoard[2][3] = 2;
			setBBoard[2][4] = 1;
			setBBoard[3][3] = 3;
			setBBoard[3][4] = 2;
			setBBoard[4][1] = 1;
			setBBoard[4][3] = 1;
			setBBoard[4][4] = 1;
			setBBoard[4][5] = 3;
			setBBoard[5][1] = 1;
			setBBoard[5][5] = 5;

			goal = 2;
			xPos = 5;
			yPos = 5;
			break;
		case '6':
			setBBoard[1][3] = 1;
			setBBoard[1][4] = 1;
			setBBoard[1][5] = 1;
			setBBoard[2][3] = 1;
			setBBoard[3][1] = 3;
			setBBoard[3][2] = 2;
			setBBoard[3][3] = 4;
			setBBoard[3][4] = 4;
			setBBoard[3][5] = 5;
			setBBoard[4][1] = 1;
			setBBoard[5][1] = 1;
			setBBoard[5][5] = 1;

			goal = 3;
			xPos = 3;
			yPos = 5;
			break;
		case '7':
			setBBoard[1][1] = 1;
			setBBoard[1][4] = 1;
			setBBoard[1][5] = 1;
			setBBoard[2][2] = 3;
			setBBoard[2][3] = 2;
			setBBoard[3][1] = 5;
			setBBoard[3][2] = 3;
			setBBoard[3][3] = 2;
			setBBoard[4][2] = 3;
			setBBoard[4][3] = 2;
			setBBoard[4][5] = 1;
			setBBoard[5][1] = 1;
			setBBoard[5][4] = 1;
			setBBoard[5][5] = 1;

			goal = 3;
			xPos = 3;
			yPos = 1;
			break;
		case '8':
			setBBoard[1][1] = 1;
			setBBoard[1][2] = 1;
			setBBoard[2][1] = 1;
			setBBoard[2][2] = 1;
			setBBoard[2][3] = 2;
			setBBoard[2][4] = 2;
			setBBoard[2][5] = 5;
			setBBoard[3][4] = 1;
			setBBoard[3][5] = 1;
			setBBoard[5][2] = 3;
			setBBoard[5][4] = 3;

			goal = 2;
			xPos = 2;
			yPos = 5;
			break;
		case '9':
			setBBoard[1][3] = 4;
			setBBoard[3][1] = 1;
			setBBoard[3][3] = 1;
			setBBoard[3][5] = 1;
			setBBoard[4][1] = 1;
			setBBoard[4][5] = 1;
			setBBoard[4][2] = 2;
			setBBoard[4][3] = 5;
			setBBoard[4][4] = 3;
			setBBoard[5][1] = 1;
			setBBoard[5][5] = 1;

			goal = 2;
			xPos = 4;
			yPos = 3;
			break;
	}
	
}

void check_win(char level){
	int i, j;
	int flag = 0;

	// counts the number of instances of 4 within the game board
	if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
		for(i=0; i<7; i++){
			for(j=0; j<6; j++){
				if(setABoard[i][j] == 4)
					flag++;
			}
		}
	}
	else{
		for(i=0; i<7; i++){
			for(j=0; j<7; j++){
				if(setBBoard[i][j] == 4)
					flag++;
			}
		}
	}

	// checks if number of instances of 4 in game board is equal to the initially set goal
	if(flag == goal){
		erase(1,1,400,220);
		write_text("LEVEL COMPLETE!", 95, 50, GREEN, 0);
		write_text("press B to go", 100,60,GREEN, 0);
		write_text("back to main menu", 85, 70, GREEN, 0);
	}
	else{
		// updates number of moves if player has not achieved goal yet
		erase(3,110,30,30);
		char str[15];
		sprintf(str, "%d", moves);
		write_text(str, 3, 110, PINK, 0);
		moves++;
	}
}

void draw_board(char level){

	print_gamemenu();
	int row, col, i, j,temp, temp2, color;

	if(level == '0' || level == '1' || level == '2' || level == '3' || level == '4'){
		temp = 150;
		temp2 = 35;
		for(i=0; i<7; i++){
			temp = 150;
			for(int j=0; j<6; j++){
				if(setABoard[i][j] == 1){
					// draw wall BROWN
					color = BROWN;
				}
				else if(setABoard[i][j] == 2){
					// draw box PINK
					color = PINK;
				}
				else if(setABoard[i][j] == 4){
					// draw finished box PURPLE
					color = PURPLE;
				}
				else if(setABoard[i][j] == 5){
					// draw character GREEN
					color = GREEN;
				}
				else if(setABoard[i][j] == 0){
					// draw space BLACK
					color = BLACK;
				}
				else if(setABoard[i][j] == 3){
					// draw goal mark BLUE
					color = BLUE;
				}
				
				box2(temp, temp2, color);
				box2(temp, temp2+1, color);
				box2(temp, temp2+2, color);
				box2(temp, temp2+3, color);
				box2(temp, temp2+4, color);
				box2(temp, temp2+5, color);
				box2(temp, temp2+6, color);
				box2(temp, temp2+7, color);
				box2(temp, temp2+8, color);
				box2(temp, temp2+9, color);
				box2(temp, temp2+10, color);
				box2(temp, temp2+11, color);
				box2(temp, temp2+12, color);
				box2(temp, temp2+13, color);
				box2(temp, temp2+14, color);
				
				temp+=16;
			}
			temp2+=16;
		}
		
	} else{
		temp = 150;
		temp2 = 35;
		for(i=0; i<7; i++){
			temp = 150;
			for(int j=0; j<7; j++){
				if(setBBoard[i][j] == 1){
					// draw wall BROWN
					color = BROWN;
				}
				else if(setBBoard[i][j] == 2){
					// draw box PINK
					color = PINK;
				}
				else if(setBBoard[i][j] == 4){
					// draw finished box PURPLE
					color = PURPLE;
				}
				else if(setBBoard[i][j] == 5){
					// draw character GREEN
					color = GREEN;
				}
				else if(setBBoard[i][j] == 0){
					// draw space BLACK
					color = BLACK;
				}
				else if(setBBoard[i][j] == 3){
					// draw goal mark BLUE
					color = BLUE;
				}
				
				box2(temp, temp2, color);
				box2(temp, temp2+1, color);
				box2(temp, temp2+2, color);
				box2(temp, temp2+3, color);
				box2(temp, temp2+4, color);
				box2(temp, temp2+5, color);
				box2(temp, temp2+6, color);
				box2(temp, temp2+7, color);
				box2(temp, temp2+8, color);
				box2(temp, temp2+9, color);
				box2(temp, temp2+10, color);
				box2(temp, temp2+11, color);
				box2(temp, temp2+12, color);
				box2(temp, temp2+13, color);
				box2(temp, temp2+14, color);
				
				temp+=16;
			}
			temp2+=16;
		}
	}
}

void box2(int x, int y, int color){
	int i;
	for(i=0; i<15; i++)write_pixel(i+x, y, color);
}

void print_gamemenu(){
	write_text("W - Move UP", 3, 35, WHITE, 0);
	write_text("S - Move DOWN", 3, 45, WHITE, 0);
	write_text("A - Move LEFT", 3, 55, WHITE, 0);
	write_text("D - Move RIGHT", 3, 65, WHITE, 0);
	write_text("B - Back to Menu", 3, 75, WHITE, 0);
	write_text("R - Reset", 3, 85, WHITE, 0);
	write_text("Moves: ", 3, 95, PINK, 0);
}

void print_header(){

	write_text("PUSH BOX!",120,50,WHITE,1); //title

	//menu options
	write_text("P - Play",40,160,WHITE,0); 
	write_text("E - Exit",200,160,WHITE,0);
}

void print_levels(){
	write_text("Choose Level", 100, 20, PURPLE, 2);

	write_text("0", 80, 40, WHITE, 1);
	write_text("1", 80, 70, WHITE, 1);
	write_text("2", 80, 100, WHITE, 1);
	write_text("3", 80, 130, WHITE, 1);
	write_text("4", 80, 160, WHITE, 1);
	
	write_text("5", 220, 40, WHITE, 1);
	write_text("6", 220, 70, WHITE, 1);
	write_text("7", 220, 100, WHITE, 1);
	write_text("8", 220, 130, WHITE, 1);
	write_text("9", 220, 160, WHITE, 1);

}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle (from lightsout code)
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}
