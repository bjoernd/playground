#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

GLuint program = 0;
GLint  attribute_coord2d = -1;

int
init_resources()
{
	GLint compile_ok = GL_FALSE;
	GLint link_ok    = GL_FALSE;

	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	char const* shader_src =
		"#version 120\n"
		"attribute vec2 coord2d;\n"
		"void main(void) {\n"
		"  gl_Position = vec4(coord2d, 0.0, 1.0);\n"
		"}";

	glShaderSource(shader, 1, &shader_src, 0);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		fprintf(stderr, "Shader compilation failed\n");
		return 0;
	}
	
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	char const *frag_src = 
		"#version 120\n"
		"void main(void) {\n"
		"  gl_FragColor[0] = 0.0;\n"
		"  gl_FragColor[1] = 0.0;\n"
		"  gl_FragColor[2] = 1.0;\n"
		"}\n";
	glShaderSource(frag, 1, &frag_src, 0);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		fprintf(stderr, "Fragment shader compilation failed\n");
		return 0;
	}
	
	program = glCreateProgram();
	glAttachShader(program, shader);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (link_ok == GL_FALSE) {
		fprintf(stderr, "Program linking failed\n");
		return 0;
	}

	char const *attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}

	return 1;
}


void
onDisplay()
{
	glClearColor(1.0,  1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord2d);
	GLfloat triangle[] = {
		0.0,  0.8,
	   -0.8, -0.8,
	    0.8, -0.8,
	};
	
	glVertexAttribPointer(
						  attribute_coord2d, 2,
						  GL_FLOAT, GL_FALSE,
						  0, triangle);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attribute_coord2d);

	glutSwapBuffers();
}


void
free_resources()
{
	glDeleteProgram(program);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Triangle");
	
	GLenum glew_stat = glewInit();
	if (glew_stat != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_stat));
		return 1;
	}


	if (init_resources() == 1) {
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}

	free_resources();

	return 0;
}
