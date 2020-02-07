#include "FunctionalityForm/AbstractFunctionalityForm.h"
#include "ui_AbstractFunctionalityForm.h"
#include <assert.h>
#include <QDebug>

extern t_AppState AppState;

AbstractFunctionalityForm::AbstractFunctionalityForm(const int& id_, const bool isCreatingNewFunctionality, InfoStore& rInfoStore_, QWidget *parent) :
    QDialog(parent),
    rInfoStore(rInfoStore_),
    ui(new Ui::AbstractFunctionalityForm)
{
    assert( !(isCreatingNewFunctionality && AppState.GetState() == t_AppState::USE) );

    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // take off ? sign from the window
    id = id_;
    isCreateNewFunctionality = isCreatingNewFunctionality;
    stateOfCallingThisForm = AppState.GetState();

    // set icons
    setWindowIcon( QIcon("Images\\lightning_iO0_icon.ico") ); // probebly bug: not set in design mode
    ui->EyeButton->SetPictures("Images\\EyeHover.png", "Images\\Eye.png", "Images\\EyePressed.png");
    ui->EditButton->SetPictures("Images\\EditHover.png", "Images\\Edit.png", "Images\\EditPressed.png");
    ui->labelSwitch->setPixmap( QPixmap("Images\\Left.png"));

    //set Rect for set it for form after selecting associated button for function
    oldLU_angle = mapToGlobal(contentsRect().topLeft());
    oldWidth = geometry().width();
    oldHeight = geometry().height();
}

AbstractFunctionalityForm::~AbstractFunctionalityForm()
{
    delete ui;
}
