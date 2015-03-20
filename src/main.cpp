#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
//	ofSetupOpenGL(&window, 1422, 800, OF_WINDOW);
    
    ofSetupOpenGL(&window, 1422, 800, OF_WINDOW);
	ofRunApp(new testApp());
}
