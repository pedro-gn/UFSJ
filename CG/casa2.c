#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define NUM_PARTICLES 100


GLfloat windowWidth;
GLfloat windowHeight;

typedef struct {
    float x;
    float y;
}Vector2;

typedef struct {
    Vector2 position;  // posição
    Vector2 velocity;  // velocidade
    float opacity;     // opacidade
} Particle;

Particle particles[NUM_PARTICLES];
Vector2 moving;
Vector2 cloudPosition = {-130, 110};  
float cloudSpeed = 1.0; 

//Desenha um quadrado de lado 1 centrado na origem
void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

//Desenha um triângulo equilátero de lado 1 centrado na origem
void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
    glEnd();
}

//Desenha um círculo de raio 1 centrado na origem
void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

//Faz o cisalhamento de um objeto em relação ao eixo X
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewX(GLfloat angle) {
    GLfloat m[16] = {
        1, 0, 0, 0,
        tan(angle), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0 ,1
    };
    glMultMatrixf(m);
}

//Faz o cisalhamento de um objeto em relação ao eixo Y
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewY(GLfloat angle) {
    GLfloat m[16] = {
        1, tan(angle), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(m);
}

void initParticles() {
    for(int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].position.x = 83;   // posição x da chaminé
        particles[i].position.y = 72;   // posição y da chaminé
        particles[i].velocity.x = (rand() % 5 - 2) * 0.1;   // velocidade aleatória em x
        particles[i].velocity.y = rand() % 5 * 0.1 + 0.5;  // velocidade aleatória em y
        particles[i].opacity = 1.0;
    }
}
void drawAndUpdateParticles() {
    for(int i = 0; i < NUM_PARTICLES; i++) {
        glColor4f(0.5, 0.5, 0.5, particles[i].opacity);  // Cor cinza da fumaça
        
        glPushMatrix();
        glTranslatef(particles[i].position.x, particles[i].position.y, 0);
        glScalef(5, 5, 0);
        desenhaCirculo();
        glPopMatrix();

        // Atualiza a posição da partícula
        particles[i].position.x += particles[i].velocity.x;
        particles[i].position.y += particles[i].velocity.y;

        // Diminui a opacidade da partícula
        particles[i].opacity -= 0.0066;

        // Se a partícula se tornar totalmente transparente, reinicie-a
        if(particles[i].opacity <= 0) {
            particles[i].position.x = 83;  // posição x da chaminé
            particles[i].position.y = 72;  // posição y da chaminé
            particles[i].velocity.x = (rand() % 5 - 2) * 0.1;
            particles[i].velocity.y = rand() % 5 * 0.1 + 0.5;
            particles[i].opacity = 1.0;
        }
    }
}

void desenhaNuvem(float x, float y) {
    glColor3f(0.8, 0.8, 0.8);  // Cor da nuvem (branco)
    
    glPushMatrix();
    glTranslatef(x, y+5, 0);
    glScalef(17, 17, 0);
    desenhaCirculo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x + 15, y+2, 0);
    glScalef(10, 10, 0);
    desenhaCirculo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x - 15, y+2, 0);
    glScalef(10, 10, 0);
    desenhaCirculo();
    glPopMatrix();
}

void Timer(int value) {
    glutPostRedisplay();  // Marca a janela para ser redesenhada
    glutTimerFunc(16, Timer, 0);  // Chama esta função a cada 16 ms
}
// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.97, 0.95, 0.93,1);
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);


    glPushMatrix();
        glColor3f(1, 0.44, 0.3);
        glTranslatef(moving.x, moving.y, 0);
        glScalef(8, 8, 0);
        desenhaCirculo();
    glPopMatrix();


    glTranslatef(110,86,0);

    //================Plantas
    glPushMatrix();
        glColor3f(0.18, 0.44, 0.3);
        glTranslatef(138, -16,0);
        glScalef(15, 15, 0);
        desenhaCirculo();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.18, 0.44, 0.3);
        glTranslatef(154, -21,0);
        glScalef(10, 10, 0);
        desenhaCirculo();
    glPopMatrix();

    glPushMatrix();//lado esq
        glColor3f(0.18, 0.44, 0.3);
        glTranslatef(-41, -16,0);
        glScalef(15, 15, 0);
        desenhaCirculo();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.18, 0.44, 0.3);
        glTranslatef(-59, -20, 0);
        glScalef(10, 10, 0);
        desenhaCirculo();
    glPopMatrix();

    //==================Teto Atras
    glPushMatrix();
        glColor3f(0.18, 0.44, 0.31);
        glTranslatef(33,36,0);
        glScalef(120, 54, 0);
        skewX(0.28);
        desenhaQuadrado();
    glPopMatrix();



    //Frente
    glPushMatrix();
        glColor3f(0.97, 0.82, 0.6);
        glScalef(60,50,1);
        desenhaQuadrado();
        glPushMatrix();
            glColor3f(0.97, 0.82, 0.6);
            glTranslatef(0,0.90,0);
            glScalef(1,0.8,0);
            desenhaTriangulo();
        glPopMatrix();

        glPushMatrix(); //Porta
            glColor3f(0.43, 0.34, 0.27);
            glTranslatef(0.05, -0.14, 0);
            glScalef(0.26, 0.72, 0);
            desenhaQuadrado();
        glPopMatrix();
    glPopMatrix();

    //Lateral
    glPushMatrix();
        glColor3f(0.91, 0.64, 0.47);
        glScalef(100,50,0);
        glTranslatef(0.8,0,0);
        desenhaQuadrado();
    glPopMatrix();

    glPushMatrix(); //beirada
        glPushMatrix();
            glColor3f(0.34, 0.72, 0.53);
            glTranslatef(9.3, 38.7,0);
            glScalef(5, 46, 0);
            skewX(8);
            skewY(0.15);
            desenhaQuadrado();
        glPopMatrix();

        glColor3f(0.34, 0.72, 0.53);
        glTranslatef(-26, 37.2, 0);
        glScalef(5, 49.3, 0);
        skewX(-8);
        skewX(0.4);
        skewY(-0.15);
        desenhaQuadrado();

    glPopMatrix();




    //Teto frente
    glPushMatrix();
        glColor3f(0.25, 0.64, 0.45);
        glTranslatef(69,41,0);
        glScalef(120, 48, 0);
        skewX(-0.28);
        desenhaQuadrado();

        glPushMatrix(); //beirada telhado
            glColor3f(0.19, 0.44, 0.31);
            skewX(0.28);
            glTranslatef(0.145,-0.55,0);
            glScalef(1, 0.1, 0);
            desenhaQuadrado();
        glPopMatrix();

    glPopMatrix();

    //==============fumaça
    drawAndUpdateParticles();
    
    //chamine
    glPushMatrix();
        glColor3f(0.91, 0.64, 0.47);
        glTranslatef(90, 60, 0);
        glScalef(13, 24, 0);
        desenhaQuadrado();//escuro

        glColor3f(0.97, 0.82, 0.6);
        glScalef(0.9,1,0);
        glTranslatef(-1.05, 0.15, 0);
        skewY(-0.3);
        desenhaQuadrado();//claro

        glTranslatef(-0.15, 0.45, 0);
        skewY(0.3);
        glScalef(1.35,0.3,0);
        desenhaQuadrado();//tampa claro

        glColor3f(0.91, 0.64, 0.47);
        glTranslatef(0.97, 0, 0);
        desenhaQuadrado();// tampa escuro

        glColor3f(0.81, 0.55, 0.37);
        glTranslatef(-0.1, -0.85, 0);
        glScalef(0.81,0.8,0);
        desenhaQuadrado();// tampa escuro sombra

        glColor3f(0.9, 0.64, 0.46);
        glTranslatef(-0.95, 0, 0);
        glScalef(0.9,1,0);
        desenhaQuadrado();// tampa claro sombra
    glPopMatrix();



    //===================Porta======================
    glPushMatrix(); //sombra
        glColor3f(0.91, 0.64, 0.47);
        glTranslatef(-7,-7,0);
        glScalef(8, 36, 0);
        desenhaQuadrado();
    glPopMatrix();

    glPushMatrix();//janela
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(8.9,5,0);
        glScalef(4, 6, 0);
        desenhaQuadrado();
    glPopMatrix();

    glPushMatrix();//janela
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(9,-5,0);
        glScalef(4, 9, 0);
        desenhaQuadrado();
    glPopMatrix();

    glPushMatrix();//janela
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(1.6,-5,0);
        glScalef(6, 9, 0);
        desenhaQuadrado();
    glPopMatrix();

    glPushMatrix();//janela
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(1.6,5,0);
        glScalef(6, 6, 0);
        desenhaQuadrado();
    glPopMatrix();

    //===================Circulo em cima da porta
    glPushMatrix();
        glColor3f(0.91, 0.64, 0.47);
        glTranslatef(-1, 26, 0);
        glScalef(9, 9, 0);
        desenhaCirculo();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.43, 0.34, 0.27);
        glTranslatef(2,26,0);
        glScalef(8, 8, 0);
        desenhaCirculo();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.43, 0.34, 0.27);
        glTranslatef(2,26,0);
        glScalef(8, 8, 0);
        desenhaCirculo();
    glPopMatrix();
    glPushMatrix();//janelinha1
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(3.7,26,0);
        glScalef(6.5, 6.5, 0);
        desenhaCirculo();
    glPopMatrix();

    //===============janelas==============
    glPushMatrix();
        glColor3f(0.43, 0.34, 0.27);
        glTranslatef(60,2.1,0);
        glScalef(16, 20, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.43, 0.34, 0.27);
        glTranslatef(100,2.1,0);
        glScalef(16, 20, 0);
        desenhaQuadrado();
    glPopMatrix();
    //vidros
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(54, -1.2, 0);
        glScalef(4, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(54,8.1,0);
        glScalef(4, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(62, 8.1,0);
        glScalef(8, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(62, -1.2,0);
        glScalef(8, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    //vidrosjanela2
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(94, -1.2, 0);
        glScalef(4, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(94,8.1,0);
        glScalef(4, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(102, 8.1, 0);
        glScalef(8, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.01, 0.65, 0.62);
        glTranslatef(102, -1.2,0);
        glScalef(8, 8, 0);
        desenhaQuadrado();
    glPopMatrix();
    //Sombras
    glPushMatrix();
        glColor3f(0.97, 0.82, 0.61);
        glTranslatef(71,2.1,0);
        glScalef(6, 20, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.97, 0.82, 0.61);
        glTranslatef(111,2.1,0);
        glScalef(6, 20, 0);
        desenhaQuadrado();
    glPopMatrix();

    //0.82, 0.55, 0.37
    //=====sombras====
    glPushMatrix();
        glColor3f(0.82, 0.55, 0.37);
        glTranslatef(41, 8.6,0);
        glScalef(21.5, 7, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.82, 0.55, 0.37);
        glTranslatef(83, 8.6,0);
        glScalef(18, 7, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.82, 0.55, 0.37);
        glTranslatef(122, 8.6,0);
        glScalef(16, 7, 0);
        desenhaQuadrado();
    glPopMatrix();


    //================CHAO
    glPushMatrix();
        glColor3f(0.18, 0.44, 0.3);
        glTranslatef(108, -28,0);
        glScalef(160, 7, 0);
        desenhaQuadrado();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.25, 0.64, 0.45);
        glTranslatef(-30, -28, 0);
        glScalef(120, 7, 0);
        desenhaQuadrado();
    glPopMatrix();


    //======nuvens
    cloudPosition.x += cloudSpeed;  // Mova a nuvem
    // Verifique se a nuvem saiu da tela e faça um loop
    if (cloudPosition.x > windowWidth + 50) {
        cloudPosition.x = -130;
    }

    desenhaNuvem(cloudPosition.x, cloudPosition.y);


    //===============Fumaça==================




    // Executa os comandos OpenGL
    glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // tecla ESC
            exit(0);
            break;
        case 'a':
            // Faça algo quando a tecla 'a' é pressionada
            break;
        // Adicione mais cases para outras teclas, conforme necessário
        default:
            break;
    }

    glutPostRedisplay();  // Marca a janela atual para ser exibida novamente
}

void specialKeyFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            moving.y += 1;
            break;
        case GLUT_KEY_DOWN:
            moving.y -= 1;
            break;
        case GLUT_KEY_RIGHT:
            moving.x += 1;
            break;
        case GLUT_KEY_LEFT:
            moving.x -= 1;
            break;
        default:
            break;
    }
    printf("\nx: %f   y: %f", moving.x, moving.y);
    glutPostRedisplay(); 
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initParticles();
    moving.x =152;
    moving.y =0;
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialKeyFunc);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    // Se a largura da janela, em pixels, for menor que a altura, a largura da viewport é fixada em 250 e a altura é escalada para o necessário
    if (w <= h)  {
        windowHeight = 250.0f*h/w;
                windowWidth = 250.0f;
    }
    else  {
    // Se a altura da janela, em pixels, for menor que a largura, a altura da viewport é fixada em 250 e a largura é escalada para o necessário
                windowWidth = 250.0f*w/h;
                windowHeight = 250.0f;
    }

    // As dimensões da janela vão de (0.0, 0.0) até (windowWidth, windowHeight), essas são as coordenadas da tela
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Minha Casa");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutTimerFunc(16, Timer, 0); 
    glutMainLoop();
    return 0;
}