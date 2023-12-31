#ifndef CONFIG_H
#define CONFIG_H

/*
 * Este arquivo contém algumas variáveis globais de configuração do puzzle
*/

#include <vector>

// altura e largura da janela
int window_h = 500;
int window_w = 1000;

// limites das coordenadas de mundo projetadas
float world_xmin = -40.0f; 
float world_xmax =  40.0f; 
float world_ymin = -20.0f; 
float world_ymax =  20.0f;

float world_w = world_xmax-world_xmin;
float world_h = world_ymax-world_ymin;

// configurações do tabuleiro

unsigned sizeof_square_grid = 3; // tamanho da grade de quadrados (se for 4, será uma grade de 4x4, etc)

float board_size = 30.0f; // tamanho do tabuleiro
float piece_edge_length = board_size / sizeof_square_grid; // lado da peça quadrada
float board_edge_thickness = 0.4; // espessura da borda do tabuleiro

// define a distância necessária para a peça encaixar automaticamente
float auto_fit_distance = 3*piece_edge_length/4;

// define _o caminho da textura que será utilizada
char *text_filepath = (char*) "textures/tex1.jpg";

#endif // CONFIG_H