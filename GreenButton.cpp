#include "GreenButton.h"
#include <assert.h>
#include <QDebug>
#include <algorithm>
#include <QMessageBox>
#include "InfoStore.h"
#include "SearchForm.h"

void GreenButton::SetUssualStyle()
{
    setStyleSheet("QPushButton {"
                  "background-color: lightGray;"
                  "border-style: solid;"
                  "border-width: 3px;"
                  "border-radius: 20px;"
                  "border-color: black;"
                  "padding: 10px;"
                  "}"
                  "QPushButton:hover {"
                  "background-color: #1aff5b;"
                  "}"
                  "QPushButton:checked {"
                  "background-color: #00d200;"
                  "border-width: 4px;"
                  "}"
                  );
}

void GreenButton::SaveNewName_Slot()
{
    BaseButton::SaveNewName_Slot();
    SetUssualStyle();
}

GreenButton::GreenButton(const QString &textOnButton,
                         const int &identifier,
                         const QPoint &UL_angle,
                         const int &width_,
                         const int &height_,
                         InfoStore *infoStore_,
                         SearchForm *parent) :
    BaseButton(textOnButton, identifier, UL_angle, width_, height_, infoStore_, parent, kGreenButtonWidthForProportion, kGreenButtonHeightForProportion)
{
    SetUssualStyle();
    setCheckable(true);
}

GreenButton::GreenButton(char *p, InfoStore* rInfoStore_, SearchForm * const parent_) :
    BaseButton(p, rInfoStore_, parent_, kGreenButtonWidthForProportion, kGreenButtonHeightForProportion)
{
    SetUssualStyle();
    setCheckable(true);
}

void GreenButton::mouseReleaseEvent(QMouseEvent *)
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE:
        toggle();
        if ( this->isChecked() ) // intersection
        {
            rInfoStore->IntersectSelectedFunctions(this);
            //Finder.intersection( id ); // Finder.arrayButtonInfo[i].id
            return;
        }
        else //merge
        {
            rInfoStore->MergeSelectedFunctions();
            //Finder.merge( id ); // Finder.arrayButtonInfo[i].id;
            return;
        }
    case t_AppState::EDIT:
        return;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        //AppState.ShowErrorMessage(searchForm);
        toggle();

        break;
    default:
        assert(false);
    }
}

void GreenButton::keyReleaseEvent(QKeyEvent* e)
{
    QMessageBox::StandardButton messageBox;

    InfoStore::FunctionInfo poorFunction; // function with single associated GreenButton
    switch ( AppState.GetState() )
    {
    case t_AppState::USE:
        break;
    case t_AppState::EDIT:
        switch ( e->key() )
        {
        case Qt::Key_Delete :
            // define if button is one associated button for some function
            if ( rInfoStore->IsFunctionWithSingleAssocGreenButton(this, poorFunction) )
            {
                QMessageBox::warning(searchForm, "Error", "This button is one associated button for "
                                     "\"" + poorFunction.shortDescription + "\" function"
                                     );
                return;
            }

            // reask user
            messageBox = QMessageBox::warning(searchForm,
                                              "Framework",
                                              "Are you sure you want to delete \"" + text() + "\" button?",
                                              QMessageBox::Yes | QMessageBox::No
                                              );

            if ( messageBox == QMessageBox::Yes )
            {
                rInfoStore->DeleteGreenButton(this);
                delete this;
            }
            break;
        default:
            ;
        }
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}
