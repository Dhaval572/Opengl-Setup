#include <array>
#include <DemoShaderLoader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex + Color data
std::array<GLfloat, 15> vertices =
{
    // positions    // colors
     0.0f,  0.9f,   1.0f, 0.0f, 0.0f,
     0.9f, -0.9f,   0.0f, 1.0f, 0.0f,
    -0.9f, -0.9f,   0.0f, 0.0f, 1.0f
};

int main()
{
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
    glfwCreateWindow
    (
        640, 480, "RGB Triangle", nullptr, nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    Shader s1;
    s1.b_LoadShaderProgramFromFile
    (
        "resources/Simple.vert", 
        "resources/Simple.frag"
    );

    // Setup VAO and VBO ( vertex array object and vertex buffer object )
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData
    (
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Position attribute
    glVertexAttribPointer
    (
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void*>(0)
    );
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer
    (
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void*>(2 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // Print OpenGL info
    std::cout << "OpenGL version: "
        << glGetString(GL_VERSION)
        << std::endl;

    std::cout << "GLSL version: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << std::endl;

    std::cout << "Renderer: "
        << glGetString(GL_RENDERER)
        << std::endl;

    std::cout << "Vendor: "
        << glGetString(GL_VENDOR)
        << std::endl;

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        s1.bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup OpenGL objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    s1.clear();

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
