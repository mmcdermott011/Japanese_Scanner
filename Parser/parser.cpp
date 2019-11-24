#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
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

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/



//=================================================
// File parser.cpp written by Group Number: 15
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: syntaxerror
// Done by: Aditya Kalani
void syntaxerror1(string s1, string s2)
{
	cout << "Syntax Error: expected " << s1 << " but found " << s2 << endl;
	cout << "Program_Exit" << endl;
	exit(EXIT_FAILURE);
}
// Type of error: syntaxerror
// Done by: Aditya Kalani
void syntaxerror2(string s1, string s2)
{
	cout << "Syntax Error: Unexpected " << s1 << " but found in " << s2 << endl;
	cout << "Program_Exit" << endl;
	exit(EXIT_FAILURE);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: next token will be updated and is returned from the scanner
// Done by: Aditya Kalani
token_type next_token()
{
	string theword;
	if (!token_available)
	{
		scanner(thetype, theword);
		token_available = true;
	}
	return thetype;    // return the saved token
}

// Purpose: will update the match type when it succeeds
// Done by: Aditya Kalani
boolean match(tokentype expected)
{
if (next_token() != expected)
	{
		syntaxerror1(typeName[expected], saved_lexeme);  //typeName[extype]
		return false;
	}
	else
	{
		cout << "Matched " << typeName[thetype] << endl;
		token_available = false;  // eat up the token
		return true;              // say there was a match
	}
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s>^*
void story() {

}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Michael McDermott
void s()
{
    if(next_token() == CONNECTOR)
    {
      match(CONNECTOR);
      noun();
      match(SUBJECT);
      afterSubject();
    }
}

//Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Michael McDermott
void noun()
{
    cout<<"processing noun"<<endl;
    switch(next_token){
        case WORD1:
            match(WORD1);
            break;
        case PRONOUN:
            match(PRONOUN);
            break;
        default:
            syntax_error2(saved_lexeme, "noun");
    }
}

//Grammar: <verb> ::= WORD2
void verb()
{
   cout<<"processing verb"<<endl;
    //J
}

//Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
void tense()
{
   cout<<"processing tense"<<endl;
    //J
}

//Grammar <be> ::=   IS | WAS
void be()
{
   cout<<"processing be"<<endl;
    //A
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Michael McDermott
void afterSubject()
{
    switch (next_token()) {
        case VERB:
        case WORD2:
                verb();
                tense();
                match(PERIOD);
            break:
        case WORD1:
        case PRONOUN:
            noun();
            afterNoun();
            break;
        default:
            syntax_error2(saved_lexeme, "afterSubject");
    }
}

// Grammar: <after noun> ::= <be> PERIOD  | DESTINATION <verb> <tense>PERIOD | OBJECT <after object>
// Done by:
void afterNoun()
{
//A
}

// Grammar: <after object> ::= <verb> <after verb> | <noun> DESTINATION <verb> <tense> PERIOD
// Done by:
void afterObject()
{
	//J
}


//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Aditya Kalani
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  story();

  fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
