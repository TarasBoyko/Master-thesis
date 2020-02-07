#ifndef BASEFUNCTIONALITYFORM_H
#define BASEFUNCTIONALITYFORM_H

#include <QWidget>
#include <fstream>
#include <QPoint>
#include <QDialog>
#include "t_AppState.h"
#include "FunctionalityForm/AbstractFunctionalityForm.h"

class InfoStore;

namespace Ui {
class BaseFunctionalityForm;
}

class BaseFunctionalityForm : public AbstractFunctionalityForm
{
    Q_OBJECT

protected:


public:
    explicit BaseFunctionalityForm(const int& id_, const bool isCreatingNewFunctionality, InfoStore& rInfoStore_, QWidget* parent = 0);
    ~BaseFunctionalityForm();

private:
    Ui::BaseFunctionalityForm *ui;
};

#endif // BASEFUNCTIONALITYFORM_H
