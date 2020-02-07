#include "BaseButton/EditSizeFrame/T_Square.h"
#include "GreenButton.h"

T_Square::T_Square(BaseButton *obj, const QCursor& cursorPix) :
    Square(obj, cursorPix)
{
    move(_parent->width()/2 - kEditSquareSize/2, 0);
}

void T_Square::mouseMoveEvent(QMouseEvent *e)
{
    if ( e->y() > 0 && ( _parent->height() - e->y() < _parent->minimumHeight() ) )
    {
        _parent->setGeometry(_parent->x(),
                            _parent->y() + _parent->height() - _parent->minimumHeight(),
                            _parent->width(),
                            _parent->minimumHeight()
                            );
    }
    else
    {
        _parent->setGeometry(
                             _parent->x(),
                             _parent->y() + e->y(),
                             _parent->width(),
                             _parent->height() - e->y()
                            );
    }
    emit Moved();
}
