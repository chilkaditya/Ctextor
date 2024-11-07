// Cursor.h
#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
    Cursor();
    void moveLeft();
    void moveRight(int maxRight);
    void moveUp();
    void moveDown(int maxDown);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

private:
    int x;
    int y;
};

#endif // CURSOR_H