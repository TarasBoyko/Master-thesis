#include <QApplication>
#include <QDir>
#include "AreaButton.h"
#include "header.h"
#include "Navigation/t_Navigator.h"
#include "SearchForm.h"
#include "CustomWidgets/CustomErrorMsgBox.h"
extern t_Navigator Navigator;

AreaButton::AreaButton(const QString& textOnButton,
                       const int &identifier,
                       const QPoint& UL_angle,
                       const int& width_,
                       const int& height_,
                       InfoStore* infoStore_,
                       SearchForm *parent_) :
    BaseButton(  textOnButton, identifier, UL_angle, width_, height_, infoStore_, parent_, kAreaButtonWidthForProportion, kAreaButtonHeightForProportion),
    AbstractAreaButton(textOnButton)
{
    SetUssualStyle();
}

AreaButton::AreaButton(const int &identifier, const QPoint &UL_angle, const int &width_, const int &height_, InfoStore *infoStore_, SearchForm *parent_) :
    BaseButton("", identifier, UL_angle, width_, height_, infoStore_, parent_, kAreaButtonWidthForProportion, kAreaButtonHeightForProportion),
    AbstractAreaButton()
{
    SetUssualStyle();
}

AreaButton::AreaButton(char* &p, InfoStore* rInfoStore_, SearchForm * parent_) :
    BaseButton(p, rInfoStore_, parent_, kAreaButtonWidthForProportion, kAreaButtonHeightForProportion),
    AbstractAreaButton( text() )
{
    // set text on button
    //unsigned dirName = strchr(p, '|') - p;

    p = strchr(p, '|') + 1;
    unsigned dirName = strchr(p, '|') - p;

    SetDirectoryName( QString::fromLatin1(p, dirName) );
    qDebug() << "FILED"<< GetDirectoryName() << "END";
    SetUssualStyle();
}

void AreaButton::SetUssualStyle()
{
    QString backgroundImage = QApplication::applicationDirPath() + "/Images/Area2.png";
    setStyleSheet("QPushButton{"
                  "border-radius: 0px transparent;"
                  "border-image: url(" + backgroundImage + ");"
                  "}"
                  );
}

void AreaButton::RecordInFile(std::ofstream &file)
{
    BaseButton::RecordInFile(file);
    file << GetDirectoryName().toStdString() << '|';
}

void AreaButton::focusInEvent(QFocusEvent *e)
{
    qDebug() << "FOCUS IN IN AREABUTTON";
    if ( QGuiApplication::keyboardModifiers() == Qt::ShiftModifier )
    {
        ;
    }
    else
    {
        BaseButton::focusInEvent(e);
    }
}

void AreaButton::focusOutEvent(QFocusEvent *)
{
    switch ( AppState.GetState() ) {
    case t_AppState::USE:
        break;
    case t_AppState::EDIT:
        /*if ( unallable name)
        {
            break;
        }*/
        if ( pEditSizeFrame != nullptr )
        {
            delete pEditSizeFrame;
            pEditSizeFrame = nullptr;


        }
        break;
    default:
        assert(false);
    }
}

void AreaButton::mouseReleaseEvent(QMouseEvent* e)
{
    switch ( AppState.GetState() )
    {
        case t_AppState::USE:
            searchForm->GoIntoAreaButton(this);
            break;
        case t_AppState::EDIT:
            if ( e->modifiers() & Qt::ShiftModifier )
            {
                searchForm->GoIntoAreaButton(this);
            }
            else
            {
                BaseButton::mouseReleaseEvent(e);
            }
            break;
        case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
            AppState.ShowWrongOperationInCurrentStateMessage();
            break;
        default:
            assert(false);
    }
}

void AreaButton::keyReleaseEvent(QKeyEvent *e)
{
    QMessageBox::StandardButton messageBox;
    switch ( e->key() )
    {
    case Qt::Key_Delete :
        switch ( AppState.GetState() )
        {
        case t_AppState::USE :
            AppState.ShowWrongOperationInCurrentStateMessage();
            break;
        case t_AppState::EDIT :
            // reask user
            messageBox = QMessageBox::warning(searchForm,
                                              "Framework",
                                              "Are you sure you want to delete \"" + text() + "\" button?",
                                              QMessageBox::Yes | QMessageBox::No
            );
            if ( messageBox == QMessageBox::Yes )
            {
                rInfoStore->DeleteAreaButton(this);
                if ( !Navigator.IsCurrentDirPathEqualsSwimmingDirPath() && GetDirectoryName() == Navigator.GetNextDirForCurrentDirPath() )
                {
                    Navigator.CutSwimDirPath();
                    dynamic_cast<SearchForm*>( parentWidget() )->UpdateNavigationButtons();
                }
                delete this;
            }
            break;
        default:
            assert(false);
        }
    default:
        ;
    }
}

void AreaButton::SaveNewName_Slot()
{
    if ( pEditingName->toPlainText().size() == 0 )
    {
        // Handle error
        CustomErrorMsgBox("UNUNknow error");
        return;
    }
    /*QString oldDirectoryName = GetDirectoryName();
    QDir correspondingDir( Navigator.GetCurrentDirPath() );
    SetDirectoryNameUsingPresentationName(pEditingName->toPlainText());
    assert ( correspondingDir.rename(oldDirectoryName, GetDirectoryName() ) );
    qDebug() << "old dir name"<<oldDirectoryName<<GetDirectoryName();
    if ( !Navigator.IsCurrentDirPathEqualsSwimmingDirPath() && GetDirectoryName() == Navigator.GetNextDirForCurrentDirPath() )
    {
        Navigator.PathChanged(oldDirectoryName, GetDirectoryName() );
    }*/

    vector<QString> namesOfAreaButtonsOnCurrentSlide;
    vector<QString> namesOfAreaButtonDirsOnCurrentSlide;
    qDebug() << "areaButton size"<<rInfoStore->areaButtons.size();
    for ( auto button : rInfoStore->areaButtons )
    {
        qDebug() << button->GetDirectoryName();
        if ( button != this )
        {
            namesOfAreaButtonsOnCurrentSlide.push_back( button->text() );
            namesOfAreaButtonDirsOnCurrentSlide.push_back( button->GetDirectoryName() );
        }

    }

    if ( std::find(namesOfAreaButtonsOnCurrentSlide.begin(),
                   namesOfAreaButtonsOnCurrentSlide.end(),
                   pEditingName->toPlainText()
                   )
         != namesOfAreaButtonsOnCurrentSlide.end()
         )
    {
        CustomErrorMsgBox("There are two equal area button names");
        SetUssualStyle();
        return;
    }


    qDebug() << "pered reset"<<namesOfAreaButtonDirsOnCurrentSlide << namesOfAreaButtonsOnCurrentSlide;
    ResetDirectoryNameUsingPresentationName(pEditingName->toPlainText(), namesOfAreaButtonDirsOnCurrentSlide );
    BaseButton::SaveNewName_Slot();
    rInfoStore->RecordDataIntoInfoFile();
    SetUssualStyle();
}
