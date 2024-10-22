#include <iostream>
#include <fstream>
#include <string>
#include <tgbot/tgbot.h>

const bool RUNNING = true;

std::string getKey() {
	std::string result = "";
	std::fstream file("key.txt");
	if (!file.is_open()) std::cout << "no such file in directory\n";
	std::getline(file, result);

	return result;
}

void startEvents(TgBot::Bot& bot) {
	bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message) {
		if (!message->newChatMembers.empty() || message->leftChatMember) 
			bot.getApi().deleteMessage(message->chat->id, message->messageId);
	});
}

int main() {
	std::string token = getKey();
	TgBot::Bot botCore(token);
	startEvents(botCore);

	try {
		printf("bot is started...\n");
		TgBot::TgLongPoll longPoll(botCore);
		while (RUNNING) {
			longPoll.start();
		}
	}
	catch (std::runtime_error& ex) {
		printf("error: %s\n", ex.what());
	}

	return EXIT_SUCCESS;
}