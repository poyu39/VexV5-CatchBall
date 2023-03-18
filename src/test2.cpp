#include "vex.h"

using namespace vex;

brain Brain;

controller Controller1 = controller(primary);

// global variable
// 0 = red, 1 = green, 2 = blue
int ball_color = 1;
int screen_ticks = 10;

int health = 5;
int score = 0;

void select() {
    while (Controller1.ButtonA.pressing() == false) {
        Brain.Screen.clearScreen();

        Brain.Screen.drawCircle(180, 80, 20, color::red);
        Brain.Screen.drawCircle(240, 80, 20, color::green);
        Brain.Screen.drawCircle(300, 80, 20, color::blue);
        Brain.Screen.printAt(120, 150, "Use < > to select ball color");
        Brain.Screen.printAt(170, 170, "Press A to start");

        switch (ball_color) {
            case 0:
                Brain.Screen.drawCircle(180, 80, 30, color::red);
                break;
            case 1:
                Brain.Screen.drawCircle(240, 80, 30, color::green);
                break;
            case 2:
                Brain.Screen.drawCircle(300, 80, 30, color::blue);
                break;
            default:
                break;
        }

        if (Controller1.ButtonLeft.pressing()) {
            ball_color--;
            wait(200, msec);
        } else if (Controller1.ButtonRight.pressing()) {
            ball_color++;
            wait(200, msec);  
        }
    }
}

int main() {
    
}


