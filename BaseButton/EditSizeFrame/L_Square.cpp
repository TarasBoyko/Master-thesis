#include "BaseButton/EditSizeFrame/L_Square.h"
#include "GreenButton.h"
#include <QDebug>

L_Square::L_Square(BaseButton *obj, const QCursor& cursorPix) :
    Square(obj, cursorPix)
{
    move(0, _parent->height()/2 - kEditSquareSize/2);
}

void L_Square::mouseMoveEvent(QMouseEvent *e)
{
    if ( e->x() > 0 && ( _parent->width() - e->x() < _parent->minimumWidth() ) )
    {
        _parent->setGeometry(_parent->x() + _parent->width() - _parent->minimumWidth(),
                            _parent->y(),
                            _parent->minimumWidth(),
                            _parent->height()
                            );
    }
    else
    {
        _parent->setGeometry(
                    _parent->x() + e->x(),
                    _parent->y(),
                    _parent->width() - e->x(),
                    _parent->height()
                            );
    }

    emit Moved();
}
