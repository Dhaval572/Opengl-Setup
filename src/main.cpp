#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex + Color data
std::array<float, 15> vertices =
{
    // positions    // colors
     0.0f,  0.8f,   1.0f, 0.0f, 0.0f,
     0.8f, -0.8f,   0.0f, 1.0f, 0.0f,
    -0.8f, -0.8f,   0.0f, 0.0f, 1.0f
};

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
void main() 
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)";

// Fragment shader
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() 
{
    FragColor = vec4(vColor, 1.0);
}
)";

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

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

    // Compile vertex shader
    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(v_shader);

    // Compile fragment shader
    unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(f_shader);

    // Link shaders into program
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);

    // Delete shader objects after linking
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    // Setup VAO and VBO (vertex array object and vertex buffer object)
    unsigned int VAO, VBO;
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
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup OpenGL objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
