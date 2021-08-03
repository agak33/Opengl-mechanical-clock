#include "scene.h"

Scene::Scene(const int& width, const int& height, 
			 const std::string& title,
			 const char* vertexShaderFile,
			 const char* geometryShaderFile,
			 const char* fragmentShaderFile)
{
	this->light_speed = 3.0f;
	this->time = .0f;
	this->light[0] = Light(glm::vec4(0, 5, -1, 1), this->light_speed, glm::vec3(0, -1, 0));
	this->light[1] = Light(glm::vec4(0, 5,  3, 1), this->light_speed, glm::vec3(0, -1, 0));

	glfwSetErrorCallback(&Scene::error_callback);
	if (!glfwInit()) { // Initialize GLFW library
		fprintf(stderr, "Failed to initialize GLFW library.\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!this->window) {	// Check if window was created
		fprintf(stderr, "Failed to create a window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) { // Initialize GLEW library
		fprintf(stderr, "Failed to initialize GLEW library.\n");
		exit(EXIT_FAILURE);
	}

	this->shader = new ShaderProgram(vertexShaderFile, geometryShaderFile, fragmentShaderFile);
	initOpenGLProgram(this->window);
}

Scene::~Scene() {
	delete this->shader;
	for (auto& element : this->models) {
		delete element;
	}
	freeOpenGLProgram(this->window);
	glfwDestroyWindow(this->window);
	glfwTerminate();
	std::cout << "Scene has been deleted successfully." << std::endl;
}

void Scene::add_static_model(const std::string& object_file, 
							 const std::string& texture_file, 
							 const std::string& specular_file) {
	this->models.push_back(new StaticObj(object_file, texture_file, specular_file));
}

void Scene::add_hand_model(	int kind, 
							const std::string& object_file,
							const std::string& texture_file,
							const std::string& specular_file, 
							const glm::vec3&   origin) {
	this->models.push_back(new Hand(kind, object_file, texture_file, specular_file, origin));
}

void Scene::add_pendulum_model(	const float& max_yaw, 
								const std::string& object_file, 
								const std::string& texture_file,
								const std::string& specular_file, 
								const glm::vec3& origin) {
	this->models.push_back(new Pendulum(max_yaw, object_file, texture_file, specular_file, origin));
}

void Scene::add_gear_model(	bool left_direction, 
							const float& pitch_num, 
							const std::string& object_file,
							const std::string& texture_file,
							const std::string& specular_file,
							const glm::vec3& origin) {
	this->models.push_back(new Gear(left_direction, pitch_num, object_file, texture_file, specular_file, origin));
}

void Scene::drawElement(const Model* element) {
	// pass texture handle
	glUniform1i(shader->u("tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, element->tex);

	// pass specular handle
	glUniform1i(shader->u("spec"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, element->spec);

	// pass pointer to vector with vertices positions
	glEnableVertexAttribArray(shader->a("vertex"));
	glVertexAttribPointer(shader->a("vertex"), 4, GL_FLOAT, false, 0, element->vertex_positions.data());

	// pass pointer to vector with normal vectors
	glEnableVertexAttribArray(shader->a("normal"));
	glVertexAttribPointer(shader->a("normal"), 4, GL_FLOAT, false, 0, element->vertex_normals.data());

	// pass pointer to vector with vertices positions on the texture
	glEnableVertexAttribArray(shader->a("texCoord0"));
	glVertexAttribPointer(shader->a("texCoord0"), 2, GL_FLOAT, false, 0, element->vertex_texcoords.data());

	glDrawArrays(GL_TRIANGLES, 0, element->vertexCount);

	glDisableVertexAttribArray(shader->a("vertex"));
	glDisableVertexAttribArray(shader->a("color"));
	glDisableVertexAttribArray(shader->a("normal"));
	glDisableVertexAttribArray(shader->a("texCoord0"));
}

void Scene::draw(const float& dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// perspective matrix
	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, this->aspectRatio, 0.01f, 100.0f);
	// view matrix
	glm::mat4 V_Scene = glm::lookAt(glm::vec3(0.0f, 1.0f, 10.0f),
									glm::vec3(0.0f, 1.0f, -10.0f),
									glm::vec3(.0f, 1.0f, .0f));
	// enable shader
	this->shader->use();
	glUniformMatrix4fv(this->shader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(this->shader->u("V"), 1, false, glm::value_ptr(this->camera.V));
	glUniformMatrix4fv(this->shader->u("V_Scene"), 1, false, glm::value_ptr(V_Scene));

	glm::vec4 l[] = { this->light[0].light_pos, this->light[1].light_pos };
	glUniform4fv(shader->u("light_pos"), 2, &l[0].r);

	for (auto& element : this->models) {
		element->update(this->time);
		glUniformMatrix4fv(this->shader->u("M"), 1, false, glm::value_ptr(element->M));
		drawElement(element);
	}
	glfwSwapBuffers(this->window);
}

void Scene::run() {
	glfwSetTime(0);
	while (!glfwWindowShouldClose(this->window)) {
		float dt = (float)glfwGetTime();
		glfwSetTime(0);
		this->time += dt;

		glfwPollEvents();
		this->light[0].update(dt);
		this->light[1].update(dt);
		this->camera.updateCamera(dt, this->speed_x, this->speed_z, this->offsetX, this->offsetY);
		draw(dt);
	}
}


float Scene::speed_x   = .0f, Scene::speed_z   = .0f;
float Scene::prev_xpos = .0f, Scene::prev_ypos = .0f;
float Scene::offsetX   = .0f, Scene::offsetY   = .0f;
bool  Scene::mouse_clicked = false;
float Scene::aspectRatio = 1.0f;

void Scene::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			speed_x = -2.0f;
		}
		else if (key == GLFW_KEY_RIGHT) {
			speed_x = 2.0f;
		}

		if (key == GLFW_KEY_UP) {
			speed_z = -2.0f;
		}
		else if (key == GLFW_KEY_DOWN) {
			speed_z = 2.0f;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			speed_x = 0;
		}
		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
			speed_z = 0;
		}
	}
}

void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouse_clicked) {
		offsetX = (prev_xpos - (float)xpos) * 0.1f;
		offsetY = (prev_ypos - (float)ypos) * 0.1f;
	}
	else {
		offsetX = 0.0f;
		offsetY = 0.0f;
	}
	prev_xpos = (float)xpos;
	prev_ypos = (float)ypos;
}

void Scene::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		mouse_clicked = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		mouse_clicked = false;
}

void Scene::initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0, 0.5, 0.5, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Scene::freeOpenGLProgram(GLFWwindow* window) { }
