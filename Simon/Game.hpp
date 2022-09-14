//
//  Game.hpp
//  Simon
//
//  Created by Karnbongkot Boonriong on 13/4/2563 BE.
//  Copyright © 2563 Karnbongkot Boonriong. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "GameObject.hpp"
using namespace std;

class Animals;

class Game{
public:
    Game();
    ~Game();
    void init(const char* title,int xpos,int ypos,int width,int height,bool fullscreen);
    void handleEvents();
    void update();
    void checkCollision();
    void render();
    void clean();
    bool running();
    void endGame1();
    void endGame2();
    void startGame();
    SDL_Renderer* renderer;
    Animals* collideAnimals = nullptr;
    Furniture* collideFurniture = nullptr;
    Place* collidePlace = nullptr;
    Map* Currentmap;
private:
    int count=0;
    bool isRunning;
    bool gameEnd1 = false;
    bool gameEnd2 = false;
    SDL_bool collision;
    SDL_Window *window;



};



#endif /* Game_hpp */
