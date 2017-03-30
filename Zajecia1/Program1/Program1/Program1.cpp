// Program1.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//


#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// Pocztkowy rozmiar i pozycja prostokta
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLsizei xsize = 80;
GLsizei ysize = 40;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
// Wywo�ywana w celu przerysowania sceny

void rysuj(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.98f, 0.04f, 0.7f);
	glBegin(GL_TRIANGLES);

	glVertex2f(-25.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);
	glVertex2f(-10.0f + windowWidth / 2 + x1, 20.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);

	glVertex2f(-10.0f + windowWidth / 2 + x1, 20.0f + windowHeight / 2 + y1);
	glVertex2f(10.0f + windowWidth / 2 + x1, 20.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);

	glVertex2f(10.0f + windowWidth / 2 + x1, 20.0f + windowHeight / 2 + y1);
	glVertex2f(25.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);

	glVertex2f(25.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);
	glVertex2f(10.0f + windowWidth / 2 + x1, -20.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);

	glVertex2f(10.0f + windowWidth / 2 + x1, -20.0f + windowHeight / 2 + y1);
	glVertex2f(-10.0f + windowWidth / 2 + x1, -20.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);

	glVertex2f(-10.0f + windowWidth / 2 + x1, -20.0f + windowHeight / 2 + y1);
	glVertex2f(-25.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);
	glVertex2f(0.0f + windowWidth / 2 + x1, 0.0f + windowHeight / 2 + y1);



	glEnd();
	glFlush();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.6f, 0.4f, 0.7f, 1.0f);

	rysuj(x1, y1);
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielko��
void TimerFunction(int value) {
	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if (x1 > windowWidth / 2 - xsize || x1 < -windowWidth / 2 + xsize)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if (y1 > windowHeight / 2 - ysize || y1 < -windowHeight / 2 + ysize)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy�o swoj wielko�� w czasie, gdy kwadrat odbija� si� od     
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza      
	//// przestrzeni� ograniczajc�.     
	if (x1 > windowWidth / 2 - xsize)
		x1 = windowWidth / 2 - xsize - 1;

	if (y1 > windowHeight / 2 - ysize)
		y1 = windowHeight / 2 - ysize - 1;

	// Wykonanie przesuni�cia kwadratu
	x1 += xstep;
	y1 += ystep;

	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszcz�cego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT przy ka�dej zmianie wielko�ci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G��wny punkt wej�cia programu
void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zad3");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}

