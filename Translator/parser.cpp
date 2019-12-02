#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include "scanner.cpp"
#include "translator.cpp"
using namespace std;

//funciton prototypes
void s();
void noun();
void verb();
void tense();
void be();
void afterSubject();
void afterNoun();
void afterObject();
string saved_lexeme;
bool  token_available = false;
tokentype saved_token;

//=================================================
// File parser.cpp written by Group Number: 15
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: syntaxerror
// Done by: Aditya Kalani
void syntaxerror1(tokentype expected, string saved_lexeme)
{
  cout<<"SYNTAX ERROR: expected "<< tokenName[expected]  << " but found "<<  saved_lexeme <<endl;
  exit (1); //halting
}

//Done By: Aditya Kalani
void syntaxerror2(string saved_lexeme, string parserFunct)
{
  cout<<"SYNTAX ERROR: unexpected "<< saved_lexeme << " found in "<< parserFunct <<endl;
  exit (1); //halting
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: next token will be updated and is returned from the scanner
// Done by: Aditya Kalani
tokentype next_token()
{
    if (!token_available)
	{
		scanner(saved_token, saved_lexeme);
		cout << "word: " << saved_lexeme << endl;
		token_available = true;
	}
	return saved_token;    // return the saved token
}

// Purpose: will update the match type when it succeeds
// Done by: Aditya Kalani
bool match(tokentype expected)
{
if (next_token() != expected)
	{
	  syntaxerror1(expected, saved_lexeme);
        return false;
	}
	else
	{
		cout << "Matched " << tokenName[expected] << endl;
		token_available = false;
		return true;
	}
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s>^*
void story()
{
  cout << "Process <story>" << endl;
  s();
  while (saved_lexeme !="eofm")
    {
        switch (next_token()) // look ahead to see if the valid start is there
        {
        case CONNECTOR:
        case WORD1:
        case PRONOUN:s();// found another beginning
            break;
        default:
            return;  // loop stops
        }//end switch
    }
  cout << "Successfully parsed <story>." << endl;
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Michael McDermott
void s()
{
  next_token();
    if(saved_lexeme !="eofm") {
      cout << "=========== Processing <s> =========== " << endl;
        if(next_token() == CONNECTOR)
        {
          match(saved_token);
          getEword();
          gen("CONNECTOR");
        }
        noun();
        getEword();
        match(SUBJECT);
        gen("ACTOR");
        afterSubject();
    }
    cout <<endl;
}

//Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Michael McDermott
void noun()
{
    cout<<"processing noun"<<endl;
    switch(next_token()){
        case WORD1:
            match(WORD1);
            break;
        case PRONOUN:
            match(PRONOUN);
            break;
        default:
            syntaxerror2(tokenName[saved_token], "noun");
    }
}

//Grammar: <verb> ::= WORD2
// Done by: Joshua Matthews
void verb()
{
   cout<<"processing verb"<<endl;

		switch (next_token()) {
			case WORD2:
				match(WORD2);
				break;
			default:
				syntaxerror2(saved_lexeme, "verb");
			}
}

//Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: Joshua Matthews
void tense()
{
   cout<<"processing tense"<<endl;

	 switch(next_token())
     {
     case  VERBPAST:
       match(VERBPAST);
       break;
     case  VERBPASTNEG:
       match(VERBPASTNEG);
       break;
     case  VERB:
       match(VERB);
       break;
     case  VERBNEG:
       match(VERBNEG);
       break;
     default:
       syntaxerror2(saved_lexeme, "tense");
     }
}

//Grammar <be> ::=   IS | WAS
//Done by: Aditya Kalani
void be()
{
	cout << "Processing <be> " << endl; // prints the name of the function

	switch (next_token())  // If the next token after "be" is "IS" or "WAS" then it matches
						   // otherwise it is a syntax error
	{
	case IS:
		match(IS);
		break;
	case WAS:
		match(WAS);
		break;
	default:
		syntaxerror2(tokenName[saved_token], "be()");
	}
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Michael McDermott
void afterSubject()
{
    switch (next_token()) {
        //case VERB:
        case WORD2:
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
		        break;
        case WORD1:
        case PRONOUN:
            noun();
            afterNoun();
            break;
        default:
            syntaxerror2(tokenName[saved_token], "afterSubject");
    }
}

// Grammar: <after noun> ::= <be> PERIOD  | DESTINATION <verb> <tense>PERIOD | OBJECT <after object>
// Done by: Aditya Kalani
void afterNoun()
{
	cout << "Processing <after_noun>" << endl;    // prints the name of the function
	switch (next_token())
	  {
	  case IS:
	  case WAS:
      getEword();
	    be();
      gen("DESCRIPTION");
      gen("TENSE");
	   // next_token();
	    match(PERIOD);
	    break;
	  case DESTINATION:
      getEword();
	    match(DESTINATION);
      gen("TO");
	//    next_token();
	    verb();
      getEword();
      gen("ACTION");
	    tense();
      gen("TENSE");
	//    next_token();
	    match(PERIOD);
	    break;

	  case OBJECT:
	    match(OBJECT);
      gen("OBJECT");
	    afterObject();
	    break;
	  default:
	    syntaxerror2(tokenName[saved_token], "<after_noun>()");
	//    break;
	  }
}

// Grammar: <after object> ::= <verb> <after verb> | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Joshua Matthews
void afterObject()
{
  cout << "Processing afterObject." << endl;

  switch(next_token())
    {
    case WORD1:
      noun();
      match(DESTINATION);
      verb();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
    case WORD2:
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "<afterObject>()");
    }
}

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Aditya Kalani
/*
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  story();

  fin.close();

}
 */
// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
