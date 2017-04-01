#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <vector>

enum class MessageType {
	MOVE_MODEL
};

struct Message {
	int entity;
	double arg1, arg2;
	MessageType type;
};

class MessageBus {
	std::vector<Message> messages;
	static MessageBus* singleton;
public:
	static MessageBus* getSingleton();
	void addMessage(Message m);
	void clearMessages();

	std::vector<Message>& getMessages() { return messages; }
};

#endif
