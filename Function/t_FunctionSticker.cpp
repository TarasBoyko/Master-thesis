#include <QDebug>
#include <QScrollBar>
#include "InfoStore.h"
#include "SearchForm.h"
#include "t_FunctionSticker.h"
#include "ui_t_FunctionSticker.h"
#include "Function/FunctionForm.h"
#include "t_AppState.h"


extern t_AppState AppState;

t_FunctionSticker::t_FunctionSticker(SearchForm* newPSearchForm, InfoStore &rInfoStore_, QWidget *parent) :
    QWidget(parent),
    rInfoStore(rInfoStore_),
    ui(new Ui::t_FunctionSticker)
{
    ui->setupUi(this);
    pSearchForm = newPSearchForm;
    switch ( AppState.GetState() ) {
    case t_AppState::USE: case t_AppState::EDIT:
        setCursor(Qt::PointingHandCursor);
        break;
    default:
        assert(false);
    }

    _oldShortDescriptionHeight = kMinDocumentHeight; // after entering the first symbol shortDescription takes such value
}

t_FunctionSticker::t_FunctionSticker(SearchForm *newPSearchForm, const int &newFunctionsId, const QString &newText, InfoStore &rInfoStore_, QWidget *parent) :
    //rInfoStore(rInfoStore_),
    t_FunctionSticker(newPSearchForm, rInfoStore_,parent)
{
    _functionsId = newFunctionsId;
    SetShortDescription(newText);
}

void t_FunctionSticker::SetShortDescription(const QString &newShortDescription)
{
    show();
    ui->shortDescription->setText(newShortDescription);
}

t_FunctionSticker::~t_FunctionSticker()
{
    delete ui;
}

void t_FunctionSticker::contextMenuEvent(QContextMenuEvent *)
{
    QMenu* menu = new QMenu;
    switch ( AppState.GetState() ) {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION :
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    case t_AppState::EDIT :
        menu->addAction("Delete", this, SLOT(DeleteMyself()) );
        menu->exec(QCursor::pos());
    default:
        assert(false);
    }
}

void t_FunctionSticker::on_shortDescription_textChanged()
{
    int newShortDescriptionHeight = ui->shortDescription->document()->size().height() + 2;
    ui->shortDescription->setMinimumHeight(newShortDescriptionHeight);
    ui->shortDescription->setFixedHeight(newShortDescriptionHeight);

    if ( newShortDescriptionHeight == 0 )
    {
        newShortDescriptionHeight = kMinDocumentHeight;
    }

    if ( newShortDescriptionHeight != _oldShortDescriptionHeight )
    {
        emit HeightChanged( newShortDescriptionHeight - _oldShortDescriptionHeight );
    }
    _oldShortDescriptionHeight = newShortDescriptionHeight;

    rInfoStore.GetReferenceToFunctionById(_functionsId).shortDescription = ui->shortDescription->toPlainText();
}

void t_FunctionSticker::mouseDoubleClickEvent(QMouseEvent *)
{
    FunctionForm* edittingFunction = nullptr;
    switch ( AppState.GetState() )
    {
    case t_AppState::USE :
        break;
    case t_AppState::EDIT :
        edittingFunction = new FunctionForm(_functionsId, false, rInfoStore);
        edittingFunction->SetShortDescription( rInfoStore.GetReferenceToFunctionById(_functionsId).shortDescription );
        connect(edittingFunction, SIGNAL(FormCompleted(InfoStore::FunctionInfo, bool)), pSearchForm, SLOT(FinishFunctionEditting(InfoStore::FunctionInfo, bool)) );
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void t_FunctionSticker::mouseReleaseEvent(QMouseEvent* e)
{
    FunctionForm* creatingFunction = nullptr;
    switch ( AppState.GetState() ) {
    case t_AppState::USE:
        if ( e->button() == Qt::LeftButton )
        {
            creatingFunction = new FunctionForm(_functionsId, false, rInfoStore);
            connect(creatingFunction, SIGNAL(FormCompleted(InfoStore::FunctionInfo, bool)), pSearchForm, SLOT(FinishFunctionEditting(InfoStore::FunctionInfo, bool)) );
            creatingFunction->SetShortDescription( rInfoStore.GetReferenceToFunctionById(_functionsId).shortDescription );
        }
        break;
    case t_AppState::EDIT :
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        parentWidget()->setFocus(); // a workaround because would be possible to edit function short description
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void t_FunctionSticker::DeleteMyself()
{
    rInfoStore.DeleteFunctionById(_functionsId);
    emit rInfoStore.SelectedFunctionsUpdated();
}

void t_FunctionSticker::enterEvent(QEvent* )
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE :
        ui->shortDescription->setReadOnly(true);
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        break;
    case t_AppState::EDIT :
        ui->shortDescription->setReadOnly(false);
        QApplication::setOverrideCursor(Qt::IBeamCursor);
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION :
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        break;
    default:
        assert(false);
    }
}

void t_FunctionSticker::leaveEvent(QEvent *)
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE: case t_AppState::EDIT: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION :
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        break;
    default:
        assert(false);
    }
}


