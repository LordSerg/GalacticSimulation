#pragma once
#include "GLFW/glfw3.h"
#include <glm.hpp>
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
class ICamera {
public:

    virtual void setPerspective(float fov, float aspect, float near, float far)
    {

    };

    virtual void setPos(glm::vec3 pos)
    {
    };

    virtual void setTarget(glm::vec3 pos)
    {

    };
    virtual glm::vec3 getPos() = 0;
    virtual void Start()
    {

    };
    virtual void End()
    {

    };
protected:
    glm::mat4 _modelproj = glm::mat4(0.0f);
    glm::vec3 _pos = glm::vec3(0.0f);
    glm::vec3 _direction = glm::vec3(0.0f);
    glm::mat4 _modelview = glm::mat4(0.0f);

};

class GLCameraTarget //: public ICamera
{
    glm::mat4 _modelproj = glm::mat4(0.0f);
    glm::vec3 _pos = glm::vec3(0.0f);
    glm::vec3 _direction = glm::vec3(0.0f);
    glm::mat4 _modelview = glm::mat4(0.0f);
public:

    void setPerspective(float fov, float aspect, float near1, float far1)
    {
        /*
        // Calculate The Aspect Ratio Of The Window
        // The parameters are:
        // (view angle, aspect ration of the width to the height,
        //  The closest distance to the camera before it clips,
        // FOV, Ratio,  The farthest distance before it stops drawing)
         */

        glMatrixMode(GL_PROJECTION);
        _modelproj = glm::perspective(fov, aspect, near1, far1);
        glLoadMatrixf(glm::value_ptr(_modelproj));


    }

    void setPos(glm::vec3 pos, glm::vec3 someShit)
    {
        glm::vec3 target = someShit;// glm::vec3(0.0f);//
        glm::vec3 direction = glm::normalize(pos - target);
        _modelview = glm::lookAt(pos, direction, glm::vec3(0, 1, 0));
        _pos = pos;
        _direction = direction;
        //glMatrixMode(...);
        //glLoadMatrixf(...);

    }
    void Start()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(glm::value_ptr(_modelview));
    }
    void End()
    {
        glPopMatrix();
    }

    glm::vec3 getPos()
    {
        return _pos;
    }
    glm::vec3 getDir()
    {
        return _direction;
    }
};