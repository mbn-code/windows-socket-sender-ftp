#include "main.h"

int main() {
    try {
        CLI::start();
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
