/*
  CatchBall
  A simple catch falling ball game on V5 brain
  Author: poyu39
*/ 

#include "vex.h"

using namespace vex;

brain Brain;

controller Controller1 = controller(primary);

// global variables

enum ball_color {red, green, blue};

ball_color bc = ball_color::green;
color bc_s = color::green;

int screen_ticks = 10;
int health = 5;
int score = 0;
int lv = 1;
int basket_position[2] = {240, 200};
int ball_position[2] = {240, 50};

void pre_game();
void ball_select();
int screen_update();
void health_bar();
void score_bar();
void basket();
void ball_fall();

int main() {
  pre_game();
  task s = task(screen_update);
  ball_fall();
  s.stop();
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(200, 80, "Game Over");
  Brain.Screen.printAt(200, 100, "score: %d", score);
  Brain.Screen.render(true);
}

void pre_game() {
  ball_select();
  switch (bc) {
  case ball_color::red:
    bc_s = color::red;
    break;
  case ball_color::green:
    bc_s = color::green;
    break;
  case ball_color::blue:
    bc_s = color::blue;
    break;
  default:
    break;
  }
  Brain.Screen.clearScreen();
}

void ball_select() {
  while(!Controller1.ButtonA.pressing()) {
    Brain.Screen.clearScreen();
    Brain.Screen.drawCircle(180, 80, 20, color::red);
    Brain.Screen.drawCircle(240, 80, 20, color::green);
    Brain.Screen.drawCircle(300, 80, 20, color::blue);
    Brain.Screen.printAt(120, 150, "Use < > to select ball color");
    Brain.Screen.printAt(170, 170, "Press A to start");
    if (Controller1.ButtonLeft.pressing()) {
      if (bc == ball_color::red) {
        bc = ball_color::red;
      } else {
        bc = ball_color(bc - 1);
      }
      wait(200, msec);
    } else if (Controller1.ButtonRight.pressing()) {
      if (bc == ball_color::blue) {
        bc = ball_color::blue;
      } else {
        bc = ball_color(bc + 1);
      }
      wait(200, msec);     
    }
    switch (bc) {
      case ball_color::red:
        Brain.Screen.drawCircle(180, 80, 30, color::red);
        break;
      case ball_color::green:
        Brain.Screen.drawCircle(240, 80, 30, color::green);
        break;
      case ball_color::blue:
        Brain.Screen.drawCircle(300, 80, 30, color::blue);
        break;
      default:
        break;
    }
    wait(screen_ticks, msec);
    Brain.Screen.render(true);
  }
}

int screen_update() {
  while (health > 0) {
    Brain.Screen.clearScreen();
    health_bar();
    score_bar();
    basket();
    Brain.Screen.render(true);
    wait(screen_ticks, msec);
  }
  return 0;
}

void health_bar() {
  char health_bar[health + 1];
  for (int i = 0; i < health; i++) {
    health_bar[i] = 'I';
  }
  health_bar[health] = '\0';
  Brain.Screen.printAt(320, 20, "[Health: %s]", &health_bar);
}

void score_bar() {
  Brain.Screen.printAt(320, 40, "[Score: %d]", score);
}

void ball_fall() {
  float t = 0;
  while(health > 0) {
    ball_position[1] = ball_position[1] + 0.5 * 9.8 * t * t;
    Brain.Screen.drawCircle(ball_position[0], ball_position[1], 10, bc_s);
    if (ball_position[1] > 200) {
      if (ball_position[0] > basket_position[0] - 10 && ball_position[0] < basket_position[0] + 40) {
        score = score + 1;
      } else {
        health = health - 1;
      }
      t = 0;
      ball_position[0] = rand() % 480;
      ball_position[1] = 50;
    }
    t = t + 0.005;
    wait(5, msec);
  }
}

void basket() {
  if (health > 0) {
    if (Controller1.ButtonLeft.pressing()) {
      basket_position[0] = basket_position[0] - 10;
    } else if (Controller1.ButtonRight.pressing()) {
      basket_position[0] = basket_position[0] + 10;
    }
    if (basket_position[0] < 0) {
      basket_position[0] = 0;
    } else if (basket_position[0] > 480) {
      basket_position[0] = 480;
    }
    Brain.Screen.drawRectangle(basket_position[0], basket_position[1], 30, 10, color::white);
  }
}
