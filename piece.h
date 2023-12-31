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
    glm::vec3 vr[4];  // vértices da peça quadrada (vetores bidimensionais com coord. homogêneas)
    glm::vec2 tx[4];  // coordenadas da textura da peça quadrada
    glm::vec3 center;
    glm::vec2 fit_spot; // posição em que o centro da peça se encaixa
    float l; // tamanho do lado do quadrado
    int rotated = 0; // flag que indica quantas vezes a peça foi rotacionada
    bool fit = false; // flag que indica se a peça já foi encaixada

public:
    Piece();
    Piece(float edge_length);
    Piece(float edge_length, glm::vec2 fit_spot, glm::vec2 tx_coords[4]);
    
    glm::vec3 getCenter();
    void setVertices();
    glm::vec3* getVertices();
    void printVertices();
    
    void rotate(); // rotaciona a peça no sentido anti-horário
    void translate(float x, float y);

    void displayColor(float colors[4][3]);
    void displayTexture();

    bool handleSelection(float x, float y);
    bool handleFitting();
};

#endif // PIECE_H