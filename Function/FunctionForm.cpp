#include "header.h"
#include <QAbstractButton>
#include <QSound>
#include <QMessageBox>
#include "FunctionForm.h"
#include "ui_FunctionForm.h"
#include "Navigation/t_Navigator.h"
#include "t_AppState.h"
#include "InfoStore.h"
#include "GreenButton.h"
#include "CustomWidgets/CustomErrorMsgBox.h"

extern t_Navigator Navigator;
extern t_AppState AppState;

static const string kHeaderChapterInFucntionFile = "Header: ";
static const string kNamespaceChapterInFunctionFile = "Namespace: ";
static const unsigned kMaxLengthOfTextFunctionAttribute = 1024; // ... (header, namespace, short description)

FunctionForm::FunctionForm(const int& id_, const bool isCreatingNewFunction, InfoStore& rInfoStore_) :
    QDialog(nullptr),
    rInfoStore(rInfoStore_),
    ui(new Ui::FunctionForm)
{
    assert( !(isCreatingNewFunction && AppState.GetState() == t_AppState::USE) );

    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // take off ? sign from the window
    id = id_;
    isCreateNewFunction = isCreatingNewFunction;
    stateOfCallingThisForm = AppState.GetState();
    qDebug() << "id of function in function form"<<id;

    // set icons
    setWindowIcon( QIcon("Images/lightning_iO0_icon.ico") ); // probebly bug: not set in design mode
    ui->selectingAssocGreenButtons->SetPictures("Images/SelectGreenButtons_Hover.png", "Images/SelectGreenButtons.png", "Images/SelectGreenButtons_Pressed.png");
    ui->EyeButton->SetPictures("Images\\EyeHover.png", "Images\\Eye.png", "Images\\EyePressed.png");
    ui->EditButton->SetPictures("Images\\EditHover.png", "Images\\Edit.png", "Images\\EditPressed.png");
    ui->labelSwitch->setPixmap( QPixmap("Images\\Left.png"));
    ui->labelSwitch->setScaledContents(true);

    //set Rect for set it for form after selecting associated button for function
    oldLU_angle = mapToGlobal(contentsRect().topLeft());
    oldWidth = geometry().width();
    oldHeight = geometry().height();

    if ( !isCreatingNewFunction )
    {
        FillFromFile();
    }
    switch (AppState.GetState()) {
    case t_AppState::USE:
        ui->selectingAssocGreenButtons->hide();
        ui->buttonBox->hide();
        break;
    case t_AppState::EDIT:
        ui->selectingAssocGreenButtons->show();
    default:
        break;
    }
    show();
}

void FunctionForm::FillFromFile()
{
    char buffer[kMaxLengthOfTextFunctionAttribute + 1]; // ... "+ 1" to '\0'
    QString pathToFunctionFile = QString( Navigator.GetCurrentDirPath() ) +
                                          kDirSeparatorInPath +
                                          QString::number(id) +
                                          QString(".txt");
    QFile functionFile(pathToFunctionFile);
    if ( !functionFile.open(QIODevice::ReadOnly) )
    {
        CustomErrorMsgBox("File could not open");
        exit(0);
    }
    int stringLength = 0;
    QByteArray checkByteArray;

    // read header
    stringLength = functionFile.read( buffer, kHeaderChapterInFucntionFile.length() );
    if ( stringLength < 0 )
    {
        CustomErrorMsgBox("Header chapter not been finded");
        exit(0);
    }
    buffer[stringLength] = '\0';
    if ( stringLength == 0 ||
         strcmp( buffer, kHeaderChapterInFucntionFile.c_str() ) != 0
       )
    {
        CustomErrorMsgBox("Header chapter not been finded");
        exit(0);
    }
    stringLength = functionFile.readLine( buffer, kMaxLengthOfTextFunctionAttribute );
    if ( stringLength < 0 || strlen(buffer) <= strlen(kLn) || strstr(buffer, kLn) == nullptr )
    {
        CustomErrorMsgBox("Header not been finded");
        exit(0);
    }
    *strstr(buffer, kLn) = '\0'; // take off kLn
    ui->headerLineEdit->setText(buffer);

    // read namespace
    stringLength = functionFile.read( buffer, kNamespaceChapterInFunctionFile.length() );
    if ( stringLength < 0 )
    {
        CustomErrorMsgBox("Namespace chapter not been finded");
        exit(0);
    }
    buffer[stringLength] = '\0';
    if ( stringLength == 0 ||
         strcmp( buffer, kNamespaceChapterInFunctionFile.c_str() ) != 0
       )
    {
        CustomErrorMsgBox("Namespace chapter not been finded");
        exit(0);
    }
    stringLength = functionFile.readLine(buffer, kMaxLengthOfTextFunctionAttribute);
    if ( stringLength < 0 || strlen(buffer) <= strlen(kLn) || strstr(buffer, kLn) == nullptr )
    {
        CustomErrorMsgBox("Namespace not been finded");
        exit(0);
    }
    *strstr(buffer, kLn) = '\0'; // take off kLn
    ui->namespaceLineEdit->setText(buffer);

    // read full function description
    QString content = functionFile.readAll();
    ui->descriptionTextEdit->setText(content);

    functionFile.close();
}

void FunctionForm::RecordIntoFile()
{
    QFile functionFile( Navigator.GetCurrentDirPath() +
                        kDirSeparatorInPath +
                        QString::number(id) +
                        QString(".txt")
                       );
    functionFile.open(QIODevice::WriteOnly);

    functionFile.write( kHeaderChapterInFucntionFile.c_str() );
    functionFile.write( ui->headerLineEdit->text().toStdString().c_str() );
    functionFile.write(kLn);

    functionFile.write( kNamespaceChapterInFunctionFile.c_str() );
    functionFile.write( ui->namespaceLineEdit->text().toStdString().c_str() );
    functionFile.write(kLn);

    functionFile.write( ui->descriptionTextEdit->toPlainText().toStdString().c_str() );

    functionFile.close();

}

void FunctionForm::SetShortDescription(const QString &newShortDescription)
{
    ui->shortDescrioptionLineEdit->setText(newShortDescription);
}

void FunctionForm::SetVisibleEditWidget(const bool isVisible)
{
    ui->selectingAssocGreenButtons->setVisible(isVisible);
    ui->buttonBox->setVisible(isVisible);
}

FunctionForm::~FunctionForm()
{
    delete ui;
}

void FunctionForm::moveEvent(QMoveEvent* )
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        break;
    case t_AppState::EDIT:
        oldLU_angle = mapToGlobal( contentsRect().topLeft() );
        break;
    default:
        assert(false);
    }
}

void FunctionForm::resizeEvent(QResizeEvent*)
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        break;
    case t_AppState::EDIT:
        oldWidth = width();
        oldHeight = height();
        break;
    default:
        assert(false);
    }
}

void FunctionForm::on_buttonBox_clicked(QAbstractButton *button)
{
    InfoStore::FunctionInfo funInfo;
    switch ( ui->buttonBox->standardButton(button) )
    {
    case QDialogButtonBox::Ok :
        if ( rInfoStore.IsAllGreenButtonsUnpressed() )
        {
            CustomErrorMsgBox("All buttons is not pressed!");
            break;
        }

        RecordIntoFile();
        funInfo.id = id;
        funInfo.shortDescription = ui->shortDescrioptionLineEdit->text();
        emit FormCompleted(funInfo, isCreateNewFunction);
        AppState.SetState(stateOfCallingThisForm);
        delete this;
        break;
    case QDialogButtonBox::Cancel :
        for ( auto button : checkedUpGreenButton )
        {
            button->setChecked(false);
        }
        emit close();
        //AppState.SetState(t_AppState::EDIT);
        break;
    default:
        assert(false);
    }
}

void FunctionForm::on_selectingAssocGreenButtons_toggled(bool checked)
{
    set<int> assocGreenButtonsForCurrentFunction;
    for ( InfoStore::FunctionInfo func : rInfoStore.functions )
    {
        if ( func.id == id )
        {
            assocGreenButtonsForCurrentFunction = func.associatedGreenButtonsId;
            break;
        }
    }
    for ( auto greenButton : rInfoStore.greenButtons )
    {
        if ( assocGreenButtonsForCurrentFunction.find( greenButton->GetId() ) != assocGreenButtonsForCurrentFunction.end() )
        {
            if ( !greenButton->isChecked() )
            {
                greenButton->setChecked(true);
                checkedUpGreenButton.push_back(greenButton);
            }
        }
    }
    if ( checked == true )
    {
        AppState.SetState(t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION);
        // forced workaround: do form not modal
        hide();
        setGeometry(1175, 560, 0, 0); // set form to right bottom angle
        setModal(false);
        show();
    }
    else
    {
        // forced workaround: do form modal
        hide();
        setModal(true);
        setGeometry(oldLU_angle.x(), oldLU_angle.y(), oldWidth, oldHeight);
        show();
        for ( auto button: checkedUpGreenButton )
        {
            button->setChecked(false);
        }
        checkedUpGreenButton.clear();
        AppState.SetState(t_AppState::EDIT);
    }
}

void FunctionForm::on_EyeButton_clicked()
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE: case t_AppState::EDIT:
        QSound::play("Sounds/SoundForSwitch.wav");
        ui->labelSwitch->setPixmap( QPixmap("Images\\Left.png"));
        rInfoStore.RecordDataIntoInfoFile();
        RecordIntoFile();
        SetVisibleEditWidget(false);
        AppState.SetState(t_AppState::USE);
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void FunctionForm::on_EditButton_clicked()
{
    switch ( AppState.GetState() )
        {
        case t_AppState::USE: case t_AppState::EDIT:
            QSound::play("Sounds\\SoundForSwitch.wav");
            ui->labelSwitch->setPixmap( QPixmap("Images\\Right.png"));
            SetVisibleEditWidget(true);
            AppState.SetState(t_AppState::EDIT);
            break;
        case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
            AppState.ShowWrongOperationInCurrentStateMessage();
            break;
        default:
            assert(false);
        }
}
