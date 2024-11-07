// Cursor.cpp
#include "cursor.hpp"

Cursor::Cursor() : x(0), y(0) {}

void Cursor::moveLeft() {
    if (x > 0) x--;
}

void Cursor::moveRight(int maxRight) {
    if (x < maxRight) x++;
}

void Cursor::moveUp() {
    if (y > 0) y--;
}

void Cursor::moveDown(int maxDown) {
    if (y < maxDown) y++;
}

int Cursor::getX() const { return x; }
int Cursor::getY() const { return y; }
void Cursor::setX(int xPos) { x = xPos; }
void Cursor::setY(int yPos) { y = yPos; }
