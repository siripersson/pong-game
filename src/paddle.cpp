#include "paddle.h"
#include "keyboard.h"
#include <string>

const int Paddle::HEIGHT = 60;
const int Paddle::WIDTH = 10;

void Paddle::updatePaddlePosition(int new_y) {
    y += new_y;
}

// Försök till att börja flytta över update funktionen till paddle objektet
/* void Paddle::movePaddle(int gamepadDirection,uint32_t buttonUp, uint32_t buttonDown, Keyboard* keyboard) {

}
 */
