#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define TRUE 1
#define FALSE 0

SDL_Window* window;
SDL_Renderer* renderer;

struct rain{
    float x;
    float y;
    float speed;
}; typedef struct rain Rain;


Rain* createRain(){
    Rain* rain = (Rain*)malloc(sizeof(Rain));
    rain->x = rand() % WINDOW_WIDTH;
    rain->y = -50;
    rain->speed = rand() % (5000 + 1) + 1000;
    return rain;
}

void updateRain(Rain** rain, float elapsed){

    for (int i = 0; i < 100; i++){
        
        rain[i]->y += rain[i]->speed * elapsed;

        if (rain[i]->y > WINDOW_HEIGHT){
            rain[i]->x = rand() % WINDOW_WIDTH;
            rain[i]->y = -50;
        }
    }
}

void renderRain(Rain** rain){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 75, 0);

    for (int i = 0; i < 100; i++)
        SDL_RenderDrawLine(renderer, rain[i]->x, rain[i]->y, rain[i]->x, rain[i]->y + 50);

    SDL_RenderPresent(renderer);
}

void update(Rain** rain, float elapsed){
    updateRain(rain, elapsed);
    renderRain(rain);
}

int main(int argc, char* argv[]){

    srand(time(NULL));
    
    Rain** rain = (Rain**)malloc(100*sizeof(Rain*)); 
    for (int i = 0; i < 100; i++)
        rain[i] = createRain();

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Rain", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH, WINDOW_HEIGHT, 
    SDL_WINDOW_OPENGL);

    if (window == NULL){
        printf("Error create window.\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    
    if (renderer == NULL){
        printf("Error create Render.\n");
        exit(1);
    }

    int isRunning = TRUE;
    SDL_Event event;
    Uint32 lastTicks = SDL_GetTicks();
    while(isRunning){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = FALSE;
            }
        }
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 diff = currentTicks - lastTicks;
        float elapsed = diff / 1000.0f;
        update(rain, elapsed);
        lastTicks = currentTicks;
        
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}







