#include "header.h"
#include "SearchForm.h"
#include "ui_SearchForm.h"
#include "BackupNoteForm.h"
#include "CustomWidgets/CustomErrorMsgBox.h"
#include "CustomWidgets/CustomWarringMsgBox.h"
#include <QScrollBar>
#include <QDebug>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>
#include <QDir>
#include <QStyle>
#include <QSound>
#include <QDragMoveEvent>
#include <QPainter>
#include <QFileDialog>
#include <string>
#include <QVBoxLayout>
#include "GreenButton.h"
#include "t_AppState.h"
#include "Navigation/t_Navigator.h"
#include "Navigation/AreaButton.h"
#include "Function/t_FunctionSticker.h"
#include "Function/t_FunctionStickerScrollArea.h"
#include "Function/FunctionForm.h"
#include "FunctionalityForm/AbstractFunctionalityForm.h"
#include "FunctionalityForm/BaseFunctionalityForm.h"
#include "Navigation/AreaButtonForm.h"
#include <QMouseEvent>
#include <QDateTime>
#include <windows.h>

#include <ShellAPI.h>

t_AppState AppState(t_AppState::USE);
t_Navigator Navigator;

extern t_AppState AppState;

void SearchForm::GoIntoAreaButton(AreaButton *areaButton)
{
    assert(AppState.GetState() == t_AppState::USE || AppState.GetState() == t_AppState::EDIT || AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION);
    if (AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION )
    {
        AppState.ShowWrongOperationInCurrentStateMessage();
        return;
    }

    if ( AppState.GetState() == t_AppState::EDIT )
    {
        infoStore.RecordDataIntoInfoFile();
    }
    infoStore.SetIntoingAreaButton(areaButton);
    infoStore.Clear();
    Navigator.AppendDirToCurrentDirPath( areaButton->GetDirectoryName() );
    infoStore.FillFromInfoFile();
    if ( Navigator.GetCurrentInfoFileName() == kGreenButtonInfoFileName ) // if comming GreanButton state
    {
        UpdateFunctionList();
        scrollArea->show();
    }

    UpdateVisibleOfEditButtons();
    UpdateNavigationButtons();   
}

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm),
    infoStore(this)
{
    ui->setupUi(this);
    mapOfEditButtons = {
           {kAreaButtonInfoFileName, {ui->AddAreaButton, ui->SaveButton, ui->DoBackupButton} },
           {kGreenButtonInfoFileName, {ui->AddGreenButton, ui->AddFunction, ui->AddFlashButton, ui->SaveButton, ui->DoBackupButton} }
       };

    scrollArea = new t_FunctionStickerScrollArea(QRect(180,60,300,400), infoStore, this);
    connect(&infoStore, SIGNAL(SelectedFunctionsUpdated()), this, SLOT(UpdateFunctionList()));

    //QMouseEvent e(Qt::MouseButtonPress, Qt::LeftButton, QPointF(283,152), 315,497);
    //QApplication::postEvent()

    //scrollArea->GetContent()->layout()->addWidget(new QPushButton);

    //scrollArea->show();
    //t_FunctionSticker* p = scrollArea->AddSticker("new t_FunctionStickerfffffffffffffffffnew t_FunctionStickerfffffffffffffffff");



    // set pictures
    /*QWidget *w = new QWidget(this);
    w->show();
    w->raise();
    w->setGeometry(300,0, 40,20);
    QVBoxLayout* lay = new QVBoxLayout;
    //lay->setSpacing(0);
    w->setLayout(lay);
    QLineEdit* line_edit = new QLineEdit;

    w->layout()->addWidget(line_edit);
    w->setFixedHeight(line_edit->height());*/



    ui->BackButton->SetPictures("Images/BackHover.png", "Images/Back.png", "Images/BackPressed.png");
    ui->ForwardButton->SetPictures("Images/ForwardHover.png", "Images/Forward.png", "Images/ForwardPressed.png");
    ui->EyeButton->SetPictures("Images/EyeHover.png", "Images/Eye.png", "Images/EyePressed.png");
    ui->EditButton->SetPictures("Images/EditHover.png", "Images/Edit.png", "Images/EditPressed.png");
    ui->AddGreenButton->SetPictures("Images/AddButtonHover.png", "Images/AddButton.png", "Images/AddButtonPressed.png");
    ui->AddAreaButton->SetPictures("Images/AddAreaHover.png", "Images/AddArea.png", "Images/AddAreaPressed.png");
    ui->AddFunction->SetPictures("Images/AddFunctionHover.png", "Images/AddFunction.png", "Images/AddFunctionPressed.png");
    ui->AddFlashButton->SetPictures("Images/AddFlashButtonHover.png", "Images/AddFlashButton.png", "Images/AddFlashButtonPressed.png");
    ui->SaveButton->SetPictures("Images\\Save_Hover.png", "Images\\Save.png", "Images\\Save_Pressed.png");
    ui->DoBackupButton->SetPictures("Images/DoBackup_Hover.png", "Images/DoBackup.png", "Images/DoBackup_Pressed.png");
    ui->labelSwitch->setPixmap( QPixmap("Images\\Left.png"));
    setWindowIcon( QIcon("Images/lightning_iO0_icon.ico") );
    ui->labelSwitch->setScaledContents(true);

    // setting start state from
    ui->BackButton->setEnabled(false);
    ui->ForwardButton->setEnabled(false);
    scrollArea->hide();
    UpdateVisibleOfEditButtons();

    infoStore.FillFromInfoFile();
    scrollArea->SetCurGeometryAsStartGeometry();



    //(new t_FunctionSticker)->show();
    //fa->AddSticker("new t_FunctionSticker");
    //fa->AddSticker("00ne");
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::on_EyeButton_clicked()
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE:
        QSound::play("Sounds/SoundForSwitch.wav");
        break;
    case t_AppState::EDIT:
        if ( !CheckCurrentSlide() )
        {
            return;
        }
        QSound::play("Sounds/SoundForSwitch.wav");
        ui->labelSwitch->setPixmap( QPixmap("Images\\Left.png"));
        infoStore.RecordDataIntoInfoFile();      
        AppState.SetState(t_AppState::USE);
        UpdateVisibleOfEditButtons();
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void SearchForm::on_EditButton_clicked()
{
    switch ( AppState.GetState() )
    {
    case t_AppState::USE:
        QSound::play("Sounds/SoundForSwitch.wav");
        ui->labelSwitch->setPixmap( QPixmap("Images/Right.png"));
        AppState.SetState(t_AppState::EDIT);
        UpdateVisibleOfEditButtons();
        break;
    case t_AppState::EDIT:
        QSound::play("Sounds/SoundForSwitch.wav");
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void SearchForm::on_AddGreenButton_pressed()
{
    GreenButton* poolingButton = nullptr;
    int poolingButtonId = infoStore.GetNewGreenButtonId();;
    switch ( AppState.GetState() )
    {
    case t_AppState::EDIT :
        poolingButton = new GreenButton(  QString(""),
                                         poolingButtonId,
                                         QCursor::pos() - QPoint(120,120),
                                         111,
                                         111,
                                         &infoStore,
                                         this);

        PoolNewBaseButton(poolingButton, QRect(ui->line->geometry().bottomLeft(), rect().bottomRight()) );
        infoStore.AddBaseButton(poolingButton);
        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}


// show corresponding edit buttons in slide
void SearchForm::UpdateVisibleOfEditButtons()
{
    // TODO
    vector<QWidget*> visiableButtons = mapOfEditButtons[ Navigator.GetCurrentInfoFileName() ];
    assert( !visiableButtons.empty() );

    for ( auto button : vector<QWidget*>{ ui->AddAreaButton, // probably bug: children() does not work
                                          ui->AddGreenButton,
                                          ui->AddFunction,
                                          ui->AddFlashButton,
                                          ui->SaveButton,
                                          ui->DoBackupButton
                                        }
          )
    {
        button->hide();
    }
    switch ( AppState.GetState() )
    {
    case t_AppState::USE :
        break;
    case t_AppState::EDIT :
        for ( auto button : vector<QWidget*>{ ui->AddAreaButton, // probably bug: children() does not work
                                              ui->AddGreenButton,
                                              ui->AddFunction,
                                              ui->AddFlashButton,
                                              ui->SaveButton,
                                              ui->DoBackupButton
                                            }
              )
        {
            if ( std::find( visiableButtons.begin(), visiableButtons.end(), dynamic_cast<QWidget*>(button) ) != visiableButtons.end() )
            {
                button->show();
            }
        }
        break;
    default:
        assert(false);
    }

}

void SearchForm::on_AddFunction_clicked()
{
    FunctionForm* newF = nullptr;
    switch ( AppState.GetState() )
    {
    case t_AppState::EDIT :
        if ( !CheckCurrentSlide() )
        {
            return;
        }
        // TODO
        newF = new FunctionForm( infoStore.GetNewFunctionId(), true, infoStore);
        connect(newF,
                SIGNAL(FormCompleted(InfoStore::FunctionInfo, bool)),
                this,
                SLOT(FinishFunctionEditting(InfoStore::FunctionInfo, bool))
                );

        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void SearchForm::on_BackButton_clicked()
{
    assert(AppState.GetState() == t_AppState::USE || AppState.GetState() == t_AppState::EDIT || AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION);
    if (AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION )
    {
        AppState.ShowWrongOperationInCurrentStateMessage();
        return;
    }

    if ( !CheckCurrentSlide() )
    {
        CustomErrorMsgBox("slide is not checked");
        return;
    }
    qDebug() <<"CURRENT(old) "<< Navigator.GetCurrentDirPath() << "SWIM"<< Navigator.GetSwimDirPath();

    QSound::play("Sounds/SoundForArrow.wav");
    if ( Navigator.GetCurrentInfoFileName() == kGreenButtonInfoFileName ) // if leaving GreanButton state
    {
        scrollArea->hide();
        scrollArea->Clear();
    }
    if ( AppState.GetState() == t_AppState::EDIT )
    {
        infoStore.RecordDataIntoInfoFile();
    }
    infoStore.Clear();
    Navigator.MoveCurrentDirPathBack();
    infoStore.FillFromInfoFile();
    if ( Navigator.GetCurrentInfoFileName() == kGreenButtonInfoFileName ) // if comming GreanButton state
        {
            UpdateFunctionList();
            scrollArea->show();
        }

    UpdateVisibleOfEditButtons();
    UpdateNavigationButtons();
    qDebug() <<"CURRENT(now) "<< Navigator.GetCurrentDirPath() << "SWIM"<< Navigator.GetSwimDirPath();
}

void SearchForm::on_ForwardButton_clicked()
{
    assert(AppState.GetState() == t_AppState::USE || AppState.GetState() == t_AppState::EDIT || AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION);

    if (AppState.GetState() == t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION )
    {
        AppState.ShowWrongOperationInCurrentStateMessage();
        return;
    }

    if ( !CheckCurrentSlide() )
    {
        CustomErrorMsgBox("not cjecked slide");
        return;
    }

    QSound::play("Sounds/SoundForArrow.wav");
    if ( AppState.GetState() == t_AppState::EDIT )
    {
        infoStore.RecordDataIntoInfoFile();
    }
    infoStore.Clear();
    Navigator.MoveCurrentDirPathForward();
    infoStore.FillFromInfoFile();
    if ( Navigator.GetCurrentInfoFileName() == kGreenButtonInfoFileName ) // if comming GreanButton state
    {
        UpdateFunctionList();
        scrollArea->show();
    }

    UpdateVisibleOfEditButtons();
    UpdateNavigationButtons();
}

void SearchForm::on_AddAreaButton_pressed()
{
    AreaButton* newAreaButton = nullptr;
    AreaButtonForm* areaButtonForm = nullptr;
    QFile infoFile;
    QDir dirName;
    vector<QString> namesOfAreaButtonsOnCurrentSlide;
    vector<QString> namesOfAreaButtonDirsOnCurrentSlide;
    int poolingButtonId = infoStore.GetNewAreaButtonId();;

    switch ( AppState.GetState() )
    {
    case t_AppState::EDIT :
        if ( !CheckCurrentSlide() )
        {
            CustomErrorMsgBox("slide is not checked");
            return;
        }

        // pool new area button
        newAreaButton = new AreaButton( poolingButtonId,
                                        QCursor::pos() /*- parent->geometry().topLeft()*/ - QPoint(120,120),
                                        111,
                                        111,
                                        &infoStore,
                                        this);
        PoolNewBaseButton(newAreaButton, QRect(ui->line->geometry().bottomLeft(), rect().bottomRight()) );

        // define names of area button, what are on current slide
        for ( auto button : infoStore.areaButtons )
        {
            namesOfAreaButtonsOnCurrentSlide.push_back( button->text() );
            namesOfAreaButtonDirsOnCurrentSlide.push_back( button->GetDirectoryName() );
        }

        areaButtonForm = new AreaButtonForm("New area button", namesOfAreaButtonsOnCurrentSlide);
        switch ( areaButtonForm->exec() )
        {
        case QDialog::Accepted :
            // create corresponding directory and file of new area button
            newAreaButton->setText( areaButtonForm->GetName() );
            newAreaButton->SetDirectoryNameUsingPresentationName( areaButtonForm->GetName(), namesOfAreaButtonDirsOnCurrentSlide );

            assert ( dirName.cd( Navigator.GetCurrentDirPath() ) );
            dirName.mkdir( newAreaButton->GetDirectoryName() );
            infoFile.setFileName( Navigator.GetCurrentDirPath() +
                                  kDirSeparatorInPath +
                                  newAreaButton->GetDirectoryName() +
                                  kDirSeparatorInPath +
                                  areaButtonForm->GetNameOfInfoFile()
            );
            infoFile.open(QIODevice::WriteOnly);

            if ( areaButtonForm->GetNameOfInfoFile() == kAreaButtonInfoFileName )
            {
                infoFile.write( infoStore.kAreaChapterInInfoFile.c_str() );
                infoFile.write(" 0");
                infoFile.write(kLn);
            }
            else if ( areaButtonForm->GetNameOfInfoFile() == kGreenButtonInfoFileName )
            {
                infoFile.write( infoStore.kGreenChapterInInfoFile.c_str() );
                infoFile.write(" 0");
                infoFile.write(kLn);
            }
            else
            {
                assert(false);
            }
            infoFile.close();
            infoStore.AddBaseButton(newAreaButton);
            infoStore.RecordDataIntoInfoFile();
            qDebug() << "Now CREated "<< newAreaButton->GetDirectoryName();
            for ( auto button : infoStore.areaButtons )
            {
                qDebug() << button->GetDirectoryName();
            }

            delete areaButtonForm;
            break;
        case QDialog::Rejected :
            delete newAreaButton;
            delete areaButtonForm;
            break;
        default :
            assert(false);
        }

        break;
    case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        AppState.ShowWrongOperationInCurrentStateMessage();
        break;
    default:
        assert(false);
    }
}

void SearchForm::PoolNewBaseButton(BaseButton *poolingButton, QRect allowedRect)
{
    allowedRect = QRect();
    while ( QApplication::mouseButtons() == Qt::LeftButton )
    {
        poolingButton->move(QCursor::pos() - geometry().topLeft() - QPoint(18,18));
        QApplication::processEvents();
    }
    /*if ( !allowedRect.contains(poolingButton->geometry(), true)) TODO
    {
        delete poolingButton;
        return;
    }*/
}

void SearchForm::UpdateFunctionList()
{
    scrollArea->Clear();
    if ( !infoStore.IsAllGreenButtonsUnpressed() )
    {
        vector<t_FunctionSticker*> pSelectedFunctions;
        for ( auto function : infoStore.GetSelectedFunctions() )
        {
            t_FunctionSticker* newSticker = scrollArea->AddSticker(this, function.id, function.shortDescription);
            pSelectedFunctions.push_back(newSticker);
        }
        if ( scrollArea->GetContent()->height() < scrollArea->height() )
        {
            for ( auto sticker : pSelectedFunctions )
            {
                sticker->setFixedWidth( scrollArea->width() );
            }
        }
        else
        {
            for ( auto sticker : pSelectedFunctions )
            {
                qDebug() << "VERTICAL SCROLLBAR"<< scrollArea->verticalScrollBar()->width();
                sticker->setFixedWidth(scrollArea->width() - 17); // ERROR IN THE LIBRARY: 17 IS A SIZE OF SCROLLBAR, IT DOEN'S REFRESHED
                sticker->on_shortDescription_textChanged();
            }
        }
    }
}

void SearchForm::mousePressEvent(QMouseEvent *)
{
    setFocus();
}

void SearchForm::UpdateNavigationButtons()
{
    if ( Navigator.GetCurrentDirPath() == kAbsoluteRootDirName )
    {
        ui->BackButton->setEnabled(false);
    }
    else
    {
        ui->BackButton->setEnabled(true);
    }
    if ( Navigator.IsCurrentDirPathEqualsSwimmingDirPath() )
    {
        ui->ForwardButton->setEnabled(false);
    }
    else
    {
        ui->ForwardButton->setEnabled(true);
    }
}

// params must contain olny english letters
void SearchForm::copyDir(const QString& sourceDirName, const QString& destinationDirName)
{
    QDir sourceDir(sourceDirName);
    if ( !sourceDir.exists() )
    {
        return;
    }

    foreach (QString leafeDir, sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDirName + QDir::separator() + leafeDir;
        sourceDir.mkpath(destinationPath);
        copyDir(sourceDirName+ QDir::separator() + leafeDir, destinationPath);

    }

    foreach (QString leafeFile, sourceDir.entryList(QDir::Files))
    {
        QFile::copy(sourceDirName + QDir::separator() + leafeFile, destinationDirName + QDir::separator() + leafeFile);
    }
}

bool SearchForm::CheckCurrentSlide()
{
    // it is not necessary to check area button slide
    for ( auto button : infoStore.areaButtons )
    {
        if ( button->text().size() == 0 )
        {
            CustomErrorMsgBox("Area button must have a not empty name. Enter name of area button");
            return false;
        }
    }

    // check green slide
    for ( auto button : infoStore.greenButtons )
    {
        if ( button->text().size() == 0 )
        {
            CustomErrorMsgBox("Green button must have a not empty name. Enter name of green button");
            return false;
        }
    }

    return true;
}

void SearchForm::FinishFunctionEditting(InfoStore::FunctionInfo newFunction, bool isCreatedNewFunction)
{
    qDebug() << "new func"<<newFunction.id;
    if ( isCreatedNewFunction )
    {
        infoStore.AddFunction(newFunction);
    }
    else
    {
        //infoStore.GetReferenceToFunctionById(newFunction.id).associatedGreenButtonsId = infoStore.GetPressedGreenButtonIds();
        newFunction.associatedGreenButtonsId = infoStore.GetPressedGreenButtonIds();
    }
    infoStore.GetReferenceToFunctionById(newFunction.id) = newFunction;
    infoStore.RecordDataIntoInfoFile();

    infoStore.UnCheckPressedGreenButtons();
    scrollArea->Clear();
    infoStore.selectedFunctions = infoStore.functions;
    setFocus(); // to after closing FunctionForm don't arise EditSizeFrame on last focused GreenButton
}

void SearchForm::on_DoBackupButton_clicked()
{
    if ( !CheckCurrentSlide() )
    {
        return;
    }

    infoStore.RecordDataIntoInfoFile();

    // type note
    BackupNoteForm* backupNote = new BackupNoteForm;
    backupNote->show();
    QString note;
    switch ( backupNote->exec() ) {
    case QDialog::Accepted :
        note = backupNote->GetNote();
        if ( !note.isEmpty() )
        {
            note = "   " + note; // separator between data-time and note
        }
        QSound::play("Sounds\\Lightning.wav");
        break;
    case QDialog::Rejected :
        return;
    default:
        assert(false);
    }

    // create new backup item
    QString backupName = QDate::currentDate().toString("yyyy.MM.dd") + "---" + QTime::currentTime().toString("hh.mm.ss.zzz") + note;
    QDir newBackupItem;
    newBackupItem.mkdir(backupName);
    copyDir("F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\" + kAbsoluteRootDirName,
            "F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\" + backupName
    );

    // insert backup item into backup archive and remove unarchived backup item
    while ( QFile::exists("F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\archivingFlag.txt") )
    {
        Sleep(1);
    }
    QFile archivingFlag("F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\archivingFlag.txt");
    archivingFlag.open(QFile::WriteOnly);
    archivingFlag.close();

    string archiveCommand = "/C F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\ShortcutToWinRAR.lnk a -ep1 -r \"F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\Backup.rar\" \"F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\" + backupName.toStdString() + "\"";
    string removeUnarchivedBackupItemCommand = "rmdir /Q /S \"F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\" + backupName.toStdString() + "\"";
    string removeArchivingFlag = "rm F:\\Framework\\build-Framework-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\archivingFlag.txt";
    string commandToCMD = archiveCommand + " && " + removeUnarchivedBackupItemCommand + " && " + removeArchivingFlag;
    ShellExecuteA(
            NULL,
            "open",
            "cmd",
            commandToCMD.c_str(),
            "C:\\",
            SW_HIDE
    );

    QSound::play("Sounds\\Bell.wav");
}

#include <QIntValidator>
#include <QLineEdit>
void SearchForm::on_SaveButton_clicked()
{
    if ( !CheckCurrentSlide() )
    {
        return;
    }

    infoStore.RecordDataIntoInfoFile();
    QSound::play("Sounds\\Lightning.wav");

}

void SearchForm::on_AddFlashButton_clicked()
{
    if ( !CheckCurrentSlide() )
    {
        return;
    }

    //AbstractFunctionalityForm* p = new BaseFunctionalityForm(0,0,infoStore);
    //p->show();
    CustomWarringMsgBox msgBox("SukaSukaSukaSukaSukaSukaSukaSukaSukaSuka","t");
    //msgBox.exec();

}
