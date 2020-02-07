#ifndef T_FUNCTIONSTICKERSCROLLAREA_H
#define T_FUNCTIONSTICKERSCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <vector>
#include <QMenu>
#include <QContextMenuEvent>

class t_FunctionSticker;
class SearchForm;
class InfoStore;
using std::vector;


namespace Ui {
class t_FunctionStickerScrollArea;
}

class t_FunctionStickerScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit t_FunctionStickerScrollArea(const QRect& startPos, InfoStore& rInfoStore_, QWidget *parent = 0);
    ~t_FunctionStickerScrollArea();

    t_FunctionSticker *AddSticker(SearchForm* newPSearchForm, const int &newFunctionsId, const QString& stickerText);
    void Clear();
    void SetCurGeometryAsStartGeometry();
    QWidget* GetContent();


private:
    QRect start_geometry;
    int contentsLimit;
    int fillingContentLine;
    InfoStore& rInfoStore;
    vector<t_FunctionSticker*> selectedStickers;
    Ui::t_FunctionStickerScrollArea *ui;
public slots:
    void UpdateContentsHeight(const int &delta);
};

#endif // T_FUNCTIONSTICKERSCROLLAREA_H
