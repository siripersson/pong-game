#include "paddle.h"
#include "keyboard.h"

#include <string>

const int Paddle::HEIGHT = 60;
const int Paddle::WIDTH = 10;

void Paddle::updatePaddlePosition(int new_y) {
    y += new_y;
}
