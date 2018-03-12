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
  window_size( size),
  field( new Field( 12,12))
{
  glutInit( argc, argv);

  glutInitDisplayMode(GLUT_RGB|GLUT_MULTISAMPLE);

  glutInitWindowSize( window_size.x, window_size.y);

  glutCreateWindow("The Hex Game");

  glutDisplayFunc(&Game::draw);
  glutKeyboardFunc(&Game::keyboard);
  glutMouseFunc(&Game::mouse);
}

Game::~Game() {
  delete field;
}

void Game::drawGame() {
    // Black background
    //glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glOrtho( -0.5 * window_size.x, 0.5 * window_size.x, -0.5 * window_size.y, 0.5 * window_size.y, 1, -1);

    glScalef( 50, 50, 1);

    field->draw();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth( 4);
    glPointSize(5);
    way = field->getWay( Position( 11, 1), Position( 1, 11));
    field->drawLine( way);

    // glColor3f( 0,1,0);
    // glPointSize( 5);
    // glBegin(GL_POINTS);
    // for( Position pos : field->getSurounding(Position(1,1))){
    //   Tile* tile = field->getTile( pos);
    //   if( tile) {
    //     vec2 vec = (vec2) (*tile);
    //     glVertex2f( vec.x, vec.y);
    //   }
    // }
    // glEnd();

    glFlush();
    glutSwapBuffers();
}

void Game::draw() {
  Game::getInstance()->drawGame();
}

void Game::keyGame(unsigned char c, int x, int y){
  if(c == 27){
    exit(0);
  }
}
void Game::keyboard(unsigned char c, int x, int y){
  Game::getInstance()->keyGame(c,x,y);
}

void Game::mouseGame(int button, int state, int x, int y){
  if(button == GLUT_RIGHT_BUTTON){
    exit(0);
  }
}
void Game::mouse(int button, int state, int x, int y) {
  Game::getInstance()->mouseGame(button,state,x,y);
}

//Main program

int main(int argc, char **argv) {
  Game::init( &argc, argv, vec2(800,600));
  return 0;
}
