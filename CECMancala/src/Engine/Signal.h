/*
Signal.h

Dylan Pozarnsky

Header-only sigslot class I wrote a few months ago
*/

#pragma once

#include <functional>
#include <map>
#include <iterator>
#include <memory>
#include <iostream>

template <typename... Args>
class Slot;

template <typename... Args>
class Slot_Scoped;

/*
This class is used as a sort of communicator to help scoped slots know
whether their referenced signal exists or not when they are destructed
*/

class SignalExistenceIndicator {};

template <typename... Args>
class Signal {
public:
	std::shared_ptr<SignalExistenceIndicator> existenceIndicator;
public:
	Signal() : id(0), existenceIndicator(std::make_shared<SignalExistenceIndicator>()) {}

	// Copy constructor creates a new signal
	Signal(Signal const& sig) : id(0), existenceIndicator(std::make_shared<SignalExistenceIndicator>()) {}

	Slot<Args...> connect(std::function<void(Args...)> const& slot) {
		slots.insert(std::make_pair(++id, slot));
		return Slot<Args...>(this, id, existenceIndicator);
	}

	template <typename T>
	Slot<Args...> connect(T* instance, void (T::*function)(const Args&...)) {
		return connect([=](const Args&... args) {
			(instance->*function)(args...);
		});
	}

	template <typename T>
	Slot<Args...> connect(T* instance, void (T::*function)(const Args&...) const) {
		return connect([=](const Args&... args) {
			(instance->*function)(args...);
		});
	}

	template <typename T>
	Slot<Args...> connect(std::shared_ptr<T> instance, void (T::*function)(const Args&...)) {
		return connect(&*instance, function);
	}

	template <typename T>
	Slot<Args...> connect(std::shared_ptr<T> instance, void (T::*function)(const Args&...) const) {
		return connect(&*instance, function);
	}

	void disconnect(const int& id) const {
		if (id < 0) {
			throw "BAD_ID";
			return;
		}

		slots.erase(id);
	}

	void disconnect(const Slot<Args...>& slot) const {
		slots.erase(slot.id);
	}

	void disconnect_all() const {
		slots.clear();
	}

	void emit(Args... args) {
		for (auto it : slots) {
			it.second(args...);
		}
	}

	size_t size() {
		return slots.size();
	}

	typename std::map<int, std::function<void(Args...)>>::iterator begin() {
		return slots.begin();
	}

	typename std::map<int, std::function<void(Args...)>>::iterator end() {
		return slots.end();
	}

	typename std::map<int, std::function<void(Args...)>>::iterator begin() const {
		return slots.begin();
	}

	typename std::map<int, std::function<void(Args...)>>::iterator end() const {
		return slots.end();
	}

	Signal& operator=(Signal const& other) {
		disconnect_all();
	}

private:
	mutable std::map<int, std::function<void(Args...)>> slots;
	mutable int id;
};

template <typename... Args>
class Slot {
private:
	Slot(const Slot<Args...>& copySlot) {}
	friend Signal<Args...>;
public:
	Slot() : id(-1), signal(nullptr), existenceIndicator(std::weak_ptr<SignalExistenceIndicator>()) {}
	Slot(Signal<Args...>* _signal, const int& _id, std::weak_ptr<SignalExistenceIndicator> _existenceIndicator) : id(_id), signal(_signal), existenceIndicator(_existenceIndicator) {}
	Slot(const Slot_Scoped<Args...>& _slot_scoped) : signal(_slot_scoped.signal), id(_slot_scoped.id), existenceIndicator(_slot_scoped.existenceIndicator) {} // Implicit Conversion
public:
	std::weak_ptr<SignalExistenceIndicator> existenceIndicator;
	Signal<Args...>* signal;
	int id;
};

template <typename... Args>
class Slot_Scoped {
public:
	Slot_Scoped() : id(-1), signal(nullptr), existenceIndicator(std::weak_ptr<SignalExistenceIndicator>()) {} // Default constructor
	Slot_Scoped(const Slot<Args...>& _slot) : signal(_slot.signal), id(_slot.id), existenceIndicator(_slot.existenceIndicator) {} // Implicit conversion
	Slot_Scoped(const Slot_Scoped<Args...>& copy) : signal(copy.signal), id(copy.id), existenceIndicator(copy.existenceIndicator) { // Copy constructor that disables destructor on old copy
		copy.signal = nullptr;
	}

	Slot_Scoped<Args...>& operator=(Slot_Scoped<Args...>& b) {
		if (this == &b) { return *this; }

		signal = b.signal;
		existenceIndicator = b.existenceIndicator;
		id = b.id;

		b.signal = nullptr;
		b.existenceIndicator = nullptr;

		return *this;
	}

	Slot_Scoped<Args...>& operator=(const Slot<Args...>& b) {
		signal = b.signal;
		existenceIndicator = b.existenceIndicator;
		id = b.id;

		return *this;
	}
public:
	std::weak_ptr<SignalExistenceIndicator> existenceIndicator;
	Signal<Args...>* signal;
	int id;
public:
	~Slot_Scoped() {
		if (signal != nullptr) {
			std::shared_ptr<SignalExistenceIndicator> exists = existenceIndicator.lock();
			if (exists != nullptr) {
				signal->disconnect(id);
			}
		}
	}
};