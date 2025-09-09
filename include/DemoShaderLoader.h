#pragma once
#include <glad/glad.h>

struct Shader
{
	GLuint id = 0;

	bool b_LoadShaderProgramFromData
	(
		const char* vertex_shader_data,
		const char* fragment_shader_data
	);

	bool b_LoadShaderProgramFromData
	(
		const char* vertex_shader_data,
		const char* geometry_shader_data,
		const char* fragment_shader_data
	);

	bool b_LoadShaderProgramFromFile
	(
		const char* vertex_shader,
		const char* fragment_shader
	);

	bool b_LoadShaderProgramFromFile
	(
		const char* vertex_shader,
		const char* geometry_shader,
		const char* fragment_shader
	);

	void bind() const;

	void clear();

	GLint GetUniform(const char* name) const;
};

GLint GetUniform(GLuint shader_id, const char* name);
