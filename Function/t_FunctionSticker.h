#ifndef T_FUNCTIONSTICKER_H
#define T_FUNCTIONSTICKER_H

#include <QWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>

class InfoStore;
class SearchForm;

namespace Ui {
class t_FunctionSticker;
}

const int kMinDocumentHeight = 21;

class t_FunctionSticker : public QWidget
{
    Q_OBJECT

    InfoStore& rInfoStore;

public:
    explicit t_FunctionSticker(SearchForm* newPSearchForm, InfoStore &rInfoStore_, QWidget *parent = 0);
    explicit t_FunctionSticker(SearchForm* newPSearchForm, const int& newFunctionsId, const QString& newText, InfoStore &rInfoStore_, QWidget *parent = 0);
    void SetShortDescription(const QString& newShortDescription);
    int _functionsId;
    ~t_FunctionSticker();
    virtual void contextMenuEvent(QContextMenuEvent *);

public slots:
    void on_shortDescription_textChanged();
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
    void DeleteMyself();


private:
    Ui::t_FunctionSticker *ui;
    int _oldShortDescriptionHeight;
    SearchForm* pSearchForm;

signals:
    void HeightChanged(int); // reports on how much has changed height
private slots:
    virtual void enterEvent(QEvent* );
    virtual void leaveEvent(QEvent* );
};

#endif // T_FUNCTIONSTICKER_H
