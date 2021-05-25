#include "Renderer.hpp"
#include "Label.hpp"

Label::Label(Parent *parent, std::string text)
: Widget(parent, 0, 0, 0, 0), Text(text){
    set(text);
    w = get_width() * Renderer::get_font_width();
    h = get_line_count() * Renderer::get_font_height();
}

void Label::update_and_render() {
    Text::render(x, (y + h / 2) - (get_line_count() * Renderer::get_font_height() / 4), foreground, show_background, background);
    Widget::update_and_render();
}

void Label::grid(int row, int column) {
    Widget::grid(row, column);
    set(text);
}

void Label::set(std::string new_text) {
    Text::set(new_text);
    // center the text;
    text_y = (y + h / 2) - (get_line_count() * Renderer::get_font_height() / 4);
}