//
//  bigboid.cpp//
// 
//

#include "bigboid.hpp"

bigboid::bigboid()
{
    separationWeight = 1.23f;      //Initialize the separation weight to 1.23
    cohesionWeight = 0.64f;        // Initialize the cohesion weight to 0.64
    alignmentWeight = 0.36f;       // Initialize the alignment weight to 0.36
    
    separationThreshold = 5;      // Initialize the separation threshold to 5
    neighbourhoodSize = 40;        // Initialize the neighbourhood size to 40
    
    position = ofVec3f(ofRandom(0, 40), ofRandom(0, 40));   // Initialize the position to a random point within a 40x40 unit square
    velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));     // Initialize the velocity to a random point within a 1x1 unit square with negative and positive values
}

void bigboid::draw(){
    ofSetColor(0, 204, 204);                  //sets the color to RGB (0, 204, 204)
    ofCircle(position.x, position.y, 36);     //draws a circle with a radius of 36 at the current position
}
