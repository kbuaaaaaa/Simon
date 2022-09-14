//
//  GameObject.cpp
//  Simon
//
//  Created by Karnbongkot Boonriong on 14/4/2563 BE.
//  Copyright © 2563 Karnbongkot Boonriong. All rights reserved.
//
#include "GameObject.hpp"
using namespace std;
enum Food{One,Two,Three,Four,Five};


void Draw(SDL_Texture* tex,SDL_Rect src,SDL_Rect dest,SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, tex, &src, &dest);
}
void createText(const char* text,int x,int y,SDL_Renderer* renderer,int size){
    TTF_Font *Font = TTF_OpenFont("/Library/Fonts/TI-NspireBd.ttf", size);
    SDL_Color textColor = { 0 , 0, 0, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(Font, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    TTF_CloseFont(Font);
    SDL_Rect textRect,srcRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    srcRect.w = textRect.w;
    srcRect.h = textRect.h;
    srcRect.x = x;
    srcRect.y = y;
    SDL_FreeSurface(textSurface);
    Draw(textTexture, textRect, srcRect, renderer);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* Loadtexture(const char* texture,SDL_Renderer* renderer){
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
//Animals class
Animals::Animals(const char* path,string n,int x,int y,SDL_Renderer* ren){
    renderer=ren;
    objTexture =Loadtexture(path,renderer);
    xpos = x;
    ypos = y;
    name = n;
    srcRect.h = 200;
    srcRect.w = 200;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = xpos;
    destRect.y = ypos;
}
Animals::~Animals(){
}
void Animals::render(){
    Draw(objTexture,srcRect, destRect,renderer);
}
Jobs Animals::getJobs() const {
    return jobs;
}
int Animals::getMoney() const{
    return money;
}
void Animals::setMoney(int m){
    money+=m;
}
SDL_Rect* Animals::getRect(){
    return &destRect;
}
void Animals::update(bool& end){

}
int Animals::action(Simon* s){
    return 1;
}


//Jobs class
void Jobs::promotion(SDL_Renderer* renderer){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png",renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Promoted!", 100, 455, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.key.keysym.sym == SDLK_SPACE) {
        return;
    }
}
void Jobs::setSalary(int newSalary){
    salary += newSalary;
}
void Jobs::setExp(int newExp){
    workExp = this->getExp()+newExp;
}
int Jobs::getSalary() const{
    return salary;
}
int Jobs::getExp() const{
    return workExp;
}






//Simon

Uint32 ticks = 0;
Simon::Simon(const char* path,string n,int x,int y,Human h,SDL_Renderer* ren,int ha,int e):Dogs(path,n,x,y,h,ren){
    renderer =ren;
    happiness = ha;
    energy = e;
    xpos = x;
    ypos = y;
    tempx = x;
    tempy = y;
    handsome =0;
    strength =0;
    money=0;
    jobs = Jobs("House Guard",100,0);
    inventory["One"] = 0;
    inventory["Two"] = 0;
    inventory["Three"] = 0;
    inventory["Four"] = 0;
    inventory["Five"] = 0;
    inventory["Six"] = 0;
    inventory["Seven"] = 0;
    inventory["Eight"] = 0;
    inventory["Nine"] = 0;
    inventory["Ten"] = 0;
}


void Simon::moveX(int x){
    static bool lastMoveR;
    if (lastMoveR==false and x>0){
            flip = SDL_FLIP_HORIZONTAL;

    }
    else if (lastMoveR==true and x<0){

            flip = SDL_FLIP_NONE;
    }
    tempx = xpos;
    xpos += x;
    if (xpos >= 800 or xpos<=0) {
        goBack();
    }
    if (x>=0) {
        lastMoveR = true;
    }
    else
        lastMoveR = false;
    
}
void Simon::moveY(int y){
    tempy=ypos;
    ypos+=y;
    if (ypos<=0 or ypos>=480) {
        goBack();
    }
}
void Simon::goBack(){
    xpos = tempx;
    ypos = tempy;
}

void Simon::update(bool& end1){
        ticks++;
        Uint32 seconds = ticks/10;
    if (ticks%100 == 0 && single == true) {
        happiness-=1;
    }
    if (happiness == 0) {
        end1 = true;
    }
        Uint32 sprite1 = seconds % 18;
        Uint32 sprite2 = seconds % 20;
        srcRect.h = 142;
        srcRect.w = 178;
    srcRect.x = sprite1*178;
        srcRect.y = 0;
        destRect.h = srcRect.h; 
        destRect.w = srcRect.w;
        destRect.x = xpos;
        destRect.y = ypos;
    if (!single) {
        gfsrcRect.h = 150;
        gfsrcRect.w = 168;
        gfsrcRect.x = sprite2*168;
        gfsrcRect.y = 0;
        gfdestRect.h = gfsrcRect.h;
        gfdestRect.w = gfsrcRect.w;
        gfdestRect.x = xpos + 100;
        gfdestRect.y = ypos;
    }
}

void Simon::render(){
    SDL_Rect barRect,srcbarRect;
    barRect.w = 1000;
    barRect.h = 30;
    barRect.x = 0;
    barRect.y = 0;
    srcbarRect.w = 1000;
    srcbarRect.h = 30;
    srcbarRect.x = 0;
    srcbarRect.y =0;
    Draw(Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/TextBar.png", renderer), barRect, srcbarRect, renderer);
    createText("Handsome Boi : ", 5, 0, renderer,20);
    createText(to_string(handsome).c_str(), 150, 0, renderer,20);
    createText("Strong Boi : ", 205, 0, renderer,20);
    createText(to_string(strength).c_str(), 350, 0, renderer,20);
    createText("Money : ", 405, 0, renderer,20);
    createText(to_string(money).c_str(), 550, 0, renderer,20);
    createText("Happy Boi : ", 605, 0, renderer,20);
    createText(to_string(happiness).c_str(), 750, 0, renderer,20);
    createText("Energy : ", 805, 0, renderer,20);
    createText(to_string(energy).c_str(), 950, 0, renderer,20);
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, NULL, flip);
    if (!single) {
        if (flip == SDL_FLIP_HORIZONTAL) {
            gfdestRect.x = xpos-100;
        }
        SDL_RenderCopyEx(renderer, girlfriend.objTexture, &gfsrcRect, &gfdestRect, 0, NULL, flip);
    }
}

void Simon::setHS(int h,int s){
    handsome += h;
    strength += s;
}


void Simon::goToWork(){
    if (energy>=20) {
        energy -= 20;
        money += jobs.getSalary();
        jobs.setExp(20);
        if (jobs.getExp()==100) {
            jobs.setSalary(100);
            jobs.promotion(renderer);
            jobs.setExp(-100);
        }
    }
    else{
        SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png",renderer);
        SDL_Rect textRect,textDestRect;
        textRect.h = 200;
        textRect.w = 1000;
        textRect.x = 0;
        textRect.y = 0;
        textDestRect.h = textRect.h;
        textDestRect.w = textRect.w;
        textDestRect.x = 0;
        textDestRect.y = 440;
        Draw(textBox, textRect, textDestRect, renderer);
        createText("Not enough energy.", 100, 455, renderer,30);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        if (event.key.keysym.sym == SDLK_SPACE) {
            return;
        }
    }
}

void Simon::setPosition(){
    xpos = 450;
    ypos = 480;
    tempx = 450;
    tempy = 480;
    destRect.x = xpos;
    destRect.y = ypos;
}

int Simon::giveSnacks(){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Which one should I give Bua ?", 100, 455, renderer,30);
    createText("1. Ice-cream Crepe : ",100, 480, renderer,30);
    createText(to_string(inventory["One"]).c_str(), 400, 480, renderer,30);
    createText("2. Chocolate Cake : ", 100, 505, renderer,30);
    createText(to_string(inventory["Two"]).c_str(), 400, 505, renderer,30);
    createText("3. Sorbet : ", 100, 530, renderer,30);
    createText(to_string(inventory["Three"]).c_str(), 400, 530, renderer,30);
    createText("4. Sponge Cake : ", 100, 555, renderer,30);
    createText(to_string(inventory["Four"]).c_str(), 400, 555, renderer,30);
    createText("5. Fruit Tart : ", 100, 580, renderer,30);
    createText(to_string(inventory["Five"]).c_str(), 400, 580, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    static Food choose = One;
    bool inLoop = true;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_1:
            choose = One;
            inLoop = false ;
            break;
        case SDLK_2:
            choose = Two;
            inLoop = false ;
            break;
        case SDLK_3:
            choose = Three;
            inLoop = false ;
            break;
        case SDLK_4:
            choose = Four;
            inLoop = false ;
            break;
        case SDLK_5:
            choose = Five;
            inLoop = false ;
            break;
        default:
            break;
    }

    if (!inLoop) {
        switch (choose) {
            case One:
                if ( inventory["One"] > 0) {
                    inventory["One"] -= 1;
                    return 10;
                }
                else{
                    Draw(textBox, textRect, textDestRect, renderer);
                    createText("No food in inventory.", 100, 455, renderer,30);
                    SDL_RenderPresent(renderer);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        return 0;
                    }
                }
                break;
            case Two:
                if (inventory["Two"] > 0) {
                    inventory["Two"] -= 1;
                    return 20;
                }
                else{
                    Draw(textBox, textRect, textDestRect, renderer);
                    createText("No food in inventory.", 100, 455, renderer,30);
                    SDL_RenderPresent(renderer);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        return 0;
                    }
                }
                break;
            case Three:
                if (inventory["Three"] > 0) {
                    inventory["Three"] -= 1;
                    return 30;
                }
                else{
                    Draw(textBox, textRect, textDestRect, renderer);
                    createText("No food in inventory.", 100, 455, renderer,30);
                    SDL_RenderPresent(renderer);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        return 0;
                    }
                }
                break;
            case Four:
                if (inventory["Four"] > 0) {
                    inventory["Four"] -= 1;
                    return 40;
                }
                else{
                    Draw(textBox, textRect, textDestRect, renderer);
                    createText("No food in inventory.", 100, 455, renderer,30);
                    SDL_RenderPresent(renderer);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        return 0;
                    }
                }
                break;
            case Five:
                if (inventory["Five"] > 0) {
                    inventory["Five"] -= 1;
                    return 50;
                }
                else{
                    Draw(textBox, textRect, textDestRect, renderer);
                    createText("No food in inventory.", 100, 455, renderer,30);
                    SDL_RenderPresent(renderer);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    SDL_WaitEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        return 0;
                    }
                }
                break;
        }
    }
    return 0;
}

void Simon::setHappiness(int h){
    if (happiness<100) {
        if (h+happiness>100) {
            happiness+=100-(happiness+h);
        }
        happiness+=h;
    }
}
void Simon::setEnergy(int e){
    if (energy<100) {
        if (e+energy>100) {
            energy += 100 - (energy+ e);
        }
        else
            energy += e;
    }
    else if (e<0){
        energy+=e;
    }
    
}

//Dogs
Dogs::Dogs(const char* path,string n,int x,int y,Human h,SDL_Renderer* ren,int hand,int s):Animals(path,n,x,y,ren),owner(h){
    handsome = hand;
    strength =s ;
    pathm = (char*)path;
    srcRect.h = 150;
    srcRect.w = 168;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = xpos;
    destRect.y = ypos;
}
void Dogs::beMyGirlfriend(Simon* s){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    SDL_Event event;
    if (s->handsome >= handsome && s->strength >= strength) {
        Dogs temp(pathm,name,xpos,ypos,owner,renderer,handsome,strength);
        s->setGF(temp);
        s->setHappiness(100 - s->getHappiness());
        single = false;
        s->single = false;
    }
    else{
        Draw(textBox, textRect, textDestRect, renderer);
        createText("Not handsome/strong enough.", 100, 455, renderer,30);
        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        if (event.key.keysym.sym == SDLK_SPACE) {
            return;
        }
    }
}

void Dogs::render(){
    if (single) {
        Draw(objTexture,srcRect, destRect,renderer);
    }
}

int Dogs::action(Simon* s){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Cute Dog : Hi!", 100, 470, renderer,30);
    createText("< Do you want to be my girlfriend ?", 100, 500, renderer,30);
    createText(" Hi !>", 600, 500, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    static bool yes = false;
    bool inLoop = true;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:
            yes = true;
            inLoop = false ;
            break;
        case SDLK_RIGHT:
            yes = false;
            inLoop = false ;
            break;
    }
    if (inLoop == 0) {
        if (yes) {
            beMyGirlfriend(s);
        }
        return 0;
    }
    return 1;
}

//Human
Human::Human(const char* path,string n,int x,int y,int h,SDL_Renderer* ren){
    renderer =ren;
    Animals(path,n,x,y,renderer);
    happiness = h;
    xpos = x;
    ypos = y;
    
}


int Human::action(Simon* s){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Give food ?", 100, 470, renderer,30);
    createText("< Yes", 100, 500, renderer,30);
    createText(" Nah >", 600, 500, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    static bool yes = false;
    bool inLoop = true;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:
            yes = true;
            inLoop = false ;
            break;
        case SDLK_RIGHT:
            yes = false;
            inLoop = false ;
            break;
    }
    if (inLoop == 0) {
        if (yes) {
            happiness+= s->giveSnacks();
        }
        return 0;
    }
    return 1;
}


void Human::render(){
    srcRect.h = 295;
    srcRect.w = 300;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = 0;
    destRect.y = 350;
    Draw(objTexture, srcRect, destRect, renderer);
    createText("Happiness : ", 10, 580, renderer, 30);
    createText(to_string(happiness).c_str(), 200, 580, renderer, 30);
}

void Human::update(bool& end2){
    if (happiness >= 100) {
        end2 = true;
    }
}

//Bua
Bua::Bua(const char* path,string n,int x,int y,int h,SDL_Renderer* ren){
    objTexture = Loadtexture(path, ren);
    renderer = ren;
    happiness=h;
    Human("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bua.png","Bua",0,0,0,ren);
    single = true;
    jobs = Jobs("Lazy Girl",0,0);
}

void Bua::render(){
    Human::render();
}

//Place
Place::Place(const char* inside,const char* outside,int x,int y,SDL_Renderer* ren,int w,int h,string n){
    Components(outside,x,y,ren,w,h);
    name = n;
    width = w;
    height = h;
    renderer=ren;
    InsideTexture = Loadtexture(inside,renderer);
    OutsideTexture = Loadtexture(outside,renderer);
    xpos = x;
    ypos = y;
}

void Place::renderInside(){
    srcRect.w = 1000;
    srcRect.h = 623;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = 1000;
    destRect.h = 623;
    destRect.x=0;
    destRect.y=0;
    Draw(InsideTexture, srcRect, destRect,renderer);
    srcRect.w = width;
    srcRect.h = height;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = width;
    destRect.h = height;
    destRect.x=0;
    destRect.y=0;
    
}


int Place::enter(Map* m){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Enter ", 100, 470, renderer,30);
    createText(name.c_str(), 180, 470, renderer,30);
    createText(" ?", 400, 470, renderer,30);
    createText("< Yes", 100, 500, renderer,30);
    createText("No >", 400, 500, renderer,30);
    SDL_RenderPresent(renderer);
    bool inLoop = true;
    static bool yes = false;
    SDL_Event event;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:
            yes = true;
            inLoop = false ;
            break;
        case SDLK_RIGHT:
            yes = false;
            inLoop = false ;
            break;
    }
    if (inLoop == false) {
        if(yes){
            m->currentPlace = this;
            m->s->setPosition();
        }
        return 0;
    }
    return 1;
}

void Place::addFurniture(Furniture* f){
    listOfFurniture.push_back(f);
}
void Place::addAnimals(Animals* a){
    listOfAnimals.push_back(a);
}

void Place::addPlaces(Place* p){
    listOfPlaces.push_back(p);
}

//WorkPlace
int WorkPlace::enter(Map* m){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Go to work ?", 100, 470, renderer,30);
    createText("< Yes", 100, 500, renderer,30);
    createText("No >", 400, 500, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    bool inLoop = true;
    static bool yes = false;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:yes = true;inLoop = false ; break;
        case SDLK_RIGHT: yes = false;inLoop = false ; break;
    }
    if (inLoop == 0) {
        if(yes)
            m->s->goToWork();
        return 0;
    }
    return 1;
}




//Map
Map::Map(){
}

Map::~Map(){
    
}

void Map::DrawMap(){
    currentPlace->renderInside();
    for(Furniture* f : currentPlace->listOfFurniture){
        f->render();
    }
    for (Animals* a : currentPlace->listOfAnimals) {
        if (a->single) {
            a->render();
        }
    }
    for (Place* p : currentPlace->listOfPlaces) {
        p->render();
    }

}



//Components
Components::Components(const char* path,int x,int y,SDL_Renderer* ren,int w,int h){
    renderer=ren;
    OutsideTexture = Loadtexture(path,renderer);
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    srcRect.w = width;
    srcRect.h = height;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = width;
    destRect.h = height;
    destRect.x = 0;
    destRect.y = 0;

}

void Components::render(){
    srcRect.w = width;
    srcRect.h =height;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = width;
    destRect.h = height;
    destRect.x = xpos;
    destRect.y = ypos;
    Draw( OutsideTexture, srcRect, destRect,renderer);
}

SDL_Rect* Components::getRect(){
    return &destRect;
}

Components::~Components(){
    
}

//Furniture
Furniture::Furniture(const char* path,int x,int y,SDL_Renderer* ren,int h,int s,int p,int e,int ha,int w,int hi,bool c){
    Components(path,x,y,ren,w,hi);
    canBeUsed = c;
    energy = e;
    happiness = ha;
    width = w;
    height = hi;
    priceForUse = p;
    handsome = h;
    strength = s;
    renderer=ren;
    OutsideTexture = Loadtexture(path,renderer);
    xpos = x;
    ypos = y;
    srcRect.w = w;
    srcRect.h = hi;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    destRect.x = xpos;
    destRect.y = ypos;

}

int Furniture::use(Simon* s){
    if (!canBeUsed) {
        return 0;
    }
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Price for use : ", 100, 470, renderer,30);
    createText(to_string(priceForUse).c_str(), 300, 470, renderer, 30);
    createText("< Use", 100, 500, renderer,30);
    createText(" Nah >", 600, 500, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    static bool yes = false;
    bool inLoop = true;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:
            yes = true;
            inLoop = false ;
            break;
        case SDLK_RIGHT:
            yes = false;
            inLoop = false ;
            break;
    }
    if (inLoop == 0) {
        if (yes) {
             if (s->getMoney() >= priceForUse && s->getEnergy() >= (energy*-1)) {
                s->setMoney(-1*priceForUse);
                s->setHS(handsome, strength);
                s->setEnergy(energy);
                s->setHappiness(happiness);
            }
             else{
                 Draw(textBox, textRect, textDestRect, renderer);
                 createText("Not enough money/energy.", 100, 455, renderer,30);
                 SDL_RenderPresent(renderer);
                 SDL_WaitEvent(&event);
                 SDL_WaitEvent(&event);
                 SDL_WaitEvent(&event);
                 if (event.key.keysym.sym == SDLK_SPACE) {
                     return 0;
                 }
             }
        }
        return 0;
    }
    return 1;
}

//ThingsForSale
int ThingsForSale::use(Simon* s){
    SDL_Texture* textBox = Loadtexture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Textbox.png", renderer);
    SDL_Rect textRect,textDestRect;
    textRect.h = 200;
    textRect.w = 1000;
    textRect.x = 0;
    textRect.y = 0;
    textDestRect.h = textRect.h;
    textDestRect.w = textRect.w;
    textDestRect.x = 0;
    textDestRect.y = 440;
    Draw(textBox, textRect, textDestRect, renderer);
    createText("Price : ", 100, 470, renderer,30);
    createText(to_string(priceForUse).c_str(), 300, 470, renderer, 30);
    createText("< Buy", 100, 500, renderer,30);
    createText(" Nah >", 600, 500, renderer,30);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    static bool yes = false;
    bool inLoop = true;
    SDL_WaitEvent(&event);
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) {
        exit(0);
    }
    switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:
            yes = true;
            inLoop = false ;
            break;
        case SDLK_RIGHT:
            yes = false;
            inLoop = false ;
            break;
    }
    if (inLoop == 0) {
        if (yes) {
             if (s->getMoney() >= priceForUse ) {
                s->setMoney(-1*priceForUse);
                s->inventory[name] += 1;
            }
             else{
                 Draw(textBox, textRect, textDestRect, renderer);
                 createText("Not enough money.", 100, 455, renderer,30);
                 SDL_RenderPresent(renderer);
                 SDL_WaitEvent(&event);
                 SDL_WaitEvent(&event);
                 SDL_WaitEvent(&event);
                 if (event.key.keysym.sym == SDLK_SPACE) {
                     return 0;
                 }
             }
        }
        return 0;
    }
    return 1;
}

