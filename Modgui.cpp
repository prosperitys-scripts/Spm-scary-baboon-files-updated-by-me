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
#include <GUI/ModGUI.hpp>
#include <GUI/Style/Style.hpp>
#include <GUI/Style/Styles.hpp>

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

void ModGUI::Init() {
    Class GameObject = Class("UnityEngine", "GameObject");
    Method<Il2CppObject*> Find = GameObject.GetMethod("Find", 1);
    Il2CppObject* MainCamera = Find(CreateMonoString("Main Camera"));
    Property<Il2CppObject*> GO_Transform = GameObject.GetProperty("transform");
    Il2CppObject* MainCameraTransform = GO_Transform[MainCamera].Get();

    Class Resources = Class("UnityEngine", "Resources");
    Class Font = Class("UnityEngine", "Font");
    Method<Mono::Array<Il2CppObject*>*> FindObjectsOfTypeAll = Resources.GetMethod("FindObjectsOfTypeAll", 1);
    auto arr = FindObjectsOfTypeAll(Font.GetMonoType());
    Il2CppObject* utopium = nullptr;
    for (auto i : arr->ToVector()) {
        Property<Mono::String*> name = Font.GetProperty("name");
        std::string realName = name[i].Get()->str();
        if (realName == "Utopium") {
            utopium = i;
            break;
        }
    }

    gui = new SPMGUI::GUIManager();
    gui->Init(MainCameraTransform, SPMGUI::TextAnchor::UpperRight, utopium);
}

void ModGUI::CorrectIndexLOL(std::vector<Button*>* modsReal) {
    int max = (int)std::ceil((float)Buttons::buttons[GUISettings::categoryIndex].size() / 8.0f) - 1;
    maxPages = std::max(0, max);

    if (GUISettings::pageIndex < 0) GUISettings::pageIndex = maxPages;
    if (GUISettings::pageIndex > maxPages) GUISettings::pageIndex = 0;

    if (GUISettings::cursorIndex < 0) GUISettings::cursorIndex = (int)modsReal->size() - 1;
    if (GUISettings::cursorIndex > (int)modsReal->size() - 1) GUISettings::cursorIndex = 0;
}

Button* ModGUI::FindButton(const std::string& name) {
    for (auto& c : Buttons::buttons) {
        for (auto& b : c) {
            if (b.name == name) return &b;
        }
    }
    return nullptr;
}

void ModGUI::HandleMods() {
    for (auto& c : Buttons::buttons) {
        for (auto& b : c) {
            if (b.enabled && b.method) b.method();
        }
    }
}

void ModGUI::Update() {
    HandleMods();

    Class Time = Class("UnityEngine", "Time");
    Property<float> time = Time.GetProperty("time");

    bool condition = XRInput::GetBoolFeature(BoolFeature::Primary2DAxisClick, Controller::Left);
    bool click = XRInput::GetBoolFeature(BoolFeature::Primary2DAxisClick, Controller::Right);
    Vector2 stick = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Right);

    std::vector<Button*> modz;
    int startIndex = GUISettings::pageIndex * 8;
    int endIndex = std::clamp(startIndex + 8, 0, (int)Buttons::buttons[GUISettings::categoryIndex].size());

    for (int i = startIndex; i < endIndex; ++i) {
        modz.push_back(&Buttons::buttons[GUISettings::categoryIndex][i]);
    }

    if (GUISettings::categoryIndex != 0) {
        if (GUISettings::pageIndex > 0) modz.push_back(&backPage);
        if (GUISettings::pageIndex < maxPages) modz.push_back(&nextPage);
    }

    float threshold = 0.7f;
    bool up = stick.y >= threshold;
    bool down = stick.y <= -threshold;
    bool left = stick.x <= -threshold;
    bool right = stick.x >= threshold;

    CorrectIndexLOL(&modz);
    Button* cbutton = modz[GUISettings::cursorIndex];

    if (condition) {
        if (click && !cooldown) {
            if (cbutton->type == "toggle") {
                cbutton->enabled = !cbutton->enabled;
                if (!cbutton->tooltip.empty()) Notifications::SendNotification("[<color=cyan>SCARY BABOON</color>] " + cbutton->tooltip);
                if (cbutton->enabled && cbutton->enableMethod) cbutton->enableMethod();
                if (!cbutton->enabled && cbutton->disableMethod) cbutton->disableMethod();
            } else if (cbutton->type == "button") {
                if (cbutton->method) cbutton->method();
                if (!cbutton->tooltip.empty()) Notifications::SendNotification("[<color=cyan>SCARY BABOON</color>] " + cbutton->tooltip);
            }
            cooldown = true;
        }

        if (time() > cooldownTime) {
            if (up) { GUISettings::cursorIndex--; cooldownTime = time() + .25f; }
            else if (down) { GUISettings::cursorIndex++; cooldownTime = time() + .25f; }
            else if (right && cbutton->type == "slider") {
                cbutton->slide = std::clamp(cbutton->slide + 1, 0, cbutton->maxSlide);
                cooldownTime = time() + .25f;
            } else if (left && cbutton->type == "slider") {
                cbutton->slide = std::clamp(cbutton->slide - 1, 0, cbutton->maxSlide);
                cooldownTime = time() + .25f;
            }
        }
    }
    if (!click) cooldown = false;

    CorrectIndexLOL(&modz);

    Button* themeButton = FindButton("Menu Theme");
    Style* theme = &(Styles::allStyles[themeButton->slide]);

    if (theme->styleName == "rainbow") {
        static std::vector<std::string> rnb = {"red", "#FFA500", "yellow", "lime", "blue", "magenta"};
        static float rainbowCooldown = 0.0f;
        static int rainbowIndex = 0;

        if (time() > rainbowCooldown) {
            rainbowCooldown = time() + .25f;
            rainbowIndex = (rainbowIndex + 1) % rnb.size();
            theme = new Style{"rainbow", rnb[rainbowIndex], "white", rnb[rainbowIndex], "red"};
        }
    }

    std::string menuText = "-- <color=" + theme->titleColor + ">SCARY BABOON MOD</color> [1.0.1] [" + std::to_string(GUISettings::pageIndex + 1) + "/" + std::to_string(maxPages + 1) + "]\n";

    for (int i = 0; i < modz.size(); ++i) {
        menuText += (GUISettings::cursorIndex == i ? "<color=" + theme->pointerColor + ">></color> " : "") + modz[i]->getFullName();
        if (modz[i]->type == "toggle") {
            std::string ts = modz[i]->enabled ? "[<color=" + theme->enabledColor + ">ON</color>]" : "[<color=" + theme->disabledColor + ">OFF</color>]";
            menuText += " " + ts;
        }
        menuText += "\n";
    }

    gui->SetText(menuText);
}
