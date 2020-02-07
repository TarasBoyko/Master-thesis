#include "header.h"
#include "t_Navigator.h"
#include "CustomWidgets/CustomErrorMsgBox.h"

t_Navigator::t_Navigator()
{
    swimmingDirPath = currentDirPath = kAbsoluteRootDirName;
}

void t_Navigator::AppendDirToCurrentDirPath(const QString &appendingDir)
{
    if ( !IsCurrentDirPathEqualsSwimmingDirPath() && appendingDir == GetNextDirForCurrentDirPath() )
    {
        MoveCurrentDirPathForward();
    }
    else
    {
        currentDirPath = currentDirPath + kDirSeparatorInPath + appendingDir;
        swimmingDirPath = currentDirPath;
    }
}

const QString t_Navigator::GetCurrentDirPath() const
{
    return currentDirPath;
}

const QString t_Navigator::GetCurrentInfoFileName() const
{
    if ( QFile::exists(GetCurrentDirPath() + kDirSeparatorInPath + kAreaButtonInfoFileName) )
    {
        return kAreaButtonInfoFileName;
    }
    if ( QFile::exists(GetCurrentDirPath() + kDirSeparatorInPath + kGreenButtonInfoFileName) )
    {
        return kGreenButtonInfoFileName;
    }

    qDebug() << GetCurrentDirPath()<<kGreenButtonInfoFileName<<kAreaButtonInfoFileName;
    QApplication::beep();
    CustomErrorMsgBox("Info file not been finded!");
    exit(0);
}

const QString t_Navigator::GetFullCurrentPath() const
{
    return GetCurrentDirPath() + kDirSeparatorInPath + GetCurrentInfoFileName();
}

const QString t_Navigator::GetNextDirForCurrentDirPath() const
{
    assert(currentDirPath != swimmingDirPath );
    QString nextDir = swimmingDirPath;
    nextDir.remove( 0, currentDirPath.length() + kDirSeparatorInPath.length() );
    int nextDirLength = nextDir.indexOf(kDirSeparatorInPath);
    if ( nextDirLength != -1 )
    {
        nextDir = nextDir.left(nextDirLength);
    }
    assert( nextDir.indexOf(kDirSeparatorInPath) == -1 );
    assert( !nextDir.isEmpty() );
    return nextDir;
}

const QString t_Navigator::GetSwimDirPath() const
{
    return swimmingDirPath;
}

void t_Navigator::MoveCurrentDirPathForward()
{
    currentDirPath = currentDirPath + kDirSeparatorInPath + GetNextDirForCurrentDirPath();
}

void t_Navigator::PathChanged(const QString &lastAbstractAreabButtonName, const QString &newAbstractAreabButtonName)
{
    int numberOfLastUnchangedCharactersOfSwimmingDirPath = swimmingDirPath.size() - currentDirPath.size() - kDirSeparatorInPath.size() - lastAbstractAreabButtonName.size();
    swimmingDirPath = currentDirPath + kDirSeparatorInPath + newAbstractAreabButtonName + swimmingDirPath.right(numberOfLastUnchangedCharactersOfSwimmingDirPath);
}

void t_Navigator::CutSwimDirPath()
{
    swimmingDirPath = currentDirPath;
}

void t_Navigator::MoveCurrentDirPathBack()
{
    int newCurrentDirLength = currentDirPath.lastIndexOf(kDirSeparatorInPath);
    assert( newCurrentDirLength != -1 );
    currentDirPath = currentDirPath.left(newCurrentDirLength);
}

bool t_Navigator::IsCurrentDirPathEqualsSwimmingDirPath() const
{
    return currentDirPath == swimmingDirPath;
}

