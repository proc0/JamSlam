#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <raylib.h>
#include <string>

#include "config.h"
#include "jamslam.hpp"

// initial screen dimensions
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
// asset files
// #define URI_SOUND_SPLAT "splat1.wav"
#define GAME_CONFIG_URI "assets/jamslam.ini"

class Game {
    JamSlam jamslam;
    
    public:
        int screenWidth = SCREEN_WIDTH;
        int screenHeight = SCREEN_HEIGHT;

        Game(): jamslam(GAME_CONFIG_URI) {};
        ~Game() = default;
        void Load();
        static void Loop(void *self);
        void Render() const;
        void Resize();
        void Run();
        void Unload();
        void Update();
};
