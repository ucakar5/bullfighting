#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <mouse.h>
#include <cmath>
#include <vector>
#include <array>
#include <iterator>

#include "keyboardAll.cpp"
#include "Game.h"
#include "Scenery.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "Background.cpp"
#include "Ground.cpp"
#include "Bullet.cpp"
#include "Wall.cpp"
#include "Arena.cpp"
#include "Door.cpp"


using namespace std;


int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *wind = SDL_CreateWindow("BULLFIGHTERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!wind) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED ;//| SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *r = SDL_CreateRenderer(wind, -1, render_flags);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    if (!r) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }

    Scenery scenery(r);
    vector<SDL_Texture*> text;
    vector<SDL_Rect> rect;
    scenery.textDeclaration(r, text);
    scenery.rectDeclaration(r, rect, text);

    SDL_Texture *img = IMG_LoadTexture(r, "media/player.png");
    SDL_Texture *imgs = IMG_LoadTexture(r, "media/playerShoot.png");
    
    char nickname[14] = "";
    
    int score = 0;
    int i=0, t=1, ir=0, rt=0, et=0;
    int textOpacity=0, itext=0;
    int loseOpacity=0, ilose=0;
    int ishoot=0, pressed = 0;
    
    
    bool running = true;
    bool shooting=0;
    bool l = 0, ri = 0, u = 0, d = 0;
    bool space=0, enter=0;
    bool entered=1, readFinish=0, isSaved=0, updatedText=1;
    
    Player player1(r);
    Background background(r);
    Ground ground(r);
    Wall wall1(r);
    Arena thearena(r);
    Arena uparena(r);
    Door door(r);

    vector <Enemy> enemyList;
    vector <Bullet> bulletList;
    vector <string> fileContent={"a", "a", "a", "a", "a", "a", "a", "a", "a", "a"};
    vector<array<int, 4>> replayMoves;

    Mouse m;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                if (scenery.scene!=0 && scenery.state!=4 && scenery.state!=5 && scenery.state!=6) {
                    scenery.save(nickname, score, player1, thearena, enemyList, bulletList);
                    if (scenery.scene==2 || scenery.scene==4 || scenery.scene==6) scenery.replaySave(replayMoves);
                }
                break;
            case SDL_TEXTINPUT:
                if (entered==0){
                    if (strlen(nickname)<12) strcat(nickname, event.text.text);
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_BACKSPACE: 
                    if (entered==0){
                        int len = strlen(nickname);
                        if (len > 0) nickname[len - 1] = '\0';
                    }
                break;
                }
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    running=false;
                    if (scenery.scene!=0 && scenery.state!=4 && scenery.state!=5 && scenery.state!=6) {
                        scenery.save(nickname, score, player1, thearena, enemyList, bulletList);
                        if (scenery.scene==2 || scenery.scene==4 || scenery.scene==6) scenery.replaySave(replayMoves);
                    }
                break;
                case SDL_SCANCODE_RETURN:
                    pressed=1;
                break;
                case SDL_SCANCODE_SPACE:
                    space=1;
                break;
                case SDL_SCANCODE_A:
                    l=1;
                break;
                case SDL_SCANCODE_D:
                    ri=1;
                break;
                case SDL_SCANCODE_W:
                    u=1;
                break;
                case SDL_SCANCODE_S:
                    d=1;
                break;
                case SDL_SCANCODE_N: 
                    //scenery.saveScore(score, nickname);
                    //player1.health=0;
                    //enemyList.push_back(Enemy(r, 0));
                    //player1.health-=5;
                    std::cout << "enemyNum: " << scenery.enemyNum << std::endl;
                    std::cout << "status: " << scenery.status << std::endl;
                    //std::cout << "bulletSize: " << bulletList.size() << std::endl;
                break;
                case SDL_SCANCODE_R: 
                    if (scenery.scene==2 || scenery.scene==4 || scenery.scene==6){
                        scenery.save(nickname, score, player1, thearena, enemyList, bulletList);
                        scenery.state=4;
                    }
                break;
                case SDL_SCANCODE_0:
                    if (player1.key==0)
                        player1.key=1;
                    else if (player1.key==1)
                        player1.key=0;
                break;

                default:
                break;
                }

                break;

            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    enter=0;
                break;
                case SDL_SCANCODE_SPACE:
                    space=0;
                break;
                case SDL_SCANCODE_A:
                    l=0;
                break;
                case SDL_SCANCODE_D:
                    ri=0;
                break;
                case SDL_SCANCODE_W:
                    u=0;
                break;
                case SDL_SCANCODE_S:
                    d=0;
                break;

                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        
        SDL_Point mousePoint {m.x, m.y};
        bool updateButtons = false;
        if (m.update(updateButtons)) {
            if (updateButtons) {
                if (m.left == true){
                    if (scenery.scene!=0 && scenery.scene%2==0 && scenery.state==2) scenery.shotClick(r, player1, bulletList, m, shooting, ishoot, l, ri);
                    else if (scenery.scene==0) scenery.buttonClick(mousePoint, rect, pressed, running);
                }
                if (m.right == true){}
            }
        }

    //!GAME
        if (scenery.scene==0){
            if (scenery.state==0 || scenery.state==5){ //!menu
                if (scenery.state==5 && pressed==0) scenery.transitionAnimation(t);
                if (pressed!=0){
                    t++;
                    scenery.x-=16;
                    if (t==68){
                        t=1;
                        if (pressed==1) scenery.state=2, pressed=0;
                        else if (pressed==2) scenery.state=3, pressed=0;
                    }
                }
            }
            else if (scenery.state==1){ //!name
                if (pressed==0) scenery.transitionAnimation(t);
                else if (pressed!=0){
                    t++;
                    scenery.x-=16;
                    if (t==68){
                        if (pressed==1){
                            scenery.scene=1, scenery.state=1;
                            scenery.sceneChange(scenery.scene, ground, background, wall1, player1, thearena, uparena, door);
                            t=1, entered=1, pressed=0;
                            remove("replay.txt");
                        }
                        else if (pressed==2) scenery.state=5, pressed=0, t=1;
                    }
                }
            }
            else if (scenery.state==2){ //!saved or new
                if (pressed==0) scenery.transitionAnimation(t);
                else if (pressed!=0){
                    t++;
                    scenery.x-=16;
                    if (t==68){
                        if (pressed==1) scenery.state=1, entered=0, pressed=0, t=1;
                        else if (pressed==2){
                            scenery.savedGame(r, t, pressed, nickname, score, player1, thearena, enemyList, bulletList, ground, background, wall1, uparena, door);
                            scenery.replayLoad(replayMoves);
                            isSaved=1, updatedText=0;
                        }
                        else if (pressed==3) scenery.state=5, pressed=0, t=1;
                    }
                }
            }
            else if (scenery.state==3){ //!leaderboard
                if (readFinish!=1) scenery.readScore(readFinish, fileContent);
                if (pressed==0) scenery.transitionAnimation(t);
                else if (pressed==2){
                    t++;
                    scenery.x-=16;
                    if (t==68) scenery.state=5, pressed=0, t=1;
                }
            }
            else if  (scenery.state==4) { //!ending
                if (scenery.transitionAnimation(t)){}
                else scenery.state=6;
            }
            else if  (scenery.state==6) { //!ending
                if (pressed==2){
                    t++;
                    scenery.x-=16;
                    if (t==68){
                        scenery.state=5, pressed=0, t=1, score=0;
                        remove("save.txt");
                    }
                }
            }
        }
        else if (scenery.scene%2==1){
            if (scenery.state==1){
                if (scenery.transitionAnimation(t)){}
                else {
                    if (player1.x!=30){
                        i++;
                        if(i%2==0){
                            ri=1;
                            player1.Move(ri, SPEED/2);
                        }
                        player1.frameUpdate(player1, l, ri, u, d);
                    }
                    if (player1.x==30){
                        i=0, ri=0;
                        player1.frameUpdate(player1, l, ri, u, d);
                        scenery.state=2;
                    }
                }
            }
            else if (scenery.state==2){
                if (isSaved==1) scenery.transitionAnimation(t);
                player1.Move(l, ri, u, d, SPEED/2);
                player1.frameUpdate(player1, l, ri, u, d);
                player1.Borders(player1, scenery.scene);
                player1.collisionMove(player1, thearena, SPEED/2);
                player1.collisionMove(player1, uparena, SPEED/2);
                thearena.radiusCalc(player1);
                scenery.textUpdating2(r, rect, text, itext, textOpacity, i, player1, door, space);
            }
            else if (scenery.state==3){
                t++;
                scenery.x-=16;
                if (t==68){
                    scenery.textUpdates(2, r, rect, text);
                    textOpacity=0, itext=0;
                    scenery.state=1, scenery.scene++;
                    scenery.sceneChange(scenery.scene, ground, background, wall1, player1, thearena, uparena, door);
                    t=1;
                }
            }
        }
        else if (scenery.scene%2==0){
            if (scenery.state==1){
                if (scenery.transitionAnimation(t)){
                    if (isSaved==1){
                        scenery.textUpdates(2, r, rect, text);
                        isSaved=0;
                    }
                }
                else {
                    if (itext<2) scenery.textAnimation(itext, textOpacity, i);
                    if (player1.x!=40){
                        ri=1;
                        player1.Move(ri, SPEED/2);
                        player1.frameUpdate(player1, l, ri, u, d);
                    }
                    if (player1.x==40){
                        i=0, ri=0;
                        player1.frameUpdate(player1, l, ri, u, d);
                        scenery.state=2;
                        
                    }
                }
            }
            else if (scenery.state==2){
                if (isSaved==1){
                    scenery.transitionAnimation(t);
                    textOpacity=0;
                }
                scenery.textUpdating(r, rect, text, itext, textOpacity, i, player1, door, space);
                player1.Move(l, ri, u, d, SPEED);
                player1.Borders(player1, scenery.scene);
                scenery.bullets(bulletList, enemyList, score);
                scenery.enemies(enemyList, player1);
                player1.damageAnimation();
                scenery.enemyHandling(et, r, enemyList, score, player1);
                if(enemyList.size()==0)cout << score << endl;
                player1.frameUpdate(player1, l, ri, u, d);
                player1.shootingAnimation(ishoot, shooting);
                scenery.replayMoves(replayMoves, l, ri, u, d);
                if (player1.health<=0) scenery.state=7;
            }
            else if (scenery.state==3){
                if (player1.y!=342){
                    u=0, d=1;
                    player1.Move(u, d, SPEED/2);
                    player1.frameUpdate(player1, l, ri, u, d);
                }
                if (player1.y == 342 && i==0){
                    i=1, u=0, d=0, t=0;
                    player1.frameUpdate(player1, l, ri, u, d);
                }
                if (player1.y == 342 && i==1){
                    if (player1.x!=1160){
                        ri=1;
                        player1.Move(ri, SPEED);
                        player1.frameUpdate(player1, l, ri, u, d);
                    }
                    else if (player1.x==1160){
                        t++;
                        scenery.x-=16;
                        if (t==68){
                            score=score+((100-player1.health)*10);
                            if (scenery.scene==6){
                                scenery.scene=0, scenery.state=4;
                                remove("save.txt");
                                remove("replay.txt");
                                score=18000-score;
                                if (score<1410) score=1410;
                                scenery.endText(score, nickname, rect, text, r);
                                scenery.saveScore(score, nickname);
                            }
                            else scenery.state=1, scenery.scene++;
                            scenery.status=1, scenery.enemyNum=0;
                            scenery.sceneChange(scenery.scene, ground, background, wall1, player1, thearena, uparena, door);
                            textOpacity=0, isSaved=0, t=1, et=0;
                            scenery.textUpdates(4, r, rect, text);
                            scenery.bulletReset(bulletList);
                            replayMoves.clear();
                            replayMoves.shrink_to_fit();
                            player1.checkpointScore = score;
                            itext=0, i=0, player1.key=0, door.frame=0;
                        }
                    } 
                }
           }
            else if (scenery.state==4){
                t++;
                scenery.x-=16;
                if (t==68){
                    scenery.state=5;
                    t=1, pressed=0, textOpacity=0;
                    scenery.sceneChange(scenery.scene, ground, background, wall1, player1, thearena, uparena, door);
                    scenery.enemyReset(enemyList);
                    scenery.bulletReset(bulletList);
                }
            }
            else if (scenery.state==5){
                if (scenery.transitionAnimation(t)){}
                else if (ir < replayMoves.size()) scenery.replayExecution(player1, replayMoves, ir); 
                else scenery.state=6;
            }
            else if (scenery.state==6){
                t++;
                scenery.x-=16;
                if (t==68){
                    t=1, isSaved=1, ir=0;
                    scenery.savedGame(r, t, pressed, nickname, score, player1, thearena, enemyList, bulletList, ground, background, wall1, uparena, door);
                }
            }
            else if (scenery.state==7){
                if(ilose!=2) scenery.textAnimation(ilose, loseOpacity, i);
                else {
                    t++;
                    scenery.x-=16;
                    if (t==68){
                        scenery.enemyReset(enemyList);
                        scenery.bulletReset(bulletList);
                        scenery.status=1, scenery.enemyNum=0, scenery.state=1, score=player1.checkpointScore;
                        et=0, t=1, loseOpacity=0, ilose=0, player1.shot=0;
                        scenery.textUpdates(3, r, rect, text);
                        scenery.sceneChange(scenery.scene, ground, background, wall1, player1, thearena, uparena, door);
                    }
                }
            }
        }
        
        // UPDATE HERE
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        
        // DRAW HERE
        if (scenery.scene==0) scenery.renderMenu(r, player1, rect, text, mousePoint, ground, fileContent, nickname);
        else if (scenery.scene%2==0 && scenery.scene!=0) scenery.renderArena(r, player1, background, ground, wall1, enemyList, bulletList, door, rect, text, textOpacity, loseOpacity, shooting);
        else if (scenery.scene%2==1 && scenery.scene!=7) scenery.renderWay(r, player1, ground, thearena, uparena, door, rect, text, textOpacity, shooting);
        
        // PRESENT RENDERED IMAGE
        SDL_RenderPresent(r);
        SDL_Delay(1000/FRAMERATE); 
    }

    SDL_DestroyTexture(text.at(0));
    SDL_DestroyTexture(img);

    TTF_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
}