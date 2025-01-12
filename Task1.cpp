#include <iostream>
#include <vector>
#include <string>
using namespace std;
class MenuNode {
public:
   string name;
   vector<MenuNode*> children;

    MenuNode(conststring& name) : name(name) {}

    void addChild(MenuNode* child) {
        children.push_back(child);
    }
};

MenuNode* createMenu() {
    MenuNode* mainMenu = new MenuNode("Main Menu");
    MenuNode* settings = new MenuNode("Settings");
    settings->addChild(new MenuNode("Display Settings"));
    settings->addChild(new MenuNode("Audio Settings"));
    MenuNode* media = new MenuNode("Media");
    media->addChild(new MenuNode("Radio"));
    media->addChild(new MenuNode("Bluetooth Audio"));
    mainMenu->addChild(settings);
    mainMenu->addChild(media);
    return mainMenu;
}

class MenuNavigator {
private:
    MenuNode* currentMenu;
    MenuNode* previousMenu;

public:
    MenuNavigator(MenuNode* root) : currentMenu(root), previousMenu(nullptr) {}

    void displayMenu() {
       cout << currentMenu->name << ":\n";
        for (size_t i = 0; i < currentMenu->children.size(); ++i) {
           cout << i + 1 << ". " << currentMenu->children[i]->name << "\n";
        }
       cout << "0. Back\n";
    }

    void navigate() {
        int choice;
        while (true) {
            displayMenu();
           cout << "Choose an option: ";
           cin >> choice;

            if (choice > 0 && choice <= currentMenu->children.size()) {
                previousMenu = currentMenu; // Store the previous menu
                currentMenu = currentMenu->children[choice - 1];
            } else if (choice == 0) {
                // Go back to parent
                if (previousMenu != nullptr) {
                    currentMenu = previousMenu;
                    previousMenu = nullptr; // Reset previous menu
                } else {
                   cout << "You are at the main menu. Cannot go back further.\n";
                }
            } else {
               cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    MenuNode* rootMenu = createMenu();
    MenuNavigator navigator(rootMenu);  
    navigator.navigate();
    delete rootMenu; 
    return 0;
}

/*sample output
Main Menu:
1. Settings
2. Media
0. Back
Choose an option: 1
Settings:
1. Display Settings
2. Audio Settings
0. Back
Choose an option: 1
Display Settings:
0. Back
Choose an option: 0
Settings:
1. Display Settings
2. Audio Settings
0. Back
Choose an option: 2
Audio Settings:
0. Back
Choose an option: 0
Settings:
1. Display Settings
2. Audio Settings
0. Back
Choose an option: 0
Main Menu:
1. Settings
2. Media
0. Back
Choose an option: 2
Media:
1. Radio
2. Bluetooth Audio
0. Back
Choose an option: 1
Radio:
0. Back
Choose an option: 0
Media:
1. Radio
2. Bluetooth Audio
0. Back
Choose an option: 0
Main Menu:
1. Settings
2. Media
0. Back
Choose an option: 3
Invalid choice. Please try again.
Main Menu:
1. Settings
2. Media
0. Back
Choose an option: 0
You are at the main menu. Cannot go back further.*/
