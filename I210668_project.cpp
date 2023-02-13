//============================================================================
// Name        : .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <ctime>
#include <fstream>
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

//**FUNCTIONS**
void SetCanvasSize(int, int);
void drawCar();
void drawOtherCars();
void moveCar();
void GameDisplay();
void NonPrintableKeys(int, int, int);
void PrintableKeys(unsigned char, int, int);
void Timer(int);
void MousePressedAndMoved(int, int);
void MouseMoved(int, int);
void MouseClicked(int, int, int, int);
void MainMenu();
void ColorSelect();
void MAP1();
void People();
void WIN();
void GameTime(int);
void Obstacles();
void LOSE();

//**FUNCTIONS**

//GLOBAL VARIABLES:
string seconds, minutes;
int sec = 0, mmin = 3;
int xI = 20, yI = 20, REDorYELLOW = 0, testx, testy, carmovement = 5, speedFPS = 200, PLAYER_SCORE = 0, pluscars = 0, passengers_dropped = 0;
const int rect_count = 21, carsize = 20, num_peeps = 3, peeps_radius = 10, numcars = 7, numobstacles = 10;
bool flag[numcars], select_color = true, flag_map = false, pickup[num_peeps], carspace = false, GRID = false, DROP[num_peeps], vertical[numcars], END = false, HIGH = true; 

bool fff[num_peeps], doingfalse = true, drawobstacles = true, flag_cars = true;;

/** 
** 
** All coordinates, width and lengths of Path ** ** **/
int rect[rect_count][4] = {{120, 70, 200, 50}, {620, 0, 50, 370}, {120, 220, 150, 100}, {370, 170, 50, 150}, {270, 420, 200, 50}, {120, 570, 200, 50}, 
							{120, 570, 50, 300}, {420, 570, 100, 50}, {620, 320, 100, 50}, {870, 320, 50, 150}, {620, 480, 150, 50}, {620, 480, 50, 100},
							  {770, 120, 150, 100}, {370, 170, 150, 50}, {620, 670, 400, 50}, {270, 720, 250, 200}, {0, 420, 150, 50}, {520, 320, 150, 50}, 
								{870, 320, 100, 50}, {0, 570, 150, 100}};

int peeps[num_peeps][6];
int peepsxy[10][2] = {{220, 160}, {920, 760}, {950, 60}, {820, 260}, {945, 410}, {470, 660}, {895, 510}, {145, 910}, {470, 60}, {145, 360}};
int peeps_pick[num_peeps][2], peeps_pick2[num_peeps][2], peeps_pick3[num_peeps][2];
int dropxy[11][2] = {{430, 220}, {190, 620}, {40, 470}, {670, 530}, {670, 720}, {220, 20}, {220, 320}, {620, 370}, {720, 20}, {870, 220}, {70, 670}};
int dropoff[num_peeps][6];

int x[numcars] = {500, 770, 320, 670, 920, 320, 190}, y[numcars] = {420, 720, 470, 100, 420, 90, 320}, w = 20; /* w = width of other cars */

int obstacxy[15][2] = {{270, 220}, {570, 170}, {70, 770}, {170, 770}, {620, 870}, {220, 420}, {520, 720}, {570, 520}, 
						{770, 320}, {670, 120}, {920, 170}, {820, 770}, {970, 470}, {20, 370}, {270, 520}};
int obstac[numobstacles][2];

int maxscore[10] = {};

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	

	for (int i = 0; i < num_peeps && doingfalse == true; i++){ //Setting all values to false as default
		pickup[i] = false;
		DROP[i] = false;
		fff[i] = false;
	}
	doingfalse = false;

	srand(time(NULL));

	int width = 1140, height = 940; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Taimur Aamir"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.	


	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters

	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(1000.0, GameTime, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	
	
	return 1;
}

void File(ofstream &highscore){
	

	
}

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void drawCar() {
/* BORDER RESTRICTIONs*/ 
	if (xI < 20){ //Left Border
		xI += carmovement;
	}
	if (xI > 1000){ //Right Border
		xI -= carmovement;
	} 
	if (yI < 20){ //Lower Border
		yI += carmovement;
	}
	if (yI > 900){ //Upper Border
		yI -= carmovement;
	}


	/*
	*
	*Setting Color of car
	*/
	if (REDorYELLOW == 1){ //IF COLOR RED
		DrawSquare(xI, yI, carsize, colors[RED]);
		DrawSquare(xI + 2, yI + 2, carsize - 4, colors[MAROON]);
	}
	else if (REDorYELLOW == 2){ //IF COLOR YELLOW
		DrawSquare(xI, yI, carsize, colors[ORANGE]);
		DrawSquare(xI + 2, yI + 2, carsize - 4, colors[GOLD]);
		carmovement = 10;
	}
	
	glutPostRedisplay();
}

void drawOtherCars(){
	if (passengers_dropped % 2 == 0 && flag_cars && pluscars < numcars){
		pluscars++;
		speedFPS /= 2;
		flag_cars = false;
	}
	if (passengers_dropped % 2 != 0)
		flag_cars = true;

	for (int i = 0; i < pluscars; i++){
		DrawSquare(x[i], y[i], w, colors[AQUA]);
		DrawSquare(x[i] + 2, y[i] + 2, w - 4, colors[DARK_BLUE]);
	}
	for (int i = 0; i < pluscars; i++){
		if (xI + (carsize - carmovement) >= x[i] && xI < (x[i] + w) && yI + (carsize - carmovement) >= y[i] && yI + carmovement <= (y[i] + w)){
			if (REDorYELLOW == 1){
				PLAYER_SCORE -= 3;
			}
			if (REDorYELLOW == 2){
				PLAYER_SCORE -= 2;
			}


			if (yI - (carsize - carmovement) < y[i] && !vertical[i]){
					yI -= 20;
			}
			
			if (yI + (carsize - carmovement) > y[i] && !vertical[i]){
					yI += 20;
			}
			
			if (xI + (carsize - carmovement) > x[i] && vertical[i]){
					xI += 20;
			}
			
			if (xI - (carsize - carmovement) < x[i] && vertical[i]){
					xI -= 20;
			}
		}
	}

	glutPostRedisplay();
}

void moveCar() {
	vertical[0] = false;
	vertical[1] = true;
	vertical[2] = true;
	vertical[3] = false;
	vertical[4] = true;
	vertical[5] = false;
	vertical[6] = true;
	for(int i = 0; i < pluscars; i++){
		if (!vertical[i]){
			if (x[i] > 20 && flag[i]) {
				x[i] -= 10;
				if((x[i] <= 470 && y[i] == 420) || (x[i] <= 670 && y[i] == 100) || (x[i] <= 320 && y[i] == 90))	
					flag[i] = false;

			}
			else if (x[i] < 1020 && !flag[i]) {
				x[i] += 10;
				if ((x[i] >= 850 && y[i] == 420) || (x[i] >= 1000 && y[i] == 100) || (x[i] >= 600 && y[i] == 90))
					flag[i] = true;
			}
		}

		else if (vertical[i]){
			if (y[i] > 20 && flag[i]) {
				y[i] -= 10;
				if((y[i] <= 720 && x[i] == 770) || (y[i] <= 470 && x[i] == 320) || (y[i] <= 420 && x[i] == 920) || (y[i] <= 320 && x[i] == 190))	
					flag[i] = false;

			}
			else if (y[i] < 1020 && !flag[i]) {
				y[i] += 10;
				if ((y[i] >= 900 && x[i] == 770) || (y[i] >= 700 && x[i] == 320) || (y[i] >= 630 && x[i] == 920) || (y[i] >= 550 && x[i] == 190))
					flag[i] = true;
			}
		}
	}
	
}

/*
 * Main Canvas drawing function.
 * */
void GameDisplay()/**/{

	/***
	* MAIN MENU PAGE
	**/
	if (select_color == true && END == false){
		MainMenu(); 
	}


	/***
	* SELECT COLOR PAGE
	**/
	else if (select_color == false && REDorYELLOW == 0 && END == false){
		ColorSelect();
	}


	/***
	* GAME PAGE
	**/
	else if (select_color == false && REDorYELLOW != 0){
		
		MAP1(); //FIRST MAP
		

		//**BORDER**
		DrawRectangle(0, 0, 1141, 20, colors[SLATE_BM]); //BOTTOM BORDER
		DrawRectangle(0, 921, 1141, 20, colors[SLATE_BM]); //TOP BORDER
		DrawRectangle(0, 0, 20, 941, colors[SLATE_BM]); //LEFT BORDER
		DrawRectangle(1021, 0, 20, 941, colors[SLATE_BM]); //RIGHT BORDER
		DrawRectangle(1121, 0, 20, 941, colors[SLATE_BM]); //EXTREME RIGHT BORDER

		if (PLAYER_SCORE >= 100){ //WIN SCREEN
			END = true;
			WIN();
		}
		if (mmin < 0){ //LOSE SCREEN
			END = true;
			LOSE();
		}
		
		

		if (END == false){
			drawCar();
			drawOtherCars();
		
			/*
			**Display Score
			***/
			string score;
			stringstream ss; //String Stream
			ss << PLAYER_SCORE; //Stroing Integer in string stream
			//Extracting the integer as string and storing in string variable: "score"
			ss >> score; 
			DrawString(1050, 600, "Score:", colors[MISTY_ROSE]);
			DrawString(1070, 570, score, colors[SALMON]);
		
			/*
			**Timer of 3min.
			***/
			DrawString(1050, 400, "Time:", colors[MISTY_ROSE]);
			DrawString(1060, 370, minutes, colors[LIGHT_GRAY]);
			DrawString(1072, 370, ":", colors[MISTY_ROSE]);
			if (sec < 10){
				DrawString(1080, 370, "0", colors[LIGHT_GRAY]);
				DrawString(1090, 370, seconds, colors[LIGHT_GRAY]);
			}
			else
				DrawString(1080, 370, seconds, colors[LIGHT_GRAY]);
		}

	}
	glutSwapBuffers(); // do not modify this line..
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		xI -= carmovement;
		/*Restriction for car to avoid black path*/
		for (int i = 0; i < rect_count; i++){
			if (xI < rect[i][0] + rect[i][2] && xI > rect[i][0] && yI + (carsize - carmovement) >= rect[i][1] && yI + carmovement <= rect[i][1] + rect[i][3]){
				xI += carmovement; 
			}
		}

		/*Bound Checking of Obstacles*/
		for (int i = 0; i < numobstacles; i++){
			if (xI < obstac[i][0] + 30 && xI > obstac[i][0] && yI + (carsize - carmovement) >= obstac[i][1] && yI + carmovement <= obstac[i][1] + 30){
				xI += carmovement + 20; 
				if (REDorYELLOW == 1)
					PLAYER_SCORE -= 2;
				else if (REDorYELLOW == 2)
					PLAYER_SCORE -= 4;
			}
		}
	} 
	
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		xI += carmovement;
		/*Restriction for car to avoid black path*/
		for (int i = 0; i < rect_count; i++){
			if (xI + (carsize - carmovement) >= rect[i][0] && xI < rect[i][0] + rect[i][2] && yI + (carsize - carmovement) >= rect[i][1] && yI + carmovement <= rect[i][1] + rect[i][3]){
				xI -= carmovement;
			}
		}

		/*Bound Checking of Obstacles*/
		for (int i = 0; i < numobstacles; i++){
			if (xI + (carsize - carmovement) >= obstac[i][0] && xI < obstac[i][0] + 30 && yI + (carsize - carmovement) >= obstac[i][1] && yI + carmovement <= obstac[i][1] + 30){
				xI -= carmovement + 20;
				if (REDorYELLOW == 1)
					PLAYER_SCORE -= 2;
				else if (REDorYELLOW == 2)
					PLAYER_SCORE -= 4;
			}
		}
	} 
	
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yI += carmovement;
		/*Restriction for car to avoid black path*/
		for (int i = 0; i < rect_count; i++){
			if (yI + (carsize - carmovement) >= rect[i][1] && yI < rect[i][1] + rect[i][3] && xI + (carsize - carmovement) >= rect[i][0] && xI + carmovement <= rect[i][0] + rect[i][2]){
				yI -= carmovement;
			}
		}

		/*Bound Checking of Obstacles*/
		for (int i = 0; i < numobstacles; i++){
			if (yI + (carsize - carmovement) >= obstac[i][1] && yI < obstac[i][1] + 30 && xI + (carsize - carmovement) >= obstac[i][0] && xI + carmovement <= obstac[i][0] + 30){
				yI -= carmovement + 20;
				if (REDorYELLOW == 1)
					PLAYER_SCORE -= 2;
				else if (REDorYELLOW == 2)
					PLAYER_SCORE -= 4;
			}
		}
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yI -= carmovement;
		/*Restriction for car to avoid black path*/
		for (int i = 0; i < rect_count; i++){
			if (yI < rect[i][1] + rect[i][3] && yI > rect[i][1] && xI + (carsize - carmovement) >= rect[i][0] && xI + carmovement <= rect[i][0] + rect[i][2]){
				yI += carmovement;
			}
		}

		/*Bound Checking of Obstacles*/
		for (int i = 0; i < numobstacles; i++){
			if (yI < obstac[i][1] + 30 && yI > obstac[i][1] && xI + (carsize - carmovement) >= obstac[i][0] && xI + carmovement <= obstac[i][0] + 30){			
				yI += carmovement + 20;
				if (REDorYELLOW == 1)
					PLAYER_SCORE -= 2;
				else if (REDorYELLOW == 2)
					PLAYER_SCORE -= 4;
			}
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}


/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //SHOWING COORDINATES OF MAIN TAXI
			{
		cout << xI << " " << yI << endl;
	}

	if (key == '\t' /* Tab key ASCII*/){ //TAB TO TOGGLE GRID
		if (GRID == false)
			GRID = true;
		else
			GRID = false;
	}
	if (key == 'd' || key == 'D'){ //KEY TO DROP PASSENGERS
		for (int i = 0; i < num_peeps && carspace == true; i++){
			if (xI + (carsize - carmovement) >= dropoff[i][0] && xI < dropoff[i][4] && yI >= dropoff[i][1] && yI <= dropoff[i][3]){
				carspace = false;
				PLAYER_SCORE += 10;
				fff[i] = false;
				if (pickup[i] == true)
					pickup[i] = false;
				passengers_dropped++;
				cout << "Pick Up " << i << " is " << pickup[i] << endl;
				cout << "carspace is " << carspace << endl << endl;
			}
		}
	}


	for(int i = 0; i < num_peeps && carspace == false; i++){
		if (key == ' '){ //KEY TO PICKUP PASSENGERS
			if ((xI + (carsize - carmovement) >= (peeps_pick[i][0] - peeps_radius) && xI < (peeps_pick[i][0] + peeps_radius) && yI + (carsize - carmovement) >= (peeps_pick[i][1] - peeps_radius) && yI + carmovement <= (peeps_pick[i][1] + peeps_radius)) || 
				  (xI + (carsize - carmovement) >= (peeps_pick2[i][0] - peeps_radius) && xI < (peeps_pick2[i][0] + peeps_radius) && yI + (carsize - carmovement) >= (peeps_pick2[i][1] - peeps_radius) && yI + carmovement <= (peeps_pick2[i][1] + peeps_radius)) ||
				    (xI + (carsize - carmovement) >= (peeps_pick3[i][0] - peeps_radius) && xI < (peeps_pick3[i][0] + peeps_radius) && yI + (carsize - carmovement) >= (peeps_pick3[i][1] - peeps_radius) && yI + carmovement <= (peeps_pick3[i][1] + peeps_radius))){
				carspace = true;
				if (pickup[i] == false)
					pickup[i] = true;
				cout << "Pick Up " << i << " is " << pickup[i] << endl;
				cout << "carspace is " << carspace << endl << endl;
			}
		}
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	
	moveCar();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(speedFPS, Timer, 0);
}
void GameTime(int m){

	if (select_color == false && REDorYELLOW != 0)
		sec--;
	if (sec <= 0){
		sec = 59;
		mmin--;
	}
	stringstream s, mi;
	s << sec;
	mi << mmin;
	
	s >> seconds;
	mi >> minutes;

	
	glutTimerFunc(1000, GameTime, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << 940 - y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	/** VALUE OF y IS SET WRONG THUS **/
	y = 940 - y;

	/*** ** SELECT COLOR BUTTON CLICKED ** ***/
	if (select_color == true){
		if (button == GLUT_LEFT_BUTTON){ 
			if (x >= 370 && x <= 370 + 190 && y >= 360 && y <= 360 + 60){
				select_color = false;
				cout << "PLAY!!" << endl;
			}
			if (x >= 370 && x <= 370 + 190 && y >= 160 && y <= 160 + 60){
				exit(1);
				cout << "QUIT!!" << endl;
			}
		}
	}

	/*** ** CHOOSING COLOR ** ***/
	else if (select_color == false && REDorYELLOW == 0){
		if (button == GLUT_LEFT_BUTTON){
			if (x >= 210 && x <= 210 + 90 && y >= 460 && y <= 460 + 90){
				REDorYELLOW = 1; //IF COLOR RED
				cout << "RED" << endl;
			}
			else if(x >= 800 && x <= 800 + 90 && y >= 460 && y <= 460 + 90){
				REDorYELLOW = 2; //IF COLOR YELLOW
				cout << "YELLOW" << endl;
			}
			else if(x >= 480 && x <= 480 + 90 && y >= 260 && y <= 260 + 90){
				REDorYELLOW = rand() % 2 + 1; //IF COLOR YELLOW
				cout << "YELLOW" << endl;
			}
		}
	}
	glutPostRedisplay();
}

void MainMenu(){
	glClearColor(0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT);

	int H = -50;
	int W = 0;
	int W1 = 0;
	int H1 = 0;

	/*R*/
	DrawLine(120 + W, 740 + H, 120 + W, 940 + H, 5, colors[WHITE]); //Vertical 
	DrawLine(120 + W, 940 + H, 220 + W, 940 + H, 5, colors[WHITE]); //Horizontal
	DrawLine(220 + W, 940 + H, 220 + W, 840 + H, 5, colors[WHITE]); //Vertical 2
	DrawLine(120 + W, 840 + H, 220 + W, 840 + H, 5, colors[WHITE]); //Horizontal
	DrawLine(170 + W, 840 + H, 220 + W, 740 + H, 5, colors[WHITE]); //Slant

	/*U*/
	DrawLine(250 + W, 740 + H, 250 + W, 840 + H, 5, colors[WHITE]); //Vertical 1
	DrawLine(250 + W, 740 + H, 350 + W, 740 + H, 5, colors[WHITE]); //Horizontal
	DrawLine(350 + W, 740 + H, 350 + W, 840 + H, 5, colors[WHITE]); //Vertical 2

	/*S*/
	DrawLine(370 + W, 740 + H, 470 + W, 740 + H, 5, colors[WHITE]); //Vertical 1
	DrawLine(370 + W, 790 + H, 370 + W, 840 + H, 5, colors[WHITE]); //Horizontal 1
	DrawLine(370 + W, 790 + H, 470 + W, 790 + H, 5, colors[WHITE]); //Vertical 2
	DrawLine(470 + W, 740 + H, 470 + W, 790 + H, 5, colors[WHITE]); //Horizontal 2
	DrawLine(370 + W, 840 + H, 470 + W, 840 + H, 5, colors[WHITE]); //Vertical 3

	/*H*/
	DrawLine(490 + W, 740 + H, 490 + W, 840 + H, 5, colors[WHITE]); //Vertical 1
	DrawLine(490 + W, 790 + H, 590 + W, 790 + H, 5, colors[WHITE]); //Horizontal
	DrawLine(590 + W, 740 + H, 590 + W, 840 + H, 5, colors[WHITE]); //Vertical 2

	
	/*H*/
	DrawLine(300 + W1, 450 + H1, 300 + W1, 650 + H1, 5, colors[WHITE]); //Vertical 1
	DrawLine(300 + W1, 550 + H1, 400 + W1, 550 + H1, 5, colors[WHITE]); //Horizontal
	DrawLine(400 + W1, 450 + H1, 400 + W1, 650 + H1, 5, colors[WHITE]); //Vertical 2

	/*O*/
	DrawLine(420 + W1, 450 + H1, 520 + W1, 450 + H1, 5, colors[WHITE]);
	DrawLine(420 + W1, 450 + H1, 420 + W1, 550 + H1, 5, colors[WHITE]);
	DrawLine(520 + W1, 450 + H1, 520 + W1, 550 + H1, 5, colors[WHITE]);
	DrawLine(420 + W1, 550 + H1, 520 + W1, 550 + H1, 5, colors[WHITE]);

	/*U*/
	DrawLine(540 + W1, 450 + H1, 540 + W1, 550 + H1, 5, colors[WHITE]); //Vertical 1
	DrawLine(540 + W1, 450 + H1, 640 + W1, 450 + H1, 5, colors[WHITE]); //Horizontal
	DrawLine(640 + W1, 450 + H1, 640 + W1, 550 + H1, 5, colors[WHITE]); //Vertical 2

	/*R*/
	DrawLine(660 + W1, 450 + H1, 660 + W1, 550 + H1, 5, colors[WHITE]); //Vertical 
	DrawLine(660 + W1, 550 + H1, 760 + W1, 550 + H1, 5, colors[WHITE]); //Horizontal
	DrawLine(760 + W1, 550 + H1, 760 + W1, 500 + H1, 5, colors[WHITE]); //Vertical 2
	DrawLine(660 + W1, 500 + H1, 760 + W1, 500 + H1, 5, colors[WHITE]); //Horizontal
	DrawLine(710 + W1, 500 + H1, 760 + W1, 450 + H1, 5, colors[WHITE]); //Slant


	DrawRoundRect(360, 350, 210, 80, colors[RED]); //OUTER
	DrawRoundRect(370, 360, 190, 60, colors[WHITE]); //INNER
	DrawString(430, 380, "PLAY", colors[BLACK]); //TEXT


	DrawRoundRect(360, 150, 210, 80, colors[RED]); //OUTER
	DrawRoundRect(370, 160, 190, 60, colors[WHITE]); //INNER
	DrawString(430, 180, "QUIT", colors[BLACK]); //TEXT

}

void ColorSelect(){
	glClearColor(0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT);

	/* ***  BOX FOR CHOOSING RED COLOR  ***  */
	DrawSquare(200, 450, 110, colors[DARK_TURQUOISE]);
	DrawSquare(210, 460, 90, colors[RED]);

	/* ***  BOX FOR CHOOSING YELLOW COLOR  ***  */
	DrawSquare(790, 450, 110, colors[DARK_TURQUOISE]);
	DrawSquare(800, 460, 90, colors[GOLD]);

	DrawSquare(480, 250, 110, colors[CYAN]);
	DrawSquare(490, 260, 90, colors[BLACK]);
}

void MAP1(){
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	

	//**GRID**
	for (int i = 20; i <= 1020 && GRID == true;){
		DrawLine(i, 0, i, 920, 1, colors[DIM_GRAY]);
		DrawLine(0, i, 1040, i, 1, colors[DIM_GRAY]);
		i += 50;
	}

	People(); //FUNCTION FOR ALL PEOPLE / PICKUPS / DROP OFFS
	
	Obstacles(); //FUNCTION FOR ALL OBSTACLES

	for(int i = 0; i < rect_count; i++) //DRAWING ALL PATHS
		DrawRectangle(rect[i][0], rect[i][1], rect[i][2], rect[i][3], colors[SNOW]);
}

/*
*
* Function involving all passenger related things,
* Including pickups, dropoffs, randomization
***/
void People(){
	for (int i = 0; i < num_peeps; i++){
		if (!fff[i]){
			do{ /* ** Randomizing Pickup Locations of Passengers ** */
				int random1 = rand() % 10; 
				peeps_pick[i][0] = peepsxy[random1][0];
				peeps_pick[i][1] = peepsxy[random1][1];
				peeps[i][0] = peeps_pick[i][0] - 10;
				peeps[i][1] = peeps_pick[i][1] - 40;
				peeps[i][2] = peeps_pick[i][0];
				peeps[i][3] = peeps_pick[i][1] - 20;
				peeps[i][4] = peeps_pick[i][0] + 10;
				peeps[i][5] = peeps_pick[i][1] - 40;
			}while ((peeps[i][3] == peeps[i + 1][3] || peeps[i][3] == peeps[i - 1][3]) || 
					  (peeps[i][3] == peeps[i + 2][3] || peeps[i][3] == peeps[i - 2][3]));

			do{ /* ** Randomizing Drop off Locations of Passengers ** */
				int random2 = rand() % 11;
				dropoff[i][0] = dropxy[random2][0];
				dropoff[i][1] = dropxy[random2][1];
				dropoff[i][2] = dropoff[i][0] + 10;
				dropoff[i][3] = dropoff[i][1] + 20;
				dropoff[i][4] = dropoff[i][0] + 20;
				dropoff[i][5] = dropoff[i][1];
			}while ((dropoff[i][3] == dropoff[i + 1][3] || dropoff[i][3] == dropoff[i - 1][3]) || 
					  (dropoff[i][3] == dropoff[i + 2][3] || dropoff[i][3] == dropoff[i - 2][3]));

			peeps_pick2[i][0] = peeps[i][0] - 20;
			peeps_pick2[i][1] = peeps[i][1] + 10;
			peeps_pick3[i][0] = peeps[i][4] + 20;
			peeps_pick3[i][1] = peeps[i][1] + 10;

			fff[i] = true;
		}
	}

	/*
	** Loop Drawing Passengers and Pickup locations
	** When certain requirements are met
	***/
	for (int i = 0; i < num_peeps; i++){
		if (pickup[i] == false){ //Drawing Passengers
			DrawCircle(peeps_pick[i][0], peeps_pick[i][1], peeps_radius, colors[GRAY]); // PICKUP LOCATIONS
			DrawCircle(peeps_pick[i][0], peeps_pick[i][1], peeps_radius - 1, colors[BLACK]); //PICKUP LOCATIONS INNERz
			DrawCircle(peeps_pick2[i][0], peeps_pick2[i][1], peeps_radius, colors[GRAY]); // PICKUP LOCATIONS
			DrawCircle(peeps_pick2[i][0], peeps_pick2[i][1], peeps_radius - 1, colors[BLACK]); //PICKUP LOCATIONS INNERz
			DrawCircle(peeps_pick3[i][0], peeps_pick3[i][1], peeps_radius, colors[GRAY]); // PICKUP LOCATIONS
			DrawCircle(peeps_pick3[i][0], peeps_pick3[i][1], peeps_radius - 1, colors[BLACK]); //PICKUP LOCATIONS INNERz
			DrawTriangle(peeps[i][0], peeps[i][1], peeps[i][2], peeps[i][3], peeps[i][4], peeps[i][5], colors[BLACK]); //PEOPLE
			DrawCircle(peeps[i][2], peeps[i][3] - 4, 4, colors[LAVENDER]);
			DrawLine(peeps[i][2], peeps[i][1] + 7, peeps[i][2], peeps[i][3], 1, colors[LAVENDER]);
			DrawLine(peeps[i][0], peeps[i][1], peeps[i][2], peeps[i][1] + 7, 1, colors[LAVENDER]);
			DrawLine(peeps[i][4], peeps[i][5], peeps[i][2], peeps[i][1] + 7, 1, colors[LAVENDER]);
			DrawLine(peeps[i][0], peeps[i][1] + 10, peeps[i][4], peeps[i][1] + 10, 1, colors[LAVENDER]);
		}
		else if (pickup[i] == true && carspace == true){
			DrawTriangle(dropoff[i][0], dropoff[i][1], dropoff[i][2], dropoff[i][3], dropoff[i][4], dropoff[i][5], colors[OLIVE_DRAB]); //DROPOFF LOCATIONS
			DrawTriangle(dropoff[i][0] + 4, dropoff[i][1] + 2, dropoff[i][2], dropoff[i][3] - 5, dropoff[i][4] - 4, dropoff[i][5] + 2, colors[LIME]); //DROPOFF LOCATIONS
		}
	}

	/*
	** Loop Checking Hitboxes of Passengers
	** If player taxi hits passengers, score is subtracted by 5
	***/
	for (int i = 0; i < num_peeps; i++){
		if (xI + (carsize - carmovement) >= peeps[i][0] && xI < peeps[i][4] && yI >= peeps[i][1] && yI <= peeps[i][3] && pickup[i] == false){
			if (xI - (carsize - carmovement) < peeps[i][0]){
				xI -= 40;
				PLAYER_SCORE -= 5;
			}
			if (xI + (carsize - carmovement) > peeps[i][0]){
				xI += 40;
				PLAYER_SCORE -= 5;
			}
		}
	}
}

/*
*
* Function involving all obstacle 
***/
void Obstacles(){
	for (int i = 0; i < numobstacles && drawobstacles == true; i++){
		bool condition = false;
		do{
			int random = rand() % 15;
			obstac[i][0] = obstacxy[random][0];
			obstac[i][1] = obstacxy[random][1];
		}while(condition);
	}
	drawobstacles = false;
	
	for (int i = 0; i < numobstacles; i++){
		DrawSquare(obstac[i][0], obstac[i][1], 30, colors[BLACK]);
		DrawRectangle(obstac[i][0], obstac[i][1], 3, 30, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0] + 7, obstac[i][1], 3, 30, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0] + 14, obstac[i][1], 3, 30, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0] + 21, obstac[i][1], 3, 30, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0] + 28, obstac[i][1], 3, 30, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0], obstac[i][1] + 27, 30, 3, colors[LIGHT_GOLDEN_ROD_YELLOW]);
		DrawRectangle(obstac[i][0], obstac[i][1], 30, 3, colors[LIGHT_GOLDEN_ROD_YELLOW]);
	}
}

void WIN(){
	glClearColor(0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT);

	DrawString(450, 450, "YOU WIN", colors[ROYAL_BLUE]);
}

void LOSE(){
	glClearColor(0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT);

	DrawString(450, 450, "YOU LOSE", colors[ROYAL_BLUE]);
}
#endif /* RushHour_CPP_ */
