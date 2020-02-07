#ifndef SQUARE
#define SQUARE

#include <QLabel>
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>

class LT_Square;
class T_Square;
class RT_Square;
class L_Square;
class R_Square;
class LB_Square;
class B_Square;
class RB_Square;
class EditSizeFrame;
class BaseButton;

const int kEditSquareSize = 10;

// base class to elongate BaseButton by a mouse
class Square : public QLabel
{
    Q_OBJECT

protected:
    QCursor cursorPix;
    BaseButton* _parent;
public:
  Square(BaseButton* obj, const QCursor& cursorPix_);

   void enterEvent(QEvent *);

   void leaveEvent(QEvent *);

signals:
   void Moved();
};

#endif // SQUARE
