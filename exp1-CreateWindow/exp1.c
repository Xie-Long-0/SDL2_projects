#include <stdio.h>

// #define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 320;

void WaitWindowClose();

int main(int argc, char *argv[])
{
    // 初始化SDL Video子系统
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -2;
    }

    // 获取窗口表面
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect rect1 = {20, 40, 200, 100};
    SDL_Rect rect2 = {200, 80, 150, 150};
    // 在表面填充矩形
    SDL_FillRect(surface, &rect1, SDL_MapRGB(surface->format, 128, 64, 192));
    SDL_FillRect(surface, &rect2, SDL_MapRGB(surface->format, 0, 255, 128));

    // 更新窗口表面
    SDL_UpdateWindowSurface(window);

    // 等待窗口关闭
    WaitWindowClose();

    // 销毁窗口
    SDL_DestroyWindow(window);
    // 退出SDL子系统
    SDL_Quit();
    return 0;
}

void WaitWindowClose()
{
    // Hack to get window to stay up
    SDL_Event e;
    int quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
    }
}
