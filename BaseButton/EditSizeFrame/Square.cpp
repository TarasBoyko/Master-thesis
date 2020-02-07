#include "BaseButton/EditSizeFrame/Square.h"
#include "BaseButton/BaseButton.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>

 Square::Square(BaseButton* obj, const QCursor &cursorPix_) :
    QLabel( static_cast<QWidget*>(obj) )
{
     _parent = obj;
     cursorPix = cursorPix_;
    setStyleSheet("QLabel {"
                  "background-color: blue;"
                  "}"
                  );
    resize(kEditSquareSize, kEditSquareSize);
    show();
 }

 void Square::enterEvent(QEvent *)
 {
     QApplication::setOverrideCursor(cursorPix);
}

void Square::leaveEvent(QEvent *)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
