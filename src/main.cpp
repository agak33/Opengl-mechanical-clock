#include "scene.h"

int main()
{
	
	Scene* scene = new Scene();

	scene->add_static_model("models/box.obj",
							"textures/wooden_texture.png",
							"textures/wooden_texture_specular.png");

	scene->add_static_model("models/clockface.obj",
							"textures/clockface_texture.png",
							"textures/clockface_texture_specular.png");

	scene->add_static_model("models/clock_face_cylinder.obj",
							"textures/metal_texture.png",
							"textures/metal_texture_specular.png");

	scene->add_gear_model(false, 32, "models/gear_left.obj",
							"textures/metal_texture.png",
							"textures/metal_texture_specular.png",
							glm::vec3(-0.405039f, 1.03836f, 0.746941f));

	scene->add_gear_model(  true, 32, "models/gear_right.obj",
							"textures/metal_texture.png",
							"textures/metal_texture_specular.png",
							glm::vec3(0.407197f, 1.041f, 0.746941f));

	scene->add_hand_model(2, "models/hour_hand.obj",
							"textures/hour_hand_texture.png",
							"textures/hour_hand_texture.png",
							glm::vec3(0.001027f, 2.19141f, 1.0437f));

	scene->add_hand_model(1, "models/minute_hand.obj",
							"textures/minute_hand_texture.png",
							"textures/minute_hand_texture.png",
							glm::vec3(0.001027f, 2.19141f, 1.0437f));

	scene->add_hand_model(0, "models/second_hand.obj",
							"textures/second_hand_texture.png", 
							"textures/second_hand_texture.png",
							glm::vec3(0.001027f, 2.19141f, 1.0437f));

	scene->add_pendulum_model(40, "models/pendulum.obj",
							  "textures/metal_texture.png", 
							  "textures/metal_texture_specular.png",
							  glm::vec3(-0.000039f, 1.08f, 0.657218f));
	
	scene->run();

	delete scene;
	exit(EXIT_SUCCESS);
}

