#include "CustomErrorMsgBox.h"
#include <QMessageBox.h>
#include <QIcon>

CustomErrorMsgBox::CustomErrorMsgBox(const QString& text, const QString& title)
{
    QMessageBox msgBox;
    msgBox.setWindowIcon( QIcon("Images\\lightning_iO0_icon.ico") );
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.exec();
}
