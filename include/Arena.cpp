Arena::Arena(SDL_Renderer *r){
    x=800;
    y=400;

    opacity=0;

    
    arena1 = IMG_LoadTexture(r, "media/arena.png");
    arena2 = IMG_LoadTexture(r, "media/arenaDesert.png");
    arena3 = IMG_LoadTexture(r, "media/arenaNether.png");
    red = IMG_LoadTexture(r, "media/red.png");

    hitbox.x = x;
    hitbox.y = y+34;
    hitbox.w = 100;
    hitbox.h = 78;
    
    cx=x+hitbox.w/2;
    cy=y+hitbox.h/2+17;
    
    current=arena1;
};


void Arena::Draw(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(current, NULL, NULL, &w, &h);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w/1.5;
    rect1.h = h/1.5;

    SDL_RenderCopy(r, current, NULL, &rect1);
    //SDL_RenderCopyF(r, red, NULL, &hitbox);

};

void Arena::updateArena(int scene, Door &door){
    if (scene==1){
            door.current=door.doors;
        }
    else if (scene==3){
        door.current=door.doord;
    }
    else if (scene==5){
        door.current=door.doorn;
    }
    hitbox.x = x;
    hitbox.y = y+34;
    hitbox.w = 100;
    hitbox.h = 78;
    cx=x+hitbox.w/2;
    cy=y+hitbox.h/2+17;
    opacity=0;

    door.x=x+35;
    door.y=y+88;
    door.type=1;
    door.hitbox.x = door.x+13;
    door.hitbox.y = door.y+20;
    door.hitbox.w = 4;
    door.hitbox.h = 20;
}


void Arena::radiusCalc(Player &player){
    radius=sqrt(abs((cx - player.cx)*(cx - player.cx) + (cy - player.cy)*(cy - player.cy)));
      
    if (radius > 112)
        opacity=0;
    else if (radius <= 112 && radius >= 96)
        opacity=-(radius-112)*16;
    else if (radius < 96)
        opacity=255;

}