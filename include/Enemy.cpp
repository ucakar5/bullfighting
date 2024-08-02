Enemy::Enemy(SDL_Renderer *r, int side, int scene){
    //srand(time(NULL));
    if (side==0){
        x=400;
        y=300;
    }
    else if (side%2==1){
        x=WIDTH+100;
        
        y=rand()%300+250;
    }
    else if (side%2==0){
        x=-100;
        
        y=rand()%300+250;
    }
    
    if (scene==2){
        health=20;      
    }
    else if (scene==4){
        health=25;
    }
    else if (scene==6){
        health=30;
    }
    
    shot=0;
    cooldown=0;

    imge = IMG_LoadTexture (r, "media/enemy.png");
    sh = IMG_LoadTexture (r, "media/shadow.png");
    red = IMG_LoadTexture(r, "media/red.png");

    hitbox.x = x + 20;
    hitbox.y = y + 50;
    hitbox.w = 30;
    hitbox.h = 20;

    dhitbox.x = x + 32;
    dhitbox.y = y + 10;
    dhitbox.w = 16;
    dhitbox.h = 56;

    cx = x + hitbox.w/2;
    cy = y + hitbox.h/2;

    i = 0;
    sprite_dir_enemy = 48;
    sprite_frame_enemy = 0;


}

void Enemy::destroyEnemy(){
    SDL_DestroyTexture(this -> imge);
    SDL_DestroyTexture(this -> sh);
    SDL_DestroyTexture(this -> red);
}

void Enemy::Draw(SDL_Renderer *r, int sprite_dir, int sprite_frame, int scene){
    SDL_Rect rect1;
    rect1.x = sprite_frame;
    rect1.y = sprite_dir;
    rect1.w = 48;
    rect1.h = 48;

    SDL_Rect rect2;
    rect2.x = x;
    rect2.y = y;
    rect2.w = 70;
    rect2.h = 70;
    
    int dir;
    if (sprite_dir == 48) dir = 14;
    else dir = 16;

    int w, h;
    SDL_QueryTexture(sh, NULL, NULL, &w, &h);
    SDL_Rect rect3;
    rect3.x = x+dir;
    rect3.y = y+62;
    rect3.w = w/32;
    rect3.h = h/22;

    SDL_Rect rect4;
    rect4.x = x+14;
    rect4.y = y-2;
    
    rect4.h = 6;

    if (shot!=0){
        SDL_SetTextureColorMod(imge, 220, 69, 91);
        SDL_SetTextureAlphaMod(imge, 192);
    }
    else {
        SDL_SetTextureColorMod(imge, 255, 255, 255);
        SDL_SetTextureAlphaMod(imge, 255);
    }

    SDL_RenderCopy(r, sh, NULL, &rect3);

    SDL_RenderCopy(r, imge, &rect1, &rect2);
    
    if (scene==2){
        rect4.w = health*2;     
    }
    else if (scene==4){
        rect4.w = health*1.6;
    }
    else if (scene==6){
        rect4.w = health*1.33;
    }
    if (rect4.w < 0) rect4.w=0;
    SDL_SetRenderDrawColor(r, 237, 28, 36, 255);
    SDL_RenderFillRect(r, &rect4);
    rect4.w = 40;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderDrawRect(r, &rect4);



}


void Enemy::frameUpdate(class Enemy &enemy1, class Player &player1){
        int target = sqrt(abs((enemy1.x - player1.x)*(enemy1.x - player1.x) + (enemy1.y - player1.y)*(enemy1.y - player1.y)));
        enemy1.target = target;
        
        enemy1.i++;
        if (enemy1.i <= SPRITE_FRAMES) enemy1.sprite_frame_enemy=0;
        if (enemy1.i >= SPRITE_FRAMES && enemy1.i <= SPRITE_FRAMES*2) enemy1.sprite_frame_enemy=SPRITE_SIZE;
        if (enemy1.i >= SPRITE_FRAMES*2 && enemy1.i <= SPRITE_FRAMES*3) enemy1.sprite_frame_enemy=SPRITE_SIZE*2;
        if (enemy1.i > SPRITE_FRAMES*3) enemy1.i=0;
        if (target <= DISTANCE) {
            enemy1.sprite_frame_enemy = SPRITE_SIZE;
        }

        //SPRITE DIRECTION
        if (enemy1.x > player1.x) enemy1.sprite_dir_enemy = SPRITE_SIZE;
        if (enemy1.x < player1.x) enemy1.sprite_dir_enemy = SPRITE_SIZE*2;
}

void Enemy::enemyMovement(class Enemy &enemy1, class Player &player1){
    int target = sqrt(abs((enemy1.x - player1.x)*(enemy1.x - player1.x) + (enemy1.y - player1.y)*(enemy1.y - player1.y)));
    //cout << target << endl;
    int angle = atan((abs(enemy1.x - player1.x))/(abs(enemy1.y - player1.y)));
    //cout << angle << endl;
    if (enemy1.cx - player1.cx < 0 && target > DISTANCE){
            if (enemy1.cy - player1.cy < 0 && target > DISTANCE){
                if (angle < 0.65){
                    enemy1.y+=SPEED/2;
                    enemy1.hitbox.y+=SPEED/2;
                }
                else if (angle >= 0.65 && angle <= 0.85){
                    enemy1.y+=SPEED/2;
                    enemy1.hitbox.y+=SPEED/2;
                }
                else if (angle > 0.85){
                    enemy1.y+=(float)SPEED/4;
                    enemy1.hitbox.y+=(float)SPEED/4;
                }
            }
            else if (enemy1.cy - player1.cy > 0 && target > DISTANCE){
                if (angle < 0.65){ 
                    enemy1.y-=SPEED/2;
                    enemy1.hitbox.y-=SPEED/2;
                }
                else if (angle >= 0.65 && angle <= 0.85){
                    enemy1.y-=SPEED/2;
                    enemy1.hitbox.y-=SPEED/2;
                }
                else if (angle > 0.85){
                    enemy1.y-=(float)SPEED/4;
                    enemy1.hitbox.y-=(float)SPEED/4;
                }
            }
            if (angle < 0.65){
                enemy1.x+=(float)SPEED/4;
                enemy1.hitbox.x+=(float)SPEED/4;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.x+=SPEED/2;
                enemy1.hitbox.x+=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.x+=SPEED/2;
                enemy1.hitbox.x+=SPEED/2;
            }
    }
    else if (enemy1.cx - player1.cx > 0 && target > DISTANCE){
        if (enemy1.cy - player1.cy < 0 && target > DISTANCE){
            if (angle < 0.65){
                enemy1.y+=SPEED/2;
                enemy1.hitbox.y+=SPEED/2;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.y+=SPEED/2;
                enemy1.hitbox.y+=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.y+=(float)SPEED/4;
                enemy1.hitbox.y+=(float)SPEED/4;
            }
        }
        else if (enemy1.cy - player1.cy > 0 && target > DISTANCE){
            if (angle < 0.65){ 
                enemy1.y-=SPEED/2;
                enemy1.hitbox.y-=SPEED/2;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.y-=SPEED/2;
                enemy1.hitbox.y-=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.y-=(float)SPEED/4;
                enemy1.hitbox.y-=(float)SPEED/4;
            }
        } 
        if (angle < 0.65){
            enemy1.x-=(float)SPEED/4;
            enemy1.hitbox.x-=(float)SPEED/4;
        }
        else if (angle >= 0.65 && angle <= 0.85){
            enemy1.x-=SPEED/2;
            enemy1.hitbox.x-=SPEED/2;
        }
        else if (angle > 0.85){
            enemy1.x-=SPEED/2;
            enemy1.hitbox.x-=SPEED/2;
        }
    }
    else if (enemy1.cx == player1.cx && target > DISTANCE){
        if (enemy1.cy - player1.cy < 0 && target > DISTANCE){
            enemy1.y+=SPEED/2;
            enemy1.hitbox.y+=SPEED/2;
        }
        else if (enemy1.cy - player1.cy > 0 && target > DISTANCE){
            enemy1.y-=SPEED/2;
            enemy1.hitbox.y-=SPEED/2;
        }

    }
    enemy1.cx = enemy1.x + 35;
    enemy1.cy = enemy1.y + 35;
    
    
    /*
    if (enemy1.x - player1.x < 0 && target > DISTANCE){
            if (enemy1.y - player1.y < 0 && target > DISTANCE){
                if (angle < 0.65){
                    enemy1.y+=SPEED/2;
                    enemy1.hitbox.y+=SPEED/2;
                }
                else if (angle >= 0.65 && angle <= 0.85){
                    enemy1.y+=SPEED/2;
                    enemy1.hitbox.y+=SPEED/2;
                }
                else if (angle > 0.85){
                    enemy1.y+=(float)SPEED/4;
                    enemy1.hitbox.y+=(float)SPEED/4;
                }
            }
            else if (enemy1.y - player1.y > 0 && target > DISTANCE){
                if (angle < 0.65){ 
                    enemy1.y-=SPEED/2;
                    enemy1.hitbox.y-=SPEED/2;
                }
                else if (angle >= 0.65 && angle <= 0.85){
                    enemy1.y-=SPEED/2;
                    enemy1.hitbox.y-=SPEED/2;
                }
                else if (angle > 0.85){
                    enemy1.y-=(float)SPEED/4;
                    enemy1.hitbox.y-=(float)SPEED/4;
                }
            }
            if (angle < 0.65){
                enemy1.x+=(float)SPEED/4;
                enemy1.hitbox.x+=(float)SPEED/4;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.x+=SPEED/2;
                enemy1.hitbox.x+=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.x+=SPEED/2;
                enemy1.hitbox.x+=SPEED/2;
            }
    }
    else if (enemy1.x - player1.x > 0 && target > DISTANCE){
        if (enemy1.y - player1.y < 0 && target > DISTANCE){
            if (angle < 0.65){
                enemy1.y+=SPEED/2;
                enemy1.hitbox.y+=SPEED/2;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.y+=SPEED/2;
                enemy1.hitbox.y+=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.y+=(float)SPEED/4;
                enemy1.hitbox.y+=(float)SPEED/4;
            }
        }
        else if (enemy1.y - player1.y > 0 && target > DISTANCE){
            if (angle < 0.65){ 
                enemy1.y-=SPEED/2;
                enemy1.hitbox.y-=SPEED/2;
            }
            else if (angle >= 0.65 && angle <= 0.85){
                enemy1.y-=SPEED/2;
                enemy1.hitbox.y-=SPEED/2;
            }
            else if (angle > 0.85){
                enemy1.y-=(float)SPEED/4;
                enemy1.hitbox.y-=(float)SPEED/4;
            }
        } 
        if (angle < 0.65){
            enemy1.x-=(float)SPEED/4;
            enemy1.hitbox.x-=(float)SPEED/4;
        }
        else if (angle >= 0.65 && angle <= 0.85){
            enemy1.x-=SPEED/2;
            enemy1.hitbox.x-=SPEED/2;
        }
        else if (angle > 0.85){
            enemy1.x-=SPEED/2;
            enemy1.hitbox.x-=SPEED/2;
        }
    }
    else if (enemy1.x == player1.x && target > DISTANCE){
        if (enemy1.y - player1.y < 0 && target > DISTANCE){
            enemy1.y+=SPEED/2;
            enemy1.hitbox.y+=SPEED/2;
        }
        else if (enemy1.y - player1.y > 0 && target > DISTANCE){
            enemy1.y-=SPEED/2;
            enemy1.hitbox.y-=SPEED/2;
        }

    }
*/
    

    






/*
        if (player1.x == 440){
            enemy1.x = enemy1.z - (player1.z - 440);
            enemy1.hitbox.x = enemy1.x + 20;
        }*/
}


bool Enemy::checkHitbox(SDL_FRect pHitbox, SDL_FRect eHitbox){
    return !(pHitbox.x + pHitbox.w < eHitbox.x || pHitbox.x > eHitbox.x + eHitbox.w || pHitbox.y + pHitbox.h < eHitbox.y || pHitbox.y > eHitbox.y + eHitbox.h);
}

void Enemy::prevCoordinates(class Enemy &enemy1){
    enemy1.prevx=enemy1.x;
    enemy1.prevy=enemy1.y;
};


void Enemy::sortEnemy(std::vector<Enemy>& enemyVector) {
    for (int i = 1; i < enemyVector.size(); ++i) {
        Enemy key = enemyVector[i];
        int j = i - 1;

        while (j >= 0 && enemyVector[j].y > key.y) {
            enemyVector[j + 1] = enemyVector[j];
            j = j - 1;
        }
        enemyVector[j + 1] = key;
    }
}