#ifndef T_APPSTATE_H
#define T_APPSTATE_H

#include <QWidget>

class t_AppState
{
public:
   enum STATE_ENUM { USE, EDIT, SELECT_ASSOC_BUTTONS_FOR_FUNCTION};

private:
   STATE_ENUM currentState;

public:

   t_AppState(const t_AppState::STATE_ENUM& currentState_);
   const STATE_ENUM& GetState() const;
   void SetState(const STATE_ENUM& newState);

   // ... when it is not possible to do this operation in current state
   void ShowWrongOperationInCurrentStateMessage() const;

};



#endif // T_APPSTATE_H

