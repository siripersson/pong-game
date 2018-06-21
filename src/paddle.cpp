#include "paddle.h"

const int Paddle::HEIGHT = 60;
const int Paddle::WIDTH = 10;

void Paddle::updatePaddleDirection(int new_y) {
    y += new_y;
}
