#pragma once

#include <BNM/UnityStructures.hpp>
#include <BNM/Method.hpp>
#include <BNM/Field.hpp>
#include <BNM/Property.hpp>
#include <BNM/Il2CppHeaders.hpp>

#include <GUI/GUISettings.hpp>
#include <Util/XRInput.hpp>
#include <GUI/Button.hpp>
#include <GUI/GUIManager.hpp>
#include <GUI/Buttons.hpp>
#include <GUI/NotificationLib/NotificationLib.h>

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

class ModGUI {
public:
    static inline SPMGUI::GUIManager* gui = nullptr;
    static inline bool cooldown = false;
    static inline int maxPages = 0;
    static inline float cooldownTime = 0.0f;
    static inline float rainbowCooldown = 0.0f;
    static inline int rainbowIndex = 0;

    static inline Button backPage{ .name = O("<- Back"), .method = []() { GUISettings::pageIndex--; }, .type = "button" };
    static inline Button nextPage{ .name = O("Next ->"), .method = []() { GUISettings::pageIndex++; }, .type = "button" };

    static void Init();
    static void CorrectIndexLOL(std::vector<Button*>* modsReal);
    static Button* FindButton(const std::string& name);
    static void HandleMods();
    static void Update();
};
