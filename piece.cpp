#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
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

void Piece::displayVertices()
{
    std::cout << glm::to_string(this->vr[0]) << " " << glm::to_string(this->vr[1]) << std::endl;
    std::cout << glm::to_string(this->vr[3]) << " " << glm::to_string(this->vr[2]) << std::endl;
}

void Piece::rotate()
{
    glm::mat3 R90 = glm::rotate(I, glm::radians(90.0f), center);
    for(int i=0; i<4; i++)
    { 
        this->vr[i] = R90 * this->vr[i];
    }
}
void Piece::translate(float x, float y)
{
    glm::mat3 T = glm::translate(I, glm::vec3(x,y,0));
    for(int i=0; i<4; i++)
    { 
        this->vr[i] = T * this->vr[i];
    }
    this->center = T * this->center;
}