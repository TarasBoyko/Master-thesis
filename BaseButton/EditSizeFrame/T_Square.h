#ifndef T_SQUARE_H
#define T_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class T_Square : public Square
{
    Q_OBJECT
public:
    explicit T_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // T_SQUARE_H
