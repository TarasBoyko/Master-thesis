#ifndef ABSTRACTFUNCTIONALITYFORM_H
#define ABSTRACTFUNCTIONALITYFORM_H

#include <QWidget>
#include <fstream>
#include <QPoint>
#include <QDialog>
#include "t_AppState.h"

class InfoStore;

namespace Ui {
class AbstractFunctionalityForm;
}

class AbstractFunctionalityForm : public QDialog
{
    Q_OBJECT

protected:
    QPoint oldLU_angle;
    int oldWidth;
    int oldHeight;
    std::fstream File; // File of functionality description
    int id;
    InfoStore& rInfoStore;
    bool isCreateNewFunctionality;
    t_AppState::STATE_ENUM stateOfCallingThisForm;

public:
    explicit AbstractFunctionalityForm(const int& id_, const bool isCreatingNewFunctionality, InfoStore& rInfoStore_, QWidget* parent = 0);
    ~AbstractFunctionalityForm();

private:
    Ui::AbstractFunctionalityForm *ui;
};

#endif // ABSTRACTFUNCTIONALITYFORM_H
