#include <iostream>
#include <map>
#include <string>

class Theme {
public:
    Theme() : backgroundColor("White"), fontColor("Black"), fontSize(12), iconStyle("Standard") {}
    Theme(const std::string& bgColor, const std::string& fColor, int fSize, const std::string& icon)
        : backgroundColor(bgColor), fontColor(fColor), fontSize(fSize), iconStyle(icon) {}
    void apply() const {
        std::cout << "Applying Theme:\n";
        std::cout << "Background Color: " << backgroundColor << "\n";
        std::cout << "Font Color: " << fontColor << "\n";
        std::cout << "Font Size: " << fontSize << "\n";
        std::cout << "Icon Style: " << iconStyle << "\n";
    }
    void displayPreview() const {
        std::cout << "Preview of Theme:\n";
        std::cout << "Background: " << backgroundColor << ", Font: " 
                  << fontColor << ", Size: " << fontSize 
                  << ", Icons: " << iconStyle << "\n";
    }
private:
    std::string backgroundColor;
    std::string fontColor;
    int fontSize;
    std::string iconStyle;
};

class ThemeManager {
public:
    ThemeManager() {
        themes["Classic"] = Theme("White", "Black", 12, "Standard");
        themes["Sport"] = Theme("Red", "White", 14, "Bold");
        themes["Eco"] = Theme("Green", "DarkGreen", 10, "Minimalist");
    }

    void displayThemes() const {
        std::cout << "Available Themes:\n";
        for (const auto& theme : themes) {
            std::cout << "- " << theme.first << "\n";
        }
    }
    void switchTheme(const std::string& themeName) {
        auto it = themes.find(themeName);
        if (it != themes.end()) {
            it->second.apply();
            it->second.displayPreview();
        } else {
            std::cout << "Theme not found!\n";
        }
    }
private:
    std::map<std::string, Theme> themes;
};
int main() {
    ThemeManager themeManager;
    std::string selectedTheme;

    while (true) {
        themeManager.displayThemes();
        std::cout << "Enter the name of the theme you want to apply (or 'exit' to quit): ";
        std::getline(std::cin, selectedTheme);

        if (selectedTheme == "exit") {
            break;
        }

        themeManager.switchTheme(selectedTheme);
    }

    return 0;
}
/*sample output:
Available Themes:
- Classic
- Sport
- Eco
Enter the name of the theme you want to apply (or 'exit' to quit): Sport
Applying Theme:
Background Color: Red
Font Color: White
Font Size: 14
Icon Style: Bold
Preview of Theme:
Background: Red, Font: White, Size: 14, Icons: Bold

Available Themes:
- Classic
- Sport
- Eco
Enter the name of the theme you want to apply (or 'exit' to quit): Eco
Applying Theme:
Background Color: Green
Font Color: DarkGreen
Font Size: 10
Icon Style: Minimalist
Preview of Theme:
Background: Green, Font: DarkGreen, Size: 10, Icons: Minimalist

Available Themes:
- Classic
- Sport
- Eco
Enter the name of the theme you want to apply (or 'exit' to quit): Classic
Applying Theme:
Background Color: White
Font Color: Black
Font Size: 12
Icon Style: Standard
Preview of Theme:
Background: White, Font: Black, Size: 12, Icons: Standard

Available Themes:
- Classic
- Sport
- Eco
Enter the name of the theme you want to apply (or 'exit' to quit): exit*/
