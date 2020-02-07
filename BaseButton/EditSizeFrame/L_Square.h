#ifndef L_SQUARE_H
#define L_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class L_Square : public Square
{
    Q_OBJECT
public:
    explicit L_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // L_SQUARE_H
