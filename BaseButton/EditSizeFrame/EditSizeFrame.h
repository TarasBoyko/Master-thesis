#ifndef EDITSIZEFRAME_H
#define EDITSIZEFRAME_H

#include "BaseButton/EditSizeFrame/LT_Square.h"
#include "BaseButton/EditSizeFrame/T_Square.h"
#include "BaseButton/EditSizeFrame/RT_Square.h"
#include "BaseButton/EditSizeFrame/L_Square.h"
#include "BaseButton/EditSizeFrame/R_Square.h"
#include "BaseButton/EditSizeFrame/LB_Square.h"
#include "BaseButton/EditSizeFrame/B_Square.h"
#include "BaseButton/EditSizeFrame/RB_Square.h"

class BaseButton;

class EditSizeFrame: public QObject
{
    Q_OBJECT

    BaseButton* parent;
    LT_Square leftTop;
    T_Square  top;
    RT_Square rightTop;
    L_Square  left;
    R_Square  right;
    LB_Square leftBottom;
    B_Square  bottom;
    RB_Square rightBottom;

public:
    explicit EditSizeFrame(BaseButton* obj);

protected slots:
    void UpdateSquaresPos();
};

#endif // EDITSIZEFRAME_H
