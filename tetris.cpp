//Andy Simphaly

#include <cstdlib>
#include <ncurses.h>

bool game_over;
int width = 12, height = 22;
int x = 1;
int y = 5;
int score;
//Enum for Direction
enum edir {STOP=0, LEFT, RIGHT, DOWN};
edir dir;
//Array of bools to see if the position is taken
bool filled [10][20] = {false};

bool match = false;

//Setup function
void setup() {
    //screen setting
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    game_over = false;

    return;
}

//Draw board function
void draw() {
    //Clear
    clear();

    //Print Borders, fruit, head, and tail
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if (i == 0 || i == 21) {
                mvprintw(i,j,"-");
            } else if (j == 0 || j == 11) {
                mvprintw(i,j,"|");
            } else if (i == x && j == y) {
                mvprintw(i,j,"X");
            } else if (filled[i][j] == true) {
                mvprintw(i,j,"X");
            }
        }
    }
    //Print score
    mvprintw(23,0,"Score %d",score);
    refresh();

    return;
}

//User input function
void input() {
    //Keypad and speed of the game
    keypad(stdscr, TRUE);
    halfdelay(1);

    //Input key
    int key = getch();

    //Switch case to change to the intended direction
    switch(key) {
        case KEY_LEFT:
            //Check that the snake does not go into itself
            if (dir != RIGHT) {
                dir = LEFT;
            }
            break;
        case KEY_RIGHT:
            //Check that the snake does not go into itself
            if (dir != LEFT) {
                dir = RIGHT;
            }
            break;
        //Quit key (Q)
        case 113:
            game_over = true;
            break;
    }
}

//Logic function
void logic() {
    //Changing the direction of the snake
    switch(dir) {
        case LEFT:
            if(y != 1 && filled[x][y-1] != true) {
                y--;
            }
            dir = DOWN;
            break;
        case RIGHT:
            if(y != width-2 && filled[x][y+1] != true) {
                y++;
            }
            dir = DOWN;
            break;
        case DOWN:
            x++;
            break;
        default:
            break;
    }

    //Check if the player has hit the bottom or a shape
    if(x == height-2 || filled[x+1][y] == true) {
        filled[x][y] = true;
        x = 1;
        y = 5;
    }

    //Check if their is a row match
    for(int i = 0; i < height; i++) {
        match = true;
        for(int j = 1; j < width-1; j++) {
            if(filled[i][j] == false) {
                match = false;
            }
        }
        if (match == true) {
            for(int j = 0; j < width; j++) {
                filled[i][j] = false;
            }
            for(int k = 0; k < i; k++) {
                for(int l = 0; l < width; l++) {
                    filled[i-k+1][l] = filled[i-k][l];
                }
            }
            score++;
        }
    }

    for(int i = 0; i < width; i ++) {
        if (filled[2][i]) {
            game_over = true;
        }
    }

    return;
}

int main() {
    //setup
    setup();
    
    while(!game_over) {
        draw();
        input();
        logic();
    }
    
   getch();
   endwin();

    return 0;
}