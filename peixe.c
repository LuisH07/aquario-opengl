#include <stdlib.h>
#include "aquario.h"

Peixe* peixes = NULL;
int numPeixes = 0;

void atualizarPeixes() {
    for (int i = 0; i < numPeixes; i++) {
        Peixe* p = &peixes[i];
        
        p->posX += p->dirX * p->velocidade;
        p->posY += p->dirY * p->velocidade;
        p->posZ += p->dirZ * p->velocidade;

        float margem = p->tamanho / 2.0f;
        float x_min = -LARGURA_AQUARIO/2 + margem;
        float x_max = LARGURA_AQUARIO/2 - margem;
        float y_min = -2.0f + margem;  // Base do aquário
        float y_max = (-2.0f + ALTURA_AGUA) - margem;
        float z_min = -PROFUNDIDADE_AQUARIO/2 + margem;
        float z_max = PROFUNDIDADE_AQUARIO/2 - margem;

        // Verifica colisão com as paredes e inverte direção se necessário
        if (p->posX < x_min || p->posX > x_max) {
            p->dirX *= -1;
            p->posX = (p->posX < x_min) ? x_min : x_max;
        }
        if (p->posY < y_min || p->posY > y_max) {
            p->dirY *= -1;
            p->posY = (p->posY < y_min) ? y_min : y_max;
        }
        if (p->posZ < z_min || p->posZ > z_max) {
            p->dirZ *= -1;
            p->posZ = (p->posZ < z_min) ? z_min : z_max;
        }

        // Atualiza rotação baseada na direção (apenas no eixo Y)
        p->rotacao = atan2f(p->dirX, p->dirZ) * 180.0f / M_PI;
    }
    glutPostRedisplay();
}

void movimentoOciosoPeixes(){
    static float tempoAnim = 0.0f;
    tempoAnim += 0.1f;

    //estruturas da cena
    float x_abacaxi = (LARGURA_AQUARIO/2 * 0.6f);
    float z_abacaxi = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_abacaxi = -2.0f + 0.35f;
    float raio_abacaxi = 0.6f * 0.5f; //raio da esfera escalada

    float x_pedra = - (LARGURA_AQUARIO/2 * 0.6f);
    float z_pedra = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_pedra = -2.0f;
    float raio_pedra = 1.0f * 0.4f; //raio da esfera escalada

    float x_moai = (LARGURA_AQUARIO/2 * 0.01f);
    float z_moai = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_moai = -2.0f;
    float altura_moai = 1.6f * 0.6f; //altura do cilindro escalado
    float raio_base_moai = 0.8f * 0.4f; //raio base do cilindro
    float raio_topo_moai = 0.6f * 0.4f; //raio topo do cilindro

    //guarda as posições anteriores e atualizar movimentos
    for(int i = 0; i < numPeixes; i++){
        Peixe* p = &peixes[i];
        
        p->prevX = p->posX;
        p->prevY = p->posY;
        p->prevZ = p->posZ;

        float margem = p->tamanho / 2.0f;
        float x_min = -LARGURA_AQUARIO/2 + margem;
        float x_max = LARGURA_AQUARIO/2 - margem;
        float y_min = -2.0f + margem;
        float y_max = (-2.0f + ALTURA_AGUA) - margem;
        float z_min = -PROFUNDIDADE_AQUARIO/2 + margem;
        float z_max = PROFUNDIDADE_AQUARIO/2 - margem;

        float area_ociosa = 2.0f;
        float x_min_ocioso = p->posX - area_ociosa;
        float x_max_ocioso = p->posX + area_ociosa;
        float y_min_ocioso = p->posY - area_ociosa;
        float y_max_ocioso = p->posY + area_ociosa;
        float z_min_ocioso = p->posZ - area_ociosa;
        float z_max_ocioso = p->posZ + area_ociosa;

        x_min_ocioso = (x_min_ocioso < x_min) ? x_min : x_min_ocioso;
        x_max_ocioso = (x_max_ocioso > x_max) ? x_max : x_max_ocioso;
        y_min_ocioso = (y_min_ocioso < y_min) ? y_min : y_min_ocioso;
        y_max_ocioso = (y_max_ocioso > y_max) ? y_max : y_max_ocioso;
        z_min_ocioso = (z_min_ocioso < z_min) ? z_min : z_min_ocioso;
        z_max_ocioso = (z_max_ocioso > z_max) ? z_max : z_max_ocioso;

        if (rand() % 200 < 1) {
            float r1 = (float)rand() / (float)RAND_MAX;
            float r2 = (float)rand() / (float)RAND_MAX;
            float r3 = (float)rand() / (float)RAND_MAX;
            
            p->dirX = r1 * 1.0f - 0.5f;
            p->dirY = r2 * 1.0f - 0.5f;
            p->dirZ = r3 * 1.0f - 0.5f;
            
            float magnitude = sqrt(p->dirX * p->dirX + p->dirY * p->dirY + p->dirZ * p->dirZ);
            if (magnitude > 0) {
                p->dirX /= magnitude;
                p->dirY /= magnitude;
                p->dirZ /= magnitude;
            }
        }

        p->posX += p->dirX * p->velocidade;
        p->posY += p->dirY * p->velocidade;
        p->posZ += p->dirZ * p->velocidade;

        if (p->posX < x_min_ocioso || p->posX > x_max_ocioso ||
            p->posY < y_min_ocioso || p->posY > y_max_ocioso ||
            p->posZ < z_min_ocioso || p->posZ > z_max_ocioso) {
            
            p->dirX = (p->posX - (x_min_ocioso + x_max_ocioso)/2) > 0 ? -1 : 1;
            p->dirY = (p->posY - (y_min_ocioso + y_max_ocioso)/2) > 0 ? -1 : 1;
            p->dirZ = (p->posZ - (z_min_ocioso + z_max_ocioso)/2) > 0 ? -1 : 1;
            
            float magnitude = sqrt(p->dirX * p->dirX + p->dirY * p->dirY + p->dirZ * p->dirZ);
            if (magnitude > 0) {
                p->dirX /= magnitude;
                p->dirY /= magnitude;
                p->dirZ /= magnitude;
            }
        }

        //verificar colisão aquário
        if (p->posX < x_min) { p->posX = x_min; p->dirX = fabs(p->dirX); }
        if (p->posX > x_max) { p->posX = x_max; p->dirX = -fabs(p->dirX); }
        if (p->posY < y_min) { p->posY = y_min; p->dirY = fabs(p->dirY); }
        if (p->posY > y_max) { p->posY = y_max; p->dirY = -fabs(p->dirY); }
        if (p->posZ < z_min) { p->posZ = z_min; p->dirZ = fabs(p->dirZ); }
        if (p->posZ > z_max) { p->posZ = z_max; p->dirZ = -fabs(p->dirZ); }

        //verificar colisão casa do bob esponja
        float dx_abacaxi = p->posX - x_abacaxi;
        float dy_abacaxi = p->posY - (base_abacaxi + raio_abacaxi);
        float dz_abacaxi = p->posZ - z_abacaxi;
        float dist_abacaxi_sq = dx_abacaxi*dx_abacaxi + dy_abacaxi*dy_abacaxi + dz_abacaxi*dz_abacaxi;
        
        if (dist_abacaxi_sq < (raio_abacaxi + p->raioColisao) * (raio_abacaxi + p->raioColisao)) {
            float dist_abacaxi = sqrt(dist_abacaxi_sq);
            float overlap = (raio_abacaxi + p->raioColisao) - dist_abacaxi;
            
            dx_abacaxi /= dist_abacaxi;
            dy_abacaxi /= dist_abacaxi;
            dz_abacaxi /= dist_abacaxi;
            
            p->posX += dx_abacaxi * overlap;
            p->posY += dy_abacaxi * overlap;
            p->posZ += dz_abacaxi * overlap;
            
            float dot = p->dirX * dx_abacaxi + p->dirY * dy_abacaxi + p->dirZ * dz_abacaxi;
            if (dot > 0) {
                p->dirX -= 2.0f * dot * dx_abacaxi;
                p->dirY -= 2.0f * dot * dy_abacaxi;
                p->dirZ -= 2.0f * dot * dz_abacaxi;
                
                float mag = sqrt(p->dirX*p->dirX + p->dirY*p->dirY + p->dirZ*p->dirZ);
                if (mag > 0) {
                    p->dirX /= mag;
                    p->dirY /= mag;
                    p->dirZ /= mag;
                }
            }
        }

        //verificar colisão casa do patrick
        float dx_pedra = p->posX - x_pedra;
        float dy_pedra = p->posY - (base_pedra + raio_pedra);
        float dz_pedra = p->posZ - z_pedra;
        float dist_pedra_sq = dx_pedra*dx_pedra + dy_pedra*dy_pedra + dz_pedra*dz_pedra;
        
        if (dist_pedra_sq < (raio_pedra + p->raioColisao) * (raio_pedra + p->raioColisao)) {
            float dist_pedra = sqrt(dist_pedra_sq);
            float overlap = (raio_pedra + p->raioColisao) - dist_pedra;
            
            dx_pedra /= dist_pedra;
            dy_pedra /= dist_pedra;
            dz_pedra /= dist_pedra;
            
            p->posX += dx_pedra * overlap;
            p->posY += dy_pedra * overlap;
            p->posZ += dz_pedra * overlap;
            
            float dot = p->dirX * dx_pedra + p->dirY * dy_pedra + p->dirZ * dz_pedra;
            if (dot > 0) {
                p->dirX -= 2.0f * dot * dx_pedra;
                p->dirY -= 2.0f * dot * dy_pedra;
                p->dirZ -= 2.0f * dot * dz_pedra;
                
                float mag = sqrt(p->dirX*p->dirX + p->dirY*p->dirY + p->dirZ*p->dirZ);
                if (mag > 0) {
                    p->dirX /= mag;
                    p->dirY /= mag;
                    p->dirZ /= mag;
                }
            }
        }

        //verificar colisão casa do lula molusco
        float dx_moai = p->posX - x_moai;
        float dz_moai = p->posZ - z_moai;
        float dist_horizontal_moai = sqrt(dx_moai*dx_moai + dz_moai*dz_moai);
        
        //raio interpolado baseado na altura
        float altura_relativa = p->posY - base_moai;
        if (altura_relativa >= 0 && altura_relativa <= altura_moai) {
            float raio_interpolado = raio_base_moai + (raio_topo_moai - raio_base_moai) * (altura_relativa / altura_moai);
            
            if (dist_horizontal_moai < (raio_interpolado + p->raioColisao)) {
                float overlap = (raio_interpolado + p->raioColisao) - dist_horizontal_moai;
                
                if (dist_horizontal_moai > 0) {
                    dx_moai /= dist_horizontal_moai;
                    dz_moai /= dist_horizontal_moai;
                } else {
                    dx_moai = 1.0f;
                    dz_moai = 0.0f;
                }
                
                p->posX += dx_moai * overlap;
                p->posZ += dz_moai * overlap;
                
                float dot_horizontal = p->dirX * dx_moai + p->dirZ * dz_moai;
                if (dot_horizontal > 0) {
                    p->dirX -= 2.0f * dot_horizontal * dx_moai;
                    p->dirZ -= 2.0f * dot_horizontal * dz_moai;
                    
                    float mag = sqrt(p->dirX*p->dirX + p->dirY*p->dirY + p->dirZ*p->dirZ);
                    if (mag > 0) {
                        p->dirX /= mag;
                        p->dirY /= mag;
                        p->dirZ /= mag;
                    }
                }
            }
        }

        if (p->dirX != 0 || p->dirZ != 0) {
            p->rotacao = atan2f(-p->dirX, -p->dirZ) * (180.0f / M_PI);
        }

        p->anguloCauda = 10.0f * sin(tempoAnim);
    }

    //colisões entre os peixes
    for(int i = 0; i < numPeixes; i++){
        for(int j = i + 1; j < numPeixes; j++){
            Peixe* p1 = &peixes[i];
            Peixe* p2 = &peixes[j];
            
            float dx = p1->posX - p2->posX;
            float dy = p1->posY - p2->posY;
            float dz = p1->posZ - p2->posZ;
            float distanciaSq = dx*dx + dy*dy + dz*dz;
            float somaRaios = p1->raioColisao + p2->raioColisao;
            float somaRaiosSq = somaRaios * somaRaios;
            
            if (distanciaSq < somaRaiosSq && distanciaSq > 0.0001f) {
                float distancia = sqrt(distanciaSq);
                
                dx /= distancia;
                dy /= distancia;
                dz /= distancia;
                
                float overlap = somaRaios - distancia;
                
                float mover = overlap * 0.5f;
                p1->posX += dx * mover;
                p1->posY += dy * mover;
                p1->posZ += dz * mover;
                
                p2->posX -= dx * mover;
                p2->posY -= dy * mover;
                p2->posZ -= dz * mover;
                
                if (rand() % 100 < 30) {
                    float dot1 = p1->dirX * dx + p1->dirY * dy + p1->dirZ * dz;
                    float dot2 = p2->dirX * (-dx) + p2->dirY * (-dy) + p2->dirZ * (-dz);
                    
                    if (dot1 > 0) {
                        p1->dirX -= 1.8f * dot1 * dx;
                        p1->dirY -= 1.8f * dot1 * dy;
                        p1->dirZ -= 1.8f * dot1 * dz;
                    }
                    
                    if (dot2 > 0) {
                        p2->dirX -= 1.8f * dot2 * (-dx);
                        p2->dirY -= 1.8f * dot2 * (-dy);
                        p2->dirZ -= 1.8f * dot2 * (-dz);
                    }
                    
                    p1->dirY += (rand() % 100) / 500.0f - 0.1f;
                    p2->dirY += (rand() % 100) / 500.0f - 0.1f;
                    
                    float mag1 = sqrt(p1->dirX*p1->dirX + p1->dirY*p1->dirY + p1->dirZ*p1->dirZ);
                    float mag2 = sqrt(p2->dirX*p2->dirX + p2->dirY*p2->dirY + p2->dirZ*p2->dirZ);
                    
                    if (mag1 > 0) {
                        p1->dirX /= mag1;
                        p1->dirY /= mag1;
                        p1->dirZ /= mag1;
                    }
                    if (mag2 > 0) {
                        p2->dirX /= mag2;
                        p2->dirY /= mag2;
                        p2->dirZ /= mag2;
                    }
                }
                
                p1->velocidade *= 0.95f;
                p2->velocidade *= 0.95f;
            }
        }
    }
    
    for(int i = 0; i < numPeixes; i++){
        Peixe* p = &peixes[i];
        if (p->velocidade < 0.0015f) {
            p->velocidade += 0.0001f;
        }
    }

    glutPostRedisplay();
}

void desenharPeixe(Peixe* peixe) {
    if (!peixe) return;

    float tamX = peixe->tamanho / 3.0f;
    float tamY = peixe->tamanho / 2.0f;
    float tamZ = peixe->tamanho;

    float hx = tamX / 2.0f;
    float hy = tamY / 2.0f;
    float hz = tamZ / 2.0f;

    GLuint idTextura = peixe->textura;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    glPushMatrix();

    // posiciona e orienta o peixe (rotacao em graus, em torno de Y)
    glTranslatef(peixe->posX, peixe->posY, peixe->posZ);
    glRotatef(peixe->rotacao, 0.0f, 1.0f, 0.0f);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-hx,  hy,  hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx,  hy, -hz);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( hx, -hy,  hz);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( hx,  hy, -hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( hx,  hy,  hz);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glColor3f(peixe->corR, peixe->corG, peixe->corB);

    // Lateral esquerda
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-hx, -hy,  hz);
        glVertex3f( hx, -hy,  hz);
        glVertex3f( hx,  hy,  hz);
        glVertex3f(-hx,  hy,  hz);
    // Lateral direita
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-hx, -hy, -hz);
        glVertex3f( hx, -hy, -hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f(-hx,  hy, -hz);
    // Topo
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-hx,  hy,  hz);
        glVertex3f( hx,  hy,  hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f(-hx,  hy, -hz);
    // Fundo
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-hx, -hy, -hz);
        glVertex3f( hx, -hy, -hz);
        glVertex3f( hx, -hy,  hz);
        glVertex3f(-hx, -hy,  hz);
    glEnd();

    // NADADEIRA
    float altura_nadadeira = tamY * 0.7f;
    float pos_nadadeira = hz + 0.0001f;
    glRotatef(peixe->anguloCauda, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, -altura_nadadeira / 2.0f, pos_nadadeira * 1.7f);
        glVertex3f(0.0f, -altura_nadadeira / 2.0f, pos_nadadeira);
        glVertex3f(0.0f,  altura_nadadeira / 2.0f, pos_nadadeira * 1.7f);
        glVertex3f(0.0f,  altura_nadadeira / 2.0f, pos_nadadeira);
    glEnd();
    glPopMatrix();
}

void adicionarPeixe() {
    if (numPeixes >= MAX_PEIXES) {
        return;
    }

    Peixe* novoArray = realloc(peixes, (numPeixes + 1) * sizeof(Peixe));
    if (!novoArray) {
        return;
    }

    peixes = novoArray;
    Peixe* novoPeixe = &peixes[numPeixes]; 

    float r = (float)rand() / (float)RAND_MAX;
    novoPeixe->velocidade = 0.0015f + r * 0.003f;
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->tamanho = 0.2f + r * 0.3f;

    novoPeixe->id = numPeixes;
    novoPeixe->raioColisao = novoPeixe->tamanho * 0.6f;

    float margemX = novoPeixe->tamanho / 2.0f + 0.05f;
    float margemZ = novoPeixe->tamanho / 2.0f + 0.05f;
    float margemY = novoPeixe->tamanho / 2.0f + 0.05f;

    // Posição aleatória dentro do aquário (centrado em 0)
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->posX = (r * (LARGURA_AQUARIO - 2.0f * margemX)) - (LARGURA_AQUARIO/2.0f - margemX);

    r = (float)rand() / (float)RAND_MAX;
    float bottomY = -1.99f + margemY;
    float topY = bottomY + ALTURA_AGUA - margemY;
    novoPeixe->posY = bottomY + r * (topY - bottomY);

    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->posZ = (r * (PROFUNDIDADE_AQUARIO - 2.0f * margemZ)) - (PROFUNDIDADE_AQUARIO/2.0f - margemZ);

    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->dirX = r * 2.0f - 1.0f;
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->dirZ = r * 2.0f - 1.0f;
    novoPeixe->dirY = 0.0f;

    // Normalizar e evitar vetor zero
    float comprimento = sqrt(novoPeixe->dirX * novoPeixe->dirX + novoPeixe->dirZ * novoPeixe->dirZ);
    if (comprimento < 1e-4f) {
        // direção quase zero -> direção padrão
        novoPeixe->dirX = 1.0f;
        novoPeixe->dirZ = 0.0f;
        comprimento = 1.0f;
    }
    novoPeixe->dirX /= comprimento;
    novoPeixe->dirZ /= comprimento;
    // Calcular rotação em graus
    // atan2(z, x) retorna ângulo no plano XZ
    novoPeixe->rotacao = atan2f(novoPeixe->dirZ, novoPeixe->dirX) * 180.0f / M_PI;

    int texturaIdx = rand() % 5;
    switch(texturaIdx) {
        case 0: novoPeixe->textura = texturaPeixe1; break;
        case 1: novoPeixe->textura = texturaPeixe2; break;
        case 2: novoPeixe->textura = texturaPeixe3; break;
        case 3: novoPeixe->textura = texturaPeixe4; break;
        default: novoPeixe->textura = texturaPeixe5; break;
    }

    novoPeixe->corR = coresTexturaPeixe[texturaIdx][0];
    novoPeixe->corG = coresTexturaPeixe[texturaIdx][1];
    novoPeixe->corB = coresTexturaPeixe[texturaIdx][2];

    numPeixes++;
}

void removerPeixe(){
    if(numPeixes == 0){
        return;
    }

    Peixe peixeVazio = {0};
    peixes[numPeixes-1] = peixeVazio;
    peixes = realloc(peixes, (numPeixes - 1) * sizeof(Peixe));

    numPeixes--;
}

void inicializarPeixes(int quantidade) {
    for (int i = 0; i < quantidade && numPeixes < MAX_PEIXES; i++) {
        adicionarPeixe();
    }
}