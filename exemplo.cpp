#include <GL/glut.h>

void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)
}


//função que sera usada para desenhar o conteudo no Frame Buffer
void desenha(){
    glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer
    
    glColor3f(1.0, 0.0, 0.0);    //instrucao que altera a cor corrente. glColor3f(R,G,B). R = vermelho, G = verde, B = azul
    glBegin(GL_TRIANGLES);       //instrucao que indica o tipo de primitiva que sera desenhada. Nesse caso, triangulos.
        glVertex2f(-0.5, -0.5);  //instrucao que envia as coordenadas dos vertices do triangulo
        glVertex2f( 0.5, -0.5);  
        glVertex2f( 0.0,  0.5);
    glEnd();
    
    glFlush();  //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                         //inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              //posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(300,300);                  //resolução da janela (framebuffer)
    glutCreateWindow("00 - Ola Mundo");             //cria a janela (a string aparece na barra de titulo da janela)
 
    inicio(); 
 
    glutDisplayFunc(desenha);   //indica pra GLUT que a função 'desenha' sera chamada para atualizar o frame buffer
 
    glutMainLoop();             //mantem um laço interno usando threads para que a janela permaneça aberta
    
    return 0;
}