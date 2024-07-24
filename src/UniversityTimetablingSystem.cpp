#include <iostream>
#include <string>
#include "../include/University.h"

void interaction(const std::string& path) {
    University uni;
    std::cout << "Loading university state from: " << path << std::endl;
    uni.loadState(path);

    std::cout << "Scheduling timetable..." << std::endl;
    uni.schedule();

    std::cout << "Saving generated timetable to: " << path << std::endl;
    uni.saveState(path);

    std::cout << "Timetable has been generated and saved successfully!" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string path = argv[1];
        interaction(path);
    }

    return 0;
}

