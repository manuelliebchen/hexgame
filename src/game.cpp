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
      field = new Field( 100 * three_sqrt_half, 100);
    }
  } else {
    field = new Field( 100 * three_sqrt_half, 100, 50, 30);
  }

  display_position = vec2(-0.5f * field->getSize()[0] * three_sqrt_half, -0.5f * field->getSize()[1] * 0.75f);
  zoom = 50;
  player = nullptr;

  int glut_argc = 1;
  char *glut_argv[1] = {(char*)"hexgame"};
  glutInit(&glut_argc, glut_argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

  glutInitWindowSize( window_size.x, window_size.y);
  glutCreateWindow("The Hex Game");

  glEnable(GL_ALPHA_TEST);
  glAlphaFunc( GL_GREATER, 0.4);
  glEnable(GL_MULTISAMPLE);
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_POLYGON_SMOOTH );

  glClearColor( 0.078f, 0.23f, 0.477f, 1.0f);

  glutDisplayFunc(&drawCallback);
  glutKeyboardFunc(&keyboardCallback);
  glutMouseFunc(&mouseCallback);
  glutMotionFunc(&mousemotionCallback);
  glutPassiveMotionFunc(&passivmotionCallback);
  glutReshapeFunc(&reshapeCallback);
}

Game::~Game() {
  delete field;
}

void Game::draw() {
  // std::clock_t c_start = std::clock();
  glClear(GL_COLOR_BUFFER_BIT);

  field->draw(display_position);

  if( player) {
    glColor4ub( 0, 192, 255, 128);
    field->mark( display_position, field->findSurounding( player->standing_on, TURN_WALKING_DISTANCE));
    if( player->standing_on) {
      std::vector<Tile*> path = field->findPath( player->standing_on, hover);
      glColor4ub( 0, 0, 255, 128);
      field->mark( display_position, path);
    }
  }

  glutSwapBuffers();
  // std::clock_t c_end = std::clock();
  // std::cout << "FPS: " << CLOCKS_PER_SEC / (float)(c_end-c_start) << std::endl;
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
      zoom *= 1.1;
      reloadMatrix();
    } else if( button == 4) {
      if( state == GLUT_DOWN) return;
      zoom /= 1.1;
      reloadMatrix();
    }
  } else if( state == GLUT_DOWN) {
    click_position = vec2(x,-y);
    vec2 mouse_position = getFieldPosition( x,y);
    Tile* tile = field->estimatTile( mouse_position);
    if( tile) {
      // if( button == GLUT_MIDDLE_BUTTON) {
      //   if( !tile->getFigure()){
      //     tile->plant();
      //   } else if ( dynamic_cast<Bush*>(tile->getFigure())) {
      //     tile->clear();
      //     tile->place( new Coin);
      //   } else if ( dynamic_cast<Coin*>(tile->getFigure())) {
      //     tile->clear();
      //     player = new Player(tile);
      //     tile->place( player);
      //   } else {
      //     if( tile->getFigure() == player) {
      //       player = nullptr;
      //     }
      //     tile->clear();
      //   }
      // } else
      if( button == GLUT_RIGHT_BUTTON) {
        if( player ) {
          if( tile == player->standing_on) {
            player = nullptr;
          } else {
            move_player_to( tile);
          }
        } else if( dynamic_cast<Player*>(tile->getFigure())) {
          player = dynamic_cast<Player*>(tile->getFigure());
        }
      }
    }
  }
  glutPostRedisplay();
}

bool
Game::move_player_to( Tile* tile) {
  std::vector<Tile*> surrounding = field->findSurounding( player->standing_on, TURN_WALKING_DISTANCE);
  std::vector<Tile*> path = field->findPath( player->standing_on, tile);
  if( std::find( surrounding.begin(), surrounding.end(), tile) == surrounding.end()) {
    return false;
  }
  player->move( tile);
  return true;
}

void
Game::reloadMatrix() {
  glLoadIdentity();
  glOrtho( -0.5 * window_size.x, 0.5 * window_size.x, -0.5 * window_size.y, 0.5 * window_size.y, 1, -1);
  glScalef( zoom, zoom, 1);
}

void
Game::reshape( int width, int height) {
  glViewport(0,0,width,height);
  window_size = vec2( width, height);
  reloadMatrix();
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
  Tile* tile = field->estimatTile( mouse_position);
  if( tile) {
    hover = tile;
    glutPostRedisplay();
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
