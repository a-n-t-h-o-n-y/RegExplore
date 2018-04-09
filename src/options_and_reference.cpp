#include <regex_explore/options_and_reference.hpp>

namespace regex_explore {

Options_and_reference::Options_and_reference() {
    this->set_active_page(0);

    options_page.change_page.clicked.connect(
        [this] { this->set_active_page(1); });
    reference_page.change_page.clicked.connect(
        [this] { this->set_active_page(0); });
}

}  // namespace regex_explore
