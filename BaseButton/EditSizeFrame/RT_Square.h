#ifndef RT_SQUARE_H
#define RT_SQUARE_H

#include "BaseButton/EditSizeFrame/Square.h"

class RT_Square : public Square
{
    Q_OBJECT
public:
    explicit RT_Square(BaseButton* obj, const QCursor& cursorPix);

    void mouseMoveEvent(QMouseEvent *e);
};

#endif // RT_SQUARE_H
