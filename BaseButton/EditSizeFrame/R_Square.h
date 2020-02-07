#ifndef R_SQUARE_H
#define R_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class R_Square : public Square
{
    Q_OBJECT
public:
    explicit R_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // R_SQUARE_H
