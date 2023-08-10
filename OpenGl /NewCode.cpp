#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnOpengl/camera.h>

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
const char* const WINDOW_TITLE = "Tutorial 3.4"; // Macro for window title

// Variables for window width and height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Stores the GL data relative to a given mesh
struct GLMesh
{
    GLuint vao;         // Handle for the vertex array object
    GLuint vbos[2];     // Handles for the vertex buffer objects
    GLuint nIndices;    // Number of indices of the mesh
};

// Main GLFW window
GLFWwindow* gWindow = nullptr;
// Triangle mesh data
GLMesh gMesh;
// Shader program
GLuint gProgramId;

// camera
Camera gCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;

// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char*[], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void UCreateMesh(GLMesh &mesh);
void UDestroyMesh(GLMesh &mesh);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint &programId);
void UDestroyShaderProgram(GLuint programId);


/* Vertex Shader Source Code*/
const GLchar * vertexShaderSource = GLSL(440,
    layout (location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
    layout (location = 1) in vec4 color;  // Color data from Vertex Attrib Pointer 1

    out vec4 vertexColor; // variable to transfer color data to the fragment shader

    //Global variables for the  transform matrices
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
        vertexColor = color; // references incoming color data
    }
);


/* Fragment Shader Source Code*/
const GLchar * fragmentShaderSource = GLSL(440,
    in vec4 vertexColor; // Variable to hold incoming color data from vertex shader

    out vec4 fragmentColor;

    void main()
    {
        fragmentColor = vec4(vertexColor);
    }
);


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    UCreateMesh(gMesh); // Calls the function to create the Vertex Buffer Object

    // Create the shader program
    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {

        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;


        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(gMesh);

    // Release shader program
    UDestroyShaderProgram(gProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;
    float velocity = cameraSpeed * gDeltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.Position -= gCamera.Up * velocity;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.Position += gCamera.Up * velocity;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}


// Functioned called to render a frame
void URender()
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);
    
    // Clear the frame and z buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. Scales the object by 2
    glm::mat4 scale = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
    // 2. Rotates shape by 15 degrees in the x axis
    glm::mat4 rotation = glm::rotate(62.0f, glm::vec3(1.0, 1.0f, 1.0f));
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * scale;

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Set the shader to be used
    glUseProgram(gProgramId);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(gProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gProgramId, "view");
    GLint projLoc = glGetUniformLocation(gProgramId, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.vao);

    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, NULL); // Draws the triangle

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}


// Implements the UCreateMesh function
void UCreateMesh(GLMesh &mesh)
{
     // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Colors (r,g,b,a)
        // These are all points to form the desk top, as well as the individual points for the towwers that house the drawers
         1.0f,  0.5f, 0.0f,   0.545f, 0.271f, 0.075f, 1.0f, // Point A = 0
         1.0f, -0.5f, 0.0f,   0.545f, 0.271f, 0.075f, 1.0f, // Point B = 1
        -1.0f, -0.5f, 0.0f,   0.545f, 0.271f, 0.075f, 1.0f, // Point C = 2
        -1.0f,  0.5f, 0.0f,   0.545f, 0.271f, 0.075f, 1.0f, // Point D = 3

        -1.0f,  0.5f,  0.2f,  0.545f, 0.271f, 0.075f, 1.0f, // Point E = 4
         1.0f,  0.5f,  0.2f,  0.545f, 0.271f, 0.075f, 1.0f, // Point F = 5
        -1.0f, -0.5f,  0.2f,  0.545f, 0.271f, 0.075f, 1.0f, // Point G = 6
         1.0f, -0.5f,  0.2f,  0.545f, 0.271f, 0.075f, 1.0f, // Point H = 7

        -1.0f, -0.5f, -0.6f,  1.0f,   0.0f,   0.0f,   1.0f, // Point I = 8
        -0.5f, -0.5f, -0.6f,  1.0f,   0.0f,   0.0f,   1.0f, // Point J = 9
        -1.0f,  0.5f, -0.6f,  1.0f,   0.0f,   0.0f,   1.0f, // Point K = 10
        -0.5f,  0.5f, -0.6f,  1.0f,   0.0f,   0.0f,   1.0f, // Point L = 11

        -0.5f, -0.5f,  0.0f,  1.0f,   1.0f,   0.0f,   1.0f, // Point M = 12
        -0.5f,  0.5f,  0.0f,  1.0f,   1.0f,   0.0f,   1.0f, // Point N = 13
         0.5f,  0.5f,  0.0f,  1.0f,   1.0f,   0.0f,   1.0f, // Point O = 14
         0.5f, -0.5f,  0.0f,  1.0f,   1.0f,   0.0f,   1.0f, // Point P = 15

         0.5f, -0.5f, -0.6f,  1.0f,   1.0f,   1.0f,   1.0f, // Point Q = 16
         0.5f,  0.5f, -0.6f,  1.0f,   1.0f,   1.0f,   1.0f, // Point R = 17
         1.0f, -0.5f, -0.6f,  1.0f,   1.0f,   1.0f,   1.0f, // Point S = 18
         1.0f,  0.5f, -0.6f,  1.0f,   1.0f,   1.0f,   1.0f, // Point T = 19

         //These are all points that will form the walls and floor
        -2.5f,  1.5f, -0.6f,  0.980f, 0.922f, 0.843f, 1.0f, // Point U = 20
        -2.5f, -1.5f, -0.6f,  0.980f, 0.922f, 0.843f, 1.0f, // Point V = 21
         2.5f, -1.5f, -0.6f,  0.980f, 0.922f, 0.843f, 1.0f, // Point W = 22
         2.5f,  1.5f, -0.6f,  0.980f, 0.922f, 0.843f, 1.0f, // Point X = 23

        -2.5f,  1.5f,  1.0f,  0.941f, 1.0f, 0.941f, 1.0f, // Point A1 = 24
        -2.5f, -1.5f,  1.0f,  0.941f, 1.0f, 0.941f, 1.0f, // Point B1 = 25
         2.5f,  1.5f,  1.0f,  0.941f, 1.0f, 0.941f, 1.0f, // Point C1 = 26
         2.5f, -1.5f,  1.0f,  0.941f, 1.0f, 0.941f, 1.0f, // Point D1 = 27

         //These are all points that will form the drawer faces
        -0.95f,-0.5f,-0.09f,  0.627f, 0.322f, 0.176f, 1.0f, // Point E1 = 28
        -0.95f,-0.5f, -0.2f,  0.627f, 0.322f, 0.176f, 1.0f, // Point F1 = 29
        -0.55f,-0.5f, -0.2f,  0.627f, 0.322f, 0.176f, 1.0f, // Point G1 = 30
        -0.55f,-0.5f,-0.09f,  0.627f, 0.322f, 0.176f, 1.0f, // Point H1 = 31

        -0.95f,-0.5f,-0.25f,  0.627f, 0.322f, 0.176f, 1.0f, // Point I1 = 32
        -0.55f,-0.5f,-0.25f,  0.627f, 0.322f, 0.176f, 1.0f, // Point J1 = 33
        -0.95f,-0.5f,-0.36f,  0.627f, 0.322f, 0.176f, 1.0f, // Point K1 = 34
        -0.55f,-0.5f,-0.36f,  0.627f, 0.322f, 0.176f, 1.0f, // Point L1 = 35

        -0.55f,-0.5f,-0.41f,  0.627f, 0.322f, 0.176f, 1.0f, // Point M1 = 36
        -0.55f,-0.5f,-0.52f,  0.627f, 0.322f, 0.176f, 1.0f, // Point N1 = 37
        -0.95f,-0.5f,-0.41f,  0.627f, 0.322f, 0.176f, 1.0f, // Point O1 = 38
        -0.95f,-0.5f,-0.52f,  0.627f, 0.322f, 0.176f, 1.0f, // Point P1 = 39

         0.95f,-0.5f,-0.09f,  0.627f, 0.322f, 0.176f, 1.0f, // Point Q1 = 40
         0.55f,-0.5f,-0.09f,  0.627f, 0.322f, 0.176f, 1.0f, // Point R1 = 41
         0.55f,-0.5f, -0.2f,  0.627f, 0.322f, 0.176f, 1.0f, // Point S1 = 42
         0.95f,-0.5f, -0.2f,  0.627f, 0.322f, 0.176f, 1.0f, // Point T1 = 43

         0.55f,-0.5f,-0.25f,  0.627f, 0.322f, 0.176f, 1.0f, // Point U1 = 44
         0.55f,-0.5f,-0.36f,  0.627f, 0.322f, 0.176f, 1.0f, // Point V1 = 45
         0.95f,-0.5f,-0.25f,  0.627f, 0.322f, 0.176f, 1.0f, // Point W1 = 46
         0.95f,-0.5f,-0.36f,  0.627f, 0.322f, 0.176f, 1.0f, // Point Z1 = 47

         0.95f,-0.5f,-0.41f,  0.627f, 0.322f, 0.176f, 1.0f, // Point A2 = 48
         0.95f,-0.5f,-0.52f,  0.627f, 0.322f, 0.176f, 1.0f, // Point B2 = 49
         0.55f,-0.5f,-0.41f,  0.627f, 0.322f, 0.176f, 1.0f, // Point C2 = 50
         0.55f,-0.5f,-0.52f,  0.627f, 0.322f, 0.176f, 1.0f, // Point D2 = 51

    };

    // Index data to share position data
    GLushort indices[] = {
        //These points will create the desktop into a 3D piece. All sides will be brown
        0, 1, 2,   // Triangle 1
        2, 3, 0,   // Triangle 2
        4, 5, 7,  //  Triangle 3
        4, 6, 7,   // Triangle 4
        0, 7, 1,   // Triangle 5
        7, 0, 5,   // Triangle 6
        4, 2, 3,   // Triangle 7
        4, 2, 6,   // Triangle 8
        6, 1, 2,   // Triangle 9
        6, 1, 7,   // Triangle 10
        5, 3, 0,   // Triangle 11
        5, 3, 4,   // Triangle 12

        //These points will create the desk towers for the drawers
        //These points are for the right tower
        1, 19, 18, // Triangle 13
        1, 19, 0,  // Triangle 14
        14, 15, 16,// Triangle 15
        14, 16, 17,// Triangle 16
        17, 19, 18,// Triangle 17
        17, 18, 16,// Triangle 18
        0, 17, 14, // Triangle 19
        0, 17, 19, // Triangle 20
        15, 18, 16,// Triangle 21
        15, 18, 1, // Triangle 22

        //These point are for the left tower
        2, 9, 8,   // Triangle 23
        2, 9, 12,  // Triangle 24
        3, 8, 10,  // Triangle 25
        3, 8, 2,   // Triangle 26
        13, 10, 3, // Triangle 27
        13, 10, 11,// Triangle 28
        13, 9, 10, // Triangle 29
        12, 13, 9, // Triangle 30
        10, 9, 11, // Triangle 31
        10, 9, 8,  // Triangle 32

        //These points are for floor
        22, 21, 20,// Triangle 33
        20, 22, 23,// Triangle 34

        //These points are for the walls
        //These points are for the left wall
        25, 20, 21,// Triangle 35
        25, 20, 24,// Triangle 36

        //These points are for the back wall
        24, 23, 20,// Triangle 37
        24, 23, 26,// Triangle 38

        //These points are for the right wall
        27, 23, 26,// Triangle 39
        27, 23, 22,// Triangle 40

        //These points are for the drawers on the front face of the desk towers
        //These points are the drawers on the right tower
        41, 43, 42,// Triangle 41
        41, 43, 40,// Triangle 42
        44, 47, 45,// Triangle 43
        44, 47, 46,// Triangle 44
        50, 49, 51,// Triangle 45
        50, 49, 48,// Triangle 46

        //These points are the drawers on the left tower
        28, 30, 29,// Triangle 47
        28, 30, 31,// Triangle 48
        32, 35, 34,// Triangle 49
        32, 35, 34,// Triangle 50
        38, 37, 36,// Triangle 51
        38, 37, 39 // Triangle 52

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride =  sizeof(float) * (floatsPerVertex + floatsPerColor);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);
}


void UDestroyMesh(GLMesh &mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}


// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint &programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}

