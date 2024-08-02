Door::Door(SDL_Renderer *r){
    x=835;
    y=488;

    opacity=0;
    frame=0;
    type=1;
    
    doors = IMG_LoadTexture(r, "media/door.png");
    doord = IMG_LoadTexture(r, "media/doorDesert.png");
    doorn = IMG_LoadTexture(r, "media/doorNether.png");
    red = IMG_LoadTexture(r, "media/red.png");

    hitbox.x = x+13;
    hitbox.y = y+20;
    hitbox.w = 4;
    hitbox.h = 20;
    
    
    current=doors;
};


void Door::Draw(SDL_Renderer *r, int scene){
    int w, h;
    SDL_QueryTexture(current, NULL, NULL, &w, &h);
    
    SDL_Rect rect1;
    rect1.x = type*64;
    rect1.y = frame*64;
    rect1.w = 64;
    rect1.h = 64;
    
    SDL_Rect rect2;
    if (scene%2==1){
        rect2.x = x;
        rect2.y = y;
        rect2.w = 30;
        rect2.h = 30;
    }
    else if (scene%2==0){
        rect2.x = x;
        rect2.y = y;
        rect2.w = 56;
        rect2.h = 56;
    }
    


    SDL_RenderCopy(r, current, &rect1, &rect2);
    //SDL_RenderCopyF(r, red, NULL, &hitbox);

};

bool Door::checkHitbox(SDL_FRect pHitbox, SDL_FRect eHitbox){
    return !(pHitbox.x + pHitbox.w < eHitbox.x || pHitbox.x > eHitbox.x + eHitbox.w || pHitbox.y + pHitbox.h < eHitbox.y || pHitbox.y > eHitbox.y + eHitbox.h);
}