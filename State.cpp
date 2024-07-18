#include <State.h>

State::State(StateID id)
: stateID(id)
{
    stateID = id;
}

State::~State() = default;

void State::OnStateEnter  () {}
void State::OnStateUpdate () {}
void State::OnStateExit   () {}

const StateID State::GetStateID() const  { return stateID; }