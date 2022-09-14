//
//  Game.cpp
//  Simon
//
//  Created by Karnbongkot Boonriong on 13/4/2563 BE.
//  Copyright © 2563 Karnbongkot Boonriong. All rights reserved.
//

#include "Game.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
Map* m;
Simon* simon;
Bua* bua;
ThingsForSale* One;
WorkPlace* work;
Mix_Music* music;
Mix_Chunk* boink;

Game::Game(){

}

Game::~Game(){
    
}

void Game::startGame(){
    while (1) {
        SDL_Surface* tempSurface = IMG_Load("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Start.png");
        SDL_Texture* textBox = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_Rect textRect,textDestRect;
        textRect.h = 623;
        textRect.w = 1000;
        textRect.x = 0;
        textRect.y = 0;
        textDestRect.h = textRect.h;
        textDestRect.w = textRect.w;
        textDestRect.x = 0;
        textDestRect.y = 0;
        SDL_RenderCopy(renderer, textBox, &textRect, &textDestRect);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.key.keysym.sym == SDLK_SPACE){
            return;
        }
        else if (event.type == SDL_QUIT){
            isRunning = false;
            return;
        }
    }
}

void Game::init(const char* title,int xpos,int ypos,int width,int height,bool fullscreen){
    int flags =0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        TTF_Init();
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,640 );
        music = Mix_LoadMUS("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Song.wav");
        boink = Mix_LoadWAV("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/boink.wav");
        //Mix_PlayMusic(music, -1);
        // Mix_VolumeMusic(20);
        isRunning = true;
        startGame();
    }
    else{
        isRunning = false;
    }
    m = new Map();
    //Create places
    Place* street = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Street.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Exit.png",750,490,renderer,250,137,"the steet");
    Place* park = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Grass.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Park.png",200,35,renderer,305,150,"the park");
    Place* supermarket = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/SupermarketFloor.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Supermarket.png",530,35,renderer,285,150,"the supermarket");
    Place* home = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/HouseFloor.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Home.png",750,420,renderer,206,200,"the house");
    Place* groomer = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/GroomerFloor.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Groomer.png",750,200,renderer,238,200,"the groomer");
    Place* gym = new Place("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/GymFloor.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Gym.png",30,150,renderer,236,250,"the gym");
    WorkPlace* work = new WorkPlace("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Floor.png","/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Work.png",0,420,renderer,279,200);
    //Create home furniture
    bua = new Bua("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bua.png","Bua",0,0,0,renderer);
    Furniture* bed  = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bed.png",30,30,renderer,0,0,0,50,0,300,263,false);
    Furniture* monBed  = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/MonBed.png",350,150,renderer,0,0,0,50,0,100,45,true);
    Furniture* hometable = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Hometable.png",600,100,renderer,0,0,0,50,0,300,228,true);
    Furniture* ball = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Ball.png",100,350,renderer,0,0,0,0,50,50,50,true);
    Furniture* bone = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bone.png",100,450,renderer,0,0,0,0,50,50,89,true);
    //park furniture
    Dogs* dog  = new Dogs("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Dog.png","Simon",400,225,Bua(),renderer,100,100);
    Furniture* tree1 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Tree1.png",20,45,renderer,0,0,0,0,0,200,279,false);
    Furniture* tree2 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Tree2.png",800,45,renderer,0,0,0,0,0,200,261,false);
    Furniture* bench1 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bench.png",200,225,renderer,0,0,0,0,0,200,103,false);
    Furniture* bench2 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bench.png",600,225,renderer,0,0,0,0,0,200,103,false);
    //Shelf
    ThingsForSale* one = new ThingsForSale("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/1.png","One",25,50,renderer,100,250,163);
    ThingsForSale* two = new ThingsForSale("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/2.png","Two",25,250,renderer,200,250,158);
    ThingsForSale* three = new ThingsForSale("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/3.png","Three",25,450,renderer,300,250,137);
    ThingsForSale* four = new ThingsForSale("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/4.png","Four",625,80,renderer,400,250,132);
    ThingsForSale* five = new ThingsForSale("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/5.png","Five",625,280,renderer,500,250,141);
    //groomer furniture
    Furniture* bathtub = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bathtub.png",350,250,renderer,20,0,100,0,0,300,128,true);
    Furniture* table1 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Table.png",80,250,renderer,20,0,100,0,0,200,137,true);
    Furniture* table2 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Table.png",700,250,renderer,20,0,100,0,0,200,137,true);
    Furniture* mirror1 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Mirror.png",650,25,renderer,0,0,0,0,0,300,202,false);
    Furniture* mirror2 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Mirror.png",350,25,renderer,0,0,0,0,0,300,202,false);
    Furniture* mirror3 = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Mirror.png",50,25,renderer,0,0,0,0,0,300,202,false);
    //gym furniture
    Furniture* pool = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Pool.png",0,25,renderer,0,20,100,-20,0,500,251,true);
    Furniture* rings = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Rings.png",575,25,renderer,0,20,100,-20,0,300,200,true);
    Furniture* bars = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Bar.png",25,440,renderer,0,20,100,-20,0,300,186,true);
    Furniture* run = new Furniture("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Run.png",775,300,renderer,0,20,100,-20,0,200,171,true);
    
    
    //Add place
    street->addPlaces(gym);
    street->addPlaces(groomer);
    street->addPlaces(home);
    street->addPlaces(park);
    street->addPlaces(supermarket);
    street->addPlaces(work);
    //Add home furniture
    home->addAnimals(bua);
    home->addFurniture(bed);
    home->addFurniture(monBed);
    home->addFurniture(hometable);
    home->addPlaces(street);
    //Add park furniture
    park->addPlaces(street);
    park->addFurniture(tree1);
    park->addFurniture(tree2);
    park->addFurniture(bench1);
    park->addFurniture(bench2);
    park->addFurniture(ball);
    park->addFurniture(bone);
    park->addAnimals(dog);
    //Add Supermarket furniture
    supermarket->addPlaces(street);
    supermarket->addFurniture(one);
    supermarket->addFurniture(two);
    supermarket->addFurniture(three);
    supermarket->addFurniture(four);
    supermarket->addFurniture(five);
    //Add groomer
    groomer->addPlaces(street);
    groomer->addFurniture(bathtub);
    groomer->addFurniture(table1);
    groomer->addFurniture(table2);
    groomer->addFurniture(mirror1);
    groomer->addFurniture(mirror2);
    groomer->addFurniture(mirror3);
    //Add gym
    gym->addPlaces(street);
    gym->addFurniture(pool);
    gym->addFurniture(rings);
    gym->addFurniture(bars);
    gym->addFurniture(run);
    
    
    
    simon = new Simon("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/Simon.png","Simon",450,480,Bua(),renderer,100,100);

    m->currentPlace = street;
    Currentmap = m;
    m->s = simon;
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  simon->moveX(-10); break;
            case SDLK_RIGHT: simon->moveX(10); break;
            case SDLK_UP:    simon->moveY(-10); break;
            case SDLK_DOWN:  simon->moveY(10); break;
        }
        break;
        default:
            break;
    }
}


void Game::checkCollision(){
    for (Furniture* f : m->currentPlace->listOfFurniture) {
        if(SDL_HasIntersection(simon->getRect(), f->getRect()) && f->canUse()){
            simon->goBack();
            collideFurniture = f;
            Mix_PlayChannel( -1, boink, 0 );
        }
    }
    for (Animals* a : m->currentPlace->listOfAnimals) {
        if (a->single) {
            if(SDL_HasIntersection(simon->getRect(),a->getRect())){
                simon->goBack();
                collideAnimals = a;
                Mix_PlayChannel( -1, boink, 0 );
            }
        }
    }
    for (Place* p: m->currentPlace->listOfPlaces) {
        if(SDL_HasIntersection(simon->getRect(),p->getRect())){
            simon->goBack();
            collidePlace = p;
            Mix_PlayChannel( -1, boink, 0 );
        }
    }
}

void Game::update(){
    simon->update(gameEnd1);
    if (gameEnd1) {
        endGame1();
    }
    bua->update(gameEnd2);
    if (gameEnd2) {
        endGame2();
    }
}

void Game::render(){
    m->DrawMap();
    simon->render();
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(music);
    TTF_Quit();
    SDL_Quit();
}

bool Game::running(){
    return isRunning;
}

void Game::endGame1(){
    while (1) {
        SDL_Surface* tempSurface = IMG_Load("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/End1.png");
        SDL_Texture* textBox = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_Rect textRect,textDestRect;
        textRect.h = 623;
        textRect.w = 1000;
        textRect.x = 0;
        textRect.y = 0;
        textDestRect.h = textRect.h;
        textDestRect.w = textRect.w;
        textDestRect.x = 0;
        textDestRect.y = 0;
        SDL_RenderCopy(renderer, textBox, &textRect, &textDestRect);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        if (event.key.keysym.sym == SDLK_SPACE){
            isRunning = false;
            return;
        }
        else if (event.type == SDL_QUIT){
            isRunning = false;
            return;
        }
    }
}

void Game::endGame2(){
    while (1) {
        SDL_Surface* tempSurface = IMG_Load("/Users/karnbongkotboonriong/Documents/Work/Project/Year 1 Sem 2 C++/Simon/Assets/End2.png");
        SDL_Texture* textBox = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_Rect textRect,textDestRect;
        textRect.h = 623;
        textRect.w = 1000;
        textRect.x = 0;
        textRect.y = 0;
        textDestRect.h = textRect.h;
        textDestRect.w = textRect.w;
        textDestRect.x = 0;
        textDestRect.y = 0;
        SDL_RenderCopy(renderer, textBox, &textRect, &textDestRect);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        SDL_WaitEvent(&event);
        if (event.key.keysym.sym == SDLK_SPACE){
            isRunning = false;
            exit(0);
            return;
        }
    }
}


