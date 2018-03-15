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
      field = new Field( 70, 70);
    }
  } else {
    field = new Field( 70, 70, 50, 10);
  }

  display_position = vec2(-0.5f * field->getSize()[0] * tile_size.x, -0.5f * field->getSize()[1] * tile_size.y);
  zoom = 50;

  int glut_argc = 1;
  char *glut_argv[1] = {(char*)"Something"};
  glutInit(&glut_argc, glut_argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

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

  reloadMatrix();
}

Game::~Game() {
  delete field;
}

void Game::draw() {
    // Black background
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor( 20/256.0f, 59/256.0f, 122/256.0f, 1.0f);

    field->draw(display_position);

    glColor4f( 0.0, 0.75f, 1.0, 0.5f);
    field->mark( display_position, second_surounding);
    glColor4f( 1.0, 0.75f, 0.0, 0.5f);
    field->mark( display_position, surounding);
    glColor4f( 0.0, 0.0f, 1.0, 0.5f);
    field->mark( display_position, path);

    glutSwapBuffers();
}

void Game::keyboard(unsigned char c, int x, int y){
  switch (c) {
    case 27:
      exit(0);
      break;
    case 's':
      field->smoothen(1);
      glutPostRedisplay();
      break;
    case 'f':
      field->forestify(3);
      glutPostRedisplay();
      break;
  }
}

void Game::mouse(int button, int state, int x, int y){
  if( state == GLUT_UP) {
    if( button == GLUT_LEFT_BUTTON) {
      display_position += (vec2(x,-y) - click_position) * (float)( 1/zoom);
      reloadMatrix();
    } else if( button == 3){
      if( state == GLUT_DOWN) return;
      zoom *= 2;
      reloadMatrix();
    } else if( button == 4) {
      if( state == GLUT_DOWN) return;
      zoom /= 2;
      reloadMatrix();
    }
 } else if( state == GLUT_DOWN) {
   click_position = vec2(x,-y);
   vec2 mouse_position = getFieldPosition( x,y);
   Tile* tile = field->getTile( mouse_position);
   if( tile) {
     if( button == GLUT_MIDDLE_BUTTON) {
       if( tile != selected) {
         if( !tile->getFigure() ){
           tile->plant();
         } else {
           tile->clear();
         }
       }
     } else if( button == GLUT_RIGHT_BUTTON) {
       if( tile->isWalkable()) {
         if( selected == tile) {
           selected = nullptr;
           path.clear();
           surounding.clear();
           second_surounding.clear();
         } else {
           selected = tile;
         }
       }
     } else if( button == 7) {
       field->raise( tile, -2);
     } else if( button == 8) {
       field->raise( tile, 2);
     }
     if( selected) {
       path = field->findPath( selected, tile);
       surounding = field->findSurounding( selected, TURN_WALKING_DISTANCE);
       second_surounding = field->findSurounding( selected, 2 * TURN_WALKING_DISTANCE);
     }
   }
  }
  glutPostRedisplay();
}

void
Game::reloadMatrix() {
  glLoadIdentity();
  window_size = vec2( glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  glOrtho( -0.5 * window_size.x, 0.5 * window_size.x, -0.5 * window_size.y, 0.5 * window_size.y, 1, -1);
  glScalef( zoom, zoom, 1);
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
    if( selected) {
      path = field->findPath( selected, tile);
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
