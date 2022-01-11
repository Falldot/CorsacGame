//
// Created by Falldot on 11.01.2022.
//

#define CORSAC_DEBUG 1
#define CORSAC_EXCEPTIONS_ENABLED 1

#include "Corsac/ecs.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"

void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

void* __cdecl operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

#include <iostream>
#include <conio.h>

corsac::Component<int, int> Position;
corsac::Component<int, int> Direction;
corsac::Component<int> Speed;

corsac::Component<> W;
corsac::Component<> A;
corsac::Component<> S;
corsac::Component<> D;

corsac::Group<Position, Direction, Speed> Transform;

corsac::Group<Transform> Person;

void KeyEventSystem()
{
    while(_kbhit()) {
        char c = _getche();
        for (auto start = Person.begin(), end = Person.end(); start < end; ++start) {
            if (c == 'a') {
                A.add(*start);
            }
            if (c == 'd') {
                D.add(*start);
            }
            if (c == 'w') {
                W.add(*start);
            }
            if (c == 's') {
                S.add(*start);
            }
        }
    }
}

void WMovebleEvent()
{
    for(auto start = W.begin(), end = W.end(); start < end; ++start)
    {
        if(Direction.has(*start))
            corsac::Entity<>(*start).fit<Direction>(0, -1).remove<W>();
    }
}

void SMovebleEvent()
{
    for(auto start = S.begin(), end = S.end(); start < end; ++start)
    {
        if(Direction.has(*start))
            corsac::Entity<>(*start).fit<Direction>(0, 1).remove<S>();
    }
}

void AMovebleEvent()
{
    for(auto start = A.begin(), end = A.end(); start < end; ++start)
    {
        if(Direction.has(*start))
            corsac::Entity<>(*start).fit<Direction>(-1, 0).remove<A>();
    }
}

void DMovebleEvent()
{
    for(auto start = D.begin(), end = D.end(); start < end; ++start)
    {
        if(Direction.has(*start))
            corsac::Entity<>(*start).fit<Direction>(1, 0).remove<D>();
    }
}

void Move()
{
    for(auto start = Transform.begin(), end = Transform.end(); start < end; ++start)
    {
        corsac::Entity<Transform>(*start)
                .set<Position>(
                        Position.get<0>(*start) + (Direction.get<0>(*start) * Speed.get(*start)),
                        Position.get<1>(*start) + (Direction.get<1>(*start) * Speed.get(*start))
                )
                .fit<Direction>(0, 0);
    }
}

void Draw()
{
    Sleep(1000/60);
    //system("cls");
    std::string map[29];

    for(int i = 0; i < 29; i++){
        for(int c = 0; c < 50; c++)
        {
            if((i == 0)||(c == 0)||(i == 28)||(c == 49))
                map[i] += "#";
            else
                map[i] += " ";
        }
    }

    for(auto start = Transform.begin(), end = Transform.end(); start < end; ++start)
    {
        auto x = Position.get<0>(*start);
        auto y = Position.get<1>(*start);
        map[y][x] = 'X';
    }

    std::string output = "";

    for(auto i = 0; i < 29; i++)
    {
        output += map[i] + '\n';
    }

    std::cout << output;
}


int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

    SDL_Window* Window = SDL_CreateWindow("Corsac Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (Window == NULL)
		return 1;

    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == NULL)
		return 1;

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);

    corsac::Entity<Person>()
            .fit<Position>(2, 2)
            .fit<Speed>(1)
            .fit<Direction>(0, 0);

    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	    SDL_RenderClear(Renderer);
        // Systems
        KeyEventSystem();
        WMovebleEvent();
        SMovebleEvent();
        DMovebleEvent();
        AMovebleEvent();
        Move();
        Draw();
        ///////////////////////
        SDL_RenderPresent(Renderer);
    }

    SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();

    return 0;
}