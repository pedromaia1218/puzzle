#ifndef CONFIG_H
#define CONFIG_H

/*
 * Este arquivo contém algumas variáveis globais de configuração do puzzle
*/

// altura e largura da janela
int window_h = 500;
int window_w = 500;

// limites das coordenadas de mundo projetadas
float world_xmin = -20.0f; 
float world_xmax =  20.0f; 
float world_ymin = -20.0f; 
float world_ymax =  20.0f; 

// define o tamanho do lado da peça quadrada
float piece_edge_length = 4.0f;

// define a distância necessária para a peça encaixar automaticamente
float auto_fit_distance = 1.0f;

#endif // CONFIG_H