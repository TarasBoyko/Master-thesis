#ifndef FUNCTIONFORM_H
#define FUNCTIONFORM_H

#include "InfoStore.h"
#include "t_AppState.h"
#include <QWidget>
#include <QDialog>
#include <QAbstractButton>
#include <string>
#include <fstream>

namespace Ui {
class FunctionForm;
}

class FunctionForm : public QDialog
{
    Q_OBJECT

    QPoint oldLU_angle;
    int oldWidth;
    int oldHeight;
    std::fstream File; // File of description function
    int id;
    InfoStore& rInfoStore;
    bool isCreateNewFunction;
    t_AppState::STATE_ENUM stateOfCallingThisForm;



public:
    explicit FunctionForm(const int &id_, const bool isCreatingNewFunction, InfoStore &rInfoStore_);

    void FillFromFile();
    void RecordIntoFile();
    void SetShortDescription(const QString& newShortDescription);
    void SetVisibleEditWidget(const bool isVisible);
    ~FunctionForm();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_selectingAssocGreenButtons_toggled(bool checked);

    void on_EyeButton_clicked();

    void on_EditButton_clicked();

private:
    Ui::FunctionForm *ui;
    vector<GreenButton*> checkedUpGreenButton;

protected:
    void resizeEvent(QResizeEvent*);
    void moveEvent(QMoveEvent *);
signals:
    void FormCompleted(InfoStore::FunctionInfo, bool isCreatedNewFunction);
};

#endif // FUNCTIONFORM_H
