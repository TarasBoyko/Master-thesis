#ifndef TEXTSHORTDESCRIPTION_H
#define TEXTSHORTDESCRIPTION_H

#include <QTextEdit>
#include <QMouseEvent>
#include <QApplication>


class TextShortDescription : public QTextEdit
{
public:
    explicit TextShortDescription(QWidget* obj = 0);
    virtual void enterEvent(QEvent* e);
    virtual void leaveEvent(QEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    void contextMenuEvent(QContextMenuEvent *e);
};

#endif // TEXTSHORTDESCRIPTION_H
