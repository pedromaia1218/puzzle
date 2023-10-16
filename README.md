# puzzle

Trabalho desenvolvido para a disciplina de Computação Gráfica do curso de Ciência da Computação, na Universidade Federal do Ceará, Campus Russas.

O trabalho se trata de um *puzzle* (quebra-cabeça) de quadradinhos desenvolvido em C++ com o auxílio das bibliotecas *openGL*, *glut* e *GLM*.

Equipe:

- **Clayver Rodrigues de Morais**, matrícula **494097**
- **Isaac Emanuel Costa de Andrade**, matrícula **493661**

## instruções de execução

Para que o código possa ser compilado, é necessário ter as bibliotecas do openGL, GLUT e GLM instaladas. As bibliotecas devem estar no *includepath* do seu compilador C++.

Para compilar utilize o seguinte comando:

```bash
g++ main.cpp -lGL -lglut -o <nome do executavel>
```

Uma vez compilado, rode o arquivo executável gerado.

## instruções do jogo

O Puzzle consistem em várias peças quadradas, que juntas formam uma imagem completa em um tabuleiro. Use o botão esquerdo do Mouse para arrastar as peças para a sua respectiva posição. Clique com o botão direito em uma peça para rotacioná-la.

As peças, no início, se encontram embaralhadas e rotacionadas aleatoriamente. É possível modificar algumas configurações do jogo (ex: número de peças do tabuleiro, imagem formada pelas peças) no arquivo [config.h](config.h), antes de compilar.

Quando uma peça estiver perto o suficiente de sua respectiva posição no tabuleiro, encaixará automaticamente. Uma peça encaixada não pode ser mais movida ou rotacionada, e o jogo acaba ao encaixar todas as peças.
