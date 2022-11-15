#include "Animation2D.h"


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
	unsigned char* img_data = stbi_load("../textures/walk.png", &width, &height, &nrChannels, 0);

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
		readKeyboard(GLHelper::ptr_window, &x_dir, &y_dir);
	}
}