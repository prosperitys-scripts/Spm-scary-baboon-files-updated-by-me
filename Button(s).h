#pragma once
#include <vector>
#include <string>
#include <GUI/Button.hpp>
#include <GUI/GUISettings.hpp>
#include <Mods/MovementMods.hpp>
#include <Mods/VisualMods.hpp>
#include <Mods/OPMods.hpp>
#include <Mods/ComputerMods.hpp>
#include <Mods/InfoMods.hpp>
#include <Mods/AntiCheatBypass.hpp>

class Buttons {
private:
    inline static void ChangeCat(int i) {
        GUISettings::categoryIndex = i;
        GUISettings::pageIndex = 0;
        GUISettings::cursorIndex = 0;
    }

public:
    inline static std::vector<std::vector<Button>> buttons = {
        {
            Button{ .name = "<color=red>SCARY BABOON DISCORD</color>", .method = []() { ((void (*)(Mono::String*))GetExternMethod("UnityEngine.Application::OpenURL"))(CreateMonoString("https://discord.gg/invite/ckPHUVCeYC")); }, .type = "button", .tooltip = "Join the community" },
            Button{ .name = "Settings", .method = []() { ChangeCat(1); }, .type = "button", .tooltip = "Menu settings" },
            Button{ .name = "Movement", .method = []() { ChangeCat(2); }, .type = "button", .tooltip = "Movement hacks" },
            Button{ .name = "Visuals", .method = []() { ChangeCat(3); }, .type = "button", .tooltip = "Visual mods" },
            Button{ .name = "OP", .method = []() { ChangeCat(4); }, .type = "button", .tooltip = "Overpowered features" },
            Button{ .name = "Computer", .method = []() { ChangeCat(5); }, .type = "button", .tooltip = "Computer commands" },
            Button{ .name = "Info", .method = []() { ChangeCat(6); }, .type = "button", .tooltip = "Game info" }
        },
        { // Settings
            Button{ .name = "Back", .method = []() { ChangeCat(0); }, .type = "button" },
            Button{ .name = "Menu Theme", .type = "slider", .maxSlide = 5, .slideNames = {"default", "blood", "dark", "nightmare", "void"}, .tooltip = "Change menu theme" }
        },
        // Movement, Visuals, OP etc. categories use the functions from the mod files below
    };
};
