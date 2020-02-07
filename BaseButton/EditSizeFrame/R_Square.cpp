#include "BaseButton/EditSizeFrame/R_Square.h"
#include "GreenButton.h"

R_Square::R_Square(BaseButton *obj, const QCursor &cursorPix) :
    Square(obj, cursorPix)
{
    move(_parent->width() - kEditSquareSize, _parent->height()/2 - kEditSquareSize/2);
}

void R_Square::mouseMoveEvent(QMouseEvent *e)
{
    _parent->setGeometry(
                _parent->x(),
                _parent->y(),
                _parent->width() + e->x(),
                _parent->height());
    emit Moved();
}
