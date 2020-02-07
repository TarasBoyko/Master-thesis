#ifndef RB_SQUARE_H
#define RB_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class RB_Square : public Square
{
    Q_OBJECT
public:
    explicit RB_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // RB_SQUARE_H
