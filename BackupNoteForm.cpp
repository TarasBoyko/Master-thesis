#include "BackupNoteForm.h"
#include "ui_BackupNoteForm.h"
#include <QPushButton>
#include <QDebug>

BackupNoteForm::BackupNoteForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackupNoteForm)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // take off ? sign from the window
    QRegExp regularExpression("[ ,_A-Za-z0-9]*");
    QValidator *validator = new QRegExpValidator(regularExpression, this);
    ui->note->setValidator(validator);
}

QString BackupNoteForm::GetNote() const
{
    return ui->note->text();
}

BackupNoteForm::~BackupNoteForm()
{
    delete ui;
}

void BackupNoteForm::on_note_textChanged(const QString &text)
{
    if ( text.right(1) == " " )
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
