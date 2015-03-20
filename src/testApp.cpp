#include "testApp.h"

using namespace ofxCv;
using namespace cv;


//ofImage loadImage;
//ofImage image;

ofImage loadImage1;
ofImage image1;

ofImage loadImage2;
ofImage image2;

ofImage loadImage3;
ofImage image3;

ofImage loadImage4;
ofImage image4;

ofImage loadImage5;
ofImage image5;

ofImage loadImage6;
ofImage image6;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(320, 240);
	
	tracker.setup();
	tracker.setRescale(.5);
    
    // start loading expressions
    classifier.load("expressions");
    
    
    
    // load Image
//    string imagePath = "Justice_CS.jpg";
//    ofLoadImage(loadImage, imagePath);
//    image.loadImage(imagePath);
    
       string imagePath1 = "gorila_1.png";
        ofLoadImage(loadImage1, imagePath1);
       image1.loadImage(imagePath1);
    
    string imagePath2 = "gorila_2.png";
    ofLoadImage(loadImage2, imagePath2);
    image2.loadImage(imagePath2);
    
    string imagePath3 = "gorila_3.png";
    ofLoadImage(loadImage3, imagePath3);
    image3.loadImage(imagePath3);
    
    
    string imagePath4 = "background.jpg";
    ofLoadImage(loadImage4, imagePath4);
    image4.loadImage(imagePath4);
    
    string imagePath5 = "iphone_background.png";
    ofLoadImage(loadImage5, imagePath5);
    image5.loadImage(imagePath5);
    
//    string imagePath6 = "white_background.png";
//    ofLoadImage(loadImage6, imagePath6);
//    image6.loadImage(imagePath6);

}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			classifier.classify(tracker);
            
		}		
	}
    
    //int position = ofxFaceTracker.getPosition();

    
    
}

void testApp::draw() {
	//ofSetColor(255);
    ofBackground(255,255,255);
    //ofSetColor(255);
//	cam.draw(0, 0);
//	tracker.draw();
	
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();


//  for(int i = 0; i < n; i++){
    
    
    ofVec2f position = tracker.getPosition();
    float scale = tracker.getScale();
   // ofLog(OF_LOG_NOTICE, "scale: ", scale.x);
    
//    ofTranslate(position.x, position.y);
   
    
    
    // background
//    image4.draw(1422,800, -200+position.x/2,-950+position.y/2);
    image4.draw(-200+position.x/2-scale*100/2,-550+position.y/2-scale*100/2, 1333+scale*100, 1056+scale*100  );

    
    
    
    
      if (primary == 0){ofLog(OF_LOG_NOTICE, "the expression is eye brown"); image3.draw((ofGetWidth()/2+90-position.x)-scale*100/2, (ofGetHeight()/2-100+position.y/2)-scale*100/2, 150+scale*100, 150+scale*100 );};
    if (primary == 1){ofLog(OF_LOG_NOTICE, "the expression is neutral"); image1.draw((ofGetWidth()/2+90-position.x)-scale*100/2, (ofGetHeight()/2-100+position.y/2)-scale*100/2, 150+scale*100, 150+scale*100 );};
        
      if (primary == 2){ofLog(OF_LOG_NOTICE, "the expression is happy"); image2.draw((ofGetWidth()/2+90-position.x)-scale*100/2, (ofGetHeight()/2-100+position.y/2)-scale*100/2, 150+scale*100, 150+scale*100 );};
    
    // iphone
   
//    image5.draw(-5,-10);
    image5.draw(-5,-10,1422,800);
    
    
//    cam.draw(0, ofGetHeight()/2-120);
   cam.draw(0,0);
	tracker.draw();
    
  
    
    
  for(int i = 0; i < n; i++){
      
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
  }
    
    
	ofPopMatrix();
	ofPopStyle();
    

	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
//	drawHighlightString(
//		string() +
//		"r - reset\n" +
//		"e - add expression\n" +
//		"a - add sample\n" +
//		"s - save expressions\n"
//		"l - load expressions",
//		14, ofGetHeight() - 7 * 12);
    
    
//    ofSetColor(150,150,0);
//    ofRect(200, 200, 100, 100);
    
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
	}
}