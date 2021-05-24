#include <GL/glut.h>
#include <stdlib.h>

void inc_line (int x1, int y1, int x2, int y2);
void desenha();
void init();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitWindowSize(256, 256);// especifica as dimensoes da janela
	glutInitWindowPosition(100, 100);// especifica aonde a janela aparece na tela
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);// especifica o uso de cores e buffers
	glutCreateWindow("Desenhando uma linha otimizada");// cria a janela
	init();
	glutDisplayFunc(desenha);// funcao que sera redesenhada pelo GLUT
	glutKeyboardFunc(keyboard);// funcoes de teclado
	glutMainLoop();// mostra todas as janelas criadas
	
	return 0;
}

void inc_line (int x1, int y1, int x2, int y2){

	int dx, dy, incE, incNE, d, x, y;

	dx = x2-x1;
	dy = y2-y1;
	d = 2*dy - dx; //valor inicial de d
	incE = 2*dy; //incremento de E
	incNE = 2*(dy - dx); //incremento de NE
	x = x1; //primeiro ponto da posiçao X -> x1
	y = y1; //primeiro ponto da posição Y -> y1

	glBegin(GL_POINTS);

	do{
		glVertex2i(x,y); //coloca o pixel na tela write-pixel
		if (d > 0){ 
			d = d + incNE; 
			y++; 
		}else 
			d = d + incE;
			 
		x++;
		 
	}while(x < x2);

	glEnd();

	return;
}

void desenha(){

	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f (0.0, 1.0, 0.0);// cor da linha
	inc_line(-100, -100, 100, 100);//coordenadas de x1, y1, x2, y2

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
