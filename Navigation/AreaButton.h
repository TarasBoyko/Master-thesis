#ifndef AREABUTTON_H
#define AREABUTTON_H

#include "BaseButton/BaseButton.h"
#include "Navigation/AbstractAreaButton.h"

const double kAreaButtonWidthForProportion = 399;
const double kAreaButtonHeightForProportion = 193;

class AreaButton : public BaseButton, public AbstractAreaButton
{
    virtual void SaveNewName_Slot() override;

protected:
    virtual void SetUssualStyle();

protected slots:
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent* e);


public:
    explicit AreaButton(const QString& textOnButton,
                        const int &identifier,
                        const QPoint& UL_angle,
                        const int& width_,
                        const int& height_,
                        InfoStore *infoStore_,
                        SearchForm *parent_
                        );
    // constructor for pool AreaButton from form
    explicit AreaButton(const int &identifier,
                        const QPoint& UL_angle,
                        const int& width_,
                        const int& height_,
                        InfoStore *infoStore_,
                        SearchForm *parent_
                        );
    // constructor for read AreaButton from file
    explicit AreaButton(char *&p,
                        InfoStore *rInfoStore_,
                        SearchForm *parent_
                        );
    virtual void RecordInFile(std::ofstream &file) override;
};

#endif // AREABUTTON_H
