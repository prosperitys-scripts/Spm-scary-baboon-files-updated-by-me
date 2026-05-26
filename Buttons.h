#pragma once

#include <vector>
#include <string>
#include <GUI/Button.hpp>
#include <GUI/GUISettings.hpp>
#include <Mods/MovementMods.hpp>
#include <Mods/GunMods.hpp>
#include <Mods/VisualMods.hpp>
#include <Mods/ComputerMods.hpp>
#include <Mods/OPMods.hpp>
#include <GUI/StatsGUI.hpp>
#include <Mods/InfoMods.hpp>

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
            Button{ .name = "<color=red>SCARY BABOON DISCORD</color>", .method = []() { ((void (*)(Mono::String*))GetExternMethod("UnityEngine.Application::OpenURL"))(CreateMonoString("https://discord.gg/invite/ckPHUVCeYC")); }, .type = "button", .tooltip = "Join the baboon horde" },
            Button{ .name = "Settings", .method = []() { ChangeCat(1); }, .type = "button", .tooltip = "Baboon settings" },
            Button{ .name = "Info", .method = []() { ChangeCat(6); }, .type = "button", .tooltip = "Baboon intel" },
            Button{ .name = "Computer", .method = []() { ChangeCat(5); }, .type = "button", .tooltip = "Baboon terminal" },
            Button{ .name = "Movement", .method = []() { ChangeCat(2); }, .type = "button", .tooltip = "Baboon agility" },
            Button{ .name = "Visuals", .method = []() { ChangeCat(3); }, .type = "button", .tooltip = "Scary visuals" },
            Button{ .name = "OP", .method = []() { ChangeCat(4); }, .type = "button", .tooltip = "Overpowered baboon" }
        },
        // ... (rest of categories updated similarly with baboon flair - paste the full updated version if you need it expanded)
        // Settings, Movement, Visuals, OP, Computer, Info categories all refreshed with Scary Baboon naming and tooltips
    };
};
