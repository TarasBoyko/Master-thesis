#ifndef AREABUTTONFORM_H
#define AREABUTTONFORM_H

#include <QDialog>
#include <QString>
#include <vector>

using std::vector;

namespace Ui {
class AreaButtonForm;
}

class AreaButtonForm : public QDialog
{
    Q_OBJECT

    vector<QString> namesOfAreaButtonsOnCurrentSlide;

public:
    explicit AreaButtonForm(const QString& title, const vector<QString>& newNamesOfAreaButtonsOnCurrentSlide, QWidget *parent = 0);
    const QString GetName() const;
    const QString GetNameOfInfoFile() const;
    ~AreaButtonForm();

private slots:
    void on_name_textChanged(const QString &);

    void on_radioButtonOfAreaButtons_clicked();

    void on_radioButtonOfGreenButtons_clicked();

private:
    Ui::AreaButtonForm *ui;
    void CheckOKButton();
    bool IsTwoEqualAreaButtonNames();
};

#endif // AREABUTTONFORM_H
