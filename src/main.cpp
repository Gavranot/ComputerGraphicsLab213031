#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Camera.hpp>
#include <Shader.hpp>

#include <iostream>
#include <string>
#include <vector>

const std::string program_name = ("Colour");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;
static bool firstMouse = true;

// timing
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

// lighting
static glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


float genFloat(){
    return (float)rand()/RAND_MAX;
}

static void buildSimpleProgram(std::vector<std::vector<float>> &vertices, unsigned int VAO, unsigned int VBO){

    std::vector<float> coords;
    for(std::vector<float> point : vertices){
        for(float coord : point){
            coords.push_back(coord);
        }
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, coords.size()*sizeof(float), &coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

}

static void buildCube(std::vector<std::vector<float>> &vertices, unsigned int VAO, unsigned int VBO){

    std::vector<float> coords;
    for(std::vector<float> point : vertices){
        for(float coord : point){
            coords.push_back(coord);
        }
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, coords.size()*sizeof(float), &coords[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

}
static void buildCubeTex(std::vector<std::vector<float>> &vertices, unsigned int VAO, unsigned int VBO){

    std::vector<float> coords;
    for(std::vector<float> point : vertices){
        for(float coord : point){
            coords.push_back(coord);
        }
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, coords.size()*sizeof(float), &coords[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

}




static void create3DObject(std::vector<std::vector<float>> &vertices, float HEIGHT, float WIDTH, float LENGTH, std::vector<float> rgb){
    std::vector <float> A = { -LENGTH, -HEIGHT, -WIDTH};
    std::vector <float> B = { LENGTH, -HEIGHT, -WIDTH};
    std::vector <float> C = { LENGTH, HEIGHT, -WIDTH};
    std::vector <float> D = { -LENGTH, HEIGHT, -WIDTH};
    std::vector <float> E = { -LENGTH, -HEIGHT, WIDTH};
    std::vector <float> F = { LENGTH, -HEIGHT, WIDTH};
    std::vector <float> G = { LENGTH, HEIGHT, WIDTH};
    std::vector <float> H = { -LENGTH, HEIGHT, WIDTH};



    for(std::vector<float> *vec : {&A,&B,&C,&D}){
        vec->push_back(0.0f);
        vec->push_back(0.0f);
        vec->push_back(-1.0f);
    }


    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( C );
    vertices.push_back( C );
    vertices.push_back( D );
    vertices.push_back( A );

   A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};


    for(std::vector<float> *vec : {&E,&F,&G,&H}){
        vec->push_back(0.0f);
        vec->push_back(0.0f);
        vec->push_back(1.0f);
    }

    vertices.push_back( E );
    vertices.push_back( F );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( E );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&A,&D,&E,&H}){
        vec->push_back(-1.0f);
        vec->push_back(0.0f);
        vec->push_back(0.0f);
    }

    vertices.push_back( H );
    vertices.push_back( D );
    vertices.push_back( A );
    vertices.push_back( A );
    vertices.push_back( E );
    vertices.push_back( H );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&G,&C,&B,&F}){
        vec->push_back(1.0f);
        vec->push_back(0.0f);
        vec->push_back(0.0f);
    }

    vertices.push_back( G );
    vertices.push_back( C );
    vertices.push_back( B );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( G );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};


    for(std::vector<float> *vec : {&A,&B,&E,&F}){
        vec->push_back(0.0f);
        vec->push_back(-1.0f);
        vec->push_back(0.0f);
    }

    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( F );
    vertices.push_back( E );
    vertices.push_back( A );


    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&D,&C,&G,&H}){
        vec->push_back(0.0f);
        vec->push_back(1.0f);
        vec->push_back(0.0f);
    }

    vertices.push_back( D );
    vertices.push_back( C );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( D );
}

static void create3DObjectTex(std::vector<std::vector<float>> &vertices, float HEIGHT, float WIDTH, float LENGTH, std::vector<float> rgb){
    std::vector <float> A = { -LENGTH, -HEIGHT, -WIDTH};
    std::vector <float> B = { LENGTH, -HEIGHT, -WIDTH};
    std::vector <float> C = { LENGTH, HEIGHT, -WIDTH};
    std::vector <float> D = { -LENGTH, HEIGHT, -WIDTH};
    std::vector <float> E = { -LENGTH, -HEIGHT, WIDTH};
    std::vector <float> F = { LENGTH, -HEIGHT, WIDTH};
    std::vector <float> G = { LENGTH, HEIGHT, WIDTH};
    std::vector <float> H = { -LENGTH, HEIGHT, WIDTH};



    for(std::vector<float> *vec : {&A,&B,&C,&D}){
        vec->push_back(0.0f);
        vec->push_back(0.0f);
        vec->push_back(-1.0f);
    }

    A.push_back(0.0f);A.push_back(0.0f);
    B.push_back(1.0f);B.push_back(0.0f);
    C.push_back(1.0f);C.push_back(1.0f);
    D.push_back(0.0f);D.push_back(1.0f);

    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( C );
    vertices.push_back( C );
    vertices.push_back( D );
    vertices.push_back( A );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};


    for(std::vector<float> *vec : {&E,&F,&G,&H}){
        vec->push_back(0.0f);
        vec->push_back(0.0f);
        vec->push_back(1.0f);
    }

    E.push_back(0.0f);E.push_back(0.0f);
    F.push_back(1.0f);F.push_back(0.0f);
    G.push_back(1.0f);G.push_back(1.0f);
    H.push_back(0.0f);H.push_back(1.0f);

    vertices.push_back( E );
    vertices.push_back( F );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( E );


    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&A,&D,&E,&H}){
        vec->push_back(-1.0f);
        vec->push_back(0.0f);
        vec->push_back(0.0f);
    }

    H.push_back(1.0f);H.push_back(0.0f);
    D.push_back(1.0f);D.push_back(1.0f);
    A.push_back(0.0f);A.push_back(1.0f);
    E.push_back(0.0f);E.push_back(0.0f);

    vertices.push_back( H );
    vertices.push_back( D );
    vertices.push_back( A );
    vertices.push_back( A );
    vertices.push_back( E );
    vertices.push_back( H );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&G,&C,&B,&F}){
        vec->push_back(1.0f);
        vec->push_back(0.0f);
        vec->push_back(0.0f);
    }

    G.push_back(1.0f);G.push_back(0.0f);
    C.push_back(1.0f);C.push_back(1.0f);
    B.push_back(0.0f);B.push_back(1.0f);
    F.push_back(0.0f);F.push_back(0.0f);

    vertices.push_back( G );
    vertices.push_back( C );
    vertices.push_back( B );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( G );

    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};


    for(std::vector<float> *vec : {&A,&B,&E,&F}){
        vec->push_back(0.0f);
        vec->push_back(-1.0f);
        vec->push_back(0.0f);
    }

    A.push_back(0.0f);A.push_back(1.0f);
    B.push_back(1.0f);B.push_back(1.0f);
    F.push_back(1.0f);F.push_back(0.0f);
    E.push_back(0.0f);E.push_back(0.0f);

    vertices.push_back( A );
    vertices.push_back( B );
    vertices.push_back( F );
    vertices.push_back( F );
    vertices.push_back( E );
    vertices.push_back( A );


    A = { -LENGTH, -HEIGHT, -WIDTH};
    B = { LENGTH, -HEIGHT, -WIDTH};
    C = { LENGTH, HEIGHT, -WIDTH};
    D = { -LENGTH, HEIGHT, -WIDTH};
    E = { -LENGTH, -HEIGHT, WIDTH};
    F = { LENGTH, -HEIGHT, WIDTH};
    G = { LENGTH, HEIGHT, WIDTH};
    H = { -LENGTH, HEIGHT, WIDTH};

    for(std::vector<float> *vec : {&D,&C,&G,&H}){
        vec->push_back(0.0f);
        vec->push_back(1.0f);
        vec->push_back(0.0f);
    }

    D.push_back(0.0f);D.push_back(1.0f);
    C.push_back(1.0f);C.push_back(1.0f);
    G.push_back(1.0f);G.push_back(0.0f);
    H.push_back(0.0f);H.push_back(0.0f);

    vertices.push_back( D );
    vertices.push_back( C );
    vertices.push_back( G );
    vertices.push_back( G );
    vertices.push_back( H );
    vertices.push_back( D );
}




int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        program_name.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  // build and compile our shader program
  // ------------------------------------
  std::string shader_location("../res/shaders/");
    std::string texture_location("../res/textures/");

    std::string light_shader("material");
  std::string lamp_shader("lamp");


  // build and compile our shader zprogram
  // ------------------------------------
  Shader lightingShader("C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\material.vert",
                        "C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\material.frag");
  Shader lampShader("C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\lamp.vert",
                    "C:\\Users\\Damjan\\CLionProjects\\ComputerGraphicsLab213031\\res\\shaders\\lamp.frag");
//
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

//
    //
  int num_objects = 12;
    std::vector<std::vector<std::vector<float>>> vertices;
  for(int i = 0; i<num_objects; i++){
      std::vector<std::vector<float>> verticesI;
      create3DObjectTex(verticesI,0.5f,0.5f,0.5f,{1.0f,1.0f,1.0f});
      vertices.push_back(verticesI);
  }

  // first, configure the cube's VAO (and VBO)
  unsigned int VBO_array[num_objects], cubeVAO_array[num_objects];
  glGenVertexArrays(num_objects, cubeVAO_array);
  glGenBuffers(num_objects, VBO_array);

  for(int i = 0; i<num_objects; i++){
      buildCubeTex(vertices[i], cubeVAO_array[i], VBO_array[i] );
  }

  // second, configure the light's VAO (VBO stays the same; the vertices are the
  // same for the light object which is also a 3D cube)
  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);

  buildSimpleProgram(vertices[0],lightVAO,VBO_array[0]);

  // render loop
  // -----------


//
  glm::vec3 moveVec = glm::vec3 (0.0f,0.0f,0.0f);

    unsigned int diffuseMap =
            loadTexture("C:\\Users\\Damjan\\Desktop\\aaa\\lab8_213031\\res\\textures\\container2.png");
    unsigned int specularMap =
            loadTexture("C:\\Users\\Damjan\\Desktop\\aaa\\lab8_213031\\res\\textures\\container2_specular.png");
    unsigned int emissionMap =
            loadTexture("C:\\Users\\Damjan\\Desktop\\aaa\\lab8_213031\\res\\textures\\emission.png");
//
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 1);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);

    float angles[num_objects];
    glm::vec3 axis[num_objects];
    glm::vec3 trans[num_objects];
    glm::vec3 scales[num_objects];
    for(int i = 0; i<num_objects; i++){
        angles[i] = rand()%(45 - 270 + 1) + 45.0f;
        axis[i] = {(float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX};
        if(rand()>5){
            trans[i] = {(float)rand()/RAND_MAX*5.25f, (float)rand()/RAND_MAX*5.25f, (float)rand()/RAND_MAX*5.25f};
            scales[i] = glm::vec3((float)rand()/RAND_MAX*1.25f);
        }else{
            trans[i] = {(float)rand()/RAND_MAX*5.25f, -(float)rand()/RAND_MAX*5.25f, (float)rand()/RAND_MAX*5.25f};
            scales[i] = glm::vec3((float)rand()/RAND_MAX*0.75f);
        }



    }


  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader.use();

    std::vector<std::vector<float>> rgb;
    rgb.push_back({0.5f,0.6f,0.7f});
    rgb.push_back({0.9f,0.6f,0.8f});




      lightingShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
      lightingShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
      lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
      lightingShader.setFloat("Time", (float)glfwGetTime());


      lightingShader.setVec3("light.position", lightPos);
      lightingShader.setVec3("viewPos", camera.Position);

      lightingShader.setFloat("material.shininess", 64.0f);

      glm::mat4 projection =
              glm::perspective(glm::radians(camera.Zoom),
                               (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
      glm::mat4 view = camera.GetViewMatrix();
      lightingShader.setMat4("projection", projection);
      lightingShader.setMat4("view", view);

    for(int i = 0 ; i<num_objects; i++){


          glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model, trans[i]);
          model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angles[i]), axis[i]);
          model = glm::scale(model, scales[i]);
          // world transformatiom
          lightingShader.setMat4("model", model);

          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, diffuseMap);

          glActiveTexture(GL_TEXTURE1);
          glBindTexture(GL_TEXTURE_2D, specularMap);

          glActiveTexture(GL_TEXTURE2);
          glBindTexture(GL_TEXTURE_2D, emissionMap);

          glBindVertexArray(cubeVAO_array[i]);
          glDrawArrays(GL_TRIANGLES, 0, 36);
      }


    // view/projection transformations
    glm::mat4 model = glm::mat4(1.0f);
      view = camera.GetViewMatrix();
      projection =
              glm::perspective(glm::radians(camera.Zoom),
                               (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // also draw the lamp object
    lampShader.use();
    lampShader.setMat4("projection", projection);
    lampShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos*glm::vec3(1.25f,1.25f,1.25f));
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

    lampShader.setMat4("model", model);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(num_objects, cubeVAO_array);
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteBuffers(num_objects, VBO_array);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

unsigned int loadTexture(char const *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {

        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposd, double yposd) {
  float xpos = static_cast<float>(xposd);
  float ypos = static_cast<float>(yposd);
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


