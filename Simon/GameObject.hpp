//
//  GameObject.hpp
//  Simon
//
//  Created by Karnbongkot Boonriong on 14/4/2563 BE.
//  Copyright © 2563 Karnbongkot Boonriong. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Jobs {
public:
    Jobs(string t = "None",int s = 0,int w = 0):title(t),salary(s),workExp(w){}
    void promotion(SDL_Renderer* renderer);
    void setSalary(int newSalary);
    void setExp(int newExp);
    int getSalary() const;
    int getExp() const;
private:
    string title;
    int salary;
    int workExp;
};
class Simon;
class Animals{
public:
    Animals(const char* path="",string name="",int x=0,int y=0,SDL_Renderer* ren = nullptr);
    ~Animals();
    virtual int action(Simon* s);
    Jobs getJobs() const;
    int getMoney() const;
    void setMoney(int m);
    virtual void update(bool& end);
    virtual void render();
    string name;
    SDL_Rect* getRect();
    SDL_Texture* objTexture;
    bool single = true;
    friend class Jobs;
protected:
    int happiness;
    Jobs jobs;
    int money;
    int xpos;
    int ypos;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};

class Map;

class Components{
public:
    Components(const char* path="",int x=0,int y=0,SDL_Renderer* ren=nullptr,int w=0,int h=0);
    ~Components();
    void render();
    SDL_Rect* getRect();
protected:
    string name;
    int xpos;
    int ypos;
    int width;
    int height;
    SDL_Texture* OutsideTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer = nullptr;
};
class Simon;

class Human : public Animals {
public:
    Human(const char* path="",string n="",int x=0,int y=0,int h=0,SDL_Renderer* ren=nullptr);
    int action(Simon* s);
    void render();
    void update(bool& end);
};


class Dogs : public Animals {
public:
    Dogs(const char* path="",string n="",int x=0,int y=0,Human h = Human(),SDL_Renderer* ren=nullptr,int hand =0,int s=0);
    void beMyGirlfriend(Simon* s);
    void setOwner(Human h){
        owner = h;
    }
    int getHandsome(){
        return handsome;
    }
    int getStrength(){
        return strength;
    }
    int action(Simon* s);
    void render();
protected:
    Human owner;
    int handsome,strength;
    char* pathm;
};

class Bua : public Human {
public:
    Bua(const char* path="",string n="",int x=0,int y=0,int h=0,SDL_Renderer* ren=nullptr);
    void render();
};

class ThingsForSale;

class Simon : public Dogs{
public:
    Simon(const char* path="",string n="",int x=0,int y=0,Human h = Human(),SDL_Renderer* ren=nullptr,int ha=100,int e = 100);
    void moveX(int x);
    void moveY(int y);
    void goBack();
    void update(bool& end1);
    void render();
    void setHS(int h,int s);
    void goToWork();
    void setEnergy(int e);
    void setHappiness(int h);
    void setGF(Dogs gf){
        girlfriend = gf;
    }
    int getEnergy(){
        return energy;
    }
    int getHappiness(){
        return happiness;
    }
    void setPosition();
    int giveSnacks();
    friend class ThingsForSale;
private:
    int energy;
    int tempx,tempy;
    Dogs girlfriend;
    SDL_Rect gfsrcRect,gfdestRect;
    map<string,int> inventory;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

class Furniture : public Components{
    public:
        Furniture(const char* path="",int x=0,int y=0,SDL_Renderer* ren=nullptr,int h=0,int s=0,int p =0,int e = 0,int ha=0,int w=0,int hi=0,bool c = false);
        virtual int use(Simon* s);
    bool canUse(){
        return canBeUsed;
    }
    protected:
        int priceForUse;
        int handsome;
        int strength;
        int energy;
        int happiness;
    bool canBeUsed;
};

class ThingsForSale : public Furniture{
public:
    ThingsForSale(const char* path="",string n = "",int x=0,int y=0,SDL_Renderer* ren=nullptr,int p=0,int w=0,int hi=0): Furniture(path,x,y,ren,0,0,p,w,hi,true),name(n){
        width = w;
        height = hi;
        canBeUsed = true;
    }
    int use(Simon* s);
    string getName();
private:
    string name;
};

class Game;

class Place : public Components {
public:
    Place(const char* Inside="",const char* Outside="",int x=0,int y=0,SDL_Renderer* ren=nullptr,int w=0,int h=0, string n="");
    virtual int enter(Map *m);
    void renderInside();
    void addFurniture(Furniture* f);
    void addAnimals(Animals* a);
    void addPlaces(Place* p);
    friend class Game;
    friend class Map;
private:
    SDL_Texture* InsideTexture;
    vector<Animals*> listOfAnimals;
    vector<Furniture*> listOfFurniture;
    vector<Place*> listOfPlaces;
};

class WorkPlace : public Place{
    public :
    WorkPlace(const char* Inside="",const char* Outside="",int x=0,int y=0,SDL_Renderer* ren=nullptr,int w=0,int h = 0):Place(Inside,Outside,x,y,ren,w,h,""){}
    int enter(Map* m);
};

class Map{
public:
    Map();
    ~Map();
    void DrawMap();
    friend class Place;
    friend class Game;
    Simon* s;

private:
    Place*  currentPlace;
    SDL_Rect src,dest;
    SDL_Texture* background;
};







#endif /* GameObject_hpp */
