#include "Animation2D.h"

#define SPEED 0.0125


void Animation2D::init(const char* filename)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// link and initialize shader programs
	GLApp::insert_shdrpgm("animation", "../shaders/Animation.vert", "../shaders/Animation.frag");

	// vertices & indices
	float vertices[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	float x_dir = 0.0f, y_dir = 0.0f;

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(GL_TRUE);
	unsigned char* img_data = stbi_load(filename, &width, &height, &nrChannels, 0);

	if (img_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}
	else
	{
		std::cout << " Failed to load texture" << std::endl;
	}

	stbi_image_free(img_data);


	// initialize delta time
	float nx_frames = 8.0f, ny_frames = 4.0f;
	float uv_x = 0.0f, uv_y = 2.0f;


	double time_now, time_old, time_delta, frames_ps;
	frames_ps = 4.0f;
	time_now = time_old = glfwGetTime();

	// loop
	while (!glfwWindowShouldClose(GLHelper::ptr_window))
	{
		// read keyboard
		Animation2D::readKeyboard(GLHelper::ptr_window, &x_dir, &y_dir);
	}
	time_now = glfwGetTime();
	time_delta = time_now - time_old;
	if (time_delta >= 1.0f / frames_ps) {
		time_old = time_now;
		time_delta = 0.0f;
		uv_x += 1.0f;
		if (uv_x >= nx_frames) {
			uv_x = 0.0f;
		}
	}

	GLuint hdlr = GLApp::shdrpgms["animation"].GetHandle();

	glUseProgram(hdlr);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1f(glGetUniformLocation(hdlr, "x_dir"), x_dir);
	glUniform1f(glGetUniformLocation(hdlr, "y_dir"), y_dir);
	glUniform1f(glGetUniformLocation(hdlr, "uv_x"), uv_x);
	glUniform1f(glGetUniformLocation(hdlr, "uv_y"), uv_y);
	glUniform1f(glGetUniformLocation(hdlr, "nx_frames"), nx_frames);
	glUniform1f(glGetUniformLocation(hdlr, "ny_frames"), ny_frames);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(GLHelper::ptr_window);
	glfwPollEvents();
}

/*void Animation2D::draw()
{
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1f(glGetUniformLocation(shaderProgram, "x_dir"), x_dir);
	glUniform1f(glGetUniformLocation(shaderProgram, "y_dir"), y_dir);
	glUniform1f(glGetUniformLocation(shaderProgram, "uv_x"), uv_x);
	glUniform1f(glGetUniformLocation(shaderProgram, "uv_y"), uv_y);
	glUniform1f(glGetUniformLocation(shaderProgram, "nx_frames"), nx_frames);
	glUniform1f(glGetUniformLocation(shaderProgram, "ny_frames"), ny_frames);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
*/

void Animation2D::readKeyboard(GLFWwindow* window, float* x_direction, float* y_direction)
{
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		*y_direction += SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		*y_direction -= SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		*x_direction -= SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		*x_direction += SPEED;
	}
}