// Cursor.h
#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
    Cursor();
    void moveLeft();
    void moveRight(unsigned int maxRight);
    void moveUp();
    void moveDown(unsigned int maxDown);
    unsigned int getX() const;
    unsigned int getY() const;
    void setX(unsigned int x);
    void setY(unsigned int y);

private:
    unsigned int x;
    unsigned int y;
};

#endif // CURSOR_H