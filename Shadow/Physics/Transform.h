#pragma once

#include <glm/glm.hpp>

/***
=========================================================================================
TRANSFORM:
	A transform stores a position, rotation as well as scale of an object. Rotation is in
	degrees and is the anti-clockwise angle about the corresponding axis.
=========================================================================================
*/
struct Transform
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
};

