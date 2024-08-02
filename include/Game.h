#define WIDTH 1080
#define HEIGHT 610
#define SPEED 2
#define SPRITE_FRAMES 24
#define SPRITE_SIZE 48
#define FRAMERATE 144
#define DISTANCE 50

class Player {
    public:
    float x, y;
    float cx, cy;
    float prevx, prevy;

    bool phase;
    bool key;
    
    SDL_Texture *img;
    SDL_Texture *imgs;
    SDL_Texture *sh;
    SDL_Texture *red;
    SDL_FRect hitbox;

    int health;
    int shot;
    int checkpointScore;

    int i;
    int sprite_dir;
    int sprite_frame;
    
    Player(SDL_Renderer *r);
    void Draw(SDL_Renderer *r, int sprite_dir, int sprite_frame, bool shooting, int scene);
    void Move(bool l, bool r, bool u, bool d, int speed);
    void Move(bool u, bool d, int speed);
    void Move(bool r, int speed);
    void Borders(class Player &, int scene);
    void enemyCollision (class Enemy &enemy1, class Player &player1, int target);
    int checkCollision( SDL_FRect a, SDL_FRect b );
    void frameUpdate(class Player &, bool l, bool ri, bool u, bool d);
    void collisionMove(class Player &, class Enemy &);
    void collisionMove(class Player &, class Arena &, int speed);
    void prevCoordinates(class Player &);
    void shootingAnimation(int &ishoot, bool &shooting);
    void damageAnimation();
};


class Enemy {
    public:
    float x, y;
    float cx, cy;
    float prevx, prevy;

    int health;
    int shot;
    int cooldown;

    SDL_Texture *imge;
    SDL_Texture *sh;
    SDL_Texture *red;
    
    SDL_FRect hitbox;
    SDL_FRect dhitbox;

    int i;
    int sprite_dir_enemy;
    int sprite_frame_enemy;

    int target;
    
    Enemy(SDL_Renderer *r, int side, int scene);
    void Draw(SDL_Renderer *r, int sprite_dir, int sprite_frame, int scene);
    void enemyMovement(class Enemy &, class Player &);
    void frameUpdate(class Enemy &, class Player &);
    bool checkHitbox(SDL_FRect a, SDL_FRect b);
    void prevCoordinates(class Enemy &enemy1);
    void sortEnemy(std::vector<Enemy>& enemyVector);
    void destroyEnemy();
};

class Background {
    public:
    int x, y;
    SDL_Texture *bg1;
    SDL_Texture *bg2;
    SDL_Texture *bg3;
    SDL_Texture *current;
    
    Background(SDL_Renderer *r);
    void Draw(SDL_Renderer *r);
    
};

class Ground {
    public:
    int x, y;
    SDL_Texture *gr1;
    SDL_Texture *gr2;
    SDL_Texture *gr3;

    SDL_Texture *grf1;
    SDL_Texture *grf2;
    SDL_Texture *grf3;

    SDL_Texture *current;
    
    Ground(SDL_Renderer *r);
    void Draw(SDL_Renderer *r);
    
};


class Wall {
    public:
    int x, y;
    SDL_Texture *wall;
    SDL_Texture *wall2;
    SDL_Texture *walld;
    SDL_Texture *wall2d;
    SDL_Texture *walln;
    SDL_Texture *wall2n;
    SDL_Texture *current;
    SDL_Texture *current2;
    
    
    Wall(SDL_Renderer *r);
    void Draw(SDL_Renderer *r);
    void Draw2(SDL_Renderer *r);
    
};


class Bullet {
    public:
    float x, y;
    float angle;
    bool destroyed;
    SDL_Texture *bullet;
    SDL_Texture *red;
    SDL_FRect hitbox;
    
    Bullet *BulletPoint;

    SDL_FPoint point;
    
    Bullet(SDL_Renderer *r, float x, float y, float angle);
    void Draw(SDL_Renderer *r);
    bool checkHitbox(SDL_FRect a, SDL_FRect b);
    void sortBullet(std::vector<Bullet>& bulletVector);
    void destroyBullet();
    bool Borders();

};




class Door {
    public:
    int x, y;
    int frame;
    int type;
    int opacity;
    
    SDL_Texture *doors;
    SDL_Texture *doord;
    SDL_Texture *doorn;

    SDL_Texture *red;
    SDL_Texture *current;

    SDL_FRect hitbox;
    
    Door(SDL_Renderer *r);
    void Draw(SDL_Renderer *r, int scene);
    bool checkHitbox(SDL_FRect pHitbox, SDL_FRect eHitbox);
    
    
};

class Arena {
    public:
    int x, y;
    int cx, cy;
    
    float radius;
    int opacity;
    
    SDL_Texture *arena1;
    SDL_Texture *arena2;
    SDL_Texture *arena3;
    SDL_Texture *red;
    SDL_Texture *current;

    SDL_FRect hitbox;
    
    Arena(SDL_Renderer *r);
    void Draw(SDL_Renderer *r);
    void updateArena(int scene, Door &door);
    void radiusCalc(Player &player);
    
};

class Scenery {
    public:
    int x, y;
    int scene;
    int state;
    int status;
    int enemyNum;
    SDL_Texture *black;
    
    Scenery(SDL_Renderer *r);
    int sceneChange(int scene, Ground &ground, Background &background, Wall &wall, Player &player, Arena &arena, Arena &arena2, Door &door);
    void textAnimation (int &itext, int &textOpacity, int &i);
    void transition(SDL_Renderer *r);
    void save(char nickname[], int score, Player &player, Arena &arena, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList);
    int savedGame(SDL_Renderer *r, int &t, int &pressed, char nickname[], int &score, Player &player, Arena &arena, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList, Ground &ground, Background &background, Wall &wall, Arena &arena2, Door &door);
    bool transitionAnimation(int &t);
    void makeText(SDL_Renderer *r, SDL_Texture *textTexture, TTF_Font *Sans2, int &itext);
    void textDeclaration(SDL_Renderer *r, std::vector<SDL_Texture*> &text);
    void rectDeclaration(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text);
    void textUpdates(int num, SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text);
    void readScore(bool &readFinish, std::vector <std::string> &fileContent);
    void replayMoves(std::vector<std::array<int, 4>> &replayMoves, int l, int ri, int u, int d);
    void replaySave(std::vector<std::array<int, 4>> &replayMoves);
    void replayLoad(std::vector<std::array<int, 4>> &replayMoves);
    void replayExecution(Player &player, std::vector<std::array<int, 4>> &replayMoves, int &ir);
    void textUpdating(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int &itext, int &textOpacity, int &i, Player &player, Door &door, bool space);
    void textUpdating2(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int &itext, int &textOpacity, int &i, Player &player, Door &door, bool space);
    void saveScore(int score, char nickname[]);
    void endText(int score, char nickname[], std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, SDL_Renderer *r);
    void enemyHandling(int &et, SDL_Renderer *r, std::vector <Enemy> &enemyList, int &score, Player &player);
    void bullets(std::vector <Bullet> &bulletList, std::vector <Enemy> &enemyList, int &score);
    void enemies(std::vector <Enemy> &enemyList, Player &player);
    void renderWay(SDL_Renderer *r, Player &player, Ground &ground, Arena &thearena, Arena &uparena, Door &door, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int textOpacity, bool shooting);
    void renderArena(SDL_Renderer *r, Player &player, Background &background, Ground &ground, Wall &wall1, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList, Door &door, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int textOpacity, int loseOpacity, bool shooting);
    void renderMenu(SDL_Renderer *r, Player &player, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, SDL_Point mousePoint, Ground &ground, std::vector <std::string> &fileContent, char nickname[]);
    void shotClick(SDL_Renderer *r, Player &player, std::vector <Bullet> &bulletList, Mouse &m, bool &shooting, int &ishoot, bool l, bool ri);
    void buttonClick(SDL_Point mousePoint, std::vector<SDL_Rect> &rect, int &pressed, bool &running);
    void enemyReset(std::vector <Enemy> &enemyList);
    void bulletReset(std::vector <Bullet> &bulletList);

};
