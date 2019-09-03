#include "State.h"

Signal<int, int> State::SignalStateChange = Signal<int, int>();
int State::state = 0;

void State::setState(const int& _state) {
	const int oldState = state;
	state = _state;
	SignalStateChange.emit(oldState, state);
}

int State::getState() {
	return state;
}