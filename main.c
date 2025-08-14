
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdio.h>
#include <math.h>

void drawAxisTicks(int width, int height, int spacing, int tickLength) {
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    // glLineWidth(2.0f);
    glBegin(GL_LINES);
        // X-axis ticks (vertical lines along y=0)
        for (int x = -halfWidth; x <= halfWidth; x += spacing) {
            if (x == halfWidth) x--;
            if (x != 0) {
                glVertex2i(x, -tickLength/2);
                glVertex2i(x, tickLength/2);
            }
        }
        // Y-axis ticks (horizontal lines along x=0)
        for (int y = -halfHeight; y <= halfHeight; y += spacing) {
            if (y == halfHeight) y--;
            if (y != 0) {
                glVertex2i(-tickLength/2, y);
                glVertex2i(tickLength/2, y);
            }
        }
    glEnd();
    // Draw main axes
    // glLineWidth(3.0f);
    glBegin(GL_LINES);
    // y-axis (x=0)
        glVertex2i(0, -halfHeight);
        glVertex2i(0, halfHeight);
        // x-axis (y=0)
        glVertex2i(-halfWidth, 0);
        glVertex2i(halfWidth, 0);
    glEnd();
}


void drawLog(int points)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glBegin(GL_POINTS);
    for (int x = 0; x <= points; x++)
    {
        int y = 100*(log10((double)(x)));
        glVertex2i(x, y);
    }
    glEnd();
}

int main(int argc, char *argv[])
{
    SDL_Window *win = NULL;
    SDL_GLContext gl_context;
    int width = 800, height = 800;
    bool loopShouldStop = false;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", width, height, SDL_WINDOW_OPENGL);
    gl_context = SDL_GL_CreateContext(win);

    // Set up OpenGL viewport and projection
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2 - 1, width / 2 - 1, -height / 2, height / 2, -1, 1); // Center origin
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!loopShouldStop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    loopShouldStop = true;
                    break;
            }
        }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxisTicks(width, height, 20, 10); // 20px spacing, 10px tick length
    drawLog(400);
    SDL_GL_SwapWindow(win);
    }

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}