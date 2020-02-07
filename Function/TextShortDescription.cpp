#include "TextShortDescription.h"
#include <QApplication>
#include <QDebug>

TextShortDescription::TextShortDescription(QWidget* obj) :
    QTextEdit(obj)
{
    setCursor(Qt::PointingHandCursor);
}

void TextShortDescription::enterEvent(QEvent* e)
{
    // not handle
    QApplication::sendEvent(parentWidget(), e);
}

void TextShortDescription::leaveEvent(QEvent* e)
{
    // not handle
    QApplication::sendEvent(parentWidget(), e);
}

void TextShortDescription::mouseReleaseEvent(QMouseEvent *e)
{
    // not handle
    QApplication::sendEvent(parentWidget(), e);
}

void TextShortDescription::mouseDoubleClickEvent(QMouseEvent *e)
{
    // not handle
    QApplication::sendEvent(parentWidget(), e);
}

void TextShortDescription::contextMenuEvent(QContextMenuEvent *e)
{
    QApplication::sendEvent(parentWidget(), e);
}
