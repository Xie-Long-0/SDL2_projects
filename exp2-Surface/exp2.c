#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

void WaitWindowClose();

int main(int argc, char *argv[])
{
    // 初始化SDL Video子系统
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // 初始化SDL Image，返回初始化完成的Flag标志位
    IMG_InitFlags flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags))
    {
        printf("SDL_image could not initialize with flags %X! SDL_image Error: %s\n", flags, SDL_GetError());
        SDL_Quit();
        return -2;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Show Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -3;
    }

    // 获取窗口表面
    SDL_Surface *screen_surface = SDL_GetWindowSurface(window);
    // 加载的表面
    SDL_Surface *loaded_surface = NULL;
    SDL_Surface *hellobmp_surface = NULL;
    SDL_Surface *bgpng_surface = NULL;

    SDL_Rect rect = { 120, 100, 400, 300 };

    // 加载PNG图像
    loaded_surface = IMG_Load_RW(SDL_RWFromFile("background.png", "rb"), 1);
    if (loaded_surface != NULL)
    {
        // 转换到屏幕表面的格式
        bgpng_surface = SDL_ConvertSurfaceFormat(loaded_surface, screen_surface->format->format, 0);
        SDL_FreeSurface(loaded_surface);
        loaded_surface = NULL;
        // 按位复制表面数据到屏幕上
        SDL_BlitSurface(bgpng_surface, NULL, screen_surface, NULL);
    }

    // 加载BMP图像
    loaded_surface = IMG_Load_RW(SDL_RWFromFile("hello.bmp", "rb"), 1);
    if (loaded_surface != NULL)
    {
        // 转换到屏幕表面的格式
        hellobmp_surface = SDL_ConvertSurfaceFormat(loaded_surface, screen_surface->format->format, 0);
        SDL_FreeSurface(loaded_surface);
        loaded_surface = NULL;
        // 按位复制表面数据到屏幕上，注：rect的宽高被忽略
        SDL_BlitSurface(hellobmp_surface, NULL, screen_surface, &rect);
    }

    // 更新窗口表面
    SDL_UpdateWindowSurface(window);

    WaitWindowClose();

    // 释放资源
    SDL_FreeSurface(hellobmp_surface);
    SDL_FreeSurface(bgpng_surface);

    // 销毁窗口
    SDL_DestroyWindow(window);
    // 退出SDL子系统
    IMG_Quit();
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
