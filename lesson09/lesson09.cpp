/*
*Copyright (c) 2014 DXkite<DXkite@163.com> All rights reserved.
* 文件名称：lesson09.c
* 标   识 : SDL2基础教程源代码
* 摘   要 : 第九课源码示列
*
* 当前版本 :1.0
* 作者 :DXkite
* 完成日期 :2014年6月26日
*/

#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#define false 0
#define true 1

SDL_Window *Window= NULL;
int TestThread(void *ptr);
int quit = false;
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    // 主线程
    SDL_Thread *thread;
    Window= SDL_CreateWindow("Hello World", 100, 100,400, 300, SDL_WINDOW_SHOWN);
    // 创建先线程并开始
    thread = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);
    SDL_Event event;
    while( quit == false )
    {
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            quit = true;
        }
    }

    // 等待线程运行完成
    //SDL_WaitThread(thread, NULL);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 1;
}

int TestThread(void *ptr)
{
    while( quit == false )
    {
        //Do the caption animation
        SDL_SetWindowTitle( Window,"线程进行中");
        SDL_Delay( 250 );
        SDL_SetWindowTitle( Window,"线程进行中.");
        SDL_Delay( 250 );
        SDL_SetWindowTitle( Window,"线程进行中..");
        SDL_Delay( 250 );
        SDL_SetWindowTitle( Window,"线程进行中...");
        SDL_Delay( 250 );
    }

    return 0;
}
