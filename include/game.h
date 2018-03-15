#ifndef _GAME_
#define _GAME_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>

#include "constants.h"
#include "util.h"
#include "vec2.h"
#include "field.h"
#include "coin.h"
#include "bush.h"

class Game {
public:
  static Game* getInstance();
  static void init( int* argc, char ** argv, vec2 size);

  void draw();
  void mouse(int button, int state, int x, int y);
  void keyboard(unsigned char c, int x, int y);
  void mousemotion( int x, int y);
  void passivmouse( int x, int y);

private:
  vec2 window_size;
  vec2 display_position;
  vec2 click_position;
  float zoom;

  Field * field;

  Tile * selected;
  Tile * second_selected;
  std::vector<Tile*> path;
  std::vector<Tile*> surounding;
  std::vector<Tile*> second_surounding;

  Game( int* argc, char ** argv, vec2 size);
  Game( const Game&);
  ~Game();
  Game operator= (const Game&);

  vec2 getFieldPosition( int x, int y);

  static Game* game;

  friend void drawCallback();
  friend void mouseCallback();
  friend void mousemotionCallback();
  friend void passivmotionCallback();
  friend void keyboardCallback();
};

inline void drawCallback() { Game::getInstance()->draw();};
inline void mouseCallback(int button, int state, int x, int y) { Game::getInstance()->mouse(button, state, x, y);};
inline void mousemotionCallback( int x, int y) { Game::getInstance()->mousemotion( x, y);};
inline void passivmotionCallback( int x, int y) { Game::getInstance()->passivmouse( x, y);};
inline void keyboardCallback(unsigned char c, int x, int y) { Game::getInstance()->keyboard( c, x, y);};

int main( int argc, char ** argv);

#endif
