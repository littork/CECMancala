/*
UserInput.h

Dylan Pozarnsky

Allows user to type multicharacter inputs
*/

#pragma once

#include <Engine/Signal.h>

#include <string>

class UserInput {
private:
	UserInput() {};
public:
	static void init();
public:
	static Signal<std::string> SignalEntryEntered;
	static Signal<std::string, std::string> SignalEntryChanged;
private:
	static void input(const char& key);
public:
	static Slot_Scoped<char> SlotKeyPress;
public:
	static std::string get();
	static void clear();
protected:
	static std::string activeEntry;
};