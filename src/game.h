#ifndef _GAME_
#define _GAME_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <functional>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "constants.h"
#include "util.h"
#include "field.h"
#include "player.h"
#include "coin.h"
#include "bush.h"

#include "gui.h"

/**
 * Game Class for gameing
 *
 */

class Game
{
public:
    static Game* getInstance();
    static void  init(int* argc, char** argv, vec2 size);

    void draw();
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char c, int x, int y);
    void mousemotion(int x, int y);
    void passivmouse(int x, int y);
    void reshape(int width, int height);

private:
    glm::vec2 window_size;
    glm::vec2 display_position;
    glm::vec2 click_position;
    float     zoom;

    glm::mat4 map_mat;
    glm::mat4 gui_mat;

    Field*  field;
    Player* player;
    GUI*    gui;

    Tile* hover;

    Game(int* argc, char** argv, glm::vec2 size);
    Game(const Game&);
    ~Game();
    Game operator=(const Game&);

    bool move_player_to(Tile* tile);

    vec2 getFieldPosition(int x, int y);

    static Game* game;
};

inline void drawCallback()
{
    Game::getInstance()->draw();
};
inline void mouseCallback(int button, int state, int x, int y)
{
    Game::getInstance()->mouse(button, state, x, y);
};
inline void mousemotionCallback(int x, int y)
{
    Game::getInstance()->mousemotion(x, y);
};
inline void passivmotionCallback(int x, int y)
{
    Game::getInstance()->passivmouse(x, y);
};
inline void keyboardCallback(unsigned char c, int x, int y)
{
    Game::getInstance()->keyboard(c, x, y);
};
inline void reshapeCallback(int width, int height)
{
    Game::getInstance()->reshape(width, height);
};

int main(int argc, char** argv);

#endif
