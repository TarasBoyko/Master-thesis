#ifndef LT_SQUARE_H
#define LT_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class LT_Square : public Square
{
public:
    explicit LT_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // LT_SQUARE_H
