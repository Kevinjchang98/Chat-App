
#include <memory>

#include "Gui.h"

int main() {
    std::unique_ptr<Gui> app = std::make_unique<Gui>();

    return 0;
}