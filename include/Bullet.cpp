Bullet::Bullet(SDL_Renderer *r, float ex, float ey, float eangle){
    x=ex;
    y=ey;
    angle= eangle;
    point = {2, 4};

    BulletPoint = this;

    destroyed=0;

    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 21;
    hitbox.h = 7;
    
    bullet = IMG_LoadTexture(r, "media/bullet.png");
    red = IMG_LoadTexture(r, "media/red.png");
}

void Bullet::destroyBullet(){
    SDL_DestroyTexture(this -> bullet);
    SDL_DestroyTexture(this -> red);
}


void Bullet::Draw(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(bullet, NULL, NULL, &w, &h);
    SDL_FRect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w/45;
    rect1.h = h/45;

    point = {2, 4};
    //SDL_RenderCopy(r, bullet, NULL, &rect1);
    SDL_RenderCopyExF(r, bullet, NULL, &rect1, -(angle * (180/3.141))+90, &point, SDL_FLIP_NONE);
    //SDL_RenderCopyExF(r, red, NULL, &hitbox, -(angle * (180/3.141))+90, &point, SDL_FLIP_NONE);
    


}

bool Bullet::checkHitbox(SDL_FRect pHitbox, SDL_FRect eHitbox){
    return !(pHitbox.x + pHitbox.w < eHitbox.x || pHitbox.x > eHitbox.x + eHitbox.w || pHitbox.y + pHitbox.h < eHitbox.y || pHitbox.y > eHitbox.y + eHitbox.h);
}


bool Bullet::Borders(){
    if (x < -30 || x > 1110 || y < -30 || y > 640) return 1;
    return 0;
}

void Bullet::sortBullet(std::vector<Bullet>& bulletVector) {
    for (int i = 1; i < bulletVector.size(); ++i) {
        Bullet key = bulletVector[i];
        int j = i - 1;

        while (j >= 0 && bulletVector[j].destroyed > key.destroyed) {
            bulletVector[j + 1] = bulletVector[j];
            j = j - 1;
        }
        bulletVector[j + 1] = key;
    }
}