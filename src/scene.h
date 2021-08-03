#pragma once
#include "constants.h"
#include "shaderprogram.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include "staticObj.h"
#include "hand.h"
#include "pendulum.h"
#include "gear.h"

/*
* Class to create 3D scene with all object, lights etc.
*/
class Scene
{
private:
	static float speed_x;
	static float speed_z;
	static float aspectRatio;
	static float prev_xpos;
	static float prev_ypos;
	static float offsetX;
	static float offsetY;
	static bool  mouse_clicked;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void initOpenGLProgram(GLFWwindow* window);
	static void freeOpenGLProgram(GLFWwindow* window);

public:
	GLFWwindow* window;
	ShaderProgram* shader;
	std::vector<Model*> models;
	Light light[2];
	Camera camera;

	float light_speed;
	float time;

	Scene(const int& width = 700, const int& height = 700,
		  const std::string& title		 = "Mechanical clock",
		  const char* vertexShaderFile	 = "src/shaders/v_tex.glsl",
		  const char* geometryShaderFile = NULL,
		  const char* fragmentShaderFile = "src/shaders/f_tex.glsl");

	~Scene();

	void add_static_model(	const std::string& object_file,
							const std::string& texture_file,
							const std::string& specular_file);

	void add_hand_model(int kind,
						const std::string& object_file,
						const std::string& texture_file,
						const std::string& specular_file,
						const glm::vec3& origin);

	void add_pendulum_model(const float& max_yaw,
							const std::string& object_file,
							const std::string& texture_file,
							const std::string& specular_file,
							const glm::vec3& origin);

	void add_gear_model(bool left_direction,
						const float& pitch_num,
						const std::string& object_file,
						const std::string& texture_file,
						const std::string& specular_file,
						const glm::vec3& origin);

	void drawElement(const Model* element);
	void draw(const float& dt);
	void run();
};

