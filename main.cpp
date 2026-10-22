#include <ftxui/component/component.hpp> //Input, Menu, Button, Container
#include <ftxui/component/screen_interactive.hpp> //ScreenInteractive
#include <ftxui/dom/elements.hpp> //text, vbox, hbox, border, flex

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    std::string input_text;
    std::vector<std::string> messages;
    std::vector<std::string> users = {"suslan", "kapygay", "ilsas"};
    int selected_user = 0;

    Component input_box = Input(&input_text, "Введите сообщение...");

    Component user_menu = Menu(&users, &selected_user);

    auto input_with_enter = CatchEvent(input_box, [&](Event event) {
        if (event == Event::Return && !input_text.empty()) {
            messages.push_back("Вы: " + input_text);
            if (messages.size() > 500) messages.erase(messages.begin());
            input_text.clear();
            return true;
        }
        return false;
    });

    auto layout = Container::Horizontal({user_menu, input_with_enter});

    auto renderer = Renderer(layout, [&] {
        Elements message_elements;
        for (const auto& msg : messages) {
            message_elements.push_back(text(msg));
        }

        auto chat_panel = vbox(std::move(message_elements)) | flex | vscroll_indicator | frame;

        return hbox({
            user_menu->Render() | border | size(WIDTH, EQUAL, 20),
            vbox({
                chat_panel | flex,
                separator(),
                hbox({text(" > "), input_with_enter->Render() | flex}) | border,
            }) | flex,
        });
    });

    screen.Loop(renderer);
    return 0;
}
