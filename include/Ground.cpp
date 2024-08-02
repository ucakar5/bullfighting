Ground::Ground(SDL_Renderer *r){
    x=0;
    y=0;
    
    gr1 = IMG_LoadTexture(r, "media/groundGrass.png");
    gr2 = IMG_LoadTexture(r, "media/groundDesert.png");
    gr3 = IMG_LoadTexture(r, "media/groundNether.png");

    grf1 = IMG_LoadTexture(r, "media/fullGrass.png");
    grf2 = IMG_LoadTexture(r, "media/fullDesert.png");
    grf3 = IMG_LoadTexture(r, "media/fullNether.png");
    
    current=grf1;

};


void Ground::Draw(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(current, NULL, NULL, &w, &h);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w/1.5;
    rect1.h = h/1.2;

    SDL_RenderCopy(r, current, NULL, &rect1);

}