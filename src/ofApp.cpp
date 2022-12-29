#include "ofApp.h"
#include <string>


int counter = 0;
float timer;
string validInput = "p12347890a=-";
string recorder = ""; //for recorder method
bool record = false; //also for recorder method


//--------------------------------------------------------------
void ofApp::setup(){
    sound.loadSound("beat.wav"); //Loads a sound file (in bin/data/)
    sound.setLoop(true); // Makes the song loop indefinitely
    sound.setVolume(vol); // Sets the song volume
    ofSetBackgroundColor(200, 50,10); // Sets the Background Color

    pikachu.load("pikachu.png");
    cloud.load("8bitCloud.png");
    energy.load("EnergyBar.png");
}

//--------------------------------------------------------------
void ofApp::songChanger(string song){
    if(playing){
    sound.loadSound(song);
    sound.play();
    sound.setLoop(true); 
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    if (drawing){// Updates Amplitudes for visualizer
        visualizer.updateAmplitudes();
        } 

    if(looping){
    
    timer = ofGetElapsedTimeMillis() - startTime;

    lock = true;
    record = false;

        for(int i; i < recorder.size(); i++){


            if(timer >= 5000*i && timer < 5000*(i+1) && counter == i)
            {
            char passer = recorder[i];
            lock = false;
            keyPressed(passer);
            lock = true;
            counter += 1;
            }
    }
    if(counter >= recorder.size()){
        looping = false;
        lock = false;
        counter =0;
    }


    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    if(!playing){
        ofSetColor(256); 
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }

    if(looping){ 
        ofSetColor(256);
        ofDrawBitmapString("You are currently loopin!", 0, 100);}

    if(record && !looping){ 
    ofSetColor(256);
    ofDrawBitmapString("You are currently recording", 0, 100); //to let user know they're recording
    ofDrawBitmapString("Press 'r' to reset recording", 0, 115);
    ofDrawBitmapString(recorder, 0, 130);} //to let user know what they've typed


    vector<float> amplitudes = visualizer.getAmplitudes();
    if(mode == '1'){
        drawMode1(amplitudes);
    }else if(mode == '2'){
        drawMode2(amplitudes);
    }else if(mode == '3'){
        drawMode3(amplitudes);
    }else if(mode == '4'){
        drawMode4(amplitudes);
    }
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        // ofDrawBitmapString(amplitudes[0], 10, 30);



        ofSetColor(R, G, B); //Changed color so that the rectangles can look different
        ofSetBackgroundColor(200,50,10);
        int total = 0;
        int bands = amplitudes.size();
        for(int i=0; i<bands;i++){
            ofDrawRectangle(total, ofGetHeight() - 100, 50,  amplitudes[i]*2);
            total += (ofGetWidth()/64); //1024 divided between 64 = 16 :)
        }

}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(0); // This resets the color of the "brush" to black
        ofSetBackgroundColor(255, 255, 102);


        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
}

void ofApp::drawMode3(vector<float> amplitudes){
    ofFill();
    ofSetColor(256); // This resets the color of the "brush" to white
    ofSetBackgroundColor(255, 153, 51);
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    ofSetColor(B,G,R);


    int total = 0;
    int bands = amplitudes.size();
    for(int i=0; i<bands;i++){
        ofDrawRectangle( ofGetWidth(), total, amplitudes[i]*2,50  );
        total += (ofGetHeight()/64);} 

    //done with this method
    /*ofDrawRectangle uses cordinates (x,y) so I inverted the values 
    so that they could be focused on the y axis instead of the x axis
    as it was in the first rectangle method */
    
}
void ofApp::drawMode4(vector<float> amplitudes){
    ofSetColor(256); // This resets the color of the "brush" to white
    ofSetBackgroundColor(152,253,255);
    ofSetLineWidth(1);

    int bands = amplitudes.size();
    ofFill();
    ofSetColor(255, 255, 102);
    for(int i=0; i < bands; i++){
        ofDrawCircle(ofGetWidth(), 0, -(amplitudes[i] * 0.5));
    }

    ofFill();
    ofSetColor(0,128,255); //Sets color to blue


    int counter = 0;
    int counter2 = 16; //two counters to alter the X variable in ofDrawLine() method 
    int half = ofGetHeight()/2 + 100; //Locates lines at half of screen :) in the y axis
    int adder = ofGetWidth()/amplitudes.size();


    //ofDrawLine uses (x1,y1) and (x2,y2) to draw lines between those 2 points

    /*for loop creates 64 lines, each with a different amplitude thanks to 
    amplitudes[] being a vector which is formed by many different amplitudes
    that are here being accessed with [i] and [i+1]*/



    for(int i =0; i<bands-1 ;i++){
        for (int j = 0; j < ofGetHeight()/2 + 50; j+= 5){
            ofDrawLine(counter, (half + j)+ amplitudes[i], counter2,(half + j) + amplitudes[i+1]);
            ofDrawLine(1008, half + j + amplitudes[63], 1028, half + j);

        }
        counter += adder;
        counter2 += adder;
    }

    //Images and their trackers:
    pikachu.resize(150,155);
    cloud.resize(200,100);
    energy.resize(230, 70);


    ofSetColor(255);
    cloud.draw(ofGetWidth() -10 - move1 - cloud.getWidth() , 100 - amplitudes[1] * 0.2);
    move1 += 8 - amplitudes[1] * 0.1;
    if(move1 >= 1000){ move1 = -200; }

    //Cloud #2
    cloud.draw(ofGetWidth() -10 - move2 - cloud.getWidth() , 10 - amplitudes[1] * 0.2);
    move2 += 8 - amplitudes[2] *0.2;
    if(move2 >= 1000){ move2 = -200; }

    //Cloud #3 
    cloud.draw(ofGetWidth() -10 - move3 - cloud.getWidth() , 150 - amplitudes[1] * 0.2);
    move3 += 8 - amplitudes[3] * 0.25;
    if(move3 >= 1000){ move3 = -200; }
    /*Dios perdoname por repetir codigo pero las funciones se complicaban cuando
    se implementaba una variable de movimiento -Angel
    (tambien habia que pasar muchas variables, eso es mucho trabajo)*/

    pikachu.draw( 100 + moveP, ofGetHeight() - 200 - amplitudes[4]*0.2);
    moveP += (0.5 * index) + (ofRandom(-1,1) * amplitudes[5] * 0.25);
    if(moveP >= 50){ index = -1 ;}
    if(moveP <= 0) { index = 1; }

    ofSetColor(255,208,14);
    ofDrawRectangle(45, 30, amplitudes[4] * -1.8, 35);
    ofSetColor(255);
    energy.draw(10, 20);


}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // This method is called automatically when any key is pressed
    if (record){

        char checker = key;

        if(validInput.find(checker) != string::npos){ //checks if input is valid


        recorder += key;
        }

        switch(key){
        
            case 'r':
            recorder.clear();
            record = true;
            break;


            case 't':
            startTime = ofGetElapsedTimeMillis(); 
            looping = true;
            break;

        }
    }
    else if(!lock){
    switch(key){
        case 'p':
            if(playing){
                sound.stop();
            }else{
                sound.play();
            }
            playing = !playing;
            break;
        case '1':
            R = ofRandom(256);
            G = ofRandom(256);
            B = ofRandom(256);
            ofSetColor(R,G,B);            
            mode = '1';
            break;

        case '2':
            mode = '2';
            break;

        case '3':
            R = ofRandom(256);
            G = ofRandom(256);
            B = ofRandom(256);
            ofSetColor(R,G,B);
            mode = '3';
            break;

        case '4':
            mode = '4';
            break;
        

        case '7':
            songChanger("beat.wav");
            break;
        case '8':
            songChanger("geesebeat.wav");
            break;
        case '9':
            songChanger("Play-em-like-atari.wav");
            break;
        case '0':
            songChanger("rock-song.wav");
            break;
        
        case 'a':
            drawing = !drawing;
            break;

        case '=':
            if(vol<1){
                vol += 0.1;
                sound.setVolume(vol);
                break;
            }
            break;
        case '-':
            if(vol>=0){
                vol -= 0.1;
                sound.setVolume(vol);
                break;
            }
            break;



        case 'r':
            recorder.clear();
            record = true;
            break;            
        
    }
    }
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}