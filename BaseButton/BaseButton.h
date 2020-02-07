#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QPushButton>
#include <QWindow>
#include <ostream>

//#include "greenbutton.h" // here was error
#include "EditingName.h"
#include "t_AppState.h"
#include "EditSizeFrame/EditSizeFrame.h"

extern t_AppState AppState;

class InfoStore;
class SearchForm;
class ofstream;

// base button for itself moving, edit size and label text
class BaseButton : public QPushButton
{
    Q_OBJECT

    friend class FunctionForm;


    QPoint delta; // delta to move BaseButton by a mouse



protected:
    int id;
    InfoStore* rInfoStore;
    EditSizeFrame* pEditSizeFrame;
    EditingName* pEditingName;
    SearchForm* searchForm;

    bool isProportional;
    double heightForProportion;
    double widthForProportion;


    virtual void SetUssualStyle() = 0;
    virtual void SetEditingNameStyle();

protected slots:
    virtual void SaveNewName_Slot();

    virtual void focusInEvent(QFocusEvent *);

    virtual void focusOutEvent(QFocusEvent *);
    void SetProportional(const bool newIsProportional);
public:
    virtual void mousePressEvent(QMouseEvent* e);

    virtual void mouseMoveEvent(QMouseEvent* e);

    virtual void mouseDoubleClickEvent(QMouseEvent* );
    virtual void resizeEvent(QResizeEvent *);
    virtual void contextMenuEvent(QContextMenuEvent*e);


public:
    explicit BaseButton(const QString& textOnButton,
                        const int &identifier,
                        const QPoint& UL_angle,
                        const int& newWidth,
                        const int& newHeight,
                        InfoStore *infoStore_,
                        SearchForm* parent_,
                        const double& newWidthForProportion,
                        const double& newHeightForProportion
                        );
    explicit BaseButton(char* &p, // pointer to string, where writen it's creation parameters
                        InfoStore* rInfoStore_,
                        SearchForm* parent_,
                        const double& newWidthForProportion,
                        const double& newHeightForProportion
                        );

    int GetId();
    void SetId(const int& newId);
    virtual void RecordInFile(std::ofstream& file);
    virtual ~BaseButton();
};

#endif // BASEBUTTON_H
