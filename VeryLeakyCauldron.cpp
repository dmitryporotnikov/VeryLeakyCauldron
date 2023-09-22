#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <string>

void allocateMemory(size_t sizeInMB) {
    size_t size = sizeInMB * 1024 * 1024 / sizeof(int);
    int* leakyMemory = new int[size];
}

int main(int argc, char* argv[]) {
    std::string mode = "";
    size_t leakSize = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc) {
            mode = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-leak") == 0 && i + 1 < argc) {
            leakSize = std::stoi(argv[i + 1]);
            i++;
        }
    }

    if (mode == "manual") {
        while (true) {
            allocateMemory(leakSize);
            std::cout << "Memory allocated. Press Enter to allocate more." << std::endl;
            std::cin.get();
            if (std::cin.get() == '\n') continue;
        }
    }
    else if (mode == "auto") {
        while (true) {
            allocateMemory(leakSize);
            std::cout << "Memory allocated automatically." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else {
        std::cout << "Pass parameters: -manual or -auto. For -auto use desired leak size in MB." << std::endl;
    }

    return 0;
}
