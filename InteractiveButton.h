#ifndef INTERACTIVEBUTTON_H
#define INTERACTIVEBUTTON_H

#include <QPushButton>
#include <QString>

// transparent interactive button
class InteractiveButton : public QPushButton
{
    Q_OBJECT

    // all these 3 paths are relative
    QIcon iconOnHover; // ... by mouse
    QIcon iconOnNormalState; // ... when it is no actions from mouse under this button
    QIcon iconOnPressed; // ... by mouse

public:
    explicit InteractiveButton(QWidget *parent = 0);
    void SetPictures(const QString& pathToImageOnHover,
                     const QString& pathToImageOnNormalState,
                     const QString& pathToImageOnPressed
                     );

protected:
    virtual void enterEvent(QEvent *);

    virtual void leaveEvent(QEvent *);

    virtual void mousePressEvent(QMouseEvent * );

    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void mouseMoveEvent(QMouseEvent * e);

};

#endif // INTERACTIVEBUTTON_H
