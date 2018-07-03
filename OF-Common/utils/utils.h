//
//  utils.h
//  theBigGame
//
//  Created by Blindsp0t on 15/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofEvents.h"

#include <locale>
#include <codecvt>

const string    globalFontName = "KGTenThousandReasons.ttf";
const int       globalFontSizeSmall = 24;
const int       globalFontSizeBig   = 48;
const int       globalFontSizeMedium   = 36;

const string settingsFileNameGame1 = "settingsGame1.xml";
const string settingsFileNameGame2 = "settingsGame2.xml";
const string settingsFileNameGame3 = "settingsGame3.xml";
const string settingsFileNameHint  = "settingsHint.xml";
const string settingsPlayers       = "settingsPlayers.xml";

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
    
    //-------------------------------------------------------------------
    static string cleanString(string _inStr){

        // Suppression des accents bizarres --
        ofStringReplace(_inStr, "“", "\"");
        ofStringReplace(_inStr, "«", "\"");
        ofStringReplace(_inStr, "»", "\"");
        ofStringReplace(_inStr, "‹", "\"");
        ofStringReplace(_inStr, "›", "\"");
        ofStringReplace(_inStr, "“", "\"");
        ofStringReplace(_inStr, "”", "\"");
        ofStringReplace(_inStr, "„", "\"");
        
        // Suppression des apostrophes --
        ofStringReplace(_inStr, "'", "'");
        ofStringReplace(_inStr, "‘", "'");
        ofStringReplace(_inStr, "’", "'");
        ofStringReplace(_inStr, "‚", "'");
        
        // Remplacement œ car pas dans le jeu de caractères OF
        ofStringReplace(_inStr, "œ", "oe");
        ofStringReplace(_inStr, "Œ", "OE");
        
        return _inStr;
    }
    
    //--------------------------------------------------------------
    static wstring getRndLetter(){
        
        wstring allLetters = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int rndIdx = (int)ofRandom(0, (float)allLetters.size());
        
        return allLetters.substr(rndIdx, 1);
//        return allLetters[rndIdx];
    };
    
    
    // CONVERSION -------------------------------------------------------------
private:
//    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
public:
    static std::string toByteString(std::wstring _WStr){
        
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        
        const std::string narrow = converter.to_bytes(_WStr);
        return narrow;
    }
    static std::wstring toWString(std::string _Str){
        
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        
        const std::wstring wide = converter.from_bytes(_Str);
        return wide;
    }
    // Examples
//    std::string narrow = converter.to_bytes(wide_utf16_source_string);
//    std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
    
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
    bool started=false;
    
public:
    
    timer(){
        mTimer.reset(1.0f);
        //mTimer.stopAutoUpdate();
    }
    
    // Timer Event
    ofEvent<void> timerEnd;
    
    // TIMER //////////////////////////////////////////////////
    void update(float dt){
        if(started)
        {
            mTimer.update(dt);
            if(mTimer.hasFinishedAnimating()){
                ofNotifyEvent(timerEnd);
            }
        }
    }
    
    void startTimer(float _seconds){
        started = true;
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
        
        string seconds = ofToString((int) fmod(mappedValue,60), 2, '0');
        string minutes = ofToString((int) (mappedValue / 60), 2, '0');
        
        if(mTimer.getDuration() >= 60){
            return minutes + ':' + seconds;
        }else{
            return seconds;
        }
        
    }
    
    void stop(){
        mTimer.reset(1.0f);
        started = false;
    }
    
    void pause(){
        mTimer.pause();
    }
    void resume(){
        mTimer.resume();
    }
    
    bool isAnimating(){
        return mTimer.isAnimating();
    }
    
    float getValuef(){
        return mTimer.getCurrentValue();
    }
    
};

