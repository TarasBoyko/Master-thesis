#ifndef EDITINGNAME_H
#define EDITINGNAME_H

#include <QTextEdit>

// QTextEdit, which use for change labal of BaseButton in EDIT_MODE
class EditingName: public QTextEdit {
    Q_OBJECT
  signals:
    void EditingNameFinished();
  protected slots:
    void focusOutEvent(QFocusEvent* );

  public:
    explicit EditingName(QWidget* obj);
};
#endif // EDITINGNAME_H
