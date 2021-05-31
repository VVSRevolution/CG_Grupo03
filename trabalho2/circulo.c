#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void midPointCircle (int r);
void desenha();
void init();
void keyboard(unsigned char key, int x, int y);
void CirclePoints(int x, int y);

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitWindowSize(256, 256);// especifica as dimensoes da janela
	glutInitWindowPosition(100, 100);// especifica aonde a janela aparece na tela
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);// especifica o uso de cores e buffers
	glutCreateWindow("Desenhando uma circunferência");// cria a janela
	init();
	glutDisplayFunc(desenha);// funcao que sera redesenhada pelo GLUT
	glutKeyboardFunc(keyboard);// funcoes de teclado
	glutMainLoop();// mostra todas as janelas criadas
	
	return 0;
}

void CirclePoints(int x, int y){
    glBegin(GL_POINTS);

    //-------- primeiro quadrante--------
    glVertex2i(x,y);
    glVertex2i(y,x);
    //---------segundo quadrante----------
    glVertex2i(-x,y);
    glVertex2i(-y,x);
    //---------terceiro quadrante--------
    glVertex2i(-x,-y);
    glVertex2i(-y,-x);
    //---------quarto quadrante---------
    glVertex2i(x,-y);
    glVertex2i(y,-x);
        
    glEnd();
}

void midPointCircle (int r){
    int x = 0, y = r;   // x = 0 e y = raio
    float d = 5.0/4.0 - r;
	
    CirclePoints(x, y);  // printa primeiro ponto de cada região

    while (y > x)
    {
        if (d < 0)      // se ponto medio estiver dentro da circunferencia
        {
            d = d + 2 * x + 3;
            x++;
        }else{         // se estiver fora

            d = d + 2 * (x - y) + 5;
            x++;
            y--;

        }

        CirclePoints(x,y);
        
    }
    

	return;
}

void desenha(){

	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f (0.0, 1.0, 0.0);// cor da linha
	midPointCircle(200);

	glFlush();
}

void init(){

	glClearColor(0, 0, 0, 0);//cor de fundo

	gluOrtho2D(-400.0, 400.0, -400.0, 400.0);// modo de projecao ortogonal 2D
}


void keyboard(unsigned char key, int x, int y){
	
	switch (key) { 
	case 27:    // tecla Esc (encerra o programa)  
		exit(0);
		break;
	}
}
