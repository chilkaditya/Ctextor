// Cursor.cpp
#include "cursor.hpp"

Cursor::Cursor() : x(0), y(0) {}

void Cursor::moveLeft() {
    if (x > 0) x--;
}

void Cursor::moveRight(unsigned int maxRight) {
    if (x < maxRight) x++;
}

void Cursor::moveUp() {
    if (y > 0) y--;
}

void Cursor::moveDown(unsigned int maxDown) {
    if (y < maxDown) y++;
}

unsigned int Cursor::getX() const { return x; }
unsigned int Cursor::getY() const { return y; }
void Cursor::setX(unsigned int xPos) { x = xPos; }
void Cursor::setY(unsigned int yPos) { y = yPos; }
