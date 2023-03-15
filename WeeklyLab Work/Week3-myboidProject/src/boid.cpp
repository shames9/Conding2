/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 */
 

#include "boid.h"
#include "ofMain.h"

Boid::Boid()
{
	separationWeight = 1.0f;     //Initialize the separation weight to 1.0
	cohesionWeight = 0.9f;       // Initialize the cohesion weight to 0.9
	alignmentWeight = 0.2f;      // Initialize the alignment weight to 0.2
	
	separationThreshold = 30;    // Initialize the separation threshold to 30
	neighbourhoodSize = 10;      // Initialize the neighbourhood size to 10
	
	position = ofVec3f(ofRandom(0, 90), ofRandom(0, 90));        // Initialize the position to a random point within a 90x90 unit square
	velocity = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10))    ;// Initialize the velocity to a random point within a 10x10 unit square with negative and positive values
}

Boid::Boid(ofVec3f &pos, ofVec3f &vel)    // Constructor with arguments for position and velocity
{
	separationWeight = 1.0f;              // Initialize the separation weight to 1.0
	cohesionWeight = 0.2f;                // Initialize the cohesion weight to 0.2
	alignmentWeight = 0.1f;               // Initialize the alignment weight to 0.1
	
	separationThreshold = 15;             // Initialize the separation threshold to 15
	neighbourhoodSize = 100;              // Initialize the neighbourhood size to 100
	
	position = pos;
	velocity = vel;
}

Boid::~Boid()
{
	
}

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}

ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
    
    ofVec3f v(0,0,0); // create v
    
	for (int i = 0; i < otherBoids.size(); i++)
	{	
		if(position.distance(otherBoids[i]->getPosition()) < separationThreshold)
		{
			//ofVec3f v = position -  otherBoids[i]->getPosition();
            v = position -  otherBoids[i]->getPosition();
			v.normalize();
			//return v;
		}
	}
    return v; // return v
}

ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - position;
	v.normalize();
	return v;
}

ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - velocity;
	v.normalize();
	return v;
}

void Boid::update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max)
{
	velocity += separationWeight*separation(otherBoids);
	velocity += cohesionWeight*cohesion(otherBoids);
	velocity += alignmentWeight*alignment(otherBoids);
	
	walls(min, max);
	position += velocity;
}

void Boid::walls(ofVec3f &min, ofVec3f &max)
{
	if (position.x < min.x){
		position.x = min.x;
		velocity.x *= -1;
	} else if (position.x > max.x){
		position.x = max.x;
		velocity.x *= -1;
	}
	
	if (position.y < min.y){
		position.y = min.y;
		velocity.y *= -1;
	} else if (position.y > max.y){
		position.y = max.y;
		velocity.y *= -1;
	}
	
	
}

void Boid::draw()
{
	ofSetColor(102, 204, 153);            //sets the color to RGB (102, 204, 153)
	ofCircle(position.x, position.y, 21); //draws a circle with a radius of 21 at the current position
}