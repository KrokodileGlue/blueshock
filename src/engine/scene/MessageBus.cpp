#include "MessageBus.h"

#include <iostream>

MessageBus* MessageBus::singleton;

MessageBus* MessageBus::getSingleton() {
	if (singleton == nullptr) singleton = new MessageBus;
	return singleton;
}

void MessageBus::addMessage(Message m) {
	messages.push_back(m);
}

void MessageBus::clearMessages() {
	messages.clear();
}
