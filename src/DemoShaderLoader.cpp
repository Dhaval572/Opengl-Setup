#include <DemoShaderLoader.h>
#include <fstream>
#include <iostream>
#include <memory>

//path is used for error reporting
GLint CreateShaderFromData
(
	const char* data,
	GLenum shader_type,
	const char* path = nullptr
)
{
	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &data, nullptr);
	glCompileShader(shader_id);

	GLint result = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int log_length = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

		if (log_length)
		{
			std::string message(log_length, '\0');
			glGetShaderInfoLog
			(
				shader_id, 
				log_length, 
				&log_length, 
				message.data()
			);

			std::cout << "error compiling shader: ";
			if (path) { std::cout << path; }
			std::cout << "\n" << message << "\n";
		}
		else
		{
			if (path) { std::cout << path << " "; }
			std::cout << "unknown error while compiling shader :(\n";
		}

		glDeleteShader(shader_id);

		shader_id = 0;
		return shader_id;
	}

	return shader_id;
}


GLint CreateShaderFromFile(const char* name, GLenum shader_type)
{
	std::ifstream f(name);
	std::string str;

	if (!f.is_open())
	{
		std::cout << "Error opening file: " + std::string(name) << "\n";
		return 0;
	}

	f.seekg(0, std::ios::end);
	str.reserve(f.tellg());
	f.seekg(0, std::ios::beg);

	if (str.capacity() <= 0)
	{
		std::cout << "Error opening file: " + std::string(name) << "\n";
		return 0;
	}

	str.assign
	(
		(std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>()
	);
	auto result = CreateShaderFromData(str.c_str(), shader_type, name);

	return result;
}

bool Shader::b_LoadShaderProgramFromData
(
	const char* vertex_shader_data,
	const char* fragment_shader_data
)
{
	GLint vertex_id =
	CreateShaderFromData
	(
		vertex_shader_data,
		GL_VERTEX_SHADER
	);

	GLint fragment_id =
	CreateShaderFromData
	(
		fragment_shader_data,
		GL_FRAGMENT_SHADER
	);

	if (vertex_id == 0 || fragment_id == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);

	glLinkProgram(id);

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		int log_length = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

		std::string message(log_length, '\0');

		glGetProgramInfoLog(id, log_length, &log_length, message.data());
		std::cout << std::string("Link error: ") + message << "\n";
		glDeleteProgram(id);
		id = 0;
		return 0;
	}
	glValidateProgram(id);

	return true;
}

bool Shader::b_LoadShaderProgramFromData
(
	const char* vertex_shader_data,
	const char* geometry_shader_data,
	const char* fragment_shader_data
)
{
	GLint vertex_id =
	CreateShaderFromData
	(
		vertex_shader_data,
		GL_VERTEX_SHADER
	);

	GLint geometry_id =
	CreateShaderFromData
	(
		geometry_shader_data,
		GL_GEOMETRY_SHADER
	);

	GLint fragment_id =
	CreateShaderFromData
	(
		fragment_shader_data,
		GL_FRAGMENT_SHADER
	);

	if (vertex_id == 0 || fragment_id == 0 || geometry_id == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertex_id);
	glAttachShader(id, geometry_id);
	glAttachShader(id, fragment_id);

	glLinkProgram(id);

	glDeleteShader(vertex_id);
	glDeleteShader(geometry_id);
	glDeleteShader(fragment_id);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		int log_length = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

		std::string message(log_length, '\0');
		glGetProgramInfoLog(id, log_length, &log_length, message.data());
		std::cout << std::string("Link error: ") + message << "\n";
		glDeleteProgram(id);
		id = 0;
		return 0;
	}
	glValidateProgram(id);

	return true;
}

bool Shader::b_LoadShaderProgramFromFile
(
	const char* vertex_shader,
	const char* fragment_shader
)
{

	GLint vertex_id =
	CreateShaderFromFile
	(
		vertex_shader,
		GL_VERTEX_SHADER
	);

	GLint fragment_id =
	CreateShaderFromFile
	(
		fragment_shader,
		GL_FRAGMENT_SHADER
	);

	if (vertex_id == 0 || fragment_id == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);

	glLinkProgram(id);

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		int log_length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

		std::string message(log_length, '\0');

		glGetProgramInfoLog(id, log_length, &log_length, message.data());

		std::cout << std::string("Link error: ") + message << "\n";
		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

bool Shader::b_LoadShaderProgramFromFile
(
	const char* vertex_shader,
	const char* geometry_shader,
	const char* fragment_shader
)
{
	GLint vertex_id =
	CreateShaderFromFile
	(
		vertex_shader,
		GL_VERTEX_SHADER
	);

	GLint geometry_id =
	CreateShaderFromFile
	(
		geometry_shader,
		GL_GEOMETRY_SHADER
	);

	GLint fragment_id =
	CreateShaderFromFile
	(
		fragment_shader,
		GL_FRAGMENT_SHADER
	);

	if (vertex_id == 0 || fragment_id == 0 || geometry_id == 0)
	{
		return 0;
	}

	id = glCreateProgram();
	glAttachShader(id, vertex_id);
	glAttachShader(id, geometry_id);
	glAttachShader(id, fragment_id);
	glLinkProgram(id);

	glDeleteShader(vertex_id);
	glDeleteShader(geometry_id);
	glDeleteShader(fragment_id);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		int log_length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

		std::string message(log_length, '\0');
		glGetProgramInfoLog(id, log_length, &log_length, message.data());
		std::cout << std::string("Link error: ") + message << "\n";
		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Clear()
{
	glDeleteProgram(id);
	id = 0;
}

GLint Shader::GetUniform(const char* name) const
{
	return ::GetUniform(this->id, name);
}

GLint GetUniform(GLuint shader_id, const char* name)
{
	GLint uniform = glGetUniformLocation(shader_id, name);
	if (uniform == -1)
	{
		std::cout << "uniform error " + std::string(name);
	}
	return uniform;
}
