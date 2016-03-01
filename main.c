#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define ROWS 10
#define COLS 10


/***************************************************
* The folowing function was taken from this stack overflow post
* http://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
***************************************************/

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
/**********************************************
* End function
**********************************************/


void printMap(char map[][COLS], int x, int y){
	int i, j;
	
	system("clear");
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			if(i == y && j == x)
				printf("x");
			else
				printf("%c",map[i][j]);
		}
		puts("");
	}
}

int main(){
	int cont = 1, i, j, x = COLS / 2, y = ROWS / 2;
	char map[ROWS][COLS];
	char input;
	
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			map[i][j] = '.';
		}
	}

	while(cont){
		printMap(map, x, y);
		input = getch();
		if(input == 'w')
			y--;
		else if(input == 's')
			y++;
		else if(input == 'a')
			x--;
		else if(input == 'd')
			x++;
		else if(input == 'q')
			cont = 0;
	}
}
