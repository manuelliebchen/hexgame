#include "game.h"

/**
 * Singelton Instance.
 */
Game* Game::game = nullptr;

/**
 * Initilice singelton Instance.
 */
void Game::init(int* argc, char** argv, glm::vec2 size)
{
    game = new Game(argc, argv, size);
    glutMainLoop();
}

/**
 * @return Instance of game
 */
Game* Game::getInstance()
{
    if (!Game::game)
    {
        Game::game = new Game(nullptr, nullptr, glm::vec2(240, 240));
    }
    return Game::game;
}

/**
 * Constructs Game.
 */
Game::Game(int* argc, char** argv, glm::vec2 size) : window_size(size)
{
    if ((*argc) >= 2)
    {
        if (argv[1] == std::string("flat"))
        {
            field = new Field(100 * three_sqrt_half, 100);
        }
    }
    else
    {
        field = new Field(100 * three_sqrt_half, 100, 50, 30);
    }

    glm::uvec2 field_size = field->getSize();

    gui = new GUI();
    gui->addButton(new Button(
        std::basic_string<unsigned char>((unsigned char*)("Forestify")),
        std::bind(&Field::forestify, field, 2), glm::vec2(20, 20),
        glm::vec2(80, 40)));
    //    gui->addButton(new Button(
    //        std::basic_string<unsigned char>((unsigned char*)("Smothen")),
    //        std::bind(&Field::smoothen, field, 2), glm::vec2(20, 80),
    //        glm::vec2(80, 40)));

    display_position = glm::vec2(-0.5f * field_size.x * three_sqrt_half,
                                 -0.5f * field_size.y * 0.75f);
    zoom             = 50;
    hover            = nullptr;

    // Placing Player
    Tile* tile;
    do
    {
        tile = field->tile_at(rand() % field_size.x, rand() % field_size.y);
    } while (!tile->isWalkable());
    tile->place(new Player(tile));
    //    player = dynamic_cast<Player*>(tile->getFigure());
    player = nullptr;

    // Calculate Projektion Matrix
    map_mat =
        glm::ortho((float)(-0.5 * window_size.x), (float)(0.5 * window_size.x),
                   (float)(-0.5 * window_size.y), (float)(0.5 * window_size.y),
                   1.0f, -1.0f);
    map_mat = glm::scale(map_mat, glm::vec3(zoom, zoom, 1));
    gui_mat = glm::ortho(0.0f, (float)window_size.x, (float)window_size.y, 0.0f,
                         1.0f, -1.0f);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |
                        GLUT_MULTISAMPLE);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.4);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_SMOOTH);

    int   glut_argc    = 1;
    char* glut_argv[1] = {(char*)"hexgame"};
    glutInit(&glut_argc, glut_argv);

    glutInitWindowSize(window_size.x, window_size.y);
    glutCreateWindow("The Hex Game");

    glClearColor(0.078f, 0.23f, 0.477f, 1.0f);

    glutDisplayFunc(&drawCallback);
    glutKeyboardFunc(&keyboardCallback);
    glutMouseFunc(&mouseCallback);
    glutMotionFunc(&mousemotionCallback);
    glutPassiveMotionFunc(&passivmotionCallback);
    glutReshapeFunc(&reshapeCallback);
}

/**
 * Delets game
 */
Game::~Game()
{
    delete field;
}

/**
 * Redraw Game.
 */
void Game::draw()
{
    // std::clock_t c_start = std::clock();
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadMatrixf(glm::value_ptr(map_mat));
    field->draw(display_position);

    if (player)
    {
        glColor4ub(0, 192, 255, 128);
        field->mark(
            display_position,
            field->findSurounding(player->standing_on, TURN_WALKING_DISTANCE));
        if (player->standing_on)
        {
            std::vector<Tile*> path =
                field->findPath(player->standing_on, hover);
            glColor4ub(0, 0, 255, 128);
            field->mark(display_position, path);
        }
    }

    glLoadMatrixf(glm::value_ptr(gui_mat));
    gui->draw();

    glutSwapBuffers();
    // std::clock_t c_end = std::clock();
    // std::cout << "FPS: " << CLOCKS_PER_SEC / (float)(c_end-c_start) << std::endl;
}

/**
 * Handel Keyboard inputs.
 */
void Game::keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
        case 27:
            exit(0);
            break;
            //        case 's':
            //            field->smoothen(1);
            //            glutPostRedisplay();
            //            break;
            //        case 'f':
            //            field->forestify(3);
            //            glutPostRedisplay();
            //            break;s
    }
    std::map<unsigned char, unsigned int> direction_key;
    direction_key['s'] = 0;
    direction_key['f'] = 1;
    direction_key['w'] = 2;
    direction_key['a'] = 3;
    direction_key['z'] = 4;
    direction_key['x'] = 5;
    if (player)
    {
        for (auto it = direction_key.begin(); it != direction_key.end(); ++it)
        {
            if (it->first == c)
            {
                if (Tile* nighbor =
                        field->getNeighboring(player->standing_on, it->second))
                {

                    glm::vec2 old_pos =
                        field->getDrawingPosition(player->standing_on);
                    move_player_to(nighbor);
                    display_position += old_pos - field->getDrawingPosition(
                                                      player->standing_on);
                }
            }
        }
    }
    glutPostRedisplay();
}

/**
 * Handels Mouse Inputs
 */
void Game::mouse(int button, int state, int x, int y)
{

    trag = false;
    if (gui->in_region(glm::vec2(x, y)))
    {
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
        {
            gui->click(glm::vec2(x, y));
        }
    }
    else
    {
        if (state == GLUT_UP)
        {
            if (button == GLUT_LEFT_BUTTON)
            {
                //                display_position +=
                //                    (glm::vec2)(glm::vec2(x, -y) - click_position) *
                //                    (float)(1 / zoom);
            }
            else if (button == 3)
            {
                if (state == GLUT_DOWN)
                    return;
                map_mat = glm::scale(map_mat, glm::vec3(1.1f, 1.1f, 1));
                zoom *= 1.1;
            }
            else if (button == 4)
            {
                if (state == GLUT_DOWN)
                    return;
                map_mat = glm::scale(map_mat, glm::vec3(1 / 1.1f, 1 / 1.1f, 1));
                zoom /= 1.1;
            }
        }
        else if (state == GLUT_DOWN)
        {

            click_position           = glm::vec2(x, -y);
            glm::vec2 mouse_position = getFieldPosition(x, y);
            Tile*     tile           = field->estimatTile(mouse_position);
            if (tile)
            {
                if (button == GLUT_MIDDLE_BUTTON)
                {
                    if (!tile->getFigure())
                    {
                        tile->plant();
                    }
                    else if (dynamic_cast<Bush*>(tile->getFigure()))
                    {
                        tile->clear();
                        tile->place(new Coin);
                    }
                    else if (dynamic_cast<Coin*>(tile->getFigure()))
                    {
                        tile->clear();
                        player = new Player(tile);
                        tile->place(player);
                    }
                    else
                    {
                        if (tile->getFigure() == player)
                        {
                            player = nullptr;
                        }
                        tile->clear();
                    }
                }
                else if (button == GLUT_RIGHT_BUTTON)
                {
                    if (player)
                    {
                        if (tile == player->standing_on)
                        {
                            player = nullptr;
                        }
                        else
                        {
                            move_player_to(tile);
                        }
                    }
                    else if (dynamic_cast<Player*>(tile->getFigure()))
                    {
                        player = dynamic_cast<Player*>(tile->getFigure());
                    }
                }
            }
            if (button == GLUT_LEFT_BUTTON)
            {
                trag = true;
            }
        }
    }
    glutPostRedisplay();
}

/**
 * Handels a move request.
 */
bool Game::move_player_to(Tile* tile)
{
    std::vector<Tile*> surrounding =
        field->findSurounding(player->standing_on, TURN_WALKING_DISTANCE);
    std::vector<Tile*> path = field->findPath(player->standing_on, tile);
    if (std::find(surrounding.begin(), surrounding.end(), tile) ==
        surrounding.end())
    {
        return false;
    }
    player->move(tile);
    return true;
}

void Game::reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    window_size = glm::vec2(width, height);
    map_mat =
        glm::ortho((float)(-0.5 * window_size.x), (float)(0.5 * window_size.x),
                   (float)(-0.5 * window_size.y), (float)(0.5 * window_size.y),
                   1.0f, -1.0f);
    map_mat = glm::scale(map_mat, glm::vec3(zoom, zoom, 1));

    gui_mat = glm::ortho(0.0f, (float)window_size.x, (float)window_size.y, 0.0f,
                         1.0f, -1.0f);
}

void Game::mousemotion(int x, int y)
{
    if (trag)
    {
        display_position +=
            (glm::vec2)(glm::vec2(x, -y) - click_position) * (float)(1 / zoom);
        click_position = glm::vec2(x, -y);
        glutPostRedisplay();
    }
}

void Game::passivmouse(int x, int y)
{
    if (!gui->in_region(glm::vec2(x, y)))
    {
        glm::vec2 mouse_position = getFieldPosition(x, y);
        Tile*     tile           = field->estimatTile(mouse_position);
        if (tile)
        {
            hover = tile;
            glutPostRedisplay();
        }
    }
}

glm::vec2 Game::getFieldPosition(int x, int y)
{

    glm::vec2 mouse_position = glm::vec2(x, y);
    mouse_position -= glm::vec2(window_size.x * 0.5f, window_size.y * 0.5f);
    mouse_position.y = -mouse_position.y;
    mouse_position *= 1 / (float)zoom;
    mouse_position -= display_position;
    return mouse_position;
}

int main(int argc, char** argv)
{
    Game::init(&argc, argv, glm::vec2(800, 600));
    return 0;
}
