#include "testApp.h"

testApp::~testApp()
{
	for (int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
}

//--------------------------------------------------------------
void testApp::setup(){
	
	
	int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();

	ofBackground(204, 255, 229);     //sets the color to RGB (204, 255, 229)
	
	// set up the boids
	for (int i = 0; i < 50; i++)
    {
        boids.push_back(new bigboid());
        boids.push_back(new Boid());
    }
	//This loop is used to create a group of Boid objects and bigboid objects when the program is started. These objects represent the individuals in the group. The program will create 50 Boid objects and 50 bigboid objects and add them to a vector container called boids.
}	


//--------------------------------------------------------------
void testApp::update(){
	
    ofVec3f min(0, 0);
	ofVec3f max(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->update(boids, min, max);
	}
}
//�ú������ڸ���Boid�����״̬����ÿ��ѭ���У�������boids���������е�ÿ�����󣬲�����ÿ�������update()������update()����ʹ�õ�ǰȺ��״̬����Ϣ������ÿ���������һ��״̬������min��max����ָ����Ⱥ��ı߽磬��ȷ��Boid���󲻻��Ƴ���Ļ��
//--------------------------------------------------------------
void testApp::draw(){

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->draw();
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}
