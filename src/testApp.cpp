#include "testApp.h"

#include "testApp.h"

//----------------------  Params -------------------------------
Params param;        //Definition of global variable
Particle newP;

void Params::setup() {
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = 1;
    velRad = 400;
    velRad2 = 400;
    lifeTime = 1.0;
    
    rotate = 0;
}

//----------------------  Particle  ----------------------------
Particle::Particle() {
    live = false;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle(){
    ofPoint pnt;
    float rad = 400;
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    //pnt.z = ofRandom(-1,1);
    
    return pnt;
}

//--------------------------------------------------------------
void Particle::setup() {
    pos = param.eCenter;
    vel =  randomPointInCircle();
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
    
    
}

//--------------------------------------------------------------
void Particle::update( float dt ){
    if ( live ) {
        //Update pos
        pos += vel * dt;    //Euler method
        //Update time and check if particle should die
        time += dt;
        if ( time >= lifeTime ) {
            live = false;   //Particle is now considered as died
        }
        
    }
    
}

void Particle::fftUpdate(){
    //---for---fft-----------------------
    float * val = ofSoundGetSpectrum(nBandsToGet);	 // request the number of  values(255) for fft
    for (int i = 0;i < nBandsToGet; i++){
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.4f;
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
    fftchosen = (fftSmoothed[3] * 200);
    
}

//--------------------------------------------------------------
void Particle::draw(){
    if ( live ) {
        
        /* unsigned char * pix = glow.getPixels();
         
         for(int i = 0; i < glow.width * glow.height * 4; i++){
         if(pix[i] != 0){
         pix[i] =ofMap(fftchosen,5,250,50,255);
         
         }
         }
         glow.update(); */
        
        
        /*unsigned char * pix = glow.getPixels();
         float numPix = glow.width * glow.height * 4;
         
         float x =ofMap(fftchosen,5,250,5,250);
         
         for(int i = 0; i <numPix;  i+=4){
         if(pix[i] != 0)    if(pix[i]<x) pix[i] = x;
         if(pix[i+1] != 0)  if(pix[i]<x) pix[i+1] = x;
         if(pix[i+2] != 0)  if(pix[i]<x) pix[i+2] = x;
         }
         glow.update(); */
        
        unsigned char * pix = glow.getPixels();
        float numPix = glow.width * glow.height * 4;
        
        float x =ofMap(fftchosen,5,250,100,250);
        
        for(int i = 0; i <numPix;  i+=4){
            if(pix[i] != 0)    pix[i] = x;
            if(pix[i+1] != 0)   pix[i+1] = x;
            if(pix[i+2] != 0)  pix[i+2] = x;
        }
        glow.update();
        
        float size = ofMap(fftchosen,5,250,20,90);
        //float size = ofMap(time,0,lifeTime,20,90);
        //	ofEnableAlphaBlending();
        //	float alpha =ofMap(time,0,lifeTime,255,0);
        //	float x = ofMap(size,1,9,128,0);
        //  ofSetColor( x,x,x,alpha );
        //ofCircle( pos, size );  //Draw particle
        glow.resize(size,size);
        glow.draw(pos,size,size);
        glow.update();
        //	ofDisableAlphaBlending();
    }
    
   /* unsigned char * pix2 = glow2.getPixels();
    float numPix2 = glow2.width * glow2.height * 4;
    
    float x =ofMap(fftchosen,5,250,5,250);
    
    for(int i = 0; i <numPix2;  i+=4){
        if(pix2[i] != 0)    if(pix2[i]<x) pix2[i] = x;
        if(pix2[i+1] != 0)  if(pix2[i]<x) pix2[i+1] = x;
        if(pix2[i+2] != 0)  if(pix2[i]<x) pix2[i+2] = x;
    }
    glow2.update();
    
    float size = ofMap(fftchosen,5,250,300,500);
    glow2.setAnchorPoint(size/2,size/2);
    glow2.resize(size,size);
    
    //	ofDrawBitmapString(ofToString(size) + "size,", 40,40);
    
    glow2.draw(ofGetWidth()/2,ofGetHeight()/2);
    */
    
}


//----------------------  testApp  -----------------------------
void Particle::setupImage(){
    
    glow.loadImage("circle_gradient2.png");
    glow.resize(20,20);
    
    glow2.loadImage("circle_gradient2.png");
    glow2.resize(300,300);
    glow2.setAnchorPoint(glow2.getWidth()/2,glow2.getHeight()/2);
}

void Particle::fftSet(){
    //fft
    fftSmoothed = new float[800];
    for (int i = 0; i < 800; i++){
        fftSmoothed[i] = 0;
    }
    
    nBandsToGet = 255;
}

void testApp::setup(){
    ofSetFrameRate( 120 );	//Set screen frame rate
    ofBackground( 0,0,0);
    color1.set(0, 0, 0);
    color2.set(0, 10, 60);
  //  ofBackgroundGradient(color1, color2);
    
    //for emitting particles-----
    newP.setupImage();
    newP.fftSet();
    
    glow3.loadImage("circle_gradient2.png");
    glow3.resize(200,200);
    glow3.setAnchorPoint(glow3.getWidth()/2,glow3.getHeight()/2);
    
    glow4.loadImage("little_glow.png");
    glow4.resize(700,700);
    glow4.setAnchorPoint(glow4.getWidth()/2,glow4.getHeight()/2);
    
    
    
    // for centre particle-------
    fftSmoothed2 = new float[800];
    for (int i = 0; i < 800; i++){
        fftSmoothed2[i] = 0;
    }
    
    nBandsToGet2 = 255;
    
    //Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    
    //loading sound
 //   song1.loadSound("jdee_beat.mp3");
    song1.loadSound("Tribute (Original Mix).mp3");
    
    
    //Set up parameters
    param.setup();	 //Global parameters
    history = 1;
    bornRate = 2;
    
    bornCount = 0;
    time0 = ofGetElapsedTimef();
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    newP.fftUpdate();
    
    //---for---fft-----------------------
    float * val2 = ofSoundGetSpectrum(nBandsToGet2);	 // request the number of  values(255) for fft
    for (int i = 0;i < nBandsToGet2; i++){
        // let the smoothed calue sink to zero:
        fftSmoothed2[i] *= 0.4f;
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed2[i] < val2[i]) fftSmoothed2[i] = val2[i];
        
    }
    fftchosen2 = (fftSmoothed2[3] * 200);
    
    
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    
    //Delete inactive particles
    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
        }
        else {
            i++;
        }
    }
    
    //Born new particles
    bornCount += dt * bornRate;      //Update bornCount value
    if ( bornCount >= 1 ) {          //It's time to born particle(s)
        int bornN = int( bornCount );//How many born
        bornCount -= bornN;          //Correct bornCount value
        for (int i=0; i<bornN; i++) {
            
            newP.setup();            //Start a new particle
            p.push_back( newP );     //Add this particle to array
        }
    }
    
    //Update the particles
    for (int i=0; i<p.size(); i++) {
        p[i].update( dt );
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
    
    unsigned char * pix3 = glow3.getPixels();
     float numpix3 = glow3.width * glow3.height * 4;
     
     float x =ofMap(fftchosen2,5,250,5,250);
     
     for(int i = 0; i <numpix3;  i+=4){
     if(pix3[i] != 0)    if(pix3[i]<x) pix3[i] = x;
     if(pix3[i+1] != 0)  if(pix3[i]<x) pix3[i+1] = x;
     if(pix3[i+2] != 0)  if(pix3[i]<x) pix3[i+2] = x;
     }
     glow3.update();
     
     float size = ofMap(fftchosen2,5,250,200,400);
     glow3.setAnchorPoint(size/2,size/2);
     glow3.resize(size,size);
     
     glow3.draw(ofGetWidth()/2,ofGetHeight()/2);
     
    glow4.draw(ofGetWidth()/2,ofGetHeight()/2);
    
    //	ofDrawBitmapString(ofToString(size) + "size,", 40,40);
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 40,50);
    ofDrawBitmapString(ofToString(bornRate) + "particles", 40,60);
    
    
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'a' || key =='A'){
        song1.play();
        bornRate =22;
    }
    if(key == 'b' || key =='B'){
        song1.stop();
        bornRate =1;
    }
    
    if(key == 's' || key == 'S'){
        
        bornRate   -= 1;
        
    }
    if(key == 'w' || key == 'W') {
        
        bornRate +=1;
    }
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
