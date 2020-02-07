#ifndef B_SQUARE_H
#define B_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class B_Square : public Square
{
    Q_OBJECT
public:
    explicit B_Square(BaseButton* obj, const QCursor& cursorPix_);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // B_SQUARE_H
