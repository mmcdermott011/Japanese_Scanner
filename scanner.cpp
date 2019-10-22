#include<iostream>
#include<fstream>
#include<string>
#include <map>
using namespace std;
//=====================================================
// File scanner.cpp written by: Group Number: 15
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Michael McDermott Group 15
// RE:   **
bool word (string s)
{
  int state = 0;
  int charpos = 0;
  // replace the following todo the word dfa  **
  while (s[charpos] != '\0')
    {
        //Q0
        if (state == 0){
            switch(s[charpos]) {
                case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                    state = 1; break;
                case 'd': case 'w': case 'z': case 'y': case 'j':
                    state = 2; break;
                case 'b': case 'm': case 'k': case 'n': case 'h': case 'p': case 'v': case 'g':
                    state = 6; break;
                case 't':
                    state = 3; break;
                case 's':
                    state = 4; break;
                case 'c':
                    state = 5;  break;
            }
        }
      // Q0Q1
        else if (state == 1) {
            switch(s[charpos]) {
              case 'n':
                state = 0; break;
              case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                state = 1; break;
              case 'd': case 'w': case 'z': case 'y': case 'j':
                state = 2; break;
              case 't':
                state = 3; break;
              case 's':
                  state = 4; break;
              case 'c':
                  state = 5;  break;
            case 'b': case 'm': case 'k': case 'h': case 'p': case 'v': case 'g':
                state = 6; break;
            }
          }
      //QSA
        else if (state == 2) {
            switch(s[charpos]) {
                   case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                     state = 1; break;
            }
      }
        //QT
      else  if (state == 3) {
          switch(s[charpos]) {
                   case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                     state = 1; break;
                   case 's':
                       state = 4; break;
          }
      }
        //QS
       else if (state == 4) {
           switch(s[charpos]) {
                     case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                       state = 1; break;
                     case 'H':
                       state = 2; break;
           }
       }
        //QC
        else if (state == 5) {
            {
                      case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                        state = 1; break;
                      case 'H':
                        state = 2; break;
            }
        }
        //QV
        else if (state == 6) {
            {
                      case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
                        state = 1; break;
            }
        }
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 1 || state == 2) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA
// Done by: Michael McDermott
bool period (string s)
{
    if(s[0] == '.') return true;
    else return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Michael McDermott

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBAPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, ERROR, EOFM };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBAPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ERROR", "EOFM"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
map<string><tokentype> reservedWords;
reservedWords["masu"] = VERB;
reservedWords["masen"] = VERBNEG;
reservedWords[" mashita"] = VERBPAST;
reservedWords["masendeshita"] = VERBPASTNEG;
reservedWords["desu"] = IS;
reservedWords["deshita"] = WAS;
reservedWords["o"] = OBJECT;
reservedWords["wa"] = SUBJECT;
reservedWords["ni"] = DESTINATION;
reservedWords["watashi"]= PRONOUN;
reservedWords["anata"]  = PRONOUN;
reservedWords["kare"]= PRONOUN;
reservedWords["kanojo"]= PRONOUN;
reservedWords["sore"] = PRONOUN;
reservedWords["mata"]= CONNECTOR;
reservedWords["soshite"] = CONNECTOR;
reservedWords["shikashi"] = CONNECTOR;
reservedWords["dakara"]= CONNECTOR;
reservedWords["eofm"]= EOFM;

// ------------ Scanner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by:
int scanner(tokentype& tt, string& w)
{

  // ** Grab the next word from the file via fin
    fin >> nextWord;
  // 1. If it is eofm, return right now.
    if(nextWord == "eofm") return;
    
  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
    */
    if(word(nextWord)) {
        iterator it = reservedWords.find(nextWord);
            /*
          3. If it was a word,
             check against the reservedwords list.
             If not reserved, tokentype is WORD1 or WORD2
             decided based on the last character.
        */
        if(it != reservedWords.end()){
            tt = it->second;
        }
        else if(reservedWords.end() == 'I' || reservedWords.end() == 'E') {
            tt = WORD2;
        }
        else {
            tt = WORD1;
        }
    }else if(period(nextWord)) {
        tt =  PERIOD;
    } else {
        tt = ERROR;
        cout << "error" <<endl;
        return -1;
    }
    return 0;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end


