#include "EditSizeFrame.h"

#include "Square.h"
#include "GreenButton.h"
#include "EditSizeFrame.h"

EditSizeFrame::EditSizeFrame(BaseButton* obj) :
    leftTop(obj, Qt::SizeFDiagCursor),
    top(obj, Qt::SizeVerCursor),
    rightTop(obj, Qt::SizeBDiagCursor),
    left(obj, Qt::SizeHorCursor),
    right(obj, Qt::SizeHorCursor),
    leftBottom(obj, Qt::SizeBDiagCursor),
    bottom(obj, Qt::SizeVerCursor),
    rightBottom(obj, Qt::SizeFDiagCursor)
{
    parent = obj;
    connect(&top, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&leftTop, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&rightTop, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&left, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&right, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&leftBottom, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&bottom, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
    connect(&rightBottom, SIGNAL(Moved()), this, SLOT(UpdateSquaresPos()));
}

void EditSizeFrame::UpdateSquaresPos()
{
    leftTop.move(0, 0);
    top.move(parent->width()/2 - kEditSquareSize/2, 0);
    rightTop.move(parent->width() - kEditSquareSize, 0);
    left.move(0, parent->height()/2 - kEditSquareSize/2);
    right.move(parent->width() - kEditSquareSize, parent->height()/2 - kEditSquareSize/2);
    leftBottom.move(0, parent->height() - kEditSquareSize);
    bottom.move(parent->width()/2 - kEditSquareSize/2, parent->height() - kEditSquareSize);
    rightBottom.move(parent->width() - kEditSquareSize, parent->height() - kEditSquareSize);
}
