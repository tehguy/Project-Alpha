/*
    Project Alpha
    Copyright (C) 2017  tehguy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "core.hpp"

#include "../gfx/gfx.hpp"

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

int Core::init() {
    if (!Graphics::Instance().initGFX("./res/spritesheet.png", "Project Alpha")) return 1;

    genTestArea();

    gameLoop();

    return 0;
}

void Core::gameLoop() {
    Graphics::Instance().setActive();
    while (Graphics::Instance().windowIsOpen()) {
        sf::Event event{};
        while (Graphics::Instance().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Graphics::Instance().shutdown();
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleInput(event.key.code);
            }
        }

        drawGame();
    }
}

void Core::handleInput(int key) {
    switch (key) {
        case sf::Keyboard::Escape:
            Graphics::Instance().shutdown();
            break;
        default:
            break;
    }
}

void Core::genTestArea() {
    currentLocation = std::make_unique<Location>("Big Test", 2, 2);
    Area area1("Test1");
    Area area2("Test2");
    Area area3("Test3");
    Area area4("Test4");

    area1.genRandom(288);
    area2.genRandom(243);
    area3.genRandom(146);
    area4.genRandom(723);

    currentLocation->placeArea(0, 0, area1);
    currentLocation->placeArea(1, 0, area2);
    currentLocation->placeArea(0, 1, area3);
    currentLocation->placeArea(1, 1, area4);

    currentLocation->setCurrentArea(0, 0);
}

void Core::drawGame() {
    Graphics::Instance().clearWindow();

    if (currentLocation != nullptr) {
        currentLocation->drawChunk();
    }
    Graphics::Instance().draw();
    Graphics::Instance().display();
}

void Core::imgui_test() {
    sf::RenderWindow window(sf::VideoMode(640,480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = { 0.f, 0.f, 0.f };

    char windowTitle[255] = "ImGui + SFML";
    window.setTitle(windowTitle);
    window.resetGLStates();

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample Window");

        if (ImGui::ColorEdit3("background color", color)) {
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        ImGui::InputText("Window Title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            window.setTitle(windowTitle);
        }
        ImGui::End();

        window.clear(bgColor);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
