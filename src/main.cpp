#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow
	(
		640, 480, "RGB Triangle", nullptr, nullptr
	);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Compile vertex shader
	unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shader, 1, &vertexShaderSource, nullptr);
	glCompileShader(v_shader);

	// Compile fragment shader
	unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_shader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(f_shader);

	// Link program
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, v_shader);
	glAttachShader(shader_program, f_shader);
	glLinkProgram(shader_program);
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	// Setup VAO/VBO
	unsigned int VBO, VAO;
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

	// Main loop
	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}