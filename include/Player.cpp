using namespace std;

Player::Player(SDL_Renderer *r){
    x=-70;
    y=20;
    
    key=0;
    phase=0;
    health=100;
    shot=0;
    checkpointScore=0;

    img = IMG_LoadTexture (r, "media/player.png");
    imgs = IMG_LoadTexture (r, "media/playerShoot.png");
    sh = IMG_LoadTexture (r, "media/shadow.png");
    red = IMG_LoadTexture(r, "media/red.png");
    
    hitbox.x = x + 4;
    hitbox.y = y + 52;
    hitbox.w = 72;
    hitbox.h = 14;
    
    cx = x + 24;
    cy = y + 24;
    
    i = 0;
    sprite_dir = 96;
    sprite_frame = 0;


}

void Player::Draw(SDL_Renderer *r, int sprite_dir, int sprite_frame, bool shooting, int scene){
    SDL_Rect rect1;
    rect1.x = sprite_frame;
    rect1.y = sprite_dir;
    rect1.w = 48;
    rect1.h = 48;
    
    SDL_Rect rect2;
    rect2.x = x;
    rect2.y = y;
    if (phase==0){
        rect2.w = 48;
        rect2.h = 48;
    }
    else if (phase==1){
        rect2.w = 80;
        rect2.h = 80;
    }

    int dir;
    if (sprite_dir == 48) dir = 8;
    else dir = -6;

    int w, h;
    SDL_QueryTexture(sh, NULL, NULL, &w, &h);
    SDL_Rect rect3;
    rect3.x = x+dir*0.6;
    rect3.y = y+55*0.6;
    if (phase==0){
        rect3.x = x+dir*0.6;
        rect3.y = y+55*0.6;
        rect3.w = w/26;
        rect3.h = h/26;
        
    }
    else if (phase==1){
        rect3.x = x+dir;
        rect3.y = y+55;
        rect3.w = w/16;
        rect3.h = h/16;
    }

    if (shot!=0){
        SDL_SetTextureColorMod(img, 220, 69, 91);
        SDL_SetTextureAlphaMod(img, 192);
        SDL_SetTextureColorMod(imgs, 220, 69, 91);
        SDL_SetTextureAlphaMod(imgs, 192);
    }
    else {
        SDL_SetTextureColorMod(img, 255, 255, 255);
        SDL_SetTextureAlphaMod(img, 255);
        SDL_SetTextureColorMod(imgs, 255, 255, 255);
        SDL_SetTextureAlphaMod(imgs, 255);
    }

    SDL_RenderCopy(r, sh, NULL, &rect3);
    if (shooting==1)
        SDL_RenderCopy(r, imgs, &rect1, &rect2);
    else
        SDL_RenderCopy(r, img, &rect1, &rect2);
    //SDL_RenderCopyF(r, red, NULL, &hitbox);

    if (scene==2 || scene==4 || scene==6){
        SDL_Rect rect4;
        rect4.x = x+4;
        rect4.y = y-2;
        rect4.h = 6;


        rect4.w = health/1.43;
        if (rect4.w < 0) rect4.w=0;
        SDL_SetRenderDrawColor(r, 4, 149, 255, 255);
        SDL_RenderFillRect(r, &rect4);
        rect4.w = 70;
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderDrawRect(r, &rect4);
    }
    

}

void Player::Move (bool l, bool r, bool u, bool d, int speed){
    if (l == 1) x-=speed;
    if (r == 1) x+=speed;
    if (u == 1){ y-=speed;}
    if (d == 1){ y+=speed;}

    if (phase==1){
        hitbox.x = x + 4;
        hitbox.y = y + 52;
        hitbox.w = 72;
        hitbox.h = 14;
        cx = x + 40;
        cy = y + 40;
    }
    else if (phase==0){
        hitbox.x = x + 3;
        hitbox.y = y + 31;
        hitbox.w = 43;
        hitbox.h = 8;
        if (sprite_dir==96)
            cx = x + 20;
        else if (sprite_dir==48)
            cx = x + 26;
        cy = y + 24;
    }
}

void Player::Move (bool r, int speed){  
    if (r == 1) x+=speed;

    if (phase==1){
        hitbox.x = x + 4;
        hitbox.y = y + 52;
        hitbox.w = 72;
        hitbox.h = 14;
        cx = x + 40;
        cy = y + 40;
    }
    else if (phase==0){
        hitbox.x = x + 3;
        hitbox.y = y + 31;
        hitbox.w = 43;
        hitbox.h = 8;
        cx = x + 20;
        cy = y + 24;
    }
}

void Player::Move (bool u, bool d, int speed){
    if (u == 1){ y-=speed;}
    if (d == 1){ y+=speed;}
    
    if (phase==1){
        hitbox.y = y + 52;
        hitbox.h = 14;
        cy = y + 40;
    }
    else if (phase==0){
        hitbox.y = y + 31;
        hitbox.h = 8;
        cy = y + 24;
    }
}

void Player::damageAnimation(){
    if (shot !=0){
        shot+=1;
        if (shot == 70) shot = 0;
    }
}

void Player::frameUpdate(class Player &player1, bool l, bool ri, bool u, bool d){

            //WALKING ANIMATION
        player1.i++;
        if (player1.i <= SPRITE_FRAMES) player1.sprite_frame=0;
        if (player1.i >= SPRITE_FRAMES && player1.i <= SPRITE_FRAMES*2) player1.sprite_frame=SPRITE_SIZE;
        if (player1.i >= SPRITE_FRAMES*2 && player1.i <= SPRITE_FRAMES*3) player1.sprite_frame=SPRITE_SIZE*2;
        if (player1.i > SPRITE_FRAMES*3) player1.i=0;


        //SPRITE DIRECTION
        if (l==1 && ri==0) player1.sprite_dir = SPRITE_SIZE;
        if (l==0 && ri==1) player1.sprite_dir = SPRITE_SIZE*2;
        
        if ((l==1 && ri==1) && (u==1 || d==1)) {}
        else if ((l==1 && ri==1)||(l==0 && ri==0 && u==0 && d==0)) player1.sprite_frame=0;
        
}

void Player::collisionMove(class Player &player1, class Enemy &enemy1){
    int hbx = player1.checkCollision(player1.hitbox, enemy1.hitbox);
    if (hbx == 0){}
    else if (hbx == 1){
        player1.x += SPEED;
        player1.y += SPEED;
    }
    else if (hbx == 2){
        player1.x += SPEED;
    }
    else if (hbx == 3){
        player1.y += SPEED;
    }
    else if (hbx == 4){
        player1.x -= SPEED;
        player1.y -= SPEED;
    }
    else if (hbx == 5){
        player1.x -= SPEED;
    }
    else if (hbx == 6){
        player1.y -= SPEED;
    }
}


void Player::collisionMove(class Player &player1, class Arena &arena, int speed){
    int hbx = player1.checkCollision(player1.hitbox, arena.hitbox);
    if (hbx == 0){}
    else if (hbx == 1){
        player1.x += speed;
        player1.y += speed;
    }
    else if (hbx == 2){
        player1.x += speed;
    }
    else if (hbx == 3){
        player1.y += speed;
    }
    else if (hbx == 4){
        player1.x -= speed;
        player1.y -= speed;
    }
    else if (hbx == 5){
        player1.x -= speed;
    }
    else if (hbx == 6){
        player1.y -= speed;
    }
}


void Player::Borders(class Player &player1, int scene){
    if (scene%2==0){
        if (player1.x < 0){
            player1.x = 0;
        }
        else if (player1.x > 1000){
            player1.x = 1000;
        }
        if (player1.y < 190){
            player1.y = 190;
        }
        else if (player1.y > 540){
            player1.y = 540;
        }
    }
    else if (scene%2==1){
        if (player1.x < 0){
            player1.x = 0;
        }
        else if (player1.x > 1032){
            player1.x = 1032;
        }
        if (player1.y < -6){
            player1.y = -6;
        }
        else if (player1.y > 568){
            player1.y = 568;
        }
    }
}


void Player::enemyCollision (class Enemy &enemy1, class Player &player1, int target){
    
    if (enemy1.x - player1.x < 0 && target < DISTANCE){  
            if ((int)enemy1.hitbox.x == enemy1.hitbox.x - 0.5){
                if ((int)(enemy1.hitbox.x - 0.5) % 2 == 1){
                    enemy1.hitbox.x = enemy1.hitbox.x + 0.5;
                    enemy1.x = enemy1.x + 0.5;
                }
            
                if ((int)(enemy1.hitbox.x - 0.5) % 2 == 0){
                    enemy1.hitbox.x = enemy1.hitbox.x - 0.5;
                    enemy1.x = enemy1.x - 0.5;
                }
            }
            else if ((int)enemy1.hitbox.x % 2 == 1){
                enemy1.hitbox.x++;
                enemy1.x++;
            }
            if (enemy1.y - player1.y < 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y++;
                    enemy1.y++;
                }
            }
            else if (enemy1.y - player1.y > 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y--;
                    enemy1.y--;
                }
            }
        }
        else if (enemy1.x - player1.x > 0 && target < DISTANCE){
                if ((int)enemy1.hitbox.x == enemy1.hitbox.x - 0.5){
                    if ((int)(enemy1.hitbox.x - 0.5) % 2 == 1){
                        enemy1.hitbox.x = enemy1.hitbox.x + 0.5;
                        enemy1.x = enemy1.x + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.x - 0.5) % 2 == 0){
                        enemy1.hitbox.x = enemy1.hitbox.x - 0.5;
                        enemy1.x = enemy1.x - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.x % 2 == 1){
                    enemy1.hitbox.x--;
                    enemy1.x--;
                }

                if (enemy1.y - player1.y < 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y++;
                    enemy1.y++;
                }
            }
            else if (enemy1.y - player1.y > 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y--;
                    enemy1.y--;
                }
            }
        }
        else if (enemy1.x - player1.x == 0 && target < DISTANCE){
            if (enemy1.y - player1.y < 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y++;
                    enemy1.y++;
                }
            }
            else if (enemy1.y - player1.y > 0){
                if ((int)enemy1.hitbox.y == enemy1.hitbox.y - 0.5){
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 1){
                        enemy1.hitbox.y = enemy1.hitbox.y + 0.5;
                        enemy1.y = enemy1.y + 0.5;
                    }
                
                    if ((int)(enemy1.hitbox.y - 0.5) % 2 == 0){
                        enemy1.hitbox.y = enemy1.hitbox.y - 0.5;
                        enemy1.y = enemy1.y - 0.5;
                    }
                }
                else if ((int)enemy1.hitbox.y % 2 == 1){
                    enemy1.hitbox.y--;
                    enemy1.y--;
                }
            }

        }
        
}



int Player::checkCollision(SDL_FRect pHitbox, SDL_FRect eHitbox){  
    
    float playerUp [] = {pHitbox.x, pHitbox.y};
    float playerDown [] = {pHitbox.x + pHitbox.w, pHitbox.y + pHitbox.h};
    float enemyUp [] = {eHitbox.x, eHitbox.y};
    float enemyDown [] = {eHitbox.x + eHitbox.w, eHitbox.y + eHitbox.h};

    if (playerUp[0]==enemyDown[0] && playerUp[1]==enemyDown[1])
        return 1;
    else if (playerUp[0]==enemyDown[0] && (playerUp[1]<enemyDown[1] && playerUp[1]>enemyDown[1]-(pHitbox.h + eHitbox.h)))
        return 2;
    else if ((playerUp[0]<enemyDown[0] && playerUp[0]>enemyDown[0]-(pHitbox.w + eHitbox.w)) && playerUp[1] == enemyDown[1])
        return 3;
    else if (playerDown[0]==enemyUp[0] && playerDown[1]==enemyUp[1])
        return 4;
    else if (playerDown[0]==enemyUp[0] && (playerDown[1]>enemyUp[1] && playerDown[1]<enemyUp[1]+(pHitbox.h + eHitbox.h)))
        return 5;
    else if ((playerDown[0]>enemyUp[0] && playerDown[0]<enemyUp[0]+(pHitbox.w + eHitbox.w)) && playerDown[1] == enemyUp[1])
        return 6;
    
    return 0;
}   


void Player::prevCoordinates(class Player &player1){
    player1.prevx=player1.x;
    player1.prevy=player1.y;
};

void Player::shootingAnimation(int &ishoot, bool &shooting){
    if (ishoot>0)
        ishoot++;
    if (ishoot == FRAMERATE/2){
        shooting=0;
        ishoot=0;
    }
}