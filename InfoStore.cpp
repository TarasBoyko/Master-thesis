#include "InfoStore.h"
#include "Navigation/AreaButton.h"
#include "GreenButton.h"
#include "Navigation/t_Navigator.h"
#include "header.h"
#include <QDir>

extern t_Navigator Navigator;

static int kNumReservedFunctions = 300;

void InfoStore::Clear()
{
    for ( auto item : areaButtons )
    {
        if (item != intoingAreaButton)
        {
            delete item;
        }
    }
    areaButtons.clear();
    for ( auto item : greenButtons )
    {
        delete item;
    }
    greenButtons.clear();
    functions.clear();
    selectedFunctions.clear();
}

InfoStore::InfoStore(SearchForm * const parentOfElements_) :
    parentOfElements(parentOfElements_)
{
    intoingAreaButton = nullptr;
    areaButtons.reserve(50);
    greenButtons.reserve(50);
    functions.reserve(kNumReservedFunctions);
    selectedFunctions.reserve(kNumReservedFunctions);
}

void InfoStore::SetIntoingAreaButton(AreaButton* newIntoingAreaButton)
{
    if (intoingAreaButton != nullptr)
    {
        qDebug() << "deleting intoingAreaButton";
        delete intoingAreaButton;
    }
    intoingAreaButton = newIntoingAreaButton;
    intoingAreaButton->hide();
}

void InfoStore::IntersectSelectedFunctions(GreenButton* const pressedButton)
{
    vector<FunctionInfo> newSelectedFunctions;
    newSelectedFunctions.reserve(kNumReservedFunctions);
    for ( unsigned int i = 0; i < selectedFunctions.size(); i++ )
    {
        if ( selectedFunctions[i].associatedGreenButtonsId.find(pressedButton->GetId())
             !=
             selectedFunctions[i].associatedGreenButtonsId.end() )
        {
            newSelectedFunctions.push_back( selectedFunctions[i] );
        }
    }
    selectedFunctions = newSelectedFunctions;
    emit SelectedFunctionsUpdated();
}

void InfoStore::MergeSelectedFunctions()
{
    selectedFunctions.clear();

    set<int> pressedGreenButtonIds = GetPressedGreenButtonIds();
    for ( unsigned int i = 0; i < functions.size(); i++ )
    {
        if ( includes(functions[i].associatedGreenButtonsId.begin(),
                      functions[i].associatedGreenButtonsId.end(),
                      pressedGreenButtonIds.begin(),
                      pressedGreenButtonIds.end()
                      )
           )
        {
            selectedFunctions.push_back( functions[i] );
        }
    }

    emit SelectedFunctionsUpdated();

    // sorting function info to record into file in order
    //sort()
}

void InfoStore::FillFromInfoFile()
{
    ifstream infoFile(Navigator.GetFullCurrentPath().toStdString().c_str() , ios::in|ios::binary);
    // define number symbols of file and
    infoFile.seekg(0, std::ios_base::end);
    ios::pos_type numberSymbolsInInfoFile = infoFile.tellg();
    infoFile.seekg(0);

    char* p = new char[numberSymbolsInInfoFile]; // read pointer in infoFile
    infoFile.read(p, numberSymbolsInInfoFile);

    // read AreaButtons chapter
    if ( strstr( p, (kAreaChapterInInfoFile + " ").c_str() ) != NULL ) // if is AreaButtons chapter in info file
    {
        p = strstr( p, (kAreaChapterInInfoFile + " ").c_str() ) + (kAreaChapterInInfoFile + " ").size();
        int numberAreaButtons = atoi(p);
        areaButtons.resize(numberAreaButtons);
        p = strstr(p, kLn) + strlen(kLn);
        for( unsigned i = 0; i < areaButtons.size(); i++ )
        {
            areaButtons[i] = new AreaButton(p, this, parentOfElements);
            p = strstr(p, kLn) + strlen(kLn);
        }

    }

    // read GreenButton chapter
    if ( strstr( p, (kGreenChapterInInfoFile + " ").c_str() ) != NULL ) // if is GreenButton chapter in info file
    {
        p = strstr( p, (kGreenChapterInInfoFile + " ").c_str() ) + (kGreenChapterInInfoFile + " ").size();
        int numberGreenButtons = atoi(p);
        greenButtons.resize(numberGreenButtons);
        p = strstr(p, kLn) + strlen(kLn);
        for( unsigned i = 0; i < greenButtons.size(); i++ )
        {
            greenButtons[i] = new GreenButton(p, this, parentOfElements);
            p = strstr(p, kLn) + strlen(kLn);
        }

    }

    // read FlashButton chapter TODO

    // read functions chapter
    if ( strstr( p, (kFunctionChapterInInfoFile + " ").c_str() ) != NULL ) // if is function chapter in info file
    {
        p = strstr( p, (kFunctionChapterInInfoFile + " ").c_str() ) + (kFunctionChapterInInfoFile + " ").size();
        int numberFunctions = atoi(p);
        functions.resize(numberFunctions);
        p = strstr(p, kLn) + strlen(kLn);
        for( unsigned i = 0; i < functions.size(); i++ )
        {
            // read functions id
            functions[i].id = atoi(p);
            p = strchr(p, '|') + 1;

            // read short description of function
            char * pEndFunDescription = strchr(p, '|');
            functions[i].shortDescription = QLatin1String(p, pEndFunDescription - p) ;
            p = pEndFunDescription + 1;

            // read associated buttons of function
            while ( strstr(p, kLn) != p ) // while not end of line
            {
                functions[i].associatedGreenButtonsId.insert( atoi(p) );
                p = strchr(p, ',') + 1;
            }
            p = strstr(p, kLn) + strlen(kLn);

            selectedFunctions = functions;
        }
    }
    infoFile.close();


}

void InfoStore::ReadBaseButtonDataFromInfoFile(char* &rp, // reference to read pointer in infoFile
                                               QString &text,
                                               int &identidier,
                                               QRect &rect
                                               )
{
    unsigned buttonNameLength = strchr(rp, '|') - rp;

    text = QString::fromLatin1(rp, buttonNameLength);
    rp = strchr(rp, '|') + 1;

    identidier = atoi(rp);
    rp = strchr(rp, '|') + 1;

    rect.setX( atoi(rp)  );
    rp = strchr(rp, '|') + 1;
    rect.setY( atoi(rp) );
    rp = strchr(rp, '|') + 1;
    rect.setWidth( atoi(rp) );
    rp = strchr(rp, '|') + 1;
    rect.setHeight( atoi(rp) );

    //p = strchr(p, '\r') + 2;
    rp = strstr(rp, kLn) + strlen(kLn);

        //pButtons[i] = new AreaButton(pSearchForm);
//        pButtons[i]->setText( newTextOnButton );
//        pButtons[i]->id = newId;

        /*if ( Navigator.getCurrentWay() == Navigator.getCurrentDirWay() + "\\GreenButtonInfo.txt" )
        {
            Finder.pFunStickersScrollArea->show();

                pButtons[i] = new GreenButton(newId,
                                              RunningRect.topLeft(),
                                              RunningRect.width(),
                                              RunningRect.height(),
                                              newTextOnButton,
                                              pSearchForm->infoStore,
                                              pSearchForm);
        }
        if ( Navigator.getCurrentWay() == Navigator.getCurrentDirWay() + "\\AreaButtonInfo.txt" )
        {
            Finder.pFunStickersScrollArea->hide();
                pButtons[i] = new AreaButton( newId,
                                              RunningRect.topLeft(),
                                              RunningRect.width(),
                                              RunningRect.height(),
                                              newTextOnButton,
                                              pSearchForm->infoStore,
                                              pSearchForm);
        }*/
        //pButtons[i]->setGeometry( RunningRect );
        //pButtons[i]->setIconSize( QSize(pButtons[i]->width(), pButtons[i]->height()) ); // icon size = size
}

void InfoStore::RecordDataIntoInfoFile()
{
    std::ofstream infoFile(Navigator.GetFullCurrentPath().toStdString().c_str(), ios::out|ios::binary);

    // record data about AreaButtons
    if ( Navigator.GetCurrentInfoFileName() == kAreaButtonInfoFileName )
    {
        infoFile << kAreaChapterInInfoFile << " " << areaButtons.size() << kLn;
    }
    if ( !areaButtons.empty() )
    {
        for( unsigned i = 0; i < areaButtons.size(); i++ )
        {
            areaButtons[i]->RecordInFile(infoFile);
            infoFile << kLn;
        }
    }


    // record data about GreenButtons
    if ( !greenButtons.empty() )
    {
        infoFile << kGreenChapterInInfoFile << " " << greenButtons.size() << kLn;
        for( unsigned i = 0; i < greenButtons.size(); i++ )
        {
            infoFile << greenButtons[i]->text().toStdString() << '|'
                     << greenButtons[i]->GetId() << '|'
                     << greenButtons[i]->x() << '|'
                     << greenButtons[i]->y() << '|'
                     << greenButtons[i]->width() << '|'
                     << greenButtons[i]->height() << '|'
                     << kLn;
        }
    }

    // record data about FlashButton TODO

    // record data about functions
    if ( !functions.empty() )
    {
        infoFile << kFunctionChapterInInfoFile << " " << functions.size() << kLn;
        for( unsigned i = 0; i < functions.size(); i++ )
        {
            infoFile << functions[i].id << '|' << functions[i].shortDescription.toStdString() << "|";
            // record associated GreenButtons
            for ( auto buttonId : functions[i].associatedGreenButtonsId )
            {
                infoFile << buttonId << ',';
            }
            infoFile << kLn;
        }
    }

    infoFile.close();
}

void InfoStore::DeleteGreenButton(GreenButton * const deletingButton)
{
    const int deletingButtonId = deletingButton->GetId();
    // delete deleting button's id in associates GreenButtons of functions
    for ( unsigned i = 0; i < functions.size(); i++ )
    {
        if ( functions[i].associatedGreenButtonsId.find(deletingButtonId)
             !=
             functions[i].associatedGreenButtonsId.end()
           )
        {
            functions[i].associatedGreenButtonsId.erase(deletingButtonId);
        }
    }

    // delete deletingButton from InfoStore
    greenButtons.erase( find(greenButtons.begin(), greenButtons.end(), deletingButton) );

    // decrement id of GreenButton, which id >= id of deleting button
    for ( auto& button : greenButtons )
    {
        if ( button->GetId() > deletingButtonId )
        {
            button->SetId( button->GetId() - 1 );
        }
    }

    // for each function (which id >= id of deleting button) i-associatedButton becomes i-1-associatedButton
    for ( auto& function : functions )
    {
        for ( auto& buttonId : function.associatedGreenButtonsId )
        {
            if ( function.associatedGreenButtonsId.find(buttonId) != function.associatedGreenButtonsId.end()
                 &&
                 buttonId > deletingButtonId
               )
            {
                function.associatedGreenButtonsId.erase(buttonId);
                function.associatedGreenButtonsId.insert(buttonId - 1);
            }
        }
    }
}

void InfoStore::DeleteAreaButton(AreaButton * const deletingButton)
{
    const int deletingButtonId = deletingButton->GetId();
    // delete deletingButton from InfoStore
    areaButtons.erase( find(areaButtons.begin(), areaButtons.end(), deletingButton) );

    // decrement id of AreaButton, which id >= id of deleting button
    for ( auto& button : areaButtons )
    {
        if ( button->GetId() > deletingButtonId )
        {
            button->SetId( button->GetId() - 1 );
        }
    }

    // remove corresponding directory
    QDir correspondingDirectory( Navigator.GetCurrentDirPath() + "\\" + deletingButton->GetDirectoryName() );
    qDebug() << Navigator.GetCurrentDirPath() + "\\" + deletingButton->GetDirectoryName();
    assert( correspondingDirectory.exists() );
    assert ( correspondingDirectory.removeRecursively() );
    RecordDataIntoInfoFile();
}

bool InfoStore::IsAllGreenButtonsUnpressed() const
{
    return GetPressedGreenButtonIds().empty();
}

bool InfoStore::IsFunctionWithSingleAssocGreenButton(GreenButton *button, InfoStore::FunctionInfo& poorFunction)
{
    for ( auto function : functions )
    {
        if ( function.associatedGreenButtonsId.size() == 1 &&
             (function.associatedGreenButtonsId.find(button->GetId()) != function.associatedGreenButtonsId.end())
           )
        {
            poorFunction = function;
            return true;
        }
    }
    return false;
}

vector<InfoStore::FunctionInfo> InfoStore::GetSelectedFunctions() const
{
    return selectedFunctions;
}

int InfoStore::GetNewAreaButtonId() const
{
    int maxId = 0;
    if ( areaButtons.empty() )
    {
        return 0;
    }
    for ( auto button : areaButtons )
    {
        if ( button->GetId() > maxId )
        {
            maxId = button->GetId();
        }
    }
    return maxId + 1;
}

int InfoStore::GetNewGreenButtonId() const
{
    int maxId = 0;
    if ( greenButtons.empty() )
    {
        return 0;
    }
    for ( auto button : greenButtons )
    {
        if ( button->GetId() > maxId )
        {
            maxId = button->GetId();
        }
    }
    return maxId + 1;
}

int InfoStore::GetNewFunctionId() const
{
    int maxId = 0;
    if ( functions.empty() )
    {
        return 0;
    }
    for ( auto button : functions )
    {
        if ( button.id > maxId )
        {
            maxId = button.id;
        }
    }
    return maxId + 1;
}

InfoStore::FunctionInfo &InfoStore::GetReferenceToFunctionById(const int &id)
{
    for ( unsigned i = 0; i < functions.size(); i++ )
    {
        if ( functions[i].id == id )
        {
            return functions[i];
        }
    }
    assert(false);
    return functions[0]; // to take off warring
}

set<int> InfoStore::GetPressedGreenButtonIds() const
{
    set<int> pressedGreenButtonIds;
    for ( auto button : greenButtons )
    {
        if ( button->isChecked() )
        {
            pressedGreenButtonIds.insert( button->GetId() );
        }
    }
    return pressedGreenButtonIds;
}

void InfoStore::AddBaseButton(BaseButton *insertingButton)
{
    // cannot do it by switch

    if ( typeid(*insertingButton) == typeid(AreaButton) )
    {
        areaButtons.push_back( dynamic_cast<AreaButton*>(insertingButton) );
    }
    else if ( typeid(*insertingButton) == typeid(GreenButton) )
    {
        greenButtons.push_back( dynamic_cast<GreenButton*>(insertingButton) );
    }
    else
    {
        assert(false);
    }
}

void InfoStore::AddFunction(FunctionInfo newFunction)
{

    // fill FunctionInfo structure ( FunctionInfo.shortDescription has filled )
    newFunction.id = GetNewFunctionId();
    set<int> pressedGreenButtonIds = GetPressedGreenButtonIds();
    newFunction.associatedGreenButtonsId = pressedGreenButtonIds;

    functions.push_back(newFunction);

    // add it to selected function if it is corresponds to the criteries
    if ( includes(newFunction.associatedGreenButtonsId.begin(),
                  newFunction.associatedGreenButtonsId.end(),
                  pressedGreenButtonIds.begin(),
                  pressedGreenButtonIds.end()
                  )
       )
    {
        selectedFunctions.push_back( newFunction );
    }

    //
}

void InfoStore::UnCheckPressedGreenButtons()
{
    for ( auto& button : greenButtons )
    {
        if ( button->isChecked() )
        {
            button->setChecked(false);
        }
    }
}

void InfoStore::DeleteFunctionById(const int &id)
{
    bool isDeletedFunction = false;
    bool isDeletedSelectedFunction = false;
    for ( unsigned i = 0; i < functions.size(); i++ )
    {
        if ( functions[i].id == id )
        {
            functions.erase( functions.begin() + i );
            isDeletedFunction = true;
            break;
        }
    }
    for ( unsigned i = 0; i < selectedFunctions.size(); i++ )
    {
        if ( selectedFunctions[i].id == id )
        {
            selectedFunctions.erase( selectedFunctions.begin() + i );
            isDeletedSelectedFunction = true;
            break;
        }
    }
    assert(isDeletedFunction && isDeletedSelectedFunction);

    for (unsigned i = 0; i < functions.size(); i++ )
    {
        if ( functions[i].id > id )
        {
            --functions[i].id;
        }
    }
    for (unsigned i = 0; i < selectedFunctions.size(); i++ )
    {
        if ( selectedFunctions[i].id > id )
        {
            --selectedFunctions[i].id;
        }
    }
    RecordDataIntoInfoFile();
}
