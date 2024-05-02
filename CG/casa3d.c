#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI_2 1.57079632679489661923

int win_id;

//refs https://www.google.com/search?q=3d+simples+house&tbm=isch&ved=2ahUKEwjm9dGW39yBAxXoR7gEHQ0UD9oQ2-cCegQIABAA&oq=3d+simples+house&gs_lcp=CgNpbWcQAzoHCAAQigUQQzoFCAAQgAQ6BggAEAcQHlDABVipD2CHEWgAcAB4AIABhQKIAeAOkgEFMC40LjWYAQCgAQGqAQtnd3Mtd2l6LWltZ8ABAQ&sclient=img&ei=d4kdZabeIeiP4dUPjai80A0&bih=976&biw=1848#imgrc=tdG-FsjuU-iRwM

typedef struct {
    float x,y,z;
}Vector3;

typedef struct{
    Vector3 scale, rotation, position;
}Transform;

Transform move;
GLfloat light_position[] = {  30.0, 10.0, 30.0, 0.0 };



//============================piramide============================================================
GLfloat vertices[] = {
    // Base
    -0.5f,  0.0f, -0.5f,  // 0: Inferior esquerdo atrás
     0.5f,  0.0f, -0.5f,  // 1: Inferior direito atrás
     0.5f,  0.0f,  0.5f,  // 2: Inferior direito frente
    -0.5f,  0.0f,  0.5f,  // 3: Inferior esquerdo frente

    // Topos
     0.0f,  1.0f, -0.5f,  // 4: Topo 1
     0.0f,  1.0f,  0.5f   // 5: Topo 2
};

GLuint baseIndices[] = {
    0, 1, 2,
    2, 3, 0
};

GLuint bodyIndices[] = {
    // Faces trapezoidais
    0, 3, 4, // Retângulo esquerdo: Parte 1 (triângulo)
    3, 5, 4, // Retângulo esquerdo: Parte 2 (triângulo)
    1, 4, 2, // Retângulo direito: Parte 1 (triângulo)
    2, 4, 5  // Retângulo direito: Parte 2 (triângulo)
};

GLuint roof1Indices[] = {
    // Telhado esquerdo
    0, 1, 4
};

GLuint roof2Indices[] = {
    // Telhado direito
    3, 2, 5
};


void DrawBase() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, sizeof(baseIndices)/sizeof(baseIndices[0]), GL_UNSIGNED_INT, baseIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawBody() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, sizeof(bodyIndices)/sizeof(bodyIndices[0]), GL_UNSIGNED_INT, bodyIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawRoof1() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, sizeof(roof1Indices)/sizeof(roof1Indices[0]), GL_UNSIGNED_INT, roof1Indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawRoof2() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, sizeof(roof2Indices)/sizeof(roof2Indices[0]), GL_UNSIGNED_INT, roof2Indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}


//=================================================transform==================================================================
void intitTransform(){
    move.position.x = 45;
    move.position.y = 20;
    move.position.z = -43;

    move.scale.x = 1;
    move.scale.y = 1;
    move.scale.z = 1;

    move.rotation.x = -3;
    move.rotation.y = -132;
    move.rotation.z = 0;
}
void printTransform() {
    printf("\033[2J");
    printf("\033[H");
    printf("glTranslatef(\033[31m%f\033[0m  ,  \033[32m%f\033[0m  ,  \033[34m%f\033[0m);", 
           move.position.x, move.position.y, move.position.z);
    printf("\nglScalef(\033[31m%f\033[0m ,  \033[32m%f\033[0m  ,  \033[34m%f\033[0m);", 
           move.scale.x, move.scale.y, move.scale.z);
    printf("\nglRotatef( %f, \033[31m1\033[0m ,  \033[32m0\033[0m,  \033[34m0\033[0m);", 
           move.rotation.x);
    printf("\nglRotatef( %f, \033[31m0\033[0m ,  \033[32m1\033[0m,  \033[34m0\033[0m);", 
           move.rotation.y);
    printf("\nglRotatef( %f, \033[31m0\033[0m ,  \033[32m0\033[0m,  \033[34m1\033[0m);\n", 
           move.rotation.z);
}




//==========================teclado=================================================================
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        //Rotacao
        case 'A': 
        case 'a':
            move.rotation.y -= 1;
            break;
        case 'D': 
        case 'd':
            move.rotation.y += 1;
            break;
        case 'W': 
        case 'w':
            move.rotation.x -= 1;
            break;
        case 'S': 
        case 's':
            move.rotation.x += 1;
            break;
        case 'E':
        case 'e':
            move.rotation.z += 1;
            break; 
        case 'Q': 
        case 'q':
            move.rotation.z -= 1; 
            break;

        //Scale
        case 'I': 
        case 'i':
            move.scale.x += 0.5;
            break;
        case 'K': 
        case 'k':
            move.scale.x -= 0.5;
            break;
        case 'J': 
        case 'j':
            move.scale.y += 0.5;
            break;
        case 'L': 
        case 'l':
            move.scale.y -= 0.5;
            break;
        case 'U': 
        case 'u':
            move.scale.z += 0.5;
            break;
        case 'O': 
        case 'o':
            move.scale.z -= 0.5;
            break;

        //Position
        case '8': 
            move.position.y += 0.5;
            break;
        case '5': 
            move.position.y -= 0.5;
            break;
        case '4': 
            move.position.x -= 0.5;
            break;
        case '6': 
            move.position.x += 0.5;
            break;
        case '7': 
            move.position.z += 0.5;
            break;
        case '9': 
            move.position.z -= 0.5;
            break;
    }
    printTransform();
    
    
    glutPostRedisplay();
}

//Aqui se capturam as teclas especiais (Alt, Control, Shift, F1, F2, etc.)
void myKeyboardSpecial(int key, int x, int y ) {
    switch ( key ) {
        case GLUT_KEY_UP:                   
            move.position.y += 1;
            break;
        case GLUT_KEY_DOWN:                 
            move.position.y -= 1;
            break;
        case GLUT_KEY_LEFT:                 
            move.position.x -= 1;
            break;
        case GLUT_KEY_RIGHT:                 
            move.position.x += 1;
            break;
        printf("Você apertou a tecla especial código: %d\n", key);  // ...para ajudar você a debugar...       
        break;
    }
    printTransform();
    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do mouse
void myMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {
      float r, g, b;
      r = (double)rand() / (double)RAND_MAX;
      g = (double)rand() / (double)RAND_MAX;
      b = (double)rand() / (double)RAND_MAX;
      glColor3f(r,g,b);
      printf("%.2f, %.2f, %.2f\n", r, g, b);
    }
  glutPostRedisplay();
}

void init(void) 
{
  // Define a cor de fundo da janela de visualização como preto
  glClearColor (0.0, 0.0, 0.0, 0.0);
  // Define o modo de rastreio de cor utilizado para misturar a cor do material nos pontos da face (smoothing)
  glShadeModel (GL_FLAT);
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);


    GLfloat AmbientLight[]={0.3,0.3,0.3,1.0};                  //Initialization values for lighting
    GLfloat DiffuseLight[] ={0.8,0.8,0.8,1.0};
    GLfloat SpecularLight[] ={1.0,1.0,1.0,1.0};
    GLfloat SpecRef[] = {0.7,0.7,0.7,1.0};
    GLint Shine =128;


  //Parâmetros para a luz ambiente, difusa e especular, definindo também a posição da luz
//   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
//   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//   GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1.0 };

        //Enable depth testing

    glLightfv(GL_LIGHT0,GL_AMBIENT,AmbientLight);//Set up and enable light zero
    glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);

    glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);//Set material to follow
    glMaterialfv(GL_FRONT,GL_SPECULAR,SpecRef);//Set specular reflectivity and shine
    glMateriali(GL_FRONT,GL_SHININESS,Shine);
  // Passa os parâmetros definidos acima para a OpenGL

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Habilita a luz ambiente, a luz zero e o depth buffer
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  //Primeira cor, para depois mudarmos com os eventos
  glColor3f(0.5, 1.0, 0.5);

  intitTransform();
}

void drawCylinder(float x, float y, float z, float height) {
    glPushMatrix();
    glTranslatef(x, y, z);
    GLUquadricObj *cylinder = gluNewQuadric();
    gluCylinder(cylinder, 0.2, 0.2, height, 16, 16);
    glPopMatrix();
}

// Função que desenha um personagem 3D simples
void drawCharacter() {
    // Cabeça (uma esfera no topo)
    glPushMatrix();
    glTranslatef(0, 2.2, 0);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();

    // Corpo (cilindro principal)
    drawCylinder(0, 1.5, 0, 1.0);

    // Braços (cilindros menores à esquerda e à direita)
    drawCylinder(-0.5, 1.7, 0, 0.8);
    drawCylinder(0.5, 1.7, 0, 0.8);

    // Pernas (cilindros menores abaixo)
    drawCylinder(-0.25, 0.5, 0, 1.0);
    drawCylinder(0.25, 0.5, 0, 1.0);
}

void display(void)
{

    glClearColor(0.35, 0.6, 0.8,1);
    // Limpa a janela de visualização com a cor de fundo especificada, e limpa também o depth buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Entra no modo de definição de matriz de visualização
    glMatrixMode(GL_MODELVIEW);
    // Carrega a matriz identidade
    glLoadIdentity();
    // Define a posição da câmera, para onde ela aponta e qual o vetor UP
    gluLookAt(5.0f, 60.0f, 70.0f, 0.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    // Desenha aq


    // glTranslatef(move.position.x, move.position.y, move.position.z);
    // glScalef(move.scale.x,move.scale.y, move.scale.z);
    glRotatef( move.rotation.x, 1 ,  0,  0);
    glRotatef( move.rotation.y, 0 ,  1,  0);
    glRotatef( move.rotation.z, 0 ,  0,  1);

    //Chao de grama
    glPushMatrix();
        glColor3f(0.5, 1.0, 0.5);   
        glTranslatef(0.000000  ,  14.000000  ,  0.000000);
        glScalef(22.000000 ,  1.000000  ,  20.000000);
        glutSolidCube(5);
    glPopMatrix();


    glPushMatrix();
        glColor3f(0.83, 0.81, 0.81);
        glTranslatef(0.000000  ,  23.000000  ,  1.000000);
        glScalef(-9.000000 ,  4.000000  ,  5.000000);
        glutSolidCube(5);
    glPopMatrix();

    //chamine
    glPushMatrix();
    glColor3f(0.83, 0.81, 0.81);
        glTranslatef(12.500000  ,  38.500000  ,  8.500000);
        glScalef(-1.000000 ,  2.500000  ,  1.000000);
        glutSolidCube(5);
        glTranslatef(0  ,  2 ,  0);
        glScalef(-1.200000 ,  0.23  ,  1.200000);
        glutSolidCube(5);
    glPopMatrix();

    //porta
    glPushMatrix();
        glColor3f(0.84, 0.59, 0.6);
        glTranslatef(-13.000000  ,  22.000000  ,  -9.500000);
        glScalef(2.000000 ,  3.000000  ,  1.000000);
        glutSolidCube(5);
    glPopMatrix();

    //janela porta
    glPushMatrix();
        glColor3f(0.56, 0.73, 0.81);
        glTranslatef(7.000000  ,  25.500000  ,  -9.500000);
        glScalef(3.000000 ,  1.500000  ,  1.000000);
        glutSolidCube(5);
    glPopMatrix();

    //janela lateral
    glPushMatrix();
        glColor3f(0.56, 0.73, 0.81);
        glTranslatef(19.000000  ,  25.500000  ,  1.000000);
        glScalef(1.500000 ,  1.500000  ,  2.500000);
        glutSolidCube(5);
    glPopMatrix();

    //macaneta
    glPushMatrix();
        glColor3f(0.75, 0.61, 0.44);
        glTranslatef(-16.000000  ,  20.500000  ,  -11.500000);
        glScalef(0.500000 ,  0.500000  ,  -0.500000);
        glutSolidSphere(2,10,5);
    glPopMatrix();

    glPushMatrix();
        glScalef(move.scale.x, move.scale.y, move.scale.z);
        glTranslatef(move.position.x, move.position.y, move.position.z);
        glutSolidTeapot(5);
    glPopMatrix();

    //================================================Teto================================================
    glColor3f(0.84, 0.71, 0.65);
    glPushMatrix();
        glTranslatef(0.000000  ,  33.000000  ,  1.000000);
        glScalef(45.000000 ,  10.500000  ,  25.000000);
        glRotatef(90, 0, 1, 0);
        //DrawBase();
        DrawRoof1();
        DrawRoof2();
        DrawBody();
    glPopMatrix();
    
  // Executa os comandos OpenGL, e depois troca os buffers de vídeo
  glFlush();
}

void reshape (int w, int h)
{
  // Define o viewport como o tamanho da janela
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  // Entra no modo de definição de matriz de projeção
  glMatrixMode (GL_PROJECTION);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a projeção ortogonal
  if (w <= h)
    // Se a largura for menor que a altura, a projeção é feita para manter a proporção da janela
    glOrtho (-50, 50, -50*(GLfloat)h/(GLfloat)w, 50*(GLfloat)h/(GLfloat)w, -100.0, 200.0);
  else
    // Se a altura for menor que a largura, a projeção é feita para manter a proporção da janela
    glOrtho (-50*(GLfloat)w/(GLfloat)h, 50*(GLfloat)w/(GLfloat)h, -50, 50, -100.0, 200.0);
   
}

int main(int argc, char** argv)
{
  // Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas
  glutInit(&argc, argv);
  // Inicializa o display, indicando que usará:
  // - um buffer de imagem (single buffer);
  // - buffer de profundidade;
  // - padrão de cores RGB)
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  // Especifica as dimensões da janela de exibição
  glutInitWindowSize (1500, 800); 
  // Especifica a posição inicial da janela de exibição
  glutInitWindowPosition (100, 100);
  // Cria a janela de exibição
  win_id = glutCreateWindow (argv[0]);
  // Chama a função init
  init ();
  // Estabelece a função "display" como a função callback de exibição.
  glutDisplayFunc(display); 
  // Estabelece a função "reshape" como a função callback de redimensionamento da janela de exibição.
  glutReshapeFunc(reshape);
  // Estabelece a função "keyboard" como a função callback de evento de teclado.
  glutKeyboardFunc(myKeyboard);
  // Estabelece a função "keyboardSpecial" como a função callback de evento de teclado especial.
  glutSpecialFunc(myKeyboardSpecial);
  // Estabelece a função "mouse" como a função callback de evento de mouse.
  glutMouseFunc(myMouse);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}