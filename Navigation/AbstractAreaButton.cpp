#include "AbstractAreaButton.h"
#include "Navigation/t_Navigator.h"
#include <assert.h>
#include <QDebug>
#include <QDir>

extern t_Navigator Navigator;

void AbstractAreaButton::SetDirectoryName(const QString &newDirectoryName)
{
    assert( !isspace(newDirectoryName.right(1).toStdString().c_str()[0]) ); // the last symbol should be not space
    directoryName = newDirectoryName;
}

void AbstractAreaButton::SetDirectoryNameUsingPresentationName(const QString &presentationName)
{
    assert( presentationName.size() != 0 );
    assert( !isspace(presentationName.right(1).toStdString().c_str()[0]) ); // the last symbol should be not space
    assert( presentationName.right(1) != " ");

    directoryName.clear();
    for ( int i = 0; i < presentationName.size(); i++ )
    {
        if ( kProhibitedSymbolsInDirectoryName.contains( presentationName[i] ) )
        {
            directoryName.push_back("_");
        }
        else
        {
            directoryName.push_back( presentationName[i] );
        }
    }
}

void AbstractAreaButton::SetDirectoryNameUsingPresentationName(const QString &presentationName, const vector<QString>& namesOfDirsOnCurrentSlide)
{
    directoryName.clear();
    qDebug() <<namesOfDirsOnCurrentSlide;
    SetDirectoryNameUsingPresentationName(presentationName);
    bool isUnique = true;
    for ( auto name : namesOfDirsOnCurrentSlide )
    {
        if ( directoryName == name )
        {
            isUnique = false;
            break;
        }
    }
    if ( isUnique )
    {
        return;
    }


    int i = 2;
    while ( true )
    {
        isUnique = true;
        for ( auto name : namesOfDirsOnCurrentSlide )
        {
            if ( directoryName + QString::number(i) == name )
            {
                qDebug() <<"1"; //directoryName;
                isUnique = false;
                break;
            }
        }
        if ( isUnique )
        {
            directoryName = directoryName + QString::number(i);
            break;
        }
        i++;
        qDebug() << "2";
    }
}

void AbstractAreaButton::ResetDirectoryNameUsingPresentationName(const QString &NewPresentationName, const vector<QString>& namesOfDirsOnCurrentSlide)
{
    QString oldDirName = directoryName;

    QDir dir(Navigator.GetCurrentDirPath() );
    SetDirectoryNameUsingPresentationName(NewPresentationName, namesOfDirsOnCurrentSlide);
    qDebug() <<"old now namesOfDirs"<< oldDirName << directoryName << Navigator.GetCurrentDirPath() << namesOfDirsOnCurrentSlide;
    if ( oldDirName != directoryName )
    {
        assert( dir.rename(oldDirName, directoryName) );
    }
    if ( !Navigator.IsCurrentDirPathEqualsSwimmingDirPath() && oldDirName == Navigator.GetNextDirForCurrentDirPath() )
     {
        qDebug() << "old swim path" << Navigator.GetSwimDirPath();
        Navigator.PathChanged(oldDirName, directoryName );
        qDebug() << "new swim path"<<Navigator.GetSwimDirPath();
    }
}

const QString &AbstractAreaButton::GetDirectoryName() const
{
    return directoryName;
}

AbstractAreaButton::AbstractAreaButton(const QString& presentationName)
{
    SetDirectoryNameUsingPresentationName(presentationName);
}

AbstractAreaButton::AbstractAreaButton()
{
    directoryName = "!!!ERROR DIRECTORY NAME!!!";
}
