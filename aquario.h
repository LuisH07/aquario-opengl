#ifndef AQUARIO_H
#define AQUARIO_H

#include <GL/glut.h>
#include <GL/glu.h> 
#include <math.h>

typedef struct {
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    float prevX, prevY, prevZ;
    float velocidade;
    float tamanho;
    float rotacao;
    GLuint textura;
    float corR, corG, corB;
    float anguloCauda;
    float raioColisao;
    int id;
} Peixe;

#define LARGURA_AQUARIO 5.0f
#define ALTURA_AQUARIO 4.0f
#define PROFUNDIDADE_AQUARIO 3.5f
#define ALTURA_AGUA (ALTURA_AQUARIO * 0.95)

#define MAX_PEIXES 50

// RECURSOS

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern float raio_camera;
extern float angulo_theta;
extern float angulo_phi;
extern int ultimoX;
extern int ultimoY;
extern int botaoEsquerdoPressionado;
extern GLuint texturaAreia;
extern GLuint texturaMesa;
extern GLuint texturaCeu;
extern GLuint texturaAbacaxi;
extern GLuint texturaPedra;
extern GLuint texturaMadeira;
extern GLuint texturaMoaiPedra;
extern GLuint texturaMoaiTopo;
extern GLuint texturaPeixe1;
extern GLuint texturaPeixe2;
extern GLuint texturaPeixe3;
extern GLuint texturaPeixe4;
extern GLuint texturaPeixe5;
extern float coresTexturaPeixe[5][3];

GLuint carregaTextura(const char* arquivo);
void inicializar();
void atualizaCamera();
void redimensiona(int largura, int altura);
void mouse(int botao, int estado, int x, int y);
void movimentoMouse(int x, int y);
void teclado(unsigned char tecla, int x, int y);

// CENA

void desenhaCeu();
void desenhaCena();
void iniciaCena();

// PEIXE

extern Peixe* peixes;
extern int numPeixes;

void atualizarPeixes();
void movimentoOciosoPeixes();
void desenharPeixe(Peixe* peixe);
void adicionarPeixe();
void removerPeixe();
void inicializarPeixes(int quantidade);

// ILUMINACAO

void inicializarIluminacao(void);
void habilitarIluminacao(void);
void desabilitarIluminacao(void);
void atualizarPosicaoLuz(float x, float y, float z, float w);
void configurarIntensidade(float ambient, float diffuse, float specular);
void configurarBrilhoMaterial(float shininess);
void usarTexturaModulate(int usar);

#endif