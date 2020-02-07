#include <QMouseEvent>

#include "BaseButton/EditSizeFrame/B_Square.h"
#include "BaseButton/BaseButton.h"


B_Square::B_Square(BaseButton* obj, const QCursor& cursorPix_) :
    Square(obj, cursorPix_)
{
    move(_parent->width()/2 - kEditSquareSize/2, _parent->height() - kEditSquareSize);
}

void B_Square::mouseMoveEvent(QMouseEvent *e)
{
    _parent->setGeometry(
                _parent->x(),
                _parent->y(),
                _parent->width(),
                _parent->height() + e->y()
                );
    emit Moved();
}
