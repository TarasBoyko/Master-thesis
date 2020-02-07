#include "header.h"
#include "basebutton.h"
#include <QMouseEvent>
#include "SearchForm.h"
#include <Navigation/t_Navigator.h>

extern t_Navigator Navigator;


BaseButton::BaseButton(const QString& textOnButton,
                       const int &identifier,
                       const QPoint& UL_angle,
                       const int& newWidth,
                       const int& newHeight,
                       InfoStore* infoStore_,
                       SearchForm *parent_,
                       const double &newWidthForProportion,
                       const double &newHeightForProportion) :
    QPushButton( dynamic_cast<QWidget*>(parent_) )
{
    rInfoStore = infoStore_;
    searchForm = parent_;
    id = identifier;
    pEditSizeFrame = nullptr;
    pEditingName = nullptr;
    isProportional = false;
    heightForProportion = newHeightForProportion;
    widthForProportion = newWidthForProportion;

    setGeometry(UL_angle.x(), UL_angle.y(), newWidth, newHeight);
    setText(textOnButton);
    setMinimumSize(4*kEditSquareSize, 4*kEditSquareSize);
    show();
}

BaseButton::BaseButton(char* &p,
                       InfoStore* rInfoStore_,
                       SearchForm * parent_,
                       const double &newWidthForProportion,
                       const double &newHeightForProportion
                       ) :
    QPushButton(parent_)
{
    rInfoStore = rInfoStore_;
    searchForm = parent_;
    isProportional = false;
    widthForProportion = newWidthForProportion;
    heightForProportion = newHeightForProportion;

    // set text on button
    unsigned buttonNameLength = strchr(p, '|') - p;
    setText( QString::fromLatin1(p, buttonNameLength) );
    p = strchr(p, '|') + 1;

    // set button identifier
    id = atoi(p);
    p = strchr(p, '|') + 1;

    // set button geometry
    QRect rect;
    rect.setX( atoi(p)  );
    p = strchr(p, '|') + 1;
    rect.setY( atoi(p) );
    p = strchr(p, '|') + 1;
    rect.setWidth( atoi(p) );
    p = strchr(p, '|') + 1;
    rect.setHeight( atoi(p) );
    setGeometry(rect);

    // set else fields
    pEditSizeFrame = nullptr;
    pEditingName = nullptr;
    setMinimumSize(4*kEditSquareSize, 4*kEditSquareSize);
    show();

    //p = strchr(p, '\r') + 2;
    //p = strstr(p, kLn) + strlen(kLn); E:
}

int BaseButton::GetId()
{
    return id;
}

void BaseButton::SetId(const int &newId)
{
    id = newId;
}

// record BaseButton's parameters in file
// file should be open, file will not close
void BaseButton::RecordInFile(std::ofstream& file)
{
    file << text().toStdString() << '|'
         << id << '|'
         << x() << '|'
         << y() << '|'
         << width() << '|'
         << height() << '|';
}

BaseButton::~BaseButton()
{
    delete pEditingName;
    delete pEditSizeFrame;
    qDebug() << "deleteing "<<text() << id;
}

void BaseButton::SetEditingNameStyle()
{
    setStyleSheet("background-color: white;" // only change background-color
                  "border-style: solid;"
                  "border-width: 3px;"
                  "border-radius: 20px;"
                  "border-color: black;"
                  "padding: 10px;"
                  );
}

void BaseButton::SaveNewName_Slot()  // set new label and set usual style
{
    qDebug() << "save slot base";

    setText(pEditingName->toPlainText());
    pEditingName = nullptr;
}

void BaseButton::focusInEvent(QFocusEvent *)
{
    qDebug() << "BaseButton::IN FOCUS ";
    switch ( AppState.GetState() ) {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        break;
    case t_AppState::EDIT:
        qDebug() << "BaseButon focus in EditMode";
        raise();
        if ( pEditSizeFrame == nullptr )
        {
            pEditSizeFrame = new EditSizeFrame(this);
        }
        //if ( Editor.CURRENT_STATE == editor::state::MAKE_FUNCTION )
        //    ;

        break;
    default:
        assert(false);
    }
}

void BaseButton::focusOutEvent(QFocusEvent *)
{
    qDebug() << "BaseButton::OUT FOCUS ";
    switch ( AppState.GetState() ) {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        break;
    case t_AppState::EDIT:
        if ( pEditSizeFrame != nullptr )
        {
            delete pEditSizeFrame;
            pEditSizeFrame = nullptr;
            //qDebug() << "out focus";
        }
        break;
    default:
        assert(false);
    }
}

void BaseButton::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "pressed";
    switch ( AppState.GetState() )
    {
    case t_AppState::USE: case t_AppState::SELECT_ASSOC_BUTTONS_FOR_FUNCTION:
        break;
    case t_AppState::EDIT:
        delta.rx() = e->pos().x();
        delta.ry() = e->pos().y();
//        if ( Editor.CURRENT_STATE == editor::state::USUAL )
//        {
//            if ( _pEditFrame == nullptr )
//            {
//                _pEditFrame = new EightSquares(this);
//            }
//        }
        break;
    default:
        assert(false);
    }
}

void BaseButton::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << "BaseButton::mouseMoveEvent";
    qDebug() << e;
    switch ( AppState.GetState() ) {
    case t_AppState::USE:
        break;
    case t_AppState::EDIT:
        move(pos() + e->pos() - delta);
        break;
    default:
        assert(false);
    }
}

void BaseButton::mouseDoubleClickEvent(QMouseEvent *)
{

    switch ( AppState.GetState() )
    {
    case t_AppState::USE:
        break;
    case t_AppState::EDIT:
        SetEditingNameStyle();
        pEditingName = new EditingName(this);
        connect(pEditingName, SIGNAL(EditingNameFinished()), this, SLOT(SaveNewName_Slot()));
        pEditingName->setGeometry(0, 0, width(), height());
        pEditingName->setText( text() );
        pEditingName->selectAll();
        pEditingName->show();
        pEditingName->setAlignment(Qt::AlignCenter);
        pEditingName->setFocus();
        break;
    default:
        assert(false);
    }
}

void BaseButton::resizeEvent(QResizeEvent *)
{
    if ( isProportional )
    {
        setFixedHeight( width() * heightForProportion / widthForProportion ); // dimensions in pixels
    }
}

void BaseButton::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu* menu = new QMenu(this);
    menu->addAction("set", this, SLOT(SetProportional(bool)));
    menu->actions().at(0)->setCheckable(true);
    menu->actions().at(0)->setChecked(true);
    menu->addSeparator();
    //menu.addAction("Exit", qApp, SLOT(qApp->exit()));
    menu->exec(e->globalPos());
}

void BaseButton::SetProportional(const bool newIsProportional)
{
    isProportional = newIsProportional;
}
