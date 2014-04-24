#include <stdlib.h>
#include <windows.h>
#include <glut.h>
#include <time.h>

#include <cmath>
#include <vector>

#include "timer.h"
#include "rand.h"
#include "molecule.h"

using namespace std;

const double deltaRotateSpeed = 1;

int Width = 1024, Height = 780;
timer MainTimer;
vector<molecule> dots;
double Depth = 9000, Scale = 3000, Speed = 0.05, wh, RotateSpeed = 5;

void Display ()
{
  static double angle = 0;

  angle += RotateSpeed * MainTimer.getDeltaTime ();

  glClearColor (0.3, 0.5, 0.7, 1);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity ();

  gluLookAt (Scale, Scale, Scale, 0, 0, 0, 0, 1, 0);

  glRotated (angle, 0, 1, 0);

  glBegin (GL_LINES);

  glColor3d (1, 0, 0);
  glVertex3d (0, 0, 0);
  glVertex4d (1, 0, 0, 0);

  glColor3d (0, 1, 0);
  glVertex3d (0, 0, 0);
  glVertex4d (0, 1, 0, 0);

  glColor3d (0, 0, 1);
  glVertex3d (0, 0, 0);
  glVertex4d (0, 0, 1, 0);

  glEnd ();

  glColor3d (0.4, 0.1, 0.5);

  glPointSize (5);

  glBegin (GL_POINTS);

  for (unsigned int i = 0; i < dots.size (); i++)
    glVertex3d (dots[i].getPos().x, dots[i].getPos().y, dots[i].getPos().z);

  glEnd ();

  glFinish ();
  glutSwapBuffers ();
}

void Idle ()
{
  MainTimer.update ();

  unsigned int i;

  if (!MainTimer.getIsPause ())
  {
    for (i = 0; i < dots.size (); i++)
      dots[i].move (dots, Speed * MainTimer.getDeltaTime ());

    for (i = 0; i < dots.size (); i++)
      dots[i].update ();
  }

  glutPostRedisplay ();
}

void Keyboard (unsigned char key, int x, int y)
{
  switch (key)
  {
  default:
    break;

  case 27:
  case 'Q':
  case 'q':
    exit (EXIT_SUCCESS);

  case 'P':
  case 'p':
    MainTimer.switchPause ();
    break;

  case 'S':
  case 's':
    Depth = 2 * SQRT3 * (Scale *= 1.1);
    gluPerspective (60, wh, 1, 10 * Depth);
    break;

  case 'W':
  case 'w':
    Depth = 2 * SQRT3 * (Scale /= 1.1);
    gluPerspective (60, wh, 1, 10 * Depth);
    break;

  case 'A':
  case 'a':
    RotateSpeed += deltaRotateSpeed;
    break;

  case 'D':
  case 'd':

    RotateSpeed -= deltaRotateSpeed;
    break;

  case '-':
    Speed /= 2;
    break;

  case '+':
    Speed *= 2;
    break;
  }
}

void Reshape (int width, int height)
{
  glViewport (0, 0, Width = width, Height = height);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  double tmp = height > width ? height / width : width / height;
  gluPerspective (60, wh = (double)width / height, 1, Depth);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

void main (int __argc, char *__argv[])
{
  FreeConsole ();

  for (int i = 0; i < 512; i++)
    dots.push_back (molecule((10 * rand01() + 2) * 1e15, vecgenerate() * 1000));

  glutInit (&__argc, __argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize (Width, Height);

  glutCreateWindow (__argv[0]);

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_POINT_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glutDisplayFunc (Display);
  glutIdleFunc (Idle);
  glutReshapeFunc (Reshape);
  glutKeyboardFunc (Keyboard);

  glutMainLoop ();
}