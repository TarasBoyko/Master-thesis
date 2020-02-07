#include "FunctionalityForm/BaseFunctionalityForm.h"
#include "ui_BaseFunctionalityForm.h"
#include <assert.h>
#include <QDebug>

extern t_AppState AppState;

BaseFunctionalityForm::BaseFunctionalityForm(const int& id_, const bool isCreatingNewFunctionality, InfoStore& rInfoStore_, QWidget *parent) :
    AbstractFunctionalityForm(id_, isCreatingNewFunctionality, rInfoStore_, parent),
    ui(new Ui::BaseFunctionalityForm)
{
    ui->setupUi(this);;
}

BaseFunctionalityForm::~BaseFunctionalityForm()
{
    delete ui;
}
