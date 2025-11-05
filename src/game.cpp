#include "game.hpp"

#if __EMSCRIPTEN__
EM_JS(int, getBrowserWidth, (), {
    return window.innerWidth;
});

EM_JS(int, getBrowserHeight, (), {
    return window.innerHeight;
});
#endif

void Game::Resize() {
    int height = GetScreenHeight();
    int width = GetScreenWidth();

    if(screenHeight != height || screenWidth != width){
        screenHeight = height;
        screenWidth = width;

    #if __EMSCRIPTEN__
        static int PADDING = 30; // set padding to avoid scrollbar and browser edge overlap
        SetWindowSize(getBrowserWidth() - PADDING, getBrowserHeight() - PADDING);
    #endif
    }
}

void Game::Update(){

    Resize();

   jamslam.Update();
    
}

void Game::Render() const {
    BeginDrawing();

    jamslam.Render();

    EndDrawing();
}

void Game::Load(){
    // std::string pathAssets = DIR_ASSETS;
    // const char* pathSoundSplat = pathAssets.append("/").append(URI_SOUND_SPLAT).c_str();
    jamslam.Load();

}

void Game::Unload(){
    jamslam.Unload();
}

void Game::Loop(void *self) {
    Game *client = static_cast<Game *>(self);

    client->Update();
    client->Render();
}

void Game::Run() {
    #ifdef __EMSCRIPTEN__
        // no target FPS for performance
        emscripten_set_main_loop_arg(Loop, this, 0, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose() && jamslam.isRunning()) {
            Loop(this);
        }
    #endif
}
