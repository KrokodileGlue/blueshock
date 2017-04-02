#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <vector>

enum class MessageType {
	ENTITY_MOVE, ENTITY_CENTER
};

struct Message {
	int entity;
	double arg1, arg2;
	MessageType type;
};

class MessageBus {
	std::vector<Message> messages;
public:
	void addMessage(Message m);
	void clearMessages();

	std::vector<Message>& getMessages() { return messages; }
};

#endif
