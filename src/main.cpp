#define GLM_ENABLE_EXPERIMENTAL
#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <cstring>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_inverse.hpp>


const std::string program_name = ("GLSL Shader class example");
short rotatedUp = 0;
short rotatedDown = 0;
short rotatedLeft = 0;
short rotatedRight = 1;
short isFlipped = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Shader shader, glm::mat4 *transform);
void render(GLFWwindow* window, Shader shader, unsigned int *VAO_array, std::vector<size_t> sizes, glm::mat4 *transform);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void createCircle(std::vector<std::vector<float>> &circleVertices, std::vector<float> centre, float radius, float angle, int numAngles, std::vector<float> rgb){
    float x,y,z = 0.0f;
    float inc = 2*3.1415f/360;
    for(int i = 0; i<numAngles+1; i++){
        x = radius*cos(angle) + centre[0];
        y = radius*sin(angle) + centre[1];
        angle+=inc;
        circleVertices.push_back({x,y,z});
        circleVertices.push_back({rgb[1],rgb[2],rgb[3]});
    }
}

void buildRGBProgram(std::vector<std::vector<float>> &vector, unsigned int VAO, unsigned int VBO){

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

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
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
    Shader ourShader("C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\shader.vert",
                     "C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\shader.frag"
                     );


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top

    };
        std::vector<std::vector<float>> pacmanVertices;
        std::vector<std::vector<float>> eyeOne;
        std::vector<std::vector<float>> eyeTwo;
    pacmanVertices.push_back({0.0f,0.0f,0.0f});
    pacmanVertices.push_back({1.0f,1.0f,0.0f});


    createCircle(pacmanVertices,{0.0f,0.0f,0.0f},0.5f,3.1415f/8.0f,319,{0.0f,1.0f,1.0f});
    createCircle(eyeOne,{-0.1f,0.3f,0.0f},0.05f,0.0f,360,{0.0f,0.0f,0.0f});
    createCircle(eyeTwo,{0.2f,0.3f,0.0f},0.05f,0.0f,360,{0.0f,0.0f,0.0f});

    unsigned int VBO_array[3], VAO_array[3];
    glGenVertexArrays(3, VAO_array);
    glGenBuffers(3, VBO_array);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    buildRGBProgram(pacmanVertices,VAO_array[0],VBO_array[0]);
    buildRGBProgram(eyeOne, VAO_array[1], VBO_array[1]);
    buildRGBProgram(eyeTwo, VAO_array[2], VBO_array[2]);


    // render loop
    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window,ourShader);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // render the triangle
//        glm::mat4 transform = glm::mat4(1.0f);
//        ourShader.use();
//        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
//
//        glBindVertexArray(VAO_array[0]);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, pacmanVertices.size());
//
//        glBindVertexArray(VAO_array[1]);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, eyeOne.size());
//        glBindVertexArray(VAO_array[2]);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, eyeTwo.size());
//
//
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//
//    }
    glm::mat4 transform = glm::mat4(1.0f);
    ourShader.use();
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    render(window,ourShader,VAO_array,{pacmanVertices.size(),eyeOne.size(),eyeTwo.size()}, &transform);
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO_array);
    glDeleteBuffers(3, VBO_array);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Shader shader, glm::mat4 *transform)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        if(rotatedUp==1){
            if(isFlipped==1){
                *transform = glm::rotate(*transform, glm::radians(-180.0f), glm::vec3(0.0f,1.0f,0.0f));
                *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
                isFlipped=0;
            }else{
                *transform = glm::rotate(*transform, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
            }

            rotatedUp=0;
            rotatedRight=1;
        }
        if(rotatedDown==1){
            if(isFlipped==1){
                *transform = glm::rotate(*transform, glm::radians(-180.0f), glm::vec3(0.0f,1.0f,0.0f));
                *transform = glm::rotate(*transform, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
                isFlipped=0;
            }else{
                *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            }

            rotatedDown=0;
            rotatedRight=1;
        }
        if(rotatedLeft==1){
            *transform = glm::rotate(*transform, glm::radians(-180.0f), glm::vec3(0.0f,1.0f,0.0f));
            //*transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            //*transform = glm::inverse(*transform);
            rotatedLeft=0;
            rotatedRight=1;
            isFlipped = 0;
        }
        *transform = glm::translate(*transform, glm::vec3(0.01f, 0.0f, 0.0f));
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*transform));
        //shader.use();
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        if(rotatedUp==1){
            if(isFlipped==1){
                *transform = glm::rotate(*transform, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
            }else{
                *transform = glm::rotate(*transform, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
                *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            }
            
            rotatedUp=0;
            rotatedLeft=1;
            isFlipped=1;
        }
        if(rotatedRight==1){
            *transform = glm::rotate(*transform, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
            //*transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedRight=0;
            rotatedLeft=1;
            isFlipped=1;
        }
        if(rotatedDown==1){
            if(isFlipped==1){
                *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            }else{
                *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
                *transform = glm::rotate(*transform, glm::radians(-180.0f), glm::vec3(0.0f,1.0f,0.0f));
            }

           // *transform = glm::rotate(*transform, glm::radians(180.0f), glm::vec3(0.0f,1.0f,0.0f));
            rotatedDown=0;
            rotatedLeft=1;
            isFlipped=1;
        }
        *transform = glm::translate(*transform, glm::vec3(0.01f, 0.0f, 0.0f));
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*transform));
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(rotatedRight==1){
            *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedUp=1;
            rotatedRight=0;
        }
        if(rotatedLeft==1){
            *transform = glm::rotate(*transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedUp=1;
            rotatedLeft=0;
        }
        if(rotatedDown==1){
            *transform = glm::rotate(*transform, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedUp=1;
            rotatedDown=0;
        }

        *transform = glm::translate(*transform, glm::vec3(0.05f, 0.0f, 0.0f));
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*transform));
        //std::cout<<glm::to_string(*transform)<<std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if(rotatedRight==1){
            *transform = glm::rotate(*transform, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedDown = 1;
            rotatedRight = 0;
        }
        if(rotatedLeft==1){
            *transform = glm::rotate(*transform, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedDown = 1;
            rotatedLeft = 0;
        }
        if(rotatedUp==1){
            *transform = glm::rotate(*transform, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));
            rotatedDown = 1;
            rotatedUp = 0;
        }

        *transform = glm::translate(*transform, glm::vec3(0.05f, 0.0f, 0.0f));
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*transform));
       // std::cout<<glm::to_string(*transform)<<std::endl;
    }
//    std::cout<<"Rotated right: "<<rotatedRight<<std::endl;
//    std::cout<<"Rotated left: "<<rotatedLeft<<std::endl;
//    std::cout<<"Rotated up: "<<rotatedUp<<std::endl;
//    std::cout<<"Rotated down: "<<rotatedDown<<std::endl;
//    std::cout<<"Perspective flipped: "<<isFlipped<<std::endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void render(GLFWwindow* window, Shader shader, unsigned int *VAO_array, std::vector<size_t> sizes, glm::mat4 *transform){
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle

        processInput(window,shader,transform);

        for(int i = 0; i<sizes.size(); i++){
            glBindVertexArray(VAO_array[i]);
            glDrawArrays(GL_TRIANGLE_FAN, 0, sizes[i]);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
}
