#include <GL/glut.h> 
#include <stdio.h> 

int x1, y1, x2, y2;

void reshape(int width, int height) 
{ 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-100, 100, -100, 100, -100, 100); 
	glMatrixMode(GL_MODELVIEW); 
} 

void write_pixel(int x, int y)
{
	glBegin(GL_POINTS); 
	glVertex3f(x, y, 0); 
	glEnd(); 
}

void inc_line(int x1, int y1, int x2, int y2)
{
	int dx, dy, incE, incNE, d, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	d = 2 * dy - dx;  
	incE = 2 * dy;   
	incNE = 2 * (dy - dx);  
	x = x1;
	y = y1;
	write_pixel(x, y);
	while (x < x2) {
		if (d <= 0) {
			d += incE;
			x++;
		} else {
			d += incNE;
			x++;
			y++;
		}
		write_pixel(x, y);
	}
}

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0, 1, 0); 
	glLoadIdentity(); 
	inc_line(x1, y1, x2, y2);
	glFlush(); 
} 

void init() 
{ 
	glClearColor(0, 0, 0, 0);  
} 

int main(int argc, char **argv) 
{ 
	printf("Ingrese x1, y1, x2, y2 (x2 > x1 y (y2 - y1)/(x2 - x1) debe estar entre 0 y 1):\n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	if (x2 <= x1 || (y2 - y1) > (x2 - x1)) {
		printf("Error: Las coordenadas no cumplen con las restricciones del primer octante.\n");
		return 1;  // Termina el programa si las condiciones no se cumplen
	}
	
	//10 10 20 15
	//0 0 50 25
	//30 45 80 75
	//5 5 10 10
	//25 30 75 50
	//10 10 100 50
	//20 20 120 80
	//0 0 150 100
	//50 50 200 150
	//40 40 240 160
	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("Dibujo de línea del primer octante en OpenGL"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMainLoop(); 
	return 0; 
}
