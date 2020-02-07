#include "header.h"
#include "t_AppState.h"
#include "SearchForm.h"
#include "CustomWidgets/CustomErrorMsgBox.h"

t_AppState::t_AppState(const t_AppState::STATE_ENUM& currentState_)
{
    currentState = currentState_;
}

const t_AppState::STATE_ENUM& t_AppState::GetState() const
{
    return currentState;
}

void t_AppState::SetState(const STATE_ENUM& newState)
{
    currentState = newState;
}

void t_AppState::ShowWrongOperationInCurrentStateMessage() const
{
   CustomErrorMsgBox("It is not possible to do this operation in current state");
}
