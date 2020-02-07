#include <QCursor>
#include "GreenButton.h"
#include "BaseButton/EditSizeFrame/RT_Square.h"

RT_Square::RT_Square(BaseButton *obj, const QCursor &cursorPix) :
    Square(obj, cursorPix)
{
    move(_parent->width() - kEditSquareSize, 0);
}

void RT_Square::mouseMoveEvent(QMouseEvent *e)
{
    if ( e->y() > 0 && ( _parent->height() - e->y() < _parent->minimumHeight() ) )
    {
        _parent->setGeometry(_parent->x(),
                            _parent->y() + _parent->height() - _parent->minimumHeight(),
                            _parent->width() + e->x(),
                            _parent->minimumHeight()
                            );
    }
    else
    {
        _parent->setGeometry(
                    _parent->x(),
                    _parent->y() + e->y(),
                    _parent->width()  + e->x(),
                    _parent->height() - e->y()
                    );
    }

    emit Moved();
}
