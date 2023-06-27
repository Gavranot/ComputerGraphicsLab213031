#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>


const std::string program_name = ("GLSL Shader class example");

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

static void buildRGBProgram(std::vector<std::vector<float>> &vector, unsigned int VAO, unsigned int VBO){

    std::vector<float> vertices;
    for(std::vector<float> point : vector){
        for(float coord : point){
            vertices.push_back(coord);
        }
    }
    int sizeOfVector = vertices.size();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVector*sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

}


float genFloat(){
    return (float)rand() / static_cast<float>(RAND_MAX);;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    //
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    std::ifstream testStream;
    testStream.open("../res/shaders/shader.vert");
    //

    Shader ourShader(R"(C:\Users\Damjan\CLionProjects\ComputerGraphicsLab213031\res\shaders\shader.vert)",
                     R"(C:\Users\Damjan\CLionProjects\ComputerGraphicsLab213031\res\shaders\shader.frag)"
                     );


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//        float vertices[] = {
//        // positions         // colors
//         0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
//        0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
//         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0,
//         0.0f,0.0f,0.0f, 1.0f, 0.0f, 0.0f// top
//
//    };



    const std::vector <float> A = { -0.5f, -0.5f, -0.5f, genFloat(), genFloat(), genFloat() };
    const std::vector <float> B = { 0.5f, -0.5f, -0.5f , genFloat(), genFloat(), genFloat() };
    const std::vector <float> C = { 0.5f, 0.5f, -0.5f  , genFloat(), genFloat(), genFloat() };
    const std::vector <float> D = { -0.5f, 0.5f, -0.5f , genFloat(), genFloat(), genFloat() };
    const std::vector <float> E = { -0.5f, -0.5f, 0.5f , genFloat(), genFloat(), genFloat() };
    const std::vector <float> F = { 0.5f, -0.5f, 0.5f  , genFloat(), genFloat(), genFloat() };
    const std::vector <float> G = { 0.5f, 0.5f, 0.5f   , genFloat(), genFloat(), genFloat() };
    const std::vector <float> H = { -0.5f, 0.5f, 0.5f  , genFloat(), genFloat(), genFloat() };

    std::vector<std::vector<float>> vertices;

    std::vector<std::vector<float>> vert = {A,B,C,D,E,F,G,H};

    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( C );
    vertices.push_back( C );
    vertices.push_back( D );
    vertices.push_back( A );
    vertices.push_back( E );
    vertices.push_back( F );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( E );
    vertices.push_back( H );
    vertices.push_back( D );
    vertices.push_back( A );
    vertices.push_back( A );
    vertices.push_back( E );
    vertices.push_back( H );
    vertices.push_back( G );
    vertices.push_back( C );
    vertices.push_back( B );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( G );
    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( F );
    vertices.push_back( E );
    vertices.push_back( A );
    vertices.push_back( D );
    vertices.push_back( C );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( D );

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    buildRGBProgram(vertices,VAO,VBO);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.



    // render loop
    // -----------
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = model =
                glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
                            glm::vec3(0.5f, 1.0f, 0.0f));
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//        projection =
//                glm::perspective(glm::radians(45.0f),
//                                 (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the
        // projection matrix rarely changes it's often best practice to set it
        // outside the main loop only once.
        ourShader.setMat4("projection", projection);




        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

