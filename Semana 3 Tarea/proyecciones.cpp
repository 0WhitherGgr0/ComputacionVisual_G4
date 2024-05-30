#include <GL/glut.h> 

GLfloat anguloCuboX = 0.0f;  
GLfloat anguloCuboY = 0.0f; 
GLfloat anguloEsfera = 0.0f; 
GLint ancho, alto; 
int hazPerspectiva = 1; 

// Variables para proyección ortogonal
GLfloat orthoLeft = -4.0f;
GLfloat orthoRight = 4.0f;
GLfloat orthoBottom = -4.0f;
GLfloat orthoTop = 4.0f;
GLfloat orthoZNear = 1.0f;
GLfloat orthoZFar = 8.0f;

// Variables para proyección en perspectiva
GLfloat perspectiveAngle = 45.0f;
GLfloat perspectiveZNear = 1.0f;
GLfloat perspectiveZFar = 4.8f;

void reshape(int width, int height) { 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	if(hazPerspectiva) 
		gluPerspective(perspectiveAngle, (GLfloat)width/(GLfloat)height, perspectiveZNear, perspectiveZFar); 
	else 
		glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoZNear, orthoZFar); 
	
	glMatrixMode(GL_MODELVIEW); 
	
	ancho = width; 
	alto = height; 
} 

void drawCube(void) { 
	glColor3f(1.0f, 0.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara frontal 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 1.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara trasera 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 0.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara lateral izq 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glEnd();
	glColor3f(1.0f, 1.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara lateral dcha 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 1.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara arriba 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glEnd(); 
	
	glColor3f(1.0f, 0.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara abajo 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glEnd(); 
} 

void display() { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLoadIdentity(); 
	
	glTranslatef(0.0f, 0.0f, -5.0f); 
	
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f); 
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.5f);
	
	glLoadIdentity(); 
	
	glTranslatef(0.0f, 0.0f, -5.0f); 
	glRotatef(anguloEsfera, 0.0f, 1.0f, 0.0f); 
	glTranslatef(3.0f, 0.0f, 0.0f); 
	
	glColor3f(1.0f, 1.0f, 1.0f); 
	//drawCube(); 
	
	glFlush(); 
	glutSwapBuffers(); 
	//    anguloCuboX+=0.1f; 
	//    anguloCuboY+=0.1f; 
	//    anguloEsfera+=0.2f; 
} 

void init() { 
	glClearColor(0,0,0,0); 
	glEnable(GL_DEPTH_TEST); 
	ancho = 400; 
	alto = 400; 
} 

void idle() { 
	display(); 
} 

void keyboard(unsigned char key, int x, int y) { 
	switch(key){
	case 'p': 
	case 'P': 
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break; 
		
	case 'o': 
	case 'O': 
		hazPerspectiva=0; 
		reshape(ancho,alto); 
		break; 
		
	case 'i':
	case 'I':
		orthoLeft -= 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'd':
	case 'D':
		orthoRight += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'a':
	case 'A':
		orthoBottom -= 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'u':
	case 'U':
		orthoTop += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'n':
		if (hazPerspectiva) perspectiveZNear -= 0.1f;
		else orthoZNear -= 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'N':
		if (hazPerspectiva) perspectiveZNear += 0.1f;
		else orthoZNear += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'f':
		if (hazPerspectiva) perspectiveZFar -= 0.1f;
		else orthoZFar -= 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'F':
		if (hazPerspectiva) perspectiveZFar += 0.1f;
		else orthoZFar += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'b':
		perspectiveAngle -= 0.1f;
		reshape(ancho, alto);
		break;
		
	case 'B':
		perspectiveAngle += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 27:   // escape 
		exit(0); 
		break; 
	} 
} 

int main(int argc, char **argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(ancho, alto); 
	glutCreateWindow("Objeto_3D"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 
	glutKeyboardFunc(keyboard); 
	glutMainLoop(); 
	return 0; 
}
