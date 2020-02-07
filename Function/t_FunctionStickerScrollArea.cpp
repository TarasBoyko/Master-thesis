#include "Function/t_FunctionSticker.h"
#include "t_FunctionStickerScrollArea.h"
#include "ui_t_FunctionStickerScrollArea.h"
#include <QDebug>
#include <QPushButton>
#include <QScrollBar>


#include <typeinfo>

t_FunctionStickerScrollArea::t_FunctionStickerScrollArea(const QRect &startPos, InfoStore &rInfoStore_, QWidget *parent) :
    QScrollArea(parent),
    rInfoStore(rInfoStore_),
    ui(new Ui::t_FunctionStickerScrollArea)
{

    ui->setupUi(this);
    setGeometry(startPos);
    SetCurGeometryAsStartGeometry();

    int contentsLayoutTopMergin;
    int contentsLayoutBottomMergin;
    ui->verticalLayout->getContentsMargins( nullptr,
                                            &contentsLayoutTopMergin,
                                            nullptr,
                                            &contentsLayoutBottomMergin );
    fillingContentLine = contentsLayoutTopMergin;
    contentsLimit = ui->contents->height() - contentsLayoutBottomMergin;
    qDebug() <<"conten lim"<< contentsLimit<<fillingContentLine;
    //ui->verticalLayout->setSpacing(15);
    //this->widget()->setFixedWidth( width() /*- horizontalScrollBar()->width()*/ );
}

t_FunctionStickerScrollArea::~t_FunctionStickerScrollArea()
{
    delete ui;
}

// add new FuctionSticker to end of list
t_FunctionSticker* t_FunctionStickerScrollArea::AddSticker(SearchForm* newPSearchForm, const int& newFunctionsId, const QString &stickerText)
{
    t_FunctionSticker* newSticker = new t_FunctionSticker(newPSearchForm, rInfoStore);//(newFunctionsId, stickerText, this);
    newSticker->_functionsId = newFunctionsId;


    int nElementsInLayout  = ui->verticalLayout->count();
    //ui->verticalLayout->addWidget(newSticker);


    ui->verticalLayout->insertWidget(nElementsInLayout - 1, newSticker);



    //newSticker->show();
    //newSticker->updateGeometry();
    connect(newSticker, SIGNAL(HeightChanged(int)), this, SLOT(UpdateContentsHeight(int)));
    UpdateContentsHeight( kMinDocumentHeight + ui->verticalLayout->spacing() );

    newSticker->SetShortDescription(stickerText);
    selectedStickers.push_back(newSticker);

    return newSticker;
}

// delete (not remove) all t_FunctionSticker Widgets from layout and sett statr geomerty
void t_FunctionStickerScrollArea::Clear()
{
    selectedStickers.clear();
    int i = 0; // layout index
    QLayoutItem* item; // running QLayoutItem
    while ( (item = ui->verticalLayout->itemAt(i)) != 0 )
    {
        if ( item->widget() && (typeid(*item->widget()) == typeid(t_FunctionSticker)) )
        {
            delete item->widget();
        }
        else
        {
            i++;
        }
    }
    ui->contents->setFixedHeight(start_geometry.height());
    //setGeometry(start_geometry);
    ui->verticalLayout->getContentsMargins(nullptr, &fillingContentLine, nullptr, nullptr);
    UpdateContentsHeight(0);
}

void t_FunctionStickerScrollArea::SetCurGeometryAsStartGeometry()
{
    QRect rectForContent = geometry();
    rectForContent.setWidth( rectForContent.width() - 2 );
    rectForContent.setHeight( rectForContent.height() - 2 );
    start_geometry =  rectForContent;
}

QWidget *t_FunctionStickerScrollArea::GetContent()
{
    return ui->contents;
}

// update contents height , update fillingContentLine
void t_FunctionStickerScrollArea::UpdateContentsHeight(const int& delta)
{
    int topLayoutMergin;
    int bottomLayoutMergin;
    ui->contents->getContentsMargins(nullptr, &topLayoutMergin, nullptr, &bottomLayoutMergin);

    if ( delta == 0 )
    {
        ui->contents->setFixedHeight( start_geometry.height() );
        fillingContentLine = topLayoutMergin;
        //updateGeometry();
        //ui->contents->updateGeometry();
        return;
    }

    if ( fillingContentLine + delta + bottomLayoutMergin > contentsLimit )
    {
        ui->contents->setFixedHeight(fillingContentLine + delta + bottomLayoutMergin);

    }
    else
    {
        ui->contents->setFixedHeight( start_geometry.height() );
        //fillingContentLine = topLayoutMergin;
    }
    fillingContentLine = fillingContentLine + delta;
}
