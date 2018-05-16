//
//  utils.h
//  theBigGame
//
//  Created by Blindsp0t on 15/05/2018.
//
//

#ifndef utils_h
#define utils_h

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofEvents.h"


const string globalFontName = "KGTenThousandReasons.ttf";

class utils
{
public:
    //--------------------------------------------------------------
    static string toUpperCase(string str)
    {
//        string strUpper = "";
//        
//        for( int i=0; i<str.length(); i++ )
//        {
//            strUpper += toupper( str[ i ] );
//        }
//        return strUpper;
        
        // On passe en majuscules
        str = ofToUpper(str);
        
        // On remplace A LA MAIN les minuscules accentuées par des majuscules
        string minus = "àâéèêîôûùœæç";
        string majus = "ÀÂÉÈÊÎÔÛÙŒÆÇ";
        
        for(int i = 0; i < minus.size(); i++){
            ofStringReplace(str, ofToString(minus[i]), ofToString(majus[i]));
        }
        
        return str;
        
    };
    
};

/* GLOBAL TIMER CLASS ----------------------------------------------
Use :

 Start the timer
 startTimer(<put the value in seconds you want to wait>)
 
 Update it with a float value which
 
------------------------------------------------------------------- */

class timer{
    // global timer available at anyTime
private:
    ofxAnimatableFloat mTimer;
    
public:
    
    // Timer Event
    ofEvent<void> timerEnd;
    
    // TIMER //////////////////////////////////////////////////
    void update(float dt){
        mTimer.update(dt);
        if(mTimer.hasFinishedAnimating()){
            ofNotifyEvent(timerEnd);
        }
    }
    
    void startTimer(float _seconds){
        
        mTimer.reset(1.0f);
        mTimer.setCurve(LINEAR);
        mTimer.setRepeatType(PLAY_ONCE);
        mTimer.setDuration(_seconds);
//        mTimer.startAutoUpdate();
        mTimer.animateTo(0.0f);
    }
    
//    void stopTimer(){
//        mTimer.stopAutoUpdate();
//    }
    
    string toString(){
        float mappedValue = mTimer.getCurrentValue() * mTimer.getDuration();
        
        string seconds = ofToString((int) mappedValue, 2, '0');
        string minutes = ofToString((int) (mappedValue / 60), 2, '0');
        
        if(mTimer.getDuration() >= 60){
            return minutes + ':' + seconds;
        }else{
            return seconds;
        }
        
    }
};

#endif /* utils_h */
