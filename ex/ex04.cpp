/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//Loads individual image
SDL_Surface* loadSurface(const char* filename);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    } 
    
    //Create window
    gWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

SDL_Surface* loadSurface(const char* filename) {
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(filename);
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    }
    return loadedSurface;
}

bool loadMedia() {
    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./images/press.bmp" );
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf( "Failed to load default image!\n" );
        return false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./images/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image!\n");
        return false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./images/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image!\n");
        return false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./images/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image!\n");
        return false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./images/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image!\n");
        return false;
    }
    return true;
}

void close() {
    //Deallocate surfaces
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    //Start up SDL and create window
    if(!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }
    
    //Load media
    if(!loadMedia() ) {
        printf( "Failed to load media!\n" );
        return -1;
    }

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //Set default current surface
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    
    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                //Select surfaces based on key press
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;
                default:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        //Apply the current image
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        //Update the surface
        SDL_UpdateWindowSurface(gWindow);
    }

    //Free resources and close SDL
    close();
    return 0;
}
