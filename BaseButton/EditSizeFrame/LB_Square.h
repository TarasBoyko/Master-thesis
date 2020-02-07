#ifndef LB_SQUARE_H
#define LB_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class LB_Square : public Square
{
    Q_OBJECT
public:
    explicit LB_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // LB_SQUARE_H
