#ifndef PIECE_H
#define PIECE_H

#include <glm/glm.hpp>

/* 
 *  Peça quadrada do tabuleiro do puzzle.
 *  a ordem dos vértices se encontra definida da seguinte forma:
 *  
 *  0---1
 *  |   |
 *  3---2
 *  
*/
class Piece{
private:
    glm::vec3 vr[4];  // vértices da peça quadrada
    glm::vec3 center;

public:
    Piece();
    Piece(float side_length);

    void setVertices(float side_length);
    glm::vec3* getVertices();
    void printVertices();
    
    void rotate(); // rotaciona a peça no sentido anti-horário
    void translate(float x, float y);

    void displayColor(float colors[4][3]);

    bool isSelected(float x, float y);
};

#endif // PIECE_H