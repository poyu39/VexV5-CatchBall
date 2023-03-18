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

        if (ball_color < 0) {
            ball_color = 0;
        } else if (ball_color > 2) {
            ball_color = 2;
        }

        Brain.Screen.render(true);
        wait(screen_ticks, msec);
    }
}

void health_bar() {
    char health_bar[health + 1];
    for (int i = 0; i < health; i++) {
        health_bar[i] = 'I';
    }
    health_bar[health] = '\0';
    Brain.Screen.printAt(10, 30, "[health: %s]", &health_bar);
}

void score_bar() {
    Brain.Screen.printAt(10, 10, "[score: %d]", score);
}

int screen_update() {
    while (true) {
        Brain.Screen.clearScreen();

        health_bar();
        score_bar();

        Brain.Screen.render(true);
        wait(screen_ticks, msec);
    }
    return 0;
}

int basket() {
    int basket_x = 240;
    int basket_y = 200;
    while (health > 0) {
        if (Controller1.ButtonRight.pressing()) { // 當按下右鍵時
            basket_x += 10; // 籃子的x位置增加
            wait(200, msec); 
        } else if (Controller1.ButtonLeft.pressing()) { // 當按下左鍵時
            basket_x -= 10; // 籃子的x位置減少
            wait(200, msec);
        }

        if (basket_x < 20) {
            basket_x = 20;
        } else if (basket_x > 440) {
            basket_x = 440;
        }
        Brain.Screen.drawRectangle(basket_x, basket_y, 40, 20, color::white);
    }
    return 0;
}

int ball_full() {
    int ball_x = rand() % 400 + 40; // 設定球的x隨機初始位置
    int ball_y = 80;              // 設定球的y初始位置
    float t = 0;                 // 設定時間
    while (health > 0) {        // 當生命值大於0時
        ball_y = int(ball_y + 0.5 * 9.8 * t * t); // 計算球的y位置，變化公式為y = 0.5 * g * t^2的重力加速度
        switch (ball_color) { // 畫出球位置與顏色
            case 0:
                Brain.Screen.drawCircle(ball_x, ball_y, 10, color::red);
                break;
            case 1:
                Brain.Screen.drawCircle(ball_x, ball_y, 10, color::green);
                break;
            case 2:
                Brain.Screen.drawCircle(ball_x, ball_y, 10, color::blue);
                break;
            default:
                break;
        }
    }
    return 0;
}

int main() {
    select();
    task s = task(screen_update);
    task b = task(basket);
}