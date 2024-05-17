#include <GL/glut.h>

// Variables para el cubo
float angleX = 0.0f;
float angleY = 0.0f;
float posX = 0.0f;
float posY = 0.0f;
float posZ = -5.0f; // Alejar el cubo inicialmente para que sea visible

// Función para dibujar el cubo
void drawCube() {
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	
	// Dibujar caras del cubo
	glBegin(GL_QUADS);
	// Cara frontal
	glColor3f(1.0f, 0.0f, 0.0f); // Rojo
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Cara trasera
	glColor3f(0.0f, 1.0f, 0.0f); // Verde
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// Cara izquierda
	glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	// Cara derecha
	glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Cara superior
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Cara inferior
	glColor3f(0.0f, 1.0f, 1.0f); // Cian
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	
	glPopMatrix();
}

// Función para configurar la cámara
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Función para dibujar la escena
void display() {
	// Limpiar el búfer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Configurar la cámara
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// Dibujar el cubo
	drawCube();
	
	// Intercambiar los búferes
	glutSwapBuffers();
}

// Función para manejar las teclas normales
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'f': // Avanzar hacia adelante 5 unidades de distancia
		posZ -= 5.0f;
		break;
	case 'r': // Girar a la derecha 10 grados
		angleY += 10.0f;
		break;
	case 'l': // Girar a la izquierda 10 grados
		angleY -= 10.0f;
		break;
	case 'b': // Retroceder 5 unidades de distancia
		posZ += 5.0f;
		break;
	case 'u': // Girar hacia arriba 10 grados
		angleX += 10.0f;
		break;
	case 'd': // Girar hacia abajo 10 grados
		angleX -= 10.0f;
		break;
	}
	glutPostRedisplay();
}

// Función para manejar las teclas especiales
void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: // Girar hacia arriba 10 grados
		angleX += 10.0f;
		break;
	case GLUT_KEY_DOWN: // Girar hacia abajo 10 grados
		angleX -= 10.0f;
		break;
	}
	glutPostRedisplay();
}

// Función principal
int main(int argc, char** argv) {
	// Inicializar GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Transformaciones del Cubo");
	
	// Habilitar el z-buffer
	glEnable(GL_DEPTH_TEST);
	
	// Configurar la función de visualización
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	
	// Configurar la cámara
	setupCamera();
	
	// Iniciar el bucle de eventos de GLUT
	glutMainLoop();
	
	return 0;
}
