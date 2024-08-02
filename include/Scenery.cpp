Scenery::Scenery(SDL_Renderer *r){
    x=1080;
    y=0;
    scene=0;
    state=0;
    status=1;
    enemyNum=0;
    black = IMG_LoadTexture(r, "media/black.png");
};

void Scenery::transition(SDL_Renderer *r){
    int w, h;
    SDL_QueryTexture(black, NULL, NULL, &w, &h);
    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = w*3;
    rect1.h = h*3;

    SDL_RenderCopy(r, black, NULL, &rect1);

};

int Scenery::sceneChange(int scene, Ground &ground, Background &background, Wall &wall, Player &player, Arena &arena, Arena &arena2, Door &door) {
    if (scene==0){
        ground.y = 0;
        ground.current=ground.grf1;
    }
    if (scene%2==1){   
        ground.x = 0;
        ground.y = 0;
        
        if (scene==1){
            door.current=door.doors;
            ground.current=ground.grf1;
            arena.current=arena.arena1;
        }
        else if (scene==3){
            door.current=door.doord;
            ground.current=ground.grf2;
            arena.current=arena.arena2;
            arena2.current=arena2.arena1;
        }
        else if (scene==5){
            door.current=door.doorn;
            ground.current=ground.grf3;
            arena.current=arena.arena3;
            arena2.current=arena2.arena2;

        }


        player.phase=0;
        player.health=100;
        //player.dashTimeout=100;
        player.x=-70;
        player.y=20;
        player.phase=0;
        player.hitbox.x = player.x + 4;
        player.hitbox.y = player.y + 52;
        player.hitbox.w = 72;
        player.hitbox.h = 14;
        player.cx = x + 24;
        player.cy = y + 24;
        player.sprite_dir = 96;

        srand(time(NULL));
        arena.x = rand() % 960 + 10;
        if (arena.x < 550)
            arena.y = rand() % 34 + 450;
        else
            arena.y = rand() % 474 + 10;
        arena.hitbox.x = arena.x;
        arena.hitbox.y = arena.y+34;
        arena.hitbox.w = 100;
        arena.hitbox.h = 78;
        arena.cx=arena.x+arena.hitbox.w/2;
        arena.cy=arena.y+arena.hitbox.h/2+17;
        arena.opacity=0;
        

        if (scene==1){
            arena2.x=-100;
            arena2.y=-78;
        }
        else {
            arena2.x=-50;
            arena2.y=-70;
        }
        
        arena2.hitbox.x = arena2.x;
        arena2.hitbox.y = arena2.y+34;
        arena2.hitbox.w = 100;
        arena2.hitbox.h = 78;
        arena2.cx=arena2.x+arena2.hitbox.w/2;
        arena2.cy=arena2.y+arena2.hitbox.h/2+17;

        

        door.x=arena.x+35;
        door.y=arena.y+88;
        door.type=1;
        door.hitbox.x = door.x+13;
        door.hitbox.y = door.y+20;
        door.hitbox.w = 4;
        door.hitbox.h = 20;
        

        return 1;

    }
    else if (scene%2==0){
        ground.x = 0;
        if (scene==2){
            ground.y = 200;
            background.x = 0;
            background.y = 0;

            ground.current=ground.gr1;
            background.current=background.bg1;
            wall.current=wall.wall;
            wall.current2=wall.wall2;

            door.current=door.doors;
        }
        else if (scene==4){
            ground.y = 190;
            background.x = -450;
            background.y = -270;

            ground.current=ground.gr2;
            background.current=background.bg2;
            wall.current=wall.walld;
            wall.current2=wall.wall2d;

            door.current=door.doord;
        }
        else if (scene==6){
            ground.y = 190;
            background.x = 0;
            background.y = -90;
            
            ground.current=ground.gr3;
            background.current=background.bg3;
            wall.current=wall.walln;
            wall.current2=wall.wall2n;
            
            door.current=door.doorn;
        }

        player.phase=1;
        player.health=100;
        //player.dashTimeout=100;
        if (state==5){
            player.x=40;
            player.y=342;
        }
        else {
        player.x=-80;
        player.y=342;
        }
        player.sprite_dir = 96;

        door.x=512;
        door.y=186;
        door.hitbox.x=512;
        door.hitbox.y=186;
        door.hitbox.x = door.x+24;
        door.hitbox.y = door.y+37;
        door.hitbox.w = 7;
        door.hitbox.h = 37;
        door.type=0;
        

        return 2;
    }
    else {
        return 0;
    }

}


void Scenery::textAnimation (int &itext, int &textOpacity, int &i){
    if (textOpacity!=254 && textOpacity!=255){
        if (itext==0)
            textOpacity+=2;
        else if (itext==1){
            if (textOpacity!=1)
                textOpacity-=2;
            else if (textOpacity==1)
                textOpacity=0;
        }
    }
    else if (textOpacity==254)
        textOpacity=255;
    else if (textOpacity==255)
        i++;
    
    
    if (i==150){
        itext=1;
        i=0;
        textOpacity=253;
    }

    if (textOpacity==0 && itext==1){
        itext=2;
    }

}

bool Scenery::transitionAnimation(int &t){
    if (t!=0 && t<94){
        t++;
        x-=16;
        if (t==94){
            x=1080;
            t=0;
        }
        return 1;
    }
    return 0;
}

void Scenery::makeText (SDL_Renderer *r, SDL_Texture *textTexture, TTF_Font *Sans2, int &itext){
    SDL_Surface *textSurface;
    textSurface = TTF_RenderText_Blended(Sans2, "Press 'SPACE' to enter", SDL_Color({255, 255, 255}));
    SDL_DestroyTexture(textTexture);
    textTexture = SDL_CreateTextureFromSurface(r, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect;
    textRect.x = 314;
    textRect.y = 10;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    itext=3;
}

void Scenery::textDeclaration(SDL_Renderer *r, std::vector<SDL_Texture*> &text){
    TTF_Init();
    TTF_Font *megaSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 70);
    TTF_Font *menuSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 50);
    TTF_Font *Sans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 30);
    TTF_Font *Sans2 = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 20);
    TTF_Font *miniSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 10);
    

    SDL_Surface *textSurface;
    textSurface = TTF_RenderText_Blended(Sans, "Find the hidden arena", SDL_Color({255, 255, 255}));
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(r, textSurface);
    SDL_FreeSurface(textSurface);
    text.push_back(textTexture);

    SDL_Surface *playSurface;
    playSurface = TTF_RenderText_Blended(menuSans, "PLAY", SDL_Color({255, 255, 255}));
    SDL_Texture *playButton = SDL_CreateTextureFromSurface(r, playSurface);
    SDL_FreeSurface(playSurface);
    text.push_back(playButton);

    SDL_Surface *scoreSurface;
    scoreSurface = TTF_RenderText_Blended(menuSans, "SCORES", SDL_Color({255, 255, 255}));
    SDL_Texture *scoreButton = SDL_CreateTextureFromSurface(r, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    text.push_back(scoreButton);

    SDL_Surface *exitSurface;
    exitSurface = TTF_RenderText_Blended(menuSans, "EXIT", SDL_Color({255, 255, 255}));
    SDL_Texture *exitButton = SDL_CreateTextureFromSurface(r, exitSurface);
    SDL_FreeSurface(exitSurface);
    text.push_back(exitButton);

    SDL_Surface *etcSurface;
    etcSurface = TTF_RenderText_Blended(miniSans, "(Press 'ENTER' to confirm)", SDL_Color({255, 255, 255}));
    SDL_Texture *etcText = SDL_CreateTextureFromSurface(r, etcSurface);
    SDL_FreeSurface(etcSurface);
    text.push_back(etcText);

    SDL_Surface *eynSurface;
    eynSurface = TTF_RenderText_Blended(Sans, "Enter you nickname", SDL_Color({255, 255, 255}));
    SDL_Texture *eynText = SDL_CreateTextureFromSurface(r, eynSurface);
    SDL_FreeSurface(eynSurface);
    text.push_back(eynText);

    SDL_Surface *gameSurface;
    gameSurface = TTF_RenderText_Blended(menuSans, "GAME", SDL_Color({255, 255, 255}));
    SDL_Texture *gameText = SDL_CreateTextureFromSurface(r, gameSurface);
    SDL_FreeSurface(gameSurface);
    text.push_back(gameText);

    SDL_Surface *newSurface;
    newSurface = TTF_RenderText_Blended(menuSans, "NEW", SDL_Color({255, 255, 255}));
    SDL_Texture *newText = SDL_CreateTextureFromSurface(r, newSurface);
    SDL_FreeSurface(newSurface);
    text.push_back(newText);

    SDL_Surface *savedSurface;
    savedSurface = TTF_RenderText_Blended(menuSans, "SAVED", SDL_Color({255, 255, 255}));
    SDL_Texture *savedText = SDL_CreateTextureFromSurface(r, savedSurface);
    SDL_FreeSurface(savedSurface);
    text.push_back(savedText);

    SDL_Surface *btmSurface;
    btmSurface = TTF_RenderText_Blended(Sans, "BACK", SDL_Color({255, 255, 255}));
    SDL_Texture *btmButton = SDL_CreateTextureFromSurface(r, btmSurface);
    SDL_FreeSurface(btmSurface);
    text.push_back(btmButton);

    SDL_Surface *placeSurface;
    placeSurface = TTF_RenderText_Blended(megaSans, "1", SDL_Color({255, 255, 255}));
    SDL_Texture *placeText = SDL_CreateTextureFromSurface(r, placeSurface);
    SDL_FreeSurface(placeSurface);
    text.push_back(placeText);

    SDL_Surface *loseSurface;
    loseSurface = TTF_RenderText_Blended(megaSans, "YOU LOST", SDL_Color({255, 255, 255}));
    SDL_Texture *loseText = SDL_CreateTextureFromSurface(r, loseSurface);
    SDL_FreeSurface(loseSurface);
    text.push_back(loseText);

    SDL_Surface *winSurface;
    winSurface = TTF_RenderText_Blended(megaSans, "YOU WON", SDL_Color({255, 255, 255}));
    SDL_Texture *winText = SDL_CreateTextureFromSurface(r, winSurface);
    SDL_FreeSurface(winSurface);
    text.push_back(winText);

    SDL_Surface *endscoreSurface;
    endscoreSurface = TTF_RenderText_Blended(menuSans, "0", SDL_Color({255, 255, 255}));
    SDL_Texture *endscoreText = SDL_CreateTextureFromSurface(r, endscoreSurface);
    SDL_FreeSurface(endscoreSurface);
    text.push_back(endscoreText);
    
    SDL_Surface *endnameSurface;
    endnameSurface = TTF_RenderText_Blended(menuSans, "NULL", SDL_Color({255, 255, 255}));
    SDL_Texture *endnameText = SDL_CreateTextureFromSurface(r, endnameSurface);
    SDL_FreeSurface(endnameSurface);
    text.push_back(endnameText);

    SDL_Surface *titleSurface;
    titleSurface = TTF_RenderText_Blended(megaSans, "BULLFIGHTERS", SDL_Color({255, 255, 255}));
    SDL_Texture *titleText = SDL_CreateTextureFromSurface(r, titleSurface);
    SDL_FreeSurface(titleSurface);
    text.push_back(titleText);


}

void Scenery::rectDeclaration(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text){
    SDL_Rect textRect;
    textRect.x = 227;
    textRect.y = 279;
    SDL_QueryTexture(text.at(0), NULL, NULL, &textRect.w, &textRect.h);
    rect.push_back(textRect);

    SDL_Rect playRect;
    playRect.x = 443;
    playRect.y = 316;
    SDL_QueryTexture(text.at(1), NULL, NULL, &playRect.w, &playRect.h);
    rect.push_back(playRect);
    
    SDL_Rect playRect2 = { playRect.x-60, playRect.y-4, playRect.w+113, playRect.h+15 };
    rect.push_back(playRect2);
    
    SDL_Rect scoreRect;
    scoreRect.x = 393;
    scoreRect.y = 409;
    SDL_QueryTexture(text.at(2), NULL, NULL, &scoreRect.w, &scoreRect.h);
    rect.push_back(scoreRect);
    
    SDL_Rect scoreRect2 = { scoreRect.x-10, scoreRect.y-4, scoreRect.w+13, scoreRect.h+15 };
    rect.push_back(scoreRect2);

    SDL_Rect exitRect;
    exitRect.x = 443;
    exitRect.y = 502;
    SDL_QueryTexture(text.at(3), NULL, NULL, &exitRect.w, &exitRect.h);
    rect.push_back(exitRect);

    SDL_Rect exitRect2 = { exitRect.x-60, exitRect.y-4, exitRect.w+113, exitRect.h+15 };
    rect.push_back(exitRect2);

    SDL_Rect fieldRect = { 227, 273, 626, 63 };
    rect.push_back(fieldRect);

    SDL_Rect etcRect;
    etcRect.x = 412;
    etcRect.y = 344;
    SDL_QueryTexture(text.at(4), NULL, NULL, &etcRect.w, &etcRect.h);
    rect.push_back(etcRect);

    SDL_Rect eynRect;
    eynRect.x = 272;
    eynRect.y = 230;
    SDL_QueryTexture(text.at(5), NULL, NULL, &eynRect.w, &eynRect.h);
    rect.push_back(eynRect);

    SDL_Rect gameButton = {215, 155, 300, 300};
    rect.push_back(gameButton);

    SDL_Rect gameRect;
    gameRect.x = 268;
    gameRect.y = 302;
    SDL_QueryTexture(text.at(6), NULL, NULL, &gameRect.w, &gameRect.h);
    rect.push_back(gameRect);

    SDL_Rect newRect;
    newRect.x = 293;
    newRect.y = 252;
    SDL_QueryTexture(text.at(7), NULL, NULL, &newRect.w, &newRect.h);
    rect.push_back(newRect);

    SDL_Rect savedRect;
    savedRect.x = 593;
    savedRect.y = 252;
    SDL_QueryTexture(text.at(8), NULL, NULL, &savedRect.w, &savedRect.h);
    rect.push_back(savedRect);

    SDL_Rect btmRect;
    btmRect.x = 930;
    btmRect.y = 550;
    SDL_QueryTexture(text.at(9), NULL, NULL, &btmRect.w, &btmRect.h);
    rect.push_back(btmRect);

    SDL_Rect btmRect2 = { btmRect.x-7, btmRect.y-6, btmRect.w+11, btmRect.h+15 };
    rect.push_back(btmRect2);

    SDL_Rect placeRect;
    placeRect.x = 312;
    placeRect.y = 90;
    placeRect.w-=70;
    SDL_QueryTexture(text.at(10), NULL, NULL, &placeRect.w, &placeRect.h); 
    rect.push_back(placeRect);

    SDL_Rect loseRect;
    loseRect.x = 259;
    loseRect.y = 250;
    SDL_QueryTexture(text.at(11), NULL, NULL, &loseRect.w, &loseRect.h);
    rect.push_back(loseRect);

    SDL_Rect winRect;
    winRect.x = 295;
    winRect.y = 30;
    SDL_QueryTexture(text.at(12), NULL, NULL, &winRect.w, &winRect.h);
    rect.push_back(winRect);

    SDL_Rect preimgRect;
    preimgRect.x = 0;
    preimgRect.y = 96;
    preimgRect.w = 48;
    preimgRect.h = 48;
    rect.push_back(preimgRect);

    SDL_Rect imgRect;
    imgRect.x = 422;
    imgRect.y = 96;
    imgRect.w = 240;
    imgRect.h = 240;
    rect.push_back(imgRect);

    SDL_Rect endnameRect;
    endnameRect.x = 450;
    endnameRect.y = 350;
    endnameRect.w = 0;
    endnameRect.h = 0;
    rect.push_back(endnameRect);

    SDL_Rect endscoreRect;
    endscoreRect.x = 450;
    endscoreRect.y = 420;
    endscoreRect.w = 0;
    endscoreRect.h = 0;
    rect.push_back(endscoreRect);

    SDL_Rect nicknameRect;
    nicknameRect.y = 276;
    rect.push_back(nicknameRect);

    SDL_Rect titleRect;
    titleRect.x = 123;
    titleRect.y = 70;
    SDL_QueryTexture(text.at(15), NULL, NULL, &titleRect.w, &titleRect.h);
    rect.push_back(titleRect);
}

void Scenery::textUpdates(int num, SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text){
    TTF_Init();
    TTF_Font *megaSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 70);
    TTF_Font *menuSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 50);
    TTF_Font *Sans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 30);
    TTF_Font *Sans2 = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 20);
    TTF_Font *miniSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 10);

    SDL_Surface *textSurface = nullptr;

    if (num==1){
        textSurface = TTF_RenderText_Blended(Sans2, "Press 'SPACE' to enter", SDL_Color({255, 255, 255}));
        SDL_DestroyTexture(text.at(0));
        text.at(0) = SDL_CreateTextureFromSurface(r, textSurface);
        SDL_FreeSurface(textSurface);
        (rect.at(0)).x = 314;
        (rect.at(0)).y = 10;
        SDL_QueryTexture(text.at(0), NULL, NULL, &(rect.at(0)).w, &(rect.at(0)).h);
    }
    else if (num==2){
        if (scene+1==2)
            textSurface = TTF_RenderText_Blended(Sans, "Level 1", SDL_Color({255, 255, 255}));
        else if (scene+1==4)
            textSurface = TTF_RenderText_Blended(Sans, "Level 2", SDL_Color({255, 255, 255}));
        else if (scene+1==6)
            textSurface = TTF_RenderText_Blended(Sans, "Level 3", SDL_Color({255, 255, 255}));
        SDL_DestroyTexture(text.at(0));
        text.at(0) = SDL_CreateTextureFromSurface(r, textSurface);
        SDL_FreeSurface(textSurface);
        (rect.at(0)).x = 437;
        (rect.at(0)).y = 130;
        SDL_QueryTexture(text.at(0), NULL, NULL, &(rect.at(0)).w, &(rect.at(0)).h);
    }
    else if (num==3){
        textSurface = TTF_RenderText_Blended(Sans2, "Go to the door to unlock it", SDL_Color({255, 255, 255}));
        SDL_DestroyTexture(text.at(0));
        text.at(0) = SDL_CreateTextureFromSurface(r, textSurface);
        SDL_FreeSurface(textSurface);
        (rect.at(0)).x = 261;
        (rect.at(0)).y = 8;
        SDL_QueryTexture(text.at(0), NULL, NULL, &(rect.at(0)).w, &(rect.at(0)).h);
    }
    else if (num==4){
        textSurface = TTF_RenderText_Blended(Sans, "Find the hidden arena", SDL_Color({255, 255, 255}));
        SDL_DestroyTexture(text.at(0));
        text.at(0) = SDL_CreateTextureFromSurface(r, textSurface);
        SDL_FreeSurface(textSurface);
        (rect.at(0)).x = 227;
        (rect.at(0)).y = 279;
        SDL_QueryTexture(text.at(0), NULL, NULL, &(rect.at(0)).w, &(rect.at(0)).h);
    }
}

void Scenery::readScore(bool &readFinish, std::vector <std::string> &fileContent){
    std::ifstream scoreRead;
    scoreRead.open("scores.txt");
    std::string content;
    int j=0; 
    while (getline(scoreRead, content)) {
        fileContent[j] = content;
        j++;
    }
    readFinish=1;
    scoreRead.close();
}

void Scenery::save(char nickname[], int score, Player &player, Arena &arena, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList){
    std::ofstream saving;
    //ofstream saving ("save.dat", ios::binary);
    //ofstream saving ("save.txt");
    saving.open("save1.txt");

    if (scene==0 || scene==7){
        saving<<"0"<< std::endl;
    }
    else if (scene==1 || scene==3 || scene==5){
        if (state==1){
            saving<<scene<< std::endl;
            saving<<state<< std::endl;
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;

        }
        else if (state==2){
            saving<<scene<< std::endl;
            saving<<state<< std::endl;
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;
            
            saving<<player.x<< std::endl;
            saving<<player.y<< std::endl;
            saving<<player.sprite_dir<< std::endl;
            saving<<player.phase<< std::endl; //phase //0
            
            saving<<arena.x<< std::endl;
            saving<<arena.y<< std::endl;

        }
        else if (state==3){
            saving<<scene<< std::endl;
            saving<<state<< std::endl; //state //1
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;
            //saving<<player.phase<< std::endl; //phase //1
        }
        
    }
    else if (scene==2 || scene==4 || scene==6){
        if (state==1){
            saving<<scene<< std::endl;
            saving<<state<< std::endl;
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;

        }
        else if (state==2 || state==4 || state==5 || state==6){
            saving<<scene<< std::endl;
            saving<<state<< std::endl;
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;
            
            saving<<player.x<< std::endl;
            saving<<player.y<< std::endl;
            saving<<player.sprite_dir<< std::endl;
            saving<<player.phase<< std::endl; //phase
            saving<<player.health<< std::endl;
            saving<<player.checkpointScore<< std::endl;
            saving<<player.key<< std::endl;

            saving<<"enemies"<< std::endl;
            std::vector <Enemy> :: iterator enemyCount;
            for (enemyCount = enemyList.begin(); enemyCount!=enemyList.end(); enemyCount++){
                saving<<enemyCount ->x<< std::endl;
                saving<<enemyCount ->y<< std::endl;
                saving<<enemyCount ->health<< std::endl;
                saving<<enemyCount ->sprite_dir_enemy<< std::endl;
            }

            saving<<"end"<< std::endl;
            /*std::vector <Bullet> :: iterator bulletCount;
            for (bulletCount = bulletList.begin(); bulletCount!=bulletList.end(); bulletCount++){
                saving<<bulletCount ->x<< std::endl;
                saving<<bulletCount ->y<< std::endl;
                saving<<bulletCount ->angle<< std::endl;
            }
            saving<<"end"<< std::endl;*/


        }
        else if (state==3){
            saving<<scene<< std::endl;
            saving<<state<< std::endl; //state //1
            saving<<nickname<< std::endl;
            saving<<score<< std::endl;
            //saving<<player.phase<< std::endl; //phase //0
        }
    }

    saving.close();
    remove("save.txt");
    rename("save1.txt", "save.txt");
}




int Scenery::savedGame(SDL_Renderer *r, int &t, int &pressed, char nickname[], int &score, Player &player, Arena &arena, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList, Ground &ground, Background &background, Wall &wall, Arena &arena2, Door &door){
    
    std::ifstream saveLoad;
    saveLoad.open("save.txt");
    std::vector<std::string> values;
    std::string value;
    while (getline(saveLoad, value)) {
        values.push_back(value);
    }
    saveLoad.close();

    if (values.size()==0){
        state=5;
        t=1;
        pressed=0;
        return 0;
    }
    
    scene=std::stoi(values.at(0));
    if (scene==0 || state==4 || state==5){
        state=5;
        t=1;
        pressed=0;
        return 0;
    }
    state=std::stoi(values.at(1));

    if (state==3){
        if (scene==1 || scene==3 || scene==5){
            scene++;
            state=1;
            
        }
        else if (scene==2 || scene==4 || scene==6){
            scene++;
            state=1;
            
        }
    }
    else if (state==5){  
        state=2;
    }

    sceneChange(scene, ground, background, wall, player, arena, arena2, door);
    pressed=0;
    t=1;

    std::string nickname2 = values.at(2);
    const char* nickname3 = nickname2.c_str();
    std::strcpy(nickname, nickname3);
    
    score = std::stoi(values.at(3));

    if (scene==1 || scene==3 || scene==5){
        if (state==1){
            player.phase=0;
            return 0;   
        }
        else if (state==2){
            player.x=std::stoi(values.at(4));
            player.y=std::stoi(values.at(5));
            player.sprite_dir=std::stoi(values.at(6));
            player.phase=std::stoi(values.at(7)); //phase
            
            arena.x=std::stoi(values.at(8));
            arena.y=std::stoi(values.at(9));

            arena.updateArena(scene, door);
            return 0;
        }
    }
    else if (scene==2 || scene==4 || scene==6){
        if (state==1){
            player.phase=1;
            return 0;

        }
        else if (state==2){
            player.x=std::stoi(values.at(4));
            player.y=std::stoi(values.at(5));
            player.sprite_dir=std::stoi(values.at(6));
            player.phase=std::stoi(values.at(7));
            player.health=std::stoi(values.at(8));
            player.checkpointScore=std::stoi(values.at(9));
            player.key=std::stoi(values.at(10));

            std::vector <Enemy> :: iterator enemyCount;
            int i;
            for (i=12; values.at(i)!="end"; i+=4)
                enemyList.push_back(Enemy(r, 0, scene));

            enemyCount = enemyList.begin();
            for (i=12; values.at(i)!="end"; i+=4){
                //enemyList.push_back(Enemy(r));
                //if (i!=12) 
                //if (i==12) 
                enemyCount -> x = std::stof(values.at(i));
                enemyCount -> y = std::stof(values.at(i+1));
                enemyCount -> health = std::stof(values.at(i+2));
                enemyCount -> sprite_dir_enemy = std::stof(values.at(i+3));
                enemyCount++;
            }
            return 0;
        }
    }

    return 0;
}

void Scenery::replayMoves(std::vector<std::array<int, 4>> &replayMoves, int l, int ri, int u, int d){
    std::array<int, 4> movesArray = {l, ri, u, d};
    replayMoves.push_back(movesArray);
}

void Scenery::replaySave(std::vector<std::array<int, 4>> &replayMoves){
    std::ofstream replayWrite;
    replayWrite.open("replay.txt", std::ios::app);
    for(int i=0; i<replayMoves.size(); i++){
        for(int j=0; j<4; j++) 
            replayWrite << replayMoves[i][j];
        replayWrite << std::endl;
    }
    replayWrite.close();
}

void Scenery::replayLoad(std::vector<std::array<int, 4>> &replayMoves){
        std::array<int, 4> a;
        std::ifstream replayRead;
        replayRead.open("replay.txt");
        std::string line;
        while(getline(replayRead, line)){
            const char* cline = line.c_str();
            a = {static_cast<int>(cline[0])-48, static_cast<int>(cline[1])-48, static_cast<int>(cline[2])-48, static_cast<int>(cline[3])-48};
            replayMoves.push_back(a);
        }
        replayRead.close();
}

void Scenery::replayExecution(Player &player, std::vector<std::array<int, 4>> &replayMoves, int &ir){
    bool l=replayMoves[ir][0];
    bool ri=replayMoves[ir][1];
    bool u=replayMoves[ir][2];
    bool d=replayMoves[ir][3];
    player.Move(l, ri, u, d, SPEED);
    player.Borders(player, scene);
    player.frameUpdate(player, l, ri, u, d);
    ir++;
}


void Scenery::textUpdating(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int &itext, int &textOpacity, int &i, Player &player, Door &door, bool space){
    if (itext<2) textAnimation(itext, textOpacity, i);
    if (itext==2){
        textUpdates(3, r, rect, text);
        itext=3;
        i=0;
    }
    
    if (player.key==1){
        textOpacity=255;
        if (door.checkHitbox(door.hitbox, player.hitbox)==1 && space==1){
            state=3;
            player.sprite_dir = 96;
            textOpacity=0;
            door.frame=1;
        }
    }
    else if (itext==3) {
        textOpacity=0;
    }

}

void Scenery::textUpdating2(SDL_Renderer *r, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int &itext, int &textOpacity, int &i, Player &player, Door &door, bool space){
    if (itext<2) textAnimation(itext, textOpacity, i);
    if (itext==2){ 
        textUpdates(1, r, rect, text);
        itext=3;
    }
    if (door.checkHitbox(door.hitbox, player.hitbox)==1){
        textOpacity=255;
        if (space==1){
            state=3;
        }
    }
    else if (itext==3){
        textOpacity=0;
    }

}

void Scenery::saveScore(int score, char nickname[]){
    std::ifstream readScore;
    std::ofstream writeScore;
    readScore.open("scores.txt");
    writeScore.open("scores1.txt");
    int written=0;
    int i=1;
    std::string a, temp;
    while(readScore >> a){
        if (i%2==1){
            temp = a;
            i++;
        }
        else if (i%2==0){
            if (score > std::stoi(a) && written!=1){
                writeScore << nickname << std::endl;
                writeScore << score << std::endl;
                writeScore << temp << std::endl;
                writeScore << a << std::endl;
                i++;
                written=1;
            }
            else {
                writeScore << temp << std::endl;
                writeScore << a << std::endl;
                i++;
            }
        }
        if (i==10) break;
    }
    readScore.close();
    writeScore.close();
    remove("scores.txt");
    rename("scores1.txt", "scores.txt");
}

void Scenery::endText(int score, char nickname[], std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, SDL_Renderer *r){
    TTF_Init();
    TTF_Font *menuSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 50);
    
    std::string scoreText = std::to_string(score);
    SDL_Surface *scoreSurface;
    scoreSurface = TTF_RenderText_Solid(menuSans, scoreText.c_str(), SDL_Color({255, 255, 255}));
    text.at(13) = SDL_CreateTextureFromSurface(r, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    
    SDL_Surface *nameSurface;
    nameSurface = TTF_RenderText_Blended(menuSans, nickname, SDL_Color({255, 255, 255}));
    text.at(14) = SDL_CreateTextureFromSurface(r, nameSurface);
    SDL_FreeSurface(nameSurface);

    SDL_QueryTexture(text.at(13), NULL, NULL, &((rect.at(22)).w), &((rect.at(22)).h));
    SDL_QueryTexture(text.at(14), NULL, NULL, &((rect.at(21)).w), &((rect.at(21)).h));

    if ((rect.at(21)).w<=50)
        (rect.at(21)).x=518;
    else if ((rect.at(21)).w>50)
        (rect.at(21)).x=543-((rect.at(21)).w/50)*25;

    if ((rect.at(22)).w<=50)
        (rect.at(22)).x=518;
    else if ((rect.at(22)).w>50)
        (rect.at(22)).x=543-((rect.at(22)).w/50)*25;
}

void Scenery::enemyHandling(int &et, SDL_Renderer *r, std::vector <Enemy> &enemyList, int &score, Player &player){
    //std::cout << "enemyNum: " << enemyNum << std::endl;
    //std::cout << "status: " << status << std::endl;
    if (scene==2){
        if (status==1){
            if (et==150 || et==250 || et==350 || et==450 || et==550 || et==650){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==6 && enemyList.size()<=2) {
                status=2;
                score+=et;
                et=0;
            }
        }
        else if (status==2){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==12 && enemyList.size()==0){
                score+=et;
                status=3;
            }
        }
        else if (status==3){
            player.key=1;
        }
    }
    else if (scene==4){
        if (status==1){
            if (et==150 || et==250 || et==350 || et==450 || et==550 || et==650){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==6 && enemyList.size()<=2) {
                status=2;
                score+=et;
                et=0;
            }
        }
        else if (status==2){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==12 && enemyList.size()<=2){
                score+=et;
                status=3;
                et=0;
            }
        }
        else if (status==3){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==18 && enemyList.size()==0){
                score+=et;
                status=4;
            }
        }
        else if (status==4){
            player.key=1;
        }
    }
    else if (scene==6){
        if (status==1){
            if (et==150 || et==250 || et==350 || et==450 || et==550 || et==650){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==6 && enemyList.size()<=2) {
                status=2;
                score+=et;
                et=0;
            }
        }
        else if (status==2){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==12 && enemyList.size()<=2){
                score+=et;
                status=3;
                et=0;
            }
        }
        else if (status==3){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==18 && enemyList.size()<=2){
                score+=et;
                status=4;
                et=0;
            }
        }
        else if (status==4){
            if (et==1 || et==100 || et==200 || et==300 || et==400 || et==500){
                enemyNum++;
                enemyList.push_back(Enemy(r, enemyNum, scene));
            }
            if (enemyNum==24 && enemyList.size()==0){
                score+=et;
                status=5;
            }
        }
        else if (status==5){
            player.key=1;
        }
    }
    et++;
}

void Scenery::bullets(std::vector <Bullet> &bulletList, std::vector <Enemy> &enemyList, int &score){
    std::vector <Bullet> :: iterator bulletCount;
    std::vector <Enemy> :: iterator enemyCount;
    if (bulletList.size() > 0) {
        for (bulletCount = bulletList.begin(); bulletCount != bulletList.end(); ) {
            bulletCount->x += sin(bulletCount->angle) * 1.25*SPEED;
            bulletCount->y += cos(bulletCount->angle) * 1.25*SPEED;
            bulletCount->hitbox.x = bulletCount->x;
            bulletCount->hitbox.y = bulletCount->y;
            /*if ((bulletCount -> Borders())==1) {
                bulletCount -> destroyBullet();
                bulletCount = bulletList.erase(bulletCount);
                score+=50;
            }*/
            for (enemyCount = enemyList.begin(); enemyCount != enemyList.end(); enemyCount++) {
                if (bulletCount->checkHitbox(bulletCount->hitbox, enemyCount->dhitbox) == 1) {
                    bulletCount -> destroyBullet();
                    bulletCount = bulletList.erase(bulletCount);
                    enemyCount -> health-=5;
                    enemyCount -> shot=1;
                    break;
                }
            }
            if (enemyCount == enemyList.end()) {
                bulletCount++;
            }
        }
    }
}

void Scenery::enemies(std::vector <Enemy> &enemyList, Player &player){
    std::vector <Enemy> :: iterator enemyCount;
    for (enemyCount = enemyList.begin(); enemyCount!=enemyList.end(); ){
        if (enemyCount -> health > 0){
        enemyCount -> prevCoordinates(*enemyCount);
        
        //player1.collisionMove(player1, *enemyCount);
        enemyCount -> enemyMovement(*enemyCount, player);
        enemyCount -> frameUpdate(*enemyCount, player);
        //player1.enemyCollision(*enemyCount, player1, enemyCount -> target);

        enemyCount -> dhitbox.x = enemyCount -> x+32;
        enemyCount -> dhitbox.y = enemyCount -> y+10;
        
        if (enemyCount -> target <= 60 && enemyCount -> cooldown == 0) {
            player.health-=5;
            player.shot=1;
            enemyCount -> cooldown=1;
        }
        else if (enemyCount -> cooldown == 140) enemyCount -> cooldown = 0;
        else if (enemyCount -> cooldown > 0) enemyCount -> cooldown = enemyCount -> cooldown + 1;
        
        if (enemyCount -> shot !=0){
            enemyCount -> shot = enemyCount -> shot + 1;
            if (enemyCount -> shot == 70) enemyCount -> shot = 0;
        }

        enemyCount++;
        }
        else {
            enemyCount -> destroyEnemy();
            enemyCount = enemyList.erase(enemyCount);
        }
    }

}



void Scenery::renderWay(SDL_Renderer *r, Player &player1, Ground &ground, Arena &thearena, Arena &uparena, Door &door, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int textOpacity, bool shooting){
    ground.Draw(r);  
    if (player1.y < thearena.hitbox.y){
        uparena.Draw(r);
        player1.Draw(r, player1.sprite_dir, player1.sprite_frame, shooting, scene);
        SDL_SetTextureAlphaMod(thearena.current, thearena.opacity);
        thearena.Draw(r);
        SDL_SetTextureAlphaMod(door.current, thearena.opacity);
        door.Draw(r, scene);
    }
    else {
        uparena.Draw(r);
        SDL_SetTextureAlphaMod(thearena.current, thearena.opacity);
        thearena.Draw(r);
        SDL_SetTextureAlphaMod(door.current, thearena.opacity);
        door.Draw(r, scene);
        player1.Draw(r, player1.sprite_dir, player1.sprite_frame, shooting, scene);
    }
    
    SDL_SetTextureAlphaMod(text.at(0), textOpacity);
    SDL_RenderCopy(r, text.at(0), NULL, &(rect.at(0)));

    transition(r);
}

void Scenery::renderArena(SDL_Renderer *r, Player &player1, Background &background, Ground &ground, Wall &wall1, std::vector <Enemy> &enemyList, std::vector <Bullet> &bulletList, Door &door, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, int textOpacity, int loseOpacity, bool shooting){
    std::vector <Enemy> :: iterator enemyCount;
    std::vector <Bullet> :: iterator bulletCount;
    background.Draw(r);
    ground.Draw(r);
    wall1.Draw(r);
    door.Draw(r, scene);
    enemyCount -> sortEnemy(enemyList);
    if (enemyList.size()>0){
        for (enemyCount = enemyList.begin(); enemyCount!=enemyList.end(); enemyCount++)
            if (player1.y > enemyCount -> y)
                enemyCount -> Draw(r, enemyCount -> sprite_dir_enemy, enemyCount -> sprite_frame_enemy, scene);
        player1.Draw(r, player1.sprite_dir, player1.sprite_frame, shooting, scene);
        for (enemyCount = enemyList.begin(); enemyCount!=enemyList.end(); enemyCount++)
            if (player1.y <= enemyCount -> y)
                enemyCount -> Draw(r, enemyCount -> sprite_dir_enemy, enemyCount -> sprite_frame_enemy, scene);
    }
    else player1.Draw(r, player1.sprite_dir, player1.sprite_frame, shooting, scene);

    if (bulletList.size()>0){
        for (bulletCount = bulletList.begin(); bulletCount!=bulletList.end(); bulletCount++)
            bulletCount -> Draw(r);   
    }
    
    wall1.Draw2(r);

    SDL_SetTextureAlphaMod(text.at(0), textOpacity);
    SDL_RenderCopy(r, text.at(0), NULL, &(rect.at(0)));

    SDL_SetTextureAlphaMod(text.at(11), loseOpacity);
    SDL_RenderCopy(r, text.at(11), NULL, &(rect.at(17)));

    transition(r);
}

void Scenery::renderMenu(SDL_Renderer *r, Player &player, std::vector<SDL_Rect> &rect, std::vector<SDL_Texture*> &text, SDL_Point mousePoint, Ground &ground, std::vector <std::string> &fileContent, char nickname[]){
    TTF_Init();
    TTF_Font *megaSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 70);
    TTF_Font *menuSans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 50);
    TTF_Font *Sans = TTF_OpenFont("fonts/open-sans/PublicPixel.ttf", 30);
    ground.Draw(r);
    if (state==0 || state==5){
        SDL_RenderCopy(r, text.at(15), NULL, &(rect.at(24)));
        
        if (SDL_PointInRect(&mousePoint, &(rect.at(2)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(2)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(2)));
        }
        if (SDL_PointInRect(&mousePoint, &(rect.at(4)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(4)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(4)));
        }
        if (SDL_PointInRect(&mousePoint, &(rect.at(6)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(6)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(6)));
        }
        SDL_RenderCopy(r, text.at(1), NULL, &(rect.at(1)));
        SDL_RenderCopy(r, text.at(2), NULL, &(rect.at(3)));
        SDL_RenderCopy(r, text.at(3), NULL, &(rect.at(5)));
        
    }
    else if (state==1){
        SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
        SDL_RenderFillRect(r, &(rect.at(7)));

        if ((rect.at(23)).w<=50)
            (rect.at(23)).x=518;
        else if ((rect.at(23)).w>50)
            (rect.at(23)).x=543-((rect.at(23)).w/50)*25;

        SDL_Surface *nicknameSurface = TTF_RenderText_Solid(menuSans, nickname, SDL_Color({255, 255, 255}));
        SDL_Texture *nicknameTexture = SDL_CreateTextureFromSurface(r, nicknameSurface);
        SDL_FreeSurface(nicknameSurface);
        
        SDL_QueryTexture(nicknameTexture, NULL, NULL, &(rect.at(23)).w, &(rect.at(23)).h);
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderCopy(r, nicknameTexture, NULL, &(rect.at(23))); 

        SDL_RenderCopy(r, text.at(5), NULL, &(rect.at(9))); 
        SDL_RenderCopy(r, text.at(4), NULL, &(rect.at(8))); 

        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(15)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(15)));
        }
        SDL_RenderCopy(r, text.at(9), NULL, &(rect.at(14))); 
    }
    else if (state==2){
        if (SDL_PointInRect(&mousePoint, &(rect.at(10)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(10)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(10)));
        }
        (rect.at(10)) = {565, 155, 300, 300};
        if (SDL_PointInRect(&mousePoint, &(rect.at(10)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(10)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(10)));
        }
        (rect.at(10)) = {215, 155, 300, 300};

        SDL_RenderCopy(r, text.at(6), NULL, &(rect.at(11))); 
        (rect.at(11)).x+=350;
        SDL_RenderCopy(r, text.at(6), NULL, &(rect.at(11))); 
        (rect.at(11)).x-=350;
        SDL_RenderCopy(r, text.at(7), NULL, &(rect.at(12))); 
        SDL_RenderCopy(r, text.at(8), NULL, &(rect.at(13))); 

        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(15)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(15)));
        }
        SDL_RenderCopy(r, text.at(9), NULL, &(rect.at(14))); 
    }
    else if (state==3){
        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(15)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(15)));
        }
        SDL_RenderCopy(r, text.at(9), NULL, &(rect.at(14))); 

        for (int i = 1; i <= 5; i++){
            std::string placeNum = std::to_string(i);
            SDL_Surface *placeSurface;
            placeSurface = TTF_RenderText_Solid(megaSans, placeNum.c_str(), SDL_Color({255, 255, 255}));
            text.at(10) = SDL_CreateTextureFromSurface(r, placeSurface);
            SDL_FreeSurface(placeSurface);
            SDL_RenderCopy(r, text.at(10), NULL, &(rect.at(16)));
            (rect.at(16)).y+=90;
            SDL_DestroyTexture(text.at(10));
        }
        (rect.at(16)).y=50;

        int line=1;
        std::string content;
        SDL_Rect scoresRect;

        for (int i=0; i<10; i++){
            SDL_Surface *scoresSurface;
            scoresSurface = TTF_RenderText_Blended(Sans, fileContent[i].c_str(), SDL_Color({255, 255, 255}));
            SDL_Texture *scoresText = SDL_CreateTextureFromSurface(r, scoresSurface);
            SDL_FreeSurface(scoresSurface);
            
            if (line==1){
            scoresRect.x = 402;
            scoresRect.y = 55;
            scoresRect.w-=70;
            }
            else if (line%2==0){
                scoresRect.y+=35;
            }
            else if (line%2==1){
                scoresRect.y+=55;
            }
            
            SDL_QueryTexture(scoresText, NULL, NULL, &scoresRect.w, &scoresRect.h);
            SDL_RenderCopy(r, scoresText, NULL, &scoresRect);
            SDL_DestroyTexture(scoresText);
            line++;
            
        }
        scoresRect.y = 90;
    }
    else if (state==4 || state==6){
        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
            SDL_RenderFillRect(r, &(rect.at(15)));
        }
        else {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            SDL_RenderDrawRect(r, &(rect.at(15)));
        }
        SDL_RenderCopy(r, text.at(9), NULL, &(rect.at(14))); 
        SDL_RenderCopy(r, text.at(12), NULL, &(rect.at(18)));
        SDL_RenderCopy(r, player.img, &(rect.at(19)), &(rect.at(20)));
        SDL_RenderCopy(r, text.at(13), NULL, &(rect.at(22)));
        SDL_RenderCopy(r, text.at(14), NULL, &(rect.at(21)));
        
    }
    transition(r);

    
    TTF_CloseFont(megaSans);
    TTF_CloseFont(menuSans);
    TTF_CloseFont(Sans);
}

void Scenery::shotClick(SDL_Renderer *r, Player &player1, std::vector <Bullet> &bulletList, Mouse &m, bool &shooting, int &ishoot, bool l, bool ri){
    shooting=1;
    ishoot=1;
    if (l==0 && ri==0){
        if (m.x < player1.cx)
            player1.sprite_dir=SPRITE_SIZE;
        else if (m.x > player1.cx)
            player1.sprite_dir=SPRITE_SIZE*2;        
    }

    float ex, ey;
    if (player1.sprite_dir==SPRITE_SIZE){
        ex = player1.x+14;
        ey = player1.y+28;
    }
    else if (player1.sprite_dir==SPRITE_SIZE*2){
        ex = player1.x+62;
        ey = player1.y+28;
    }

    float angle=-atan2(ey - m.y, ex - m.x)-(3.141/2);
    bulletList.push_back(Bullet(r, ex, ey, angle));
}

void Scenery::buttonClick(SDL_Point mousePoint, std::vector<SDL_Rect> &rect, int &pressed, bool &running){
    if (state==0 || state==5){
        if (SDL_PointInRect(&mousePoint, &(rect.at(2)))){
            pressed=1;
        }
        else if (SDL_PointInRect(&mousePoint, &(rect.at(4)))){
            pressed=2;
        }
        else if (SDL_PointInRect(&mousePoint, &(rect.at(6)))){
            running=false;
        }
    }
    else if (state==1 || state==3 || state==4 ||state==6){
        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            pressed=2;
        }
    }
    else if (state==2){
        if (SDL_PointInRect(&mousePoint, &(rect.at(10)))){
            pressed=1;
        }
        (rect.at(10)) = {565, 155, 300, 300};
        if (SDL_PointInRect(&mousePoint, &(rect.at(10)))){
            pressed=2;
        }
        (rect.at(10)) = {215, 155, 300, 300};
        if (SDL_PointInRect(&mousePoint, &(rect.at(15)))){
            pressed=3;
        }
    }
}


void Scenery::enemyReset(std::vector <Enemy> &enemyList){
    std::vector <Enemy> :: iterator enemyCount;
    for (enemyCount = enemyList.begin(); enemyCount!=enemyList.end();){
        enemyCount -> destroyEnemy();
        enemyCount = enemyList.erase(enemyCount);
    }
}

void Scenery::bulletReset(std::vector <Bullet> &bulletList){
    std::vector <Bullet> :: iterator bulletCount;
    for (bulletCount = bulletList.begin(); bulletCount!=bulletList.end();){
        bulletCount -> destroyBullet();
        bulletCount = bulletList.erase(bulletCount);
    }
}