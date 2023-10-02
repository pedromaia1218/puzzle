#include <GL/glut.h>
#include "piece.h"
#include "piece.cpp"

#include "config.h"

Piece s = Piece(20);

float colors[4][3] = {
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 1.0f}
};

glm::vec3 windowToWorldCoordinates(int x_window, int y_window)
{
    y_window = window_h - y_window;

    float y_norm = float(y_window) / float(window_h);
    float x_norm = float(x_window) / float(window_w);

    float world_height = world_ymax - world_ymin;
    float y_world = world_ymin + y_norm*world_height;
    float world_width = world_xmax - world_xmin;
    float x_world = world_xmin + x_norm*world_width;

    return glm::vec3(x_world, y_world, 1.0f);
}

void inicio()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'r':
        case 'R':
            s.printVertices();
            s.rotate();
            s.printVertices();
        break;

        case 't':
        case 'T':
            s.printVertices();
            s.translate(2,2);
            s.printVertices();
        break;
        default:
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON and state == GLUT_UP)
    {
        std::cout << x << ", " << y << std::endl;
        std::cout << glm::to_string(windowToWorldCoordinates(x,y)) << std::endl;
    }
}

//função que sera usada para desenhar o conteudo no Frame Buffer
void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(world_xmin, world_xmax, world_ymin, world_ymax, -2, 2);

    s.displayColor(colors);

    glFlush();  // Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                         //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(window_w,window_h);        //resolução da janela (framebuffer)
    glutCreateWindow("Puzzle");                   //cria a janela (a string aparece na barra de titulo da janela)

    inicio();
 
    glutDisplayFunc(desenha);   // indica pra GLUT que a função 'desenha' sera chamada para atualizar o frame buffer
    glutKeyboardFunc(keyboard); // tratamento do teclado
    glutMouseFunc(mouse);       // tratamento do mouse

    glutMainLoop();

    return 0;
}