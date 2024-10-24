#include <iostream>
#include <fstream>
#include <string>
#include "vendor/tgbot-cpp/include/tgbot/tgbot.h"

const bool RUNNING = true;

std::string getKey() {
	std::string result = "";
	std::fstream file("key.txt");
	if (!file.is_open()) std::cout << "no such file in directory\n";
	std::getline(file, result);

	return result;
}

void startEvents(TgBot::Bot& bot) {
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, я бот-чистильщик! Чтобы добавить бота в группу пропиши /invite");
    });
	bot.getEvents().onCommand("invite", [&bot](TgBot::Message::Ptr message){
		bot.getApi().sendMessage(message->chat->id, "Чтобы добавить бота в группу, нужно выполнить несколько простых действий:\n"
													"1) Нажмите \"Добавить нового участника\" в группе.\n"
													"2) В появившемся окне выберите или найдите по поиску бота (@trash_c_bot)."
													"3) После добавления бота в группу, вы должны дать права администратора.\n"
													"После выполнения всех действий бот будет полностью готов к работе :)");
	});
	bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message) {
		try{
			if (!message->newChatMembers.empty() || message->leftChatMember){
				try {
					bot.getApi().deleteMessage(message->chat->id, message->messageId);
				} 
				catch (const TgBot::TgException& ex) {
						if (ex.what() == std::string("Bad Request: message to delete not found")) {
							std::cout << "message to delete not found. ignoring..." << std::endl;
						} else {
							std::cout << "error: " << ex.what() << std::endl;
						}
					}
				}
		}
		catch(const TgBot::TgException& ex){
			std::cout << "error: " << ex.what() << std::endl;
		}
	});
}

int main() {
	std::string token = getKey();
	if (token.empty()) {
        return EXIT_FAILURE;
    }
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