
/* X compile line: gcc -o main main.c -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>    
#define PI 3.14159265359

#define NUM_SMOKE_PARTICLES 10

#define NUM_CLOUDS 5
GLfloat cloudPositions[NUM_CLOUDS][2];

typedef struct {
    GLfloat x, y;      //posição da fumaça
    GLfloat radius;    //tamanho da fumaça
    GLfloat alpha;     //transparência da fumaça
} Smoke;

Smoke smokeParticles[NUM_SMOKE_PARTICLES];

void initializeSmoke();
void drawSmoke();
void updateSmoke();
void drawLine(float x1,float y1, float x2, float y2, float width);
GLfloat randomFloat(GLfloat min, GLfloat max);
void updateClouds();
void drawEllipse(GLfloat x, GLfloat y, GLfloat xRadius, GLfloat yRadius);
void drawCloud(GLfloat x, GLfloat y);
void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a);


//============================================UTILS=====================================================
GLfloat randomFloat(GLfloat min, GLfloat max) {
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

void drawLine(float x1,float y1, float x2, float y2, float width){

    //calcular a direção da linha
    float length = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    float dx = (x2 - x1) / length;
    float dy = (y2 - y1) / length;

    //vetor perpendicular
    float perpX = -dy;
    float perpY = dx;

    //pontos do retângulo
    float halfWidth = width / 2;
    float p1x = x1 + halfWidth * perpX;
    float p1y = y1 + halfWidth * perpY;
    float p2x = x2 + halfWidth * perpX;
    float p2y = y2 + halfWidth * perpY;
    float p3x = x2 - halfWidth * perpX;
    float p3y = y2 - halfWidth * perpY;
    float p4x = x1 - halfWidth * perpX;
    float p4y = y1 - halfWidth * perpY;

    //desenhar o retângulo pequeno 
    glBegin(GL_QUADS);
        glColor3f(0.45, 0.32, 0.18); 
        glVertex2f(p1x, p1y);
        glVertex2f(p2x, p2y);
        glVertex2f(p3x, p3y);
        glVertex2f(p4x, p4y);
    glEnd();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
}

void timer(int value) {
    updateClouds();
    updateSmoke();
    glutPostRedisplay();  //redesenha a cena
    glutTimerFunc(30, timer, 0);
}


void drawEllipse(GLfloat x, GLfloat y, GLfloat xRadius, GLfloat yRadius){
    int i;
    int lineAmount = 100;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);  // branco
    for(i = 0; i <= lineAmount; i++) { 
        glVertex2f(
            x + (xRadius * cos(i * twicePi / lineAmount)), 
            y + (yRadius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}



void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	

	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
        glColor4f(r,g,b, a);  /* blue */
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}
//=========================================SMOKE FUNCS==================================================
void initializeSmoke() {
    for (int i = 0; i < NUM_SMOKE_PARTICLES; i++) {
        smokeParticles[i].x = 660;  //posição x da chamine
        smokeParticles[i].y = 560;  //posição y da chamine
        smokeParticles[i].radius = randomFloat(5, 15);
        smokeParticles[i].alpha = 1.0;
    }
}

void drawSmoke() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = 0; i < NUM_SMOKE_PARTICLES; i++) {
        drawCircle(smokeParticles[i].x, smokeParticles[i].y, smokeParticles[i].radius, 0.5, 0.5, 0.5, smokeParticles[i].alpha);
    }
    glDisable(GL_BLEND);
}

void updateSmoke() {
    for (int i = 0; i < NUM_SMOKE_PARTICLES; i++) {
        smokeParticles[i].y += randomFloat(2, 5);
        smokeParticles[i].radius += randomFloat(0.1, 0.5);
        smokeParticles[i].alpha -= 0.02;
        
        if (smokeParticles[i].alpha <= 0) {
            smokeParticles[i].x = 660;
            smokeParticles[i].y = 560;
            smokeParticles[i].radius = randomFloat(5, 15);
            smokeParticles[i].alpha = 1.0;
        }
    }
}




//======================================NUVEM FUNCS==============================================
void updateClouds() {
    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloudPositions[i][0] += 1.0;  // Move a nuvem horizontalmente

        // Se a nuvem sair da tela, reinicie sua posição
        if (cloudPositions[i][0] > 1300) { 
            cloudPositions[i][0] = -100;
            cloudPositions[i][1] = randomFloat(600, 750);
        }
    }
}

void drawCloud(GLfloat x, GLfloat y) {
    //principal
    drawEllipse(x, y, randomFloat(60, 70), randomFloat(40, 50));
    
    //forma
    drawEllipse(x - randomFloat(40, 50), y, randomFloat(35, 45), randomFloat(25, 35));
    drawEllipse(x + randomFloat(40, 50), y, randomFloat(35, 45), randomFloat(25, 35));
    drawEllipse(x, y + randomFloat(25, 35), randomFloat(50, 60), randomFloat(30, 40));
    drawEllipse(x - randomFloat(70, 80), y, randomFloat(25, 35), randomFloat(20, 30));
    drawEllipse(x + randomFloat(70, 80), y, randomFloat(25, 35), randomFloat(20, 30));

    //circulos para detalhar
    drawEllipse(x - randomFloat(25, 35), y + randomFloat(15, 25), randomFloat(30, 40), randomFloat(20, 30));
    drawEllipse(x + randomFloat(25, 35), y + randomFloat(15, 25), randomFloat(30, 40), randomFloat(20, 30));
    drawEllipse(x - randomFloat(55, 65), y + randomFloat(10, 20), randomFloat(25, 35), randomFloat(15, 25));
    drawEllipse(x + randomFloat(55, 65), y + randomFloat(10, 20), randomFloat(25, 35), randomFloat(15, 25));


}


//==========================================================Display=====================================================
void display(void)
{

    //COR DE FUNDO
    glClearColor(0.36, 0.83, 0.93, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);

    //======================CHAO
    glBegin(GL_POLYGON);
        glColor3f(0.26, 0.44, 0.2);  /* blue */
        glVertex2i(0, 0);
        glVertex2i(0, 400);
        glVertex2i(1250, 500);
        glVertex2i(1250,0);
    glEnd();

    //=======================SOL
    drawCircle(40, 620, 50, 1.0, 1.0, 0.0, 1);

    //=======================NUVEM
    for (int i = 0; i < NUM_CLOUDS; i++) {
        drawCloud(cloudPositions[i][0], cloudPositions[i][1]);
    }

    //======================TETO TRAS
    glBegin(GL_POLYGON);
        glColor3f(0.53, 0.18, 0.19);  
        glVertex2i(250, 500);
        glVertex2i(750, 550);
        glVertex2i(800, 440);
        glVertex2i(150, 370);
    glEnd();

    //==================PAREDE FRENTE TRIANGULAR
    glBegin(GL_TRIANGLES);
        glColor3f(0.59, 0.28, 0.29);  
        glVertex2i(200, 400);
        glVertex2i(300, 500);
        glVertex2i(400, 350);
    glEnd();
    drawLine(200, 400, 300, 500, 4);
    drawLine(200, 400, 400, 350, 7);


    //=================CIRCULO EM CIMA DA PORTA
    drawCircle(280, 430, 20, 0.76, 0.91, 0.98, 1); 

    //====================PAREDE FRENTE
    glBegin(GL_POLYGON);
        glColor3f(0.81, 0.65, 0.47);  
        glVertex2i(200, 200);
        glVertex2i(200, 400);
        glVertex2i(400, 350);
        glVertex2i(400, 150);
    glEnd();

    //======================PAREDE LATERAL
    glBegin(GL_POLYGON);
        glColor3f(0.78, 0.62, 0.44);  
        glVertex2i(400, 150);
        glVertex2i(400, 350);
        glVertex2i(800, 400);
        glVertex2i(800, 200);
    glEnd();

    //=====================TETO FRENTE
    glBegin(GL_POLYGON);
        glColor3f(0.53, 0.18, 0.19);  
        glVertex2i(250, 500);
        glVertex2i(750, 550);
        glVertex2i(850, 350);
        glVertex2i(350, 300);
    glEnd();
    drawLine(250, 500, 750, 550, 7);

    //======================PORTA
    glBegin(GL_POLYGON);
        glColor3f(0.52, 0.39, 0.25); 
        glVertex2i(270, 182);
        glVertex2i(270, 288);
        glVertex2i(330, 277);
        glVertex2i(330, 167);
    glEnd();
    drawLine(270, 182, 270, 288, 7);
    drawLine(270, 288, 330, 277, 7);
    drawLine(330, 277, 330, 167, 7);


    //=======================MACANETA
    drawCircle(320, 210, 3, 0.8, 0.92, 0.93, 1); 

    //==========================JANELA 1
    glBegin(GL_POLYGON);
        glColor3f(0.76, 0.91, 0.98); 
        glVertex2i(460, 224);
        glVertex2i(460, 274);
        glVertex2i(560, 284);
        glVertex2i(560, 234);
    glEnd();
    //LINHAS JANELA 1
    drawLine(460, 224, 460, 274, 7);
    drawLine(460, 274, 560, 284, 7);
    drawLine(560, 284, 560, 234, 7);
    drawLine(560, 234, 460, 224, 7); 
    drawLine(460, 250, 560, 260, 7); // horizontal meio
    drawLine(510, 228, 510, 278, 7); // vertical meio

    //========================JANELA 2
    glBegin(GL_POLYGON);
        glColor3f(0.76, 0.91, 0.98); 
        glVertex2i(650, 242);
        glVertex2i(650, 292);
        glVertex2i(750, 302);
        glVertex2i(750, 252);
    glEnd();
    //LINHAS JANELA 2
    drawLine(650, 242, 650, 292, 7);
    drawLine(650, 292, 750, 302, 7);
    drawLine(750, 302, 750, 252, 7);
    drawLine(750, 252, 650, 242, 7); 
    drawLine(650, 267, 750, 277, 7); // horizontal meio
    drawLine(700, 297, 700, 247, 7); // vertical meio

    //==============================Sombra
    glBegin(GL_POLYGON);
        glColor3f(0.21, 0.37, 0.16); 
        glVertex2i(400, 150);
        glVertex2i(800, 200);
        glVertex2i(1000, 150);
        glVertex2i(600, 100);
    glEnd();

    //=======================CHAMINE 
    glBegin(GL_POLYGON); //direita
        glColor3f(0.38, 0.08, 0.09); 
        glVertex2i(650, 480);
        glVertex2i(650, 550);
        glVertex2i(700, 557);
        glVertex2i(700, 487);
    glEnd();
    glBegin(GL_POLYGON); //esquerda
        glColor3f(0.41, 0.13, 0.14); 
        glVertex2i(650, 480);
        glVertex2i(625, 520);
        glVertex2i(625, 565);
        glVertex2i(650, 550);
    glEnd();
    glBegin(GL_POLYGON); //topo
        glColor3f(0.29, 0.09, 0.05); 
        glVertex2i(650, 550);
        glVertex2i(625, 565);
        glVertex2i(673, 572); //-adef
        glVertex2i(700, 557);
    glEnd();

    //==========================FUMACA
    drawSmoke();
    glFlush();  /* Single buffered, so needs a flush. */
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    //inicializa posicao das nuvens
    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloudPositions[i][0] = randomFloat(100, 1100);
        cloudPositions[i][1] = randomFloat(600, 750);
    }
    
    //inicializa a fumaca da chamine
    initializeSmoke();


    //GLUT INIT SETTINGS
    glutInit(&argc, argv);
    glutInitWindowSize(1250,800);
    glutCreateWindow("single triangle");

    //ve o tamanho ou largura maximo permitido da linha
    GLfloat sizes[2];
    glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);
    printf("Min line width: %f, Max line width: %f\n", sizes[0], sizes[1]);
    glDisable(GL_LINE_SMOOTH);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(30, timer, 0);
    glutMainLoop();

  return 0;    
}