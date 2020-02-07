#ifndef T_NAVIGATOR_H
#define T_NAVIGATOR_H

#include <QString>

const QString kAbsoluteRootDirName = "root"; // related *.exe appication file
const QString kAreaButtonInfoFileName = "AreaButtonInfo.txt";
const QString kGreenButtonInfoFileName = "GreenButtonInfo.txt";
const QString kDirSeparatorInPath = "\\"; // directory separator in directory path
const QString kProhibitedSymbolsInDirectoryName = ".\\/:*?\"<>"; // first is tab


class t_Navigator
{
    QString swimmingDirPath; // path, where it is possible to go using forward button on form
    QString currentDirPath; // path, that is corresponding to current slide on form



public:
    explicit t_Navigator();

    void AppendDirToCurrentDirPath(const QString& appendingDir);
    void MoveCurrentDirPathBack();
    void MoveCurrentDirPathForward();
    void PathChanged(const QString& lastAbstractAreabButtonName, const QString& newAbstractAreabButtonName);
    void CutSwimDirPath();

    const QString GetCurrentDirPath() const;
    const QString GetCurrentInfoFileName() const;
    const QString GetFullCurrentPath() const;
    const QString GetNextDirForCurrentDirPath() const;
    const QString GetSwimDirPath() const;

    bool IsCurrentDirPathEqualsSwimmingDirPath() const;
};

#endif // T_NAVIGATOR_H
