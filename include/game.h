#ifndef _GAME_
#define _GAME_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>

#include "util.h"
#include "vec2.h"
#include "field.h"

class Game {
public:
  static Game* getInstance();
  static void init( int* argc, char ** argv, vec2 size);

  static void draw();
  static void mouse(int button, int state, int x, int y);
  static void keyboard(unsigned char c, int x, int y);

private:
  vec2 window_size;
  Field * field;

  std::vector<Tile*> way;

  Game( int* argc, char ** argv, vec2 size);
  Game( const Game&);
  ~Game();
  Game operator= (const Game&);
  void drawGame();
  void mouseGame(int button, int state, int x, int y);
  void keyGame(unsigned char c, int x, int y);

  static Game* game;
};

int main( int argc, char ** argv);

#endif
