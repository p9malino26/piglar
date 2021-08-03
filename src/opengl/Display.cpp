#include <glad/glad.h>
#include "Display.h"

Display* Display::instance;

Display::Display(const std::string& title, int width, int height, int contextVersionMajor, int contextVersionMinor)
    :m_width(width), m_height(height), m_title(title), m_good(true) // set the good flag to on
{
    instance = this;
    try
    {
        //glClearError();
        if (!glfwInit())
        {
            std::cerr << "[ERROR] Failed to initialize GLFW" << std::endl;
            throw std::exception();
        }

        //m_states = m_states | DISPLAY_GLFW_INIT_GOOD;

        //glfw has initialized, so set the bit to true

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (m_window == nullptr)
        {
            std::cerr << "[ERROR] Failed to create GLFW window" << std::endl;
            throw std::exception();
        }

        //m_states = m_states | DISPLAY_GLFW_WINDOW_GOOD;
        std::cout << "[INFO] Starting OpenGL context.\n";
        glfwMakeContextCurrent(m_window);
        std::cout << "[INFO] Context started successfully.\n";
        
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw std::exception();
        }  
        
        glViewport(0, 0, m_width, m_height);
        
        std::cout << "[INFO] Context initialized successfully: " <<  glGetString(GL_VERSION) << std::endl;


    }catch (std::exception& e)
    {
        m_good = false;
    }
}

Display::~Display()
{
    printf("[INFO] Clearing up and quitting program.\n");
    glfwTerminate();
}

void Display::checkEvents() const
{
    glfwPollEvents();
}

/*void Display::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const // deprecated
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}*/

/*void Display::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}*/

void Display::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

bool Display::isOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

void Display::close() const
{
    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

glm::mat4 Display::getProjectionMatrix()
{
    glm::mat4 projection(1.0f);
    projection = glm::scale(projection, glm::vec3(static_cast<float>(height()) / static_cast<float>(width()), 1.0f, 1.0f));
    return projection;
}

glm::mat4 Display::getPixelMatrix()
{
    glm::mat4 output(1.0f);
    output = glm::scale(output, glm::vec3(static_cast<float>(m_width), static_cast<float>(m_height), 1.f));
    output = glm::scale(output, glm::vec3(0.5f, -0.5f, 1.f));
    output = glm::translate(output, glm::vec3(1.f, -1.f, 0.f));
    return output;
}

