#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>


enum class CameraMode {
    FirstPerson,
    ThirdPerson
};

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec2& orientation);
    
    glm::mat4 getFirstPersonViewMatrix();
    glm::mat4 getThirdPersonViewMatrix();
    void toggleMode(); // pour basculer entre les modes
    CameraMode getMode();
    
private:
    const glm::vec3& m_position;
    const glm::vec2& m_orientation;
    CameraMode m_mode;
    float m_radius = 6.0f;

};


#endif // CAMERA_H
