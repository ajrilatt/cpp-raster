/*
Adam Rilatt
07 October 2021
C++ Raster Engine -- Engine Functions
*/

// Allow for compiler to cross-check definitions
#include "Engine.hpp"

#include <vector>

namespace Engine {
    
// User-tweakable constants
const double GAME_SPEED = 60.0;
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const double FOV = 90.0;
const double FAR_PLANE  = 10000.0;
const double NEAR_PLANE = 0.1;
    
// Non-user setup (do not touch!)
const double ASPECT_RATIO = static_cast<double>(SCREEN_HEIGHT) / SCREEN_WIDTH;
//private final Timer timer = new Timer((int)((1 / GAME_SPEED) * 1000), this);
//private Screen screen;
//private Camera cam;

void run() {
  
    // Initialize everything
    vector<Mesh> sceneObjects;
    
    
    while (true) {
        
        // Get input
        // Draw screen
        
    }
  
}

}