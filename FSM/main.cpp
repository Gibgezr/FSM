#include <iostream>
#include "FSM.h"

enum ListOfBobStates {EATING = 0, SLEEPING, WORKING};

class BOB
{
public:
	float timer = 0;
	int tired = 0;
	int hungry = 0;
};

class BOB_eating : public FSMState<BOB>
{
	void OnEnter(){ parent->timer = 0; std::cout << "Bob is eatting." << std::endl; }
	void Update(float seconds)
	{
		parent->timer += seconds;
		if(parent->timer > 2)
		{
			parent->hungry = 0;
			fsm->ChangeState(WORKING);
			return;
		}
	}
	void OnExit() { std::cout << "Done eating, that was yummy!" << std::endl; }
};

class BOB_sleeping : public FSMState<BOB>
{
	void OnEnter(){ parent->timer = 0; std::cout << "Bob is sleeping." << std::endl; }
	void Update(float seconds)
	{
		parent->tired--;
		if(parent->tired < 1)
		{
			fsm->ChangeState(WORKING);
			return;
		}
	}
	void OnExit() { std::cout << "Done sleeping, I feel refreshed!" << std::endl; }
};

class BOB_working : public FSMState<BOB>
{
	void OnEnter(){ parent->timer = 0; std::cout << "Bob is working." << std::endl; }
	void Update(float seconds)
	{
		parent->tired++;
		if(parent->tired > 12)
		{
			fsm->ChangeState(SLEEPING);
			return;
		}

		parent->hungry++;
		if(parent->hungry > 4)
		{
			fsm->ChangeState(EATING);
			return;
		}
	}
	void OnExit() { std::cout << "Done sleeping, I feel refreshed!" << std::endl; }
};

int main()
{
	FSM<BOB> fsm(SLEEPING);
	BOB bob;
	BOB_eating b0;
	b0.parent = &bob;
	b0.fsm = &fsm;
	BOB_sleeping b1;
	b1.parent = &bob;
	b1.fsm = &fsm;
	BOB_working b2;
	b2.parent = &bob;
	b2.fsm = &fsm;
	fsm.states.push_back(&b0);
	fsm.states.push_back(&b1);
	fsm.states.push_back(&b2);

	for(int i = 0; i < 100; ++i)
		fsm.Update(0.5f);

	system("pause");

	return 0;
}