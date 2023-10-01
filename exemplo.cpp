#include <GL/glut.h>
#include "piece.h"

void display_square(Square s)
{
    glm::vec3 *vertices = s.get_points();

    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<4; i++)
    {
        glColor3f(0, 1-0.25*i, 0.25*i);
        glVertex2fv(glm::value_ptr(vertices[i]));
    }
    glEnd();
}

Square s = Square(20);

void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'r':
            s.display_points();
            s.rotate();
            s.display_points();
        break;
        case 'R':
            s.display_points();
            s.rotate();
            s.display_points();
        break;
        default:
        break;
    }
    glutPostRedisplay();
}

//função que sera usada para desenhar o conteudo no Frame Buffer
void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -1, 1);

    display_square(s);

    glFlush();  //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                         //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(500,500);                  //resolução da janela (framebuffer)
    glutCreateWindow("Puzzle");                   //cria a janela (a string aparece na barra de titulo da janela)

    inicio();
 
    glutDisplayFunc(desenha);   //indica pra GLUT que a função 'desenha' sera chamada para atualizar o frame buffer
    glutKeyboardFunc(keyboard);

    glutMainLoop();             //mantem um laço interno usando threads para que a janela permaneça aberta
    
    return 0;
}