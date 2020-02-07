#ifndef GREENBUTTON_H
#define GREENBUTTON_H

#include "header.h"
#include "BaseButton/BaseButton.h"

#include "t_AppState.h"

extern t_AppState AppState;

using namespace std;

const double kGreenButtonWidthForProportion = 97;
const double kGreenButtonHeightForProportion = 61;

class GreenButton : public BaseButton
{
    Q_OBJECT

    friend class FunctionForm;

protected:
    virtual void SetUssualStyle();

protected slots:
    virtual void SaveNewName_Slot() override;
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent* );
public:
    explicit GreenButton(const QString& textOnButton,
                         const int& identifier,
                         const QPoint& UL_angle,
                         const int& width_,
                         const int& height_,
                         InfoStore* infoStore_,
                         SearchForm *parent);
    explicit GreenButton(char *p, InfoStore* rInfoStore_, SearchForm * const parent_);
};

#endif // GREENBUTTON_H



