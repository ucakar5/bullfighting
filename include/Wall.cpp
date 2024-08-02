Wall::Wall(SDL_Renderer *r){
    x=0;
    y=170;
    
    wall = IMG_LoadTexture(r, "media/wall.png");
    wall2 = IMG_LoadTexture(r, "media/wall2.png");
    walld = IMG_LoadTexture(r, "media/wallDesert.png");
    wall2d = IMG_LoadTexture(r, "media/wall2Desert.png");
    walln = IMG_LoadTexture(r, "media/wallNether.png");
    wall2n = IMG_LoadTexture(r, "media/wall2Nether.png");

    current=wall;
    current2=wall2;
};


void Wall::Draw(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(current, NULL, NULL, &w, &h);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w*1.55;
    rect1.h = h*1.2;

    SDL_RenderCopy(r, current, NULL, &rect1);

};

void Wall::Draw2(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(current2, NULL, NULL, &w, &h);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w*1.55;
    rect1.h = h*1.2;

    SDL_RenderCopy(r, current2, NULL, &rect1);

};