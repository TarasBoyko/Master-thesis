#ifndef ABSTRACTAREABUTTON_H
#define ABSTRACTAREABUTTON_H

#include <QString>
#include <vector>

using std::vector;

class AbstractAreaButton
{
    QString directoryName;
public:
    void SetDirectoryName(const QString& newDirectoryName);
    void SetDirectoryNameUsingPresentationName(const QString& presentationName);
    void SetDirectoryNameUsingPresentationName(const QString& presentationName, const vector<QString> &namesOfDirsOnCurrentSlide);
    void ResetDirectoryNameUsingPresentationName(const QString& NewPresentationName, const vector<QString>& namesOfDirsOnCurrentSlide);
    const QString& GetDirectoryName() const;
    AbstractAreaButton(const QString &presentationName);
    AbstractAreaButton();
};

#endif // ABSTRACTAREABUTTON_H
