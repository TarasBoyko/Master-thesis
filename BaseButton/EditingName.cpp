#include "header.h"
#include "EditingName.h"

EditingName::EditingName(QWidget *obj): QTextEdit(obj)
{
    ;
}

void EditingName::focusOutEvent(QFocusEvent *)
{
    emit EditingNameFinished();
    delete this;
}
