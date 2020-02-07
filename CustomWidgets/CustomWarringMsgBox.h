#ifndef CUSTOMWARRINGMSGBOX_H
#define CUSTOMWARRINGMSGBOX_H

#include <QMessageBox>

class CustomWarringMsgBox : public QMessageBox
{
public:
    CustomWarringMsgBox(const QString& text, const QString& title = "Warring");
};

#endif // CUSTOMWARRINGMSGBOX_H
