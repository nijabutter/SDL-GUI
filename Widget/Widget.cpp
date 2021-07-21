#include "Widget.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"

Widget::Widget(Parent *parent, int x, int y, int w, int h)
:parent(parent), x(x), y(y), w(w), h(h) {
    window = parent->get_root();
    tooltip.window = window;
}

void Widget::grid(int row, int column) {
    parent->grid(this, row, column);
}

void Widget::update_and_render(float dt) {
    if (show_tooltip && has_tooltip) {
        if (collected_time >= tooltip_delay) {
            window->top_level.push_back([tooltip=&tooltip, window=window]() {
                tooltip->render(EventHandler::get_mouse_x() + 15, EventHandler::get_mouse_y() + 15, { 255, 255, 255 }, true, { 0, 0, 0 });
                });
        }
        else {
            collected_time += dt;
        }
    }
#ifdef DRAW_DEBUG
    window->draw_rect(x, y, w, h, { 255, 0, 0 });
#endif
}
void Widget::on_hover() {
    show_tooltip = true;
    collected_time = 0;
}

void Widget::off_hover() {
    show_tooltip = false;
    collected_time = 0;
}

void Widget::set_tooltip(std::wstring text) {
    has_tooltip = true;
    tooltip.set(text);
}

void Widget::remove_tooltip() {
    has_tooltip = false;
}