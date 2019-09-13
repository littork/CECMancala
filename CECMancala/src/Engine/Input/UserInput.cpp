#include "UserInput.h"

#include <Engine/Input/Input.h>
#include <Engine/Input/Keys.h>

Signal<std::string> UserInput::SignalEntryEntered = Signal<std::string>();
Signal<std::string, std::string> UserInput::SignalEntryChanged = Signal<std::string, std::string>();
Slot_Scoped<char> UserInput::SlotKeyPress = Slot_Scoped<char>();
std::string UserInput::activeEntry = "";

std::string UserInput::get() {
	return activeEntry;
}

void UserInput::clear() {
	std::string initialEntry = activeEntry;
	activeEntry = "";
	SignalEntryChanged.emit(initialEntry, activeEntry);
}

void UserInput::input(const char& key) {
	if (key == Key::Return) {
		if (activeEntry.length()) {
			std::string initialEntry = activeEntry;
			activeEntry = "";
			SignalEntryEntered.emit(initialEntry);
			SignalEntryChanged.emit(initialEntry, activeEntry);
		}
		return;
	}

	if (key == Key::Backspace) {
		if (activeEntry.length()) {
			std::string initialEntry = activeEntry;
			activeEntry = activeEntry.substr(0, activeEntry.length() - 1);
			SignalEntryChanged.emit(initialEntry, activeEntry);
		}
		return;
	}

	if (key >= 'A' && key <= 'Z') {
		std::string initialEntry = activeEntry;
		activeEntry += key;
		SignalEntryChanged.emit(initialEntry, activeEntry);
		return;
	}
}

void UserInput::init() {
	SlotKeyPress = Input::SignalKeyPress.connect(&input);
}