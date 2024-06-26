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
	glVertex3f(x,y,0); 
	glEnd(); 
}

void line(int x1, int y1, int x2, int y2)
{
	int x, y;
	float a;
	int valor;
	a=(float)(y2-y1)/(x2-x1);
	for (x=x1;x<=x2;x++)
	{
		/* redondear y */
		y = (y1 + a * (x- x1));
		write_pixel(x, y);
	}/* end for */
}/*end line */

//ALgoritmo de Punto-Medio incremental
void inc_line(int x1, int y1, int x2, int y2) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx, sy;
	
	int d, incE, incNE, x, y;
	
	if (x1 < x2) {
		sx = 1;
	} else {
		sx = -1;
	}
	
	if (y1 < y2) {
		sy = 1;
	} else {
		sy = -1;
	}
	
	if (dx >= dy) {
		// La l�nea es m�s horizontal que vertical
		d = 2 * dy - dx;
		incE = 2 * dy;
		incNE = 2 * (dy - dx);
		
		x = x1;
		y = y1;
		while (x != x2) {
			write_pixel(x, y);
			if (d <= 0) {
				d += incE;
				x += sx;
			} else {
				d += incNE;
				x += sx;
				y += sy;
			}
		}
	} else {
		// La l�nea es m�s vertical que horizontal
		d = 2 * dx - dy;
		incE = 2 * dx;
		incNE = 2 * (dx - dy);
		
		x = x1;
		y = y1;
		while (y != y2) {
			write_pixel(x, y);
			if (d <= 0) {
				d += incE;
				y += sy;
			} else {
				d += incNE;
				y += sy;
				x += sx;
			}
		}
	}
	write_pixel(x, y); // Ensure the last point is drawn
}
void CirclePoints(int x, int y)
{
	write_pixel(x, y);
	write_pixel(x,-y);
	write_pixel(-x, y);
	write_pixel(-x,-y);
	write_pixel(y, x);
	write_pixel(y,-x);
	write_pixel(-y, x);
	write_pixel(-y,-x);
}/*endCirclePoints*/

void MidPointCircle(int r)
{
	int x, y;
	float d;
	/* Valores iniciais */
	x = 0;
	y = r;
	d = 5/4- r;
	CirclePoints(x, y);
	while (y > x){
		if (d < 0){
			/* Selecione E */
			d = d + 2 * x + 3;
			x++;
		}else{
			/* Selecione SE */
			d = d + 2 * (x- y) + 5;
			x++;
			y--;
		}/*end if*/
		CirclePoints(x, y);
	}/* end while */
}/* end MidpointCircle */

void MidPointCircleInt(int r)
{
	int x, y, d;
	/* Valores iniciais */
	x = 0;
	y = r;
	d = 1- r;
	CirclePoints(x, y);
	while (y > x){
		if (d < 0){
			/* Selecione E */
			d = d + 2 * x + 3;
			x++;
		}else{
			/* Selecione SE */
			d = d + 2 * (x- y) + 5;
			x++;
			y--;
		}/*end if*/
		CirclePoints(x, y);
	}/* end while */
}/* end MidpointCircleInt */

void ElipsePoints(int x, int y)
{
	write_pixel(x, y);
	write_pixel(x,-y);
	write_pixel(-x, y);
	write_pixel(-x,-y);
	
}/*endCirclePoints*/

void MidpointElipse(int a,int b)
{
	int x,y;
	float d1, d2;
	/*Valoresiniciais*/
	x =0;
	y =b;
	d1=(float)(b*b-a*a*b+a*a)/4.0;
	ElipsePoints(x,y);/*Simetriadeordem4*/
	while(a*a*(y-0.5)>b*b*(x+1))
	{
		/*Regi~ao1*/
		if(d1<0)
		{
			d1=d1+b*b*(2*x+3);
			x++;
		}
		else
		{
			d1=d1+b*b*(2*x+3)+a*a*(-2*y+2);
			x++;
			y--;
		}/*endif*/
		ElipsePoints(x,y);
	}/*endwhile*/
	d2=(float) b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b* b;
	while(y>0)
	{
		/*Regi~ao2*/
		if(d2<0)
		{
			d2=d2+b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
			y--;
		}
		else
		{
			d2=d2+a*a*(-2*y+3);
			y--;
		}/*endif*/
		ElipsePoints(x,y);
	}/*endwhile*/
}/*endMidpointElipse*/

void display() 
{ 
	
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0,1,0); 
	glLoadIdentity(); 
	//line(x1, y1, x2, y2);
	
	inc_line(x1, y1, x2, y2);
	
	// Prueba de l�neas en diferentes cuadrantes
	inc_line(10, 10, 60, 60);     // Primer cuadrante
	inc_line(-10, 10, -60, 60);   // Segundo cuadrante
	inc_line(-10, -10, -60, -60); // Tercer cuadrante
	inc_line(10, -10, 60, -60);   // Cuarto cuadrante
	inc_line(80, 5, -80, -50);   // Del primer al tercer cuadrante
	
	//MidPointCircle(x2);
	//MidPointCircleInt(x2);
	//MidpointElipse(x2,y2);
	glFlush(); 
} 

void init() 
{ 
	glClearColor(0,0,0,0); 
} 

int main(int argc, char **argv) 
{ 
	printf("Ingresar x1, y1, x2, y2 \n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("Hello OpenGL"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMainLoop(); 
	return 0; 
} 
