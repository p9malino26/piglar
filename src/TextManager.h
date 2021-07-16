//
// Created by patryk on 15/07/2021.
//

#pragma once

#include <memory>
#include <glm/glm.hpp>

class GLFont;
class FTLabel;

class TextManager {
public:
    TextManager(std::shared_ptr<GLFont> fontFace);
    std::shared_ptr<GLFont> m_fontFace;

    std::unique_ptr<FTLabel> newLabel();
private:
    const char* fontShaderPath = "res/shaders";
    static constexpr glm::vec3 color{0.89, 0.26, 0.3};
};


