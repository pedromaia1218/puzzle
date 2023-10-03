#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/gl.h>

#include <iostream>
#include <cstdlib>

#include "utils.h"
#include "piece.h"
#include "config.h"

void Piece::setVertices()
{
    this->vr[0] = glm::vec3(-0.5f, 0.5f, 1.0f);
    this->vr[1] = glm::vec3( 0.5f, 0.5f, 1.0f);
    this->vr[2] = glm::vec3( 0.5f,-0.5f, 1.0f);
    this->vr[3] = glm::vec3(-0.5f,-0.5f, 1.0f);

    this->center = glm::vec3(0.0f, 0.0f, 1.0f);
}

Piece::Piece()
{
    this->setVertices();
    this->l = 1;
    selected = false;
}
Piece::Piece(float edge_length)
{
    this->setVertices();

    glm::mat3 S = scale2D(edge_length, edge_length);

    for(int i=0; i<4; i++)
    {
        this->vr[i] = S * this->vr[i];
    }

    this->l = edge_length;
    selected = false;
}

bool Piece::isSelected()
{
    return selected;
}

glm::vec3 Piece::getCenter()
{
    return this->center;
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
    // condicional para evitar que a peça passe dos limites do tabuleiro
    
    float half_l = (this->l)/2;

    if(center[0]+half_l + x > world_xmax) x = world_xmax-half_l - center[0];
    if(center[0]-half_l + x < world_xmin) x = world_xmin+half_l - center[0];
    if(center[1]+half_l + y > world_ymax) y = world_ymax-half_l - center[1];
    if(center[1]-half_l + y < world_ymin) y = world_ymin+half_l - center[1];

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

bool Piece::handleSelection(float x, float y)
{
    /* O método é baseado na seguinte fórmula, que quando satisfeita para um ponto M,
     * define M como interno ao quadrado/retângulo 
     * (0 < AM⋅AB < AB⋅AB) e (0 < AM⋅AC < AC⋅AC)
     * 
     * Considere um quadrado/retângulo no formato abaixo para a fórmula acima.
     * A---B
     * |   |
     * C---D
     *
    */
    
    glm::vec3 m = glm::vec3(x, y, 1.0f);

    glm::vec3 a = this->vr[0]; 
    glm::vec3 b = this->vr[1];
    glm::vec3 c = this->vr[3];

    glm::vec3 am = m-a;
    glm::vec3 ab = b-a;
    glm::vec3 ac = c-a;

    float sizeof_proj_am_ab = glm::dot(am, ab);
    float sizeof_proj_am_ac = glm::dot(am, ac);
    float mod_ab = glm::dot(ab, ab);
    float mod_ac = glm::dot(ac, ac);

    return this->selected =
        (sizeof_proj_am_ab > 0)      and
        (sizeof_proj_am_ab < mod_ab) and
        (sizeof_proj_am_ac > 0)      and
        (sizeof_proj_am_ac < mod_ac);
}