//
// Created by patryk on 15/07/2021.
//

#include "TextManager.h"

#include "opengl/Display.h"
#include <glm/glm.hpp>

#include <GLFont/FTLabel.h>
TextManager::TextManager(std::shared_ptr<GLFont> fontFace) {
    m_fontFace = fontFace;
}

std::unique_ptr<FTLabel> TextManager::newLabel() {
    const int fontSize = 48;
    auto label =std::make_unique<FTLabel>(m_fontFace, Display::get()->width(), Display::get()->height(), fontShaderPath);
    label->setPixelSize(fontSize);
    label->setColor(glm::vec4(color, 1.0f));
    return label;
}
