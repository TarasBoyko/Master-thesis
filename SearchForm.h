#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QWindow>
#include <QMenu>
//#include "Function/t_FunctionStickerScrollArea.h"
#include "InfoStore.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::map;
using std::string;
using std::vector;
using std::find;



class BaseButton;
class t_FunctionStickerScrollArea;

namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

    Ui::SearchForm *ui;
    t_FunctionStickerScrollArea* scrollArea; //_pFunctionStickersList;
    map< QString, vector<QWidget*> > mapOfEditButtons;

public:
    explicit SearchForm(QWidget *parent = 0);
    InfoStore infoStore;

    void GoIntoAreaButton(AreaButton* areaButton);


    void UpdateVisibleOfEditButtons();
    void UpdateNavigationButtons();
    ~SearchForm();


private slots:
    void on_BackButton_clicked();
    void on_ForwardButton_clicked();


    void on_EyeButton_clicked();

    void on_EditButton_clicked();

    void on_AddGreenButton_pressed();
    void on_AddFunction_clicked();
    void on_AddAreaButton_pressed(); private:
        // pool created BaseButton and inserts it in InfoStore
        void PoolNewBaseButton(BaseButton* poolingButton, QRect allowedRect); private slots: // up 3



    void UpdateFunctionList();

    void mousePressEvent(QMouseEvent *);
    void on_DoBackupButton_clicked();

    void on_SaveButton_clicked();

    void on_AddFlashButton_clicked();

private:

    void copyDir(const QString &sourceDirName, const QString &destinationDirName);
    bool CheckCurrentSlide();
public slots:
    void FinishFunctionEditting(InfoStore::FunctionInfo newFunction, bool isCreatedNewFunction);


};

#endif // SEARCHFORM_H
