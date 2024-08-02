Background::Background(SDL_Renderer *r){
    x=0;
    y=0;
    bg1 = IMG_LoadTexture(r, "media/skyGrass.png");
    bg2 = IMG_LoadTexture(r, "media/skyDesert.png");
    bg3 = IMG_LoadTexture(r, "media/skyNether.png");

    current=bg1;
};


void Background::Draw(SDL_Renderer *r){
    int ws, hs;
    SDL_QueryTexture(current, NULL, NULL, &ws, &hs);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = ws/2;
    rect1.h = hs/2;

    SDL_RenderCopy(r, current, NULL, &rect1);

}