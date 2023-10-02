#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/gl.h>
#include <iostream>

#include "utils.h"
#include "piece.h"

void Piece::setVertices(float side_length)
{
    float half_length = side_length/2.0f;
    this->vr[0] = glm::vec3(-half_length, half_length, 1.0f);
    this->vr[1] = glm::vec3( half_length, half_length, 1.0f);
    this->vr[2] = glm::vec3( half_length,-half_length, 1.0f);
    this->vr[3] = glm::vec3(-half_length,-half_length, 1.0f);

    this->center = glm::vec3(0.0f, 0.0f, 1.0f);
}

Piece::Piece()
{
    this->setVertices(1.0f);
}
Piece::Piece(float side_length)
{
    this->setVertices(side_length);
}

glm::vec3* Piece::getVertices()
{
    return this->vr;
}

void Piece::printVertices()
{
    std::cout << glm::to_string(this->vr[0]) << " " << glm::to_string(this->vr[1]) << std::endl;
    std::cout << glm::to_string(this->vr[3]) << " " << glm::to_string(this->vr[2]) << std::endl;
}

void Piece::rotate()
{
    glm::mat3 translate_to_origin = translation2D(-this->center[0], -this->center[1]);
    glm::mat3 rotate_on_origin = rotation2D();
    glm::mat3 translate_back = translation2D(this->center[0], this->center[1]);
    
    glm::mat3 local_rotate = translate_back * rotate_on_origin * translate_to_origin;

    std::cout << glm::to_string(local_rotate) << std::endl;
    for(int i=0; i<4; i++)
    { 
        this->vr[i] = local_rotate * this->vr[i];
    }
}
void Piece::translate(float x, float y)
{
    glm::mat3 T = translation2D(x,y);

    for(int i=0; i<4; i++)
    {
        this->vr[i] = T * this->vr[i];
    }
    this->center = T * this->center;
}

void Piece::displayColor(float colors[4][3])
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<4; i++)
    {
        glColor3fv(colors[i]);
        glVertex3fv(glm::value_ptr(this->vr[i]));
    }
    glEnd();
}

// TODO: Implementar outro método de display só que com textura 

bool Piece::isSelected(float x, float y)
{
    float x_min = this->vr[0][0];
    float x_max = this->vr[1][0];
    float y_min = this->vr[0][1];
    float y_max = this->vr[3][1];
    
    return (x>x_min) and (x<x_max) and (y>y_min) and (y<y_max);
}