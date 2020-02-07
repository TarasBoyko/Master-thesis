#ifndef BACKUPNOTEFORM_H
#define BACKUPNOTEFORM_H

#include <QDialog>

namespace Ui {
class BackupNoteForm;
}

class BackupNoteForm : public QDialog
{
    Q_OBJECT

public:
    explicit BackupNoteForm(QWidget *parent = 0);
    QString GetNote() const;
    ~BackupNoteForm();

private slots:
    void on_note_textChanged(const QString &text);

private:
    Ui::BackupNoteForm *ui;
};

#endif // BACKUPNOTEFORM_H
