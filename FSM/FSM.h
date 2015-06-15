#pragma once
#include <vector>

template <class entity_type>class FSM;

template <class entity_type>
class FSMState
{
public:
	FSM<entity_type> *fsm;
	entity_type *parent;
	virtual void Update(float seconds){}
	virtual void OnEnter(){}
	virtual void OnExit(){}
};

template <class entity_type>
class FSM
{
public:
	std::vector< FSMState<entity_type> * >states;
	int stateEnum;

	FSM(int startingState)
	{
		stateEnum = startingState;
	}

	void Update(float seconds)
	{
		states[stateEnum]->Update(seconds);
	}

	void ChangeState(int newState)
	{
		states[stateEnum]->OnExit();
		stateEnum = newState;
		states[stateEnum]->OnEnter();
	}
};