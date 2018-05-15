//
//  utils.h
//  theBigGame
//
//  Created by Blindsp0t on 15/05/2018.
//
//

#ifndef utils_h
#define utils_h

class utils
{
public:
    //--------------------------------------------------------------
    static string toUpperCase(string str)
    {
        string strUpper = "";
        
        for( int i=0; i<str.length(); i++ )
        {
            strUpper += toupper( str[ i ] );
        }
        return strUpper;
    };
    
};



#endif /* utils_h */
