//
//  main.cpp
//  Simon
//
//  Created by Karnbongkot Boonriong on 6/4/2563 BE.
//  Copyright © 2563 Karnbongkot Boonriong. All rights reserved.
//
#include "Game.hpp"
#include <iostream>
const int FPS = 50;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;
Game *game = nullptr;
int main( )
{
    game = new Game();
    game->init("Simon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 623, false);
    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        SDL_RenderClear(game->renderer);
        if (game->collideAnimals) {
            game->render();
            int x = game->collideAnimals->action(game->Currentmap->s);
            if (!x) {
                game->collideAnimals = nullptr;
            }
        }
        else if (game->collidePlace){
            game->render();
            int x = game->collidePlace->enter(game->Currentmap);
            if (!x) {
                game->collidePlace = nullptr;
                game->collideFurniture = nullptr;
                game->collideAnimals = nullptr;
            }
        }
        else if (game->collideFurniture){
            game->render();
            int x = game->collideFurniture->use(game->Currentmap->s);
            if (!x) {
                game->collideFurniture = nullptr;
            }
        }
        else{
            game->render();
            SDL_RenderPresent(game->renderer);
        }
        game->checkCollision();
        frameTime = SDL_GetTicks() + frameStart;
        if (frameDelay>frameTime) {
            SDL_Delay(frameDelay-frameTime);
        }
        game->update();;
        
    }
    game->clean();
    return 0;
}
