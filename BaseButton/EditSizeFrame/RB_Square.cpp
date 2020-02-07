#include "BaseButton/EditSizeFrame/RB_Square.h"
#include "GreenButton.h"

RB_Square::RB_Square(BaseButton *obj, const QCursor& cursorPix) :
    Square(obj, cursorPix)
{
    move(_parent->width() - kEditSquareSize, _parent->height() - kEditSquareSize);
}

void RB_Square::mouseMoveEvent(QMouseEvent *e)
{
    _parent->setGeometry(
                _parent->x(),
                _parent->y(),
                _parent->width()  + e->x(),
                _parent->height() + e->y()
                );
    emit Moved();
}
