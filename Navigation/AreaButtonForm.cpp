#include "AreaButtonForm.h"
#include "ui_AreaButtonForm.h"
#include "Navigation/t_Navigator.h"
#include <assert.h>
#include <QPushButton>
#include <QDebug>

AreaButtonForm::AreaButtonForm(const QString &title, const vector<QString> &newNamesOfAreaButtonsOnCurrentSlide, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreaButtonForm)
{
    namesOfAreaButtonsOnCurrentSlide = newNamesOfAreaButtonsOnCurrentSlide;

    ui->setupUi(this);
    setWindowTitle(title);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // take off ? sign from the window
    setWindowIcon( QIcon("Images/lightning_iO0_icon.ico") ); // probebly bug: not set in design mode

    QString regString = "[a-zA-Z0-9\\`\\~\\!\\@\\#\\$\\%\\^\\&\\*\\(\\)\\-\\_\\=\\+\\/\\[\\{\\]\\}\\\\\\|\\;\\:\\'\\\"\\,\\<\\.\\>\\?\\ ]*";
    QRegExp regularExpression(regString);
    QValidator *validator = new QRegExpValidator(regularExpression, this);
    ui->name->setValidator(validator);
    on_name_textChanged( ui->name->text() );
}

const QString AreaButtonForm::GetName() const
{
    return ui->name->text();
}

const QString AreaButtonForm::GetNameOfInfoFile() const
{
    if ( ui->radioButtonOfAreaButtons->isChecked() )
    {
        return kAreaButtonInfoFileName;
    }
    if ( ui->radioButtonOfGreenButtons->isChecked() )
    {
        return kGreenButtonInfoFileName;
    }
    assert(false);
    return QString(""); // to take off warring
}

AreaButtonForm::~AreaButtonForm()
{
    qDebug() << "deleting AreaButtonForm";
    delete ui;
}

void AreaButtonForm::on_name_textChanged(const QString&)
{
    if ( IsTwoEqualAreaButtonNames() )
    {
        ui->errorTextLabel->setText("There are two equal area button names");
    }
    else
    {
        ui->errorTextLabel->setText("");
    }
    CheckOKButton();
}

void AreaButtonForm::on_radioButtonOfAreaButtons_clicked()
{
    CheckOKButton();
}

void AreaButtonForm::on_radioButtonOfGreenButtons_clicked()
{
    CheckOKButton();
}

void AreaButtonForm::CheckOKButton()
{
    bool isTwoEqualAreaButtonNames = IsTwoEqualAreaButtonNames();

    if ( ui->name->text().size() == 0 ||
         ui->name->text().right(1) == " " ||
         isTwoEqualAreaButtonNames ||
         ( !ui->radioButtonOfAreaButtons->isChecked() && !ui->radioButtonOfGreenButtons->isChecked() )
       )
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false); // TODO not set enablef(false) completly
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

bool AreaButtonForm::IsTwoEqualAreaButtonNames()
{
    for ( auto name : namesOfAreaButtonsOnCurrentSlide )
    {
        if ( name == ui->name->text() )
        {
            return true;
        }
    }
    return false;
}
