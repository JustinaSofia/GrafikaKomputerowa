// Program1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
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
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
// Wywo³ywana w celu przerysowania sceny

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
// Wywo³ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkoœæ
void TimerFunction(int value) {
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	if (x1 > windowWidth / 2 - xsize || x1 < -windowWidth / 2 + xsize)
		xstep = -xstep;

	// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	if (y1 > windowHeight / 2 - ysize || y1 < -windowHeight / 2 + ysize)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	//// przestrzeni¹ ograniczajc¹.     
	if (x1 > windowWidth / 2 - xsize)
		x1 = windowWidth / 2 - xsize - 1;

	if (y1 > windowHeight / 2 - ysize)
		y1 = windowHeight / 2 - ysize - 1;

	// Wykonanie przesuniêcia kwadratu
	x1 += xstep;
	y1 += ystep;

	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszcz¹cego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT przy ka¿dej zmianie wielkoœci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk³adu wspó³rzêdnych
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

	// Ustanowienie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G³ówny punkt wejœcia programu
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

