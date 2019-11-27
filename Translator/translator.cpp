#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include "parser.cpp"
using namespace std;
map<string,string> lexMap;
string saved_E_word;
/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 15
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 
void buildLexicon(){
    ifstream lexFile;
    lexFile.open("lexicon.txt");
    string lex1, lex2;
    cout <<"testing buildLexicon" <<endl;
    while(lexFile >> lex1 >> lex2) {
        lexMap.insert({lex1,lex2});
        cout <<lex1 << " " <<lex2 <<endl;
    }
    lexFile.close();
}

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
void getEword() {
    
    
}

//  Done by: ** 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
void gen(line_type) {
    
    
    /*
     if #gen#("Tense") is called, dont use saved_e_word, use saved_token
     */
    
    //fout output to translated.txt
}

//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  **
int main()
{
    string filename;
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 
    buildLexicon();
  //** opens the output file translated.txt
    ofstream outFile;
    outFile.open("translated.txt");
    
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
    story();
  //** closes the input file
    fin.close();
  //** closes translated.txt
    outFile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

