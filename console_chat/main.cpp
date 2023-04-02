#include "Chat.h"

int main() {
	Chat chat;
	chat.start();
	while (chat.isWork()) {
		chat.showMainMenu();
		while (chat.isCurrentUser()) {
			chat.showUserMenu();
		}
	}
	return 0;
}