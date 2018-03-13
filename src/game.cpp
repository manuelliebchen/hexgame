#include "game.h"

Game * Game::game = nullptr;

void Game::init( int* argc, char ** argv, vec2 size) {
  game = new Game( argc, argv, size);
  glutMainLoop();
}

Game* Game::getInstance(){
  if(!Game::game){
    Game::game = new Game( nullptr, nullptr, vec2(240,240));
  }
  return Game::game;
}

Game::Game( int* argc, char ** argv, vec2 size) :
  window_size( size)
{
  if( (*argc) >= 2) {
    if( argv[1] == std::string("flat")) {
      field = new Field( 50, 50, 0, 0);
    }
  } else {
    field = new Field( 50, 50, 50, 4);
  }

  display_position = vec2(-0.5f * field->getSize()[0] * tile_size.x, -0.5f * field->getSize()[1] * tile_size.y);
  zoom = 50;

  int glut_argc = 1;
  char *glut_argv[1] = {(char*)"Something"};
  glutInit(&glut_argc, glut_argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

  glutInitWindowSize( window_size.x, window_size.y);

  glutCreateWindow("The Hex Game");

  // glClearColor (0.0, 0.0, 0.0, 0.0);
  // glShadeModel (GL_SMOOTH);

  glEnable(GL_ALPHA_TEST);
  glAlphaFunc( GL_GREATER, 0.4);
  glEnable(GL_MULTISAMPLE);
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_POLYGON_SMOOTH );

  glutDisplayFunc(&drawCallback);
  glutKeyboardFunc(&keyboardCallback);
  glutMouseFunc(&mouseCallback);
  glutMotionFunc(&mousemotionCallback);
  glutPassiveMotionFunc(&passivmotionCallback);
}

Game::~Game() {
  delete field;
}

void Game::draw() {
    // Black background
    //glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
      window_size = vec2( glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
      glOrtho( -0.5 * window_size.x, 0.5 * window_size.x, -0.5 * window_size.y, 0.5 * window_size.y, 1, -1);
      glScalef( zoom, zoom, 1);
      glTranslatef( display_position.x, display_position.y, 0);

      field->draw();

      glColor4f( 1.0, 0.75f, 0.0, 0.75f);
      field->drawPath( surounding);
      glColor4f( 0.0, 0.0f, 1.0, 0.75f);
      field->drawPath( path);
    glPopMatrix();

    glFlush();
}

void Game::keyboard(unsigned char c, int x, int y){
  switch (c) {
    case 27:
      exit(0);
      break;
  }
}

void Game::mouse(int button, int state, int x, int y){
  if( state == GLUT_UP) {
    if( button == GLUT_LEFT_BUTTON) {
      display_position += (vec2(x,-y) - click_position) * (float)( 1/zoom);
    } else if( button == 3){
     if( state == GLUT_DOWN) return;
     zoom *= 2;
    } else if( button == 4) {
     if( state == GLUT_DOWN) return;
     zoom /= 2;
   }
 } else if( state == GLUT_DOWN) {
   click_position = vec2(x,-y);
   vec2 mouse_position = getFieldPosition( x,y);
   Tile* tile = field->getTile( mouse_position);
   if( tile) {
     if( button == GLUT_MIDDLE_BUTTON) {
       Figure*& fig = tile->getFigure();
       if( !fig ){
         fig = new Figure();
       } else {
         fig = nullptr;
       }
     } else if( button == GLUT_RIGHT_BUTTON) {
       selected = tile;
     } else if( button == 7) {
       field->raise( tile, -1);
     } else if( button == 8) {
       field->raise( tile, 1);
     }
     if( selected && second_selected) {
       path = field->findPath( selected, second_selected);
       surounding = field->findSurounding( selected, 5);
     }
   }
  }
  glutPostRedisplay();
}

void
Game::mousemotion( int x, int y) {
  display_position += (vec2(x,-y) - click_position) * (float)( 1/zoom);
  click_position = vec2(x,-y);
  glutPostRedisplay();
}

void
Game::passivmouse( int x, int y) {
  vec2 mouse_position = getFieldPosition( x,y);
  Tile* tile = field->getTile( mouse_position);
  if( tile) {
    second_selected = tile;
    if( selected && second_selected) {
      path = field->findPath( selected, second_selected);
      glutPostRedisplay();
    }
  }
}

vec2
Game::getFieldPosition( int x, int y) {
  vec2 mouse_position(x,y);
  mouse_position -= vec2(window_size.x * 0.5f, window_size.y * 0.5f);
  mouse_position.y = -mouse_position.y;
  mouse_position *= 1/(float)zoom;
  mouse_position -= display_position;
  return mouse_position;
}

int main(int argc, char **argv) {
  Game::init( &argc, argv, vec2(800,600));
  return 0;
}
