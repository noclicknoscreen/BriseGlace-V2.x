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



#endif /* utils_h */
