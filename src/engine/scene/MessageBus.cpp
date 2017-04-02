#include "MessageBus.h"

#include <iostream>

void MessageBus::addMessage(Message m) {
	messages.push_back(m);
}

void MessageBus::clearMessages() {
	messages.clear();
}
