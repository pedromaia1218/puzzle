#ifndef CONFIG_H
#define CONFIG_H

/*
 * Este arquivo contém algumas variáveis globais de configuração do puzzle
*/

// altura e largura da janela
int window_h = 500;
int window_w = 500;

// limites das coordenadas de mundo projetadas
float world_xmin = -50.0f; 
float world_xmax =  50.0f; 
float world_ymin = -50.0f; 
float world_ymax =  50.0f; 

// define o tamanho do lado da peça quadrada
float piece_edge_length = 8.0f;
// define o tamanho da grade de quadrados (se for 4, será uma grade de 4x4, etc)
unsigned sizeof_square_grid = 2;

// define a distância necessária para a peça encaixar automaticamente
float auto_fit_distance = 3*piece_edge_length/4;

#endif // CONFIG_H