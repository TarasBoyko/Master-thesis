#include "BaseButton/EditSizeFrame/LT_Square.h"
#include "GreenButton.h"

LT_Square::LT_Square(BaseButton* obj, const QCursor &cursorPix) :
    Square(obj, cursorPix)
{

}

void LT_Square::mouseMoveEvent(QMouseEvent *e)
{
    if ( (e->x() > 0 && ( _parent->width() - e->x() < _parent->minimumWidth() ))
         &&
         (e->y() > 0 && ( _parent->height() - e->y() < _parent->minimumHeight() )) )
    {
        _parent->setGeometry(_parent->x() + _parent->width() - _parent->minimumWidth(),
                            _parent->y() + _parent->height() - _parent->minimumHeight(),
                            _parent->minimumWidth(),
                            _parent->minimumHeight()
                            );
        emit Moved();
        return;
    }
    if ( e->x() > 0 && ( _parent->width() - e->x() < _parent->minimumWidth() ) )
    {
        _parent->setGeometry(_parent->x() + _parent->width() - _parent->minimumWidth(),
                            _parent->y() + e->y(),
                            _parent->minimumWidth(),
                            _parent->height() - e->y()
                            );
        emit Moved();
        return;
    }
    if ( e->y() > 0 && ( _parent->height() - e->y() < _parent->minimumHeight() ) )
    {
        _parent->setGeometry(_parent->x() + e->x(),
                            _parent->y() + _parent->height() - _parent->minimumHeight(),
                            _parent->width() - e->x(),
                            _parent->minimumHeight()
                            );
        emit Moved();
        return;
    }
    _parent->setGeometry(
                _parent->x() + e->x(),
                _parent->y() + e->y(),
                _parent->width() - e->x(),
                _parent->height() - e->y()
                );
    emit Moved();
}
