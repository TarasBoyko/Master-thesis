#include "BaseButton/EditSizeFrame/LB_Square.h"
#include "GreenButton.h"

LB_Square::LB_Square(BaseButton* obj, const QCursor &cursorPix) :
    Square(obj, cursorPix)
{
    move(0, _parent->height() - kEditSquareSize);
}

void LB_Square::mouseMoveEvent(QMouseEvent *e)
{
    if ( e->x() > 0 && ( _parent->width() - e->x() < _parent->minimumWidth() ) )
    {
        _parent->setGeometry(_parent->x() + _parent->width() - _parent->minimumWidth(),
                             _parent->y(),
                             _parent->minimumWidth(),
                             _parent->height() + e->y()
                            );
    }
    else
    {
        _parent->setGeometry(
                             _parent->x() + e->x(),
                             _parent->y(),
                             _parent->width() - e->x(),
                             _parent->height() + e->y()
                            );
    }
    emit Moved();
}
