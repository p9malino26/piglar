class MyApp: public Application
{
public:
    MyApp()
        :Application()
    {

        float vertices[] = {
            // positions    // colors           // texture coords
             0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        unsigned int eboVertices[] = {
            0, 1, 3,
            1, 2, 3
        };

        int offsets[3] = {2, 3, 2};


        ResourceManager::createVertexArray("vao");
        ResourceManager::getVertexArray("vao")->bind();
        ResourceManager::createBuffer("vbo", GL_ARRAY_BUFFER, vertices, sizeof(vertices));
        ResourceManager::getBuffer("vbo")->bind();
        ResourceManager::getVertexArray("vao")->specifyVertexAttributes(offsets, 3);
        ResourceManager::createBuffer("ebo", GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));
        ResourceManager::getBuffer("ebo")->bind();
        ResourceManager::getVertexArray("vao")->unbind();


        ResourceManager::createShader("shader","res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
        assert(ResourceManager::getShader("shader")->good());


        ResourceManager::createTexture("","pigfarming.jpg");
        assert(ResourceManager::getTexture("")->good());

        ResourceManager::createTexture("crateTex","crate.jpg");
        assert(ResourceManager::getTexture("crateTex")->good());


    }

    void processFrame() override
    {
        ResourceManager::getTexture("")->activate(0);
        ResourceManager::getTexture("crateTex")->activate(1);
        
        ResourceManager::getVertexArray("vao")->bind();
        ResourceManager::getShader("shader")->use();

        glm::mat4 trans(1.f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, -2 * TimeManager::time(), glm::vec3(0.f, 0.f, 1.f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));


        //bind texture

        ResourceManager::getShader("shader")->uniformInt("", 0);
        ResourceManager::getShader("shader")->uniformMat4("model", trans);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //draw square 2

        trans = glm::mat4(1.f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::rotate(trans,  TimeManager::time(), glm::vec3(0.f, 0.f, 1.f));
        trans = glm::scale(trans, glm::vec3(0.7f, 0.7f, 1.0f));

        //bind texture

        ResourceManager::getShader("shader")->uniformInt("", 0);
        ResourceManager::getShader("shader")->uniformMat4("model", trans);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }


};