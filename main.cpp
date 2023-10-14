#include <GL/glut.h>
#include <glm/glm.hpp>

#include <cstdlib>
#include <ctime>

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "piece.h"
#include "piece.cpp"
#include "config.h"

glm::vec2 board_pos;

std::vector<Piece> pieces; // lista contendo todas as peças do jogo
std::vector<int> priority_order; // lista que define a ordem de prioridade da peça a ser selecionada
std::vector<int> fit_pieces; // lista que guarda os índices referentes as peças que já foram encaixadas

int selected_piece = -1; // variável que indica qual peça está selecionada (-1 quando nenhuma)
glm::vec2 selected_coords; // variável que marca as coordenadas de mundo atualmente selecionadas

unsigned texture;

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

}

unsigned loadTexture(char *filepath)
{
    unsigned tex_id;
    int width, height, n_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(filepath, &width, &height, &n_channels, 0); //qtd de pixels na largura e altura preenchidas automaticamente
    if(image == NULL) //verifica se o carregamento da imagem ocorreu com sucesso
        std::cout << "Erro, Imagem não carregada" << std::endl;
    else
        std::cout << "Imagem carregada com sucesso" << std::endl;

    glEnable(GL_TEXTURE_2D);              //habilitando o uso de texturas
    glGenTextures(1, &tex_id);            //gerando um objeto textura na máquina OpenGL
    glBindTexture(GL_TEXTURE_2D, tex_id); //ativando o objeto textura recém criado

    //parâmetros da textura caso coordenadas além do intervalo [0,1] seja utilizado
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //repetição espelhada no eixo S
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //repetição espelhada no eixo T

    //parâmetros da textura para filtragem quando tamanho de pixel e texel sejam diferentes (interpolação linear em ambos os casos)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificação - quando um texel cobre vários pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificação - quando muitos texels cabem em um único pixel

    //parâmetros da textura para indicar se a textura deve-se combinar ou substituir a atual cor do objeto
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //GL_REPLACE = substitui, GL_COMBINE = combina (ou multiplica)

    //envio dos dados da textura para o OpenGL
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,            //largura da textura
                 height,           //altura da textura (carregadas automaticamente pela função da biblioteca)
                 0,
                 GL_RGB,           //formato da cor da textura
                 GL_UNSIGNED_BYTE, //tipos de dados de cada texel da textura
                 image);           //ponteiro para os dados da textura

    glBindTexture(GL_TEXTURE_2D, 0); //desativando o objeto textura criado (ativa apenas quando for usar em algum objeto)

    stbi_image_free(image); //memória RAM pode ser liberada pois a imagem foi enviada ao OpenGL (memória gráfica)

    return tex_id; //retornando o identificador da textura (sem ele não há como acessar a textura carregada)
}

// Função que cria todas as peças
void gameStart()
{
    board_pos.x = world_xmin + world_w/2 + (world_h-board_size)/2;
    board_pos.y = world_ymin + (world_h-board_size)/2;

    unsigned s = sizeof_square_grid;
    float l = piece_edge_length;

    for(int i=0; i<s; i++)
    {
        for(int j=0; j<s; j++)
        {
            glm::vec2 fit_pos;
            fit_pos.x = board_pos.x+l*i + l/2;
            fit_pos.y = board_pos.y+l*j + l/2;

            glm::vec2 tx_coords[4];
            tx_coords[0] = glm::vec2((float)(i  )/s, (float)(j+1)/s);
            tx_coords[1] = glm::vec2((float)(i+1)/s, (float)(j+1)/s);
            tx_coords[2] = glm::vec2((float)(i+1)/s, (float)(j  )/s);
            tx_coords[3] = glm::vec2((float)(i  )/s, (float)(j  )/s);

            pieces.push_back(Piece(l, fit_pos, tx_coords));

            int id = sizeof_square_grid*i + j;
            priority_order.push_back(id);
        }
    }

    texture = loadTexture(text_filepath);
}

void openglStart()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)
}

void windowResize(int width, int height){
    window_w = width;
    window_h = height;

    glViewport(0, 0, width, height);
    glutPostRedisplay();
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
            for(int i=priority_order.size()-1; i>=0; i--)
            {
                if(pieces.at(priority_order[i]).handleSelection(x_world, y_world))
                {
                    int p = priority_order[i];
                    priority_order.erase(priority_order.begin() + i);
                    selected_coords = world_coords;
                    selected_piece = p;
                    priority_order.push_back(p);
                    
                    // for (auto x: priority_order) // DEBUGGING
                    //     std::cout << x << " ";
                    // std::cout << std::endl;

                    // for (auto x: fit_pieces)
                    //     std::cout << x << " ";
                    // std::cout << "=-=-=-=-=" << std::endl;
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
                if (pieces.at(selected_piece).handleFitting())
                {
                    priority_order.erase(priority_order.begin()+priority_order.size()-1);
                    fit_pieces.push_back(selected_piece);
                }
                // desseleciona a peça
                selected_piece = -1;
            }
        }
    }
    else if (button == GLUT_RIGHT_BUTTON and state == GLUT_UP)
    {
        for(int i : priority_order)
        {
            if (pieces.at(i).handleSelection(x_world, y_world))
            {
                pieces.at(i).rotate();
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
        
        pieces.at(selected_piece).translate(trans_vector[0], trans_vector[1]);
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

    // Desenha o tabuleiro:
    // (um quadrado branco em cima de um quadrado preto levemente maior)
    
    float k = board_edge_thickness;
    glColor3f(0,0,0); 
    glBegin(GL_QUADS);
    glVertex2f(board_pos.x            -k, board_pos.y            -k);
    glVertex2f(board_pos.x            -k, board_pos.y+board_size +k);  
    glVertex2f(board_pos.x+board_size +k, board_pos.y+board_size +k);
	glVertex2f(board_pos.x+board_size +k, board_pos.y            -k);
    glEnd();
    
    glColor3f(1,1,1); 
    glBegin(GL_QUADS);
    glVertex2f(board_pos.x           , board_pos.y           );
    glVertex2f(board_pos.x           , board_pos.y+board_size);  
    glVertex2f(board_pos.x+board_size, board_pos.y+board_size);
	glVertex2f(board_pos.x+board_size, board_pos.y           );
    glEnd();

    // float colors[4][3] = {
    //     {0.0f, 1.0f, 0.0f},
    //     {0.0f, 1.0f, 1.0f},
    //     {0.0f, 0.0f, 1.0f},
    //     {0.0f, 1.0f, 1.0f}
    // };

    // exibe as peças que já foram encaixadas
    glBindTexture(GL_TEXTURE_2D, texture);
    for(int i: fit_pieces)
    {
        pieces.at(i).displayTexture();
    }
    // exibe as peças que podem ser movidas, ainda não-encaixadas
    for(int i: priority_order)
    {
        pieces.at(i).displayTexture();
    }
    glBindTexture(GL_TEXTURE_2D, 0);

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
    glutReshapeFunc(windowResize); // tratamento do redimensionamento da janela
    // glutKeyboardFunc(keyboardAscii); // tratamento do teclado
    glutMouseFunc(mouseClick);       // tratamento do mouse
    glutMotionFunc(mouseDrag);

    glutMainLoop();

    return 0;
}