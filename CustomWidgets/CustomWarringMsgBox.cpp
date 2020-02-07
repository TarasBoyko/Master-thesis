#include "CustomWarringMsgBox.h"
#include <QIcon>

CustomWarringMsgBox::CustomWarringMsgBox(const QString& text, const QString& title)
{
    setWindowIcon( QIcon("Images\\lightning_iO0_icon.ico") );
    setIcon(QMessageBox::Warning);
    setWindowTitle(title);
    setText(text);
    setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
}
