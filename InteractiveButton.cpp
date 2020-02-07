#include "header.h"
#include "InteractiveButton.h"


InteractiveButton::InteractiveButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet("QPushButton{"
                  "border-radius: 0px transparent;"
                  "}"
                  );
}

void InteractiveButton::SetPictures(const QString& pathToImageOnHover,
                                    const QString& pathToImageOnNormalState,
                                    const QString& pathToImageOnPressed
                                    )
{
    iconOnHover = QIcon(pathToImageOnHover);
    iconOnNormalState = QIcon(pathToImageOnNormalState);
    iconOnPressed = QIcon(pathToImageOnPressed);
    setIcon(iconOnNormalState);
}

void InteractiveButton::enterEvent(QEvent *)
{
    // may be bug: for other event not need to do this check
    if ( !isEnabled() )
    {
        return;
    }

    setIcon(iconOnHover);
}

void InteractiveButton::leaveEvent(QEvent *)
{
    setIcon(iconOnNormalState);
}

void InteractiveButton::mousePressEvent(QMouseEvent *)
{
    setIcon(iconOnPressed);
    emit pressed();
}

void InteractiveButton::mouseReleaseEvent(QMouseEvent *e)
{
    setIcon(iconOnHover);
    if ( 0 <= e->pos().x() &&
         e->pos().x() <= width() &&
         0 <= e->pos().y() &&
         e->pos().y() <= height()
        )
    {
        emit clicked();
        toggle();
    }
}

void InteractiveButton::mouseMoveEvent(QMouseEvent *e)
{
    if ( 0 <= e->pos().x() &&
         e->pos().x() <= width() &&
         0 <= e->pos().y() &&
         e->pos().y() <= height()
        )
    {
        setIcon(iconOnPressed);
    }
    else
    {
        setIcon(iconOnNormalState);
    }

}
