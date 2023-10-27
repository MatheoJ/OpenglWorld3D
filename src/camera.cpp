#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

Camera::Camera(const glm::vec3& position, const glm::vec2& orientation):
	m_position(position),
	m_orientation(orientation)

{
	m_mode = CameraMode::FirstPerson;

}

glm::mat4 Camera::getFirstPersonViewMatrix()
{
	GLfloat yaw = m_orientation.x;
	GLfloat pitch = m_orientation.y;

	//Get indentity matrix
	glm::mat4 viewMatrix = glm::mat4(1.0f);

	
	viewMatrix = glm::rotate( viewMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = glm::rotate( viewMatrix, pitch, glm::vec3(cos(yaw), 0.0f, sin(yaw)));
	viewMatrix = glm::translate(viewMatrix, -m_position);
	

	return viewMatrix;
}

glm::mat4 Camera::getThirdPersonViewMatrix() {

	GLfloat yaw = m_orientation.x;
	GLfloat pitch = m_orientation.y;

	float x = - m_radius * cos(pitch) * sin(yaw);
	float y = m_radius * sin(pitch);
	float z = m_radius * cos(pitch) * cos(yaw);

	glm::vec3 cameraPos = m_position + glm::vec3(x, y, z);
	return glm::lookAt(cameraPos, m_position, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::toggleMode() {
	if (m_mode == CameraMode::FirstPerson) {
		m_mode = CameraMode::ThirdPerson;
	}
	else {
		m_mode = CameraMode::FirstPerson;
	}
}


CameraMode Camera::getMode() {
	return m_mode;
}



