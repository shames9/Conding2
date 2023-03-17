#include "ofApp.h"

 //--------------------------------------------------------------
    void ofApp::setup() {
        maxBoxes = 100;//Define and assign an integer variable maxBoxes with a value of 100
        spaceRange = 450;//Define and assign an integer variable spaceRange with a value of 450
        length = 500;//Define and assign the value of the integer variable length to 500
        velocity = 1.0;//Define and assign the value of the floating-point variable velocity to 1.0
        ofSetBackgroundColor(0, 0, 0);//Set up a background colour
        hue = 0;//Define and assign the value of the integer variable hue to 0
        backgroundMusic.load("music1.mp3"); // Loading musci files
        backgroundMusic.setLoop(true); // Let the music play on a loop
        backgroundMusic.play(); // Start playing music
        for (int j = 0; j < maxBoxes; j++) {//Defines a loop statement that executes the loop from 0 to maxBoxes-1.
        size = ofRandom(40, 150);//Set the size of each cube to generate a random value between 40 and 150.
        ofBoxPrimitive newBox;//Create an ofBoxPrimitive object (cube).
        newBox.set(size);//Set the size of the new cube.
        newBox.setPosition(ofRandom(-spaceRange, spaceRange),// Set the position of the new cube at random, where the x coordinate is between -spaceRange and spaceRange, the y coordinate is between half of the top of the screen minus 100, and the z coordinate is between -length and 0
        ofGetHeight() / 2 - 100,
        ofRandom(-length, 0));

        for (int side = 0; side < 6; side++) {//Define a loop statement that loops 6 times (each cube has 6 faces).
        newBox.setSideColor(side, ofColor::fromHsb(ofRandom(255), 150, 210, 180));//Set a random colour for each face of the new cube.
        }
        boxes.push_back(newBox);//Add the new cube to a vector called boxes.
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    if (boxes.size() > maxBoxes) {//Check if the number of elements in the "boxes" vector exceeds "maxBoxes" and if so use the "erase" method to remove an element from the start of the If so, use the "erase" method to remove an element from the start of the "boxes" vector.
        boxes.erase(boxes.begin());
    }

    boxes[ofRandom(boxes.size())].setPosition(ofRandom(-spaceRange, spaceRange),//Select a random element from the "boxes" vector and set its position to a new random position to bring it back into the screen view from the top.
        ofRandom(-spaceRange, -100),
        ofRandom(-length, -(length - 500)));
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    for (int i = 0; i < particles.size(); i++) {
        particles[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw() {
    float time = ofGetElapsedTimef();//a float variable called time to the number of seconds that have elapsed since the program started running.
    for (int x = 1; x < 20; x++) {//starts a nested loop that will run 19 times for each iteration of the outer loop. The variable x is initialized to 1, and the loop will continue as long as x is less than 20.
        for (int i = 0; i < 900; i += 5) {//starts another loop that will run 180 times for each iteration of the outer loop. The variable i is initialized to 0, and the loop will continue as long as i is less than 900. i is incremented by 5 each time the loop runs.
            ofSetColor(127 + 127 * sin(i * 0.01 + time + x),//sets the color used to draw subsequent shapes. The color is determined by sine waves with different frequencies and phases, based on the current values of i, time, and x
                127 + 127 * sin(i * 0.011 + time),
                127 + 127 * sin(i * 0.012 + time));
            //ofDrawCircle(ofGetWidth() / 2, i, 100);
            ofDrawCircle(50 * x + 100 * sin(i * 0.01 + time + x), 50 + i, 50 + 40 * sin(i * 0.005 + time + x));//draws a circle with a position that is determined by sine waves with different frequencies and phases, based on the current values of i, time, and x.
        }

    }
    ofSetColor(255);
    
    ofPushMatrix();//saves the current matrix to the matrix stack.
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 + 600);//translates the origin of the coordinate system to the center of the screen with an additional y-axis offset of 600 pixels.
    //ofRotateDeg(time);
    for (int i = 0; i < boxes.size(); i++) {//loops through the boxes vector and performs the following operations for each ofBoxPrimitive element.
        boxes[i].draw();//draws the current ofBoxPrimitive element on the screen.
    }
    ofPopMatrix();// restores the previous matrix from the matrix stack.

    for (int i = 0; i < particles.size(); i++) {//loops through the particles vector and performs the following operations for each Particle object.
        particles[i].draw();//draws the current Particle object on the screen. 
    }
    
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {//Use the 'f' key on the keyboard to control turning the full screen on and off
    switch (key) {
    case 'f':
    case 'F':
        ofToggleFullscreen();
        break;

    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters
    particle newParticle(mouseX, mouseY, hue);
    // push the new particle we just made onto the back of the vector 'particles'
    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    hue = ofRandom(255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int hue) {
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    position = glm::vec2(startX, startY);
    force = glm::vec2(0, 0.02);
    direction = glm::vec2(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0));
    size = 30;
    color.setHsb(hue, 255, 255, 200);
}
//--------------------------------------------------------------

particle::~particle() {
    // destructor
}
//--------------------------------------------------------------

void particle::update() {
    // update the particle x,y position by incrementing each by the velocity vx and vy
    position += direction;
    direction += force;
    if (size > 1) {
        size -= 0.07;
    }
    float brightness = color.getBrightness();
    float myHue = color.getHue();

    if (brightness > 20) {
        // color.setBrightness( brightness -=0.5 );
        color.setHue(myHue -= 0.5);

    }
    // Add friction to slow down particle movement
    float friction = 0.98;
    direction *= friction;
    // Increase particle velocity while mouse is dragged
   
    // Draw rectangle instead of circle
    ofDrawRectangle(position.x, position.y, size, size);
    // Set random initial velocity and direction
    float initialVelocity = ofRandom(1.0, 5.0);
    float initialDirection = ofRandom(0, 360);
    direction = glm::vec2(initialVelocity * cos(initialDirection), initialVelocity * sin(initialDirection));

    // Add color gradient effect
    float lerpAmt = ofMap(ofGetElapsedTimef(), 0, 2, 0, 120);
    ofColor startColor = ofColor::fromHsb(color.getHue(), 255, 255);
    ofColor endColor = ofColor::fromHsb(color.getHue(), 255, 255);
    color = startColor.lerp(endColor, lerpAmt);

}

//--------------------------------------------------------------

void particle::draw() {
    ofSetColor(color);
    ofDrawCircle(position, size);

}
