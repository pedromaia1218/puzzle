#include <GL/glut.h>
#include <glm/glm.hpp>
#include "piece.h"
#include "piece.cpp"
#include <vector>

#include "config.h"

#include <cstdlib>
#include <ctime>

// std::vector<Piece> pieces; // lista contendo todas as peças do jogo
Piece pieces[3];
std::vector<int> priority_order; // lista que define a ordem de prioridade da peça a ser selecionada
int selected_piece = -1; // variável que indica qual peça está selecionada (-1 quando nenhuma)
glm::vec2 selected_coords; // variável que marca as coordenadas de mundo atualmente selecionadas


glm::vec2 windowToWorldCoordinates(int x_window, int y_window)
{
    y_window = window_h - y_window;

    float y_norm = float(y_window) / float(window_h);
    float x_norm = float(x_window) / float(window_w);

    float world_height = world_ymax - world_ymin;
    float y_world = world_ymin + y_norm*world_height;
    float world_width = world_xmax - world_xmin;
    float x_world = world_xmin + x_norm*world_width;

    return glm::vec2(x_world, y_world);
}

// TODO: função que move todas as peças para lugares aleatórios do tabuleiro e as rotaciona
void shuffle_pieces()
{
    // std::rand
}

void gameStart()
{
    for(int i=0; i<3; i++)
    {
        pieces[i] = Piece(piece_edge_length, glm::vec2(10,-10));
    }

    pieces[0].translate(2,2);
    pieces[1].translate(8,8);
    pieces[2].translate(-3,-2);
}

void openglStart()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)
}

// Função que comanda o CLIQUE do mouse
void mouseClick(int button, int state, int x, int y)
{
    glm::vec2 world_coords = windowToWorldCoordinates(x,y);
    float x_world = world_coords[0];
    float y_world = world_coords[1];
    
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            for(int i=0; i<3; i++)
            {
                if(pieces[i].handleSelection(x_world, y_world))
                {
                    selected_coords = world_coords;
                    selected_piece = i;
                    break;
                }
            }
        }
        else
        {
            if (selected_piece >= 0)
            {
                // se ao soltar o clique a peça estiver nas condições favoráveis,
                // realizar encaixe automático
                pieces[selected_piece].handleFitting();
                
                // desseleciona a peça
                selected_piece = -1;   
            }
        }
    }
    else if (button == GLUT_RIGHT_BUTTON and state == GLUT_UP)
    {
        for(int i=0; i<3; i++)
        {
            if (pieces[i].handleSelection(x_world, y_world))
            {
                pieces[i].rotate();
                break;
            }
        }
    }
    glutPostRedisplay();
}

// Função que comanda o ARRASTO do mouse
void mouseDrag(int x, int y)
{
    if(selected_piece >= 0)
    {
        glm::vec2 world_coords = windowToWorldCoordinates(x,y);
        glm::vec2 trans_vector = world_coords - selected_coords;
        
        pieces[selected_piece].translate(trans_vector[0], trans_vector[1]);
        selected_coords = world_coords;
    }
    glutPostRedisplay();
}

//função que desenha no frame buffer
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(world_xmin, world_xmax, world_ymin, world_ymax, -2, 2);


    float colors[4][3] = {
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}
    };

    for(int i=0; i<3; i++)
    {
        pieces[i].displayColor(colors);
    }
    glColor3f(0,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(10, -10);
    glEnd();
    glFlush();  // Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                         //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(window_w,window_h);        //resolução da janela (framebuffer)
    glutCreateWindow("Puzzle");                   //cria a janela (a string aparece na barra de titulo da janela)

    openglStart();
    gameStart();

    glutDisplayFunc(display);   // indica pra GLUT que a função 'desenha' sera chamada para atualizar o frame buffer
    // glutKeyboardFunc(keyboardAscii); // tratamento do teclado
    glutMouseFunc(mouseClick);       // tratamento do mouse
    glutMotionFunc(mouseDrag);

    glutMainLoop();

    return 0;
}