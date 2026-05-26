#pragma once
#include <string>
#include <vector>
#include <functional>

class Button {
public:
    std::string name;
    std::function<void()> method;
    std::function<void()> enableMethod;
    std::function<void()> disableMethod;
    bool enabled = false;
    std::string type = "toggle";
    int slide = 0;
    int maxSlide = 4;
    std::vector<std::string> slideNames;
    std::string tooltip = "";

    std::string getFullName() {
        if (type != "slider") return name;
        std::string nn = name;
        if (!slideNames.empty()) nn += " (" + slideNames[slide] + ")";
        nn += " [" + std::to_string(slide + 1) + "/" + std::to_string(maxSlide + 1) + "]";
        return nn;
    }
};
