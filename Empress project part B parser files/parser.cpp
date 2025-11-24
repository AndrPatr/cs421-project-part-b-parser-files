#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
          and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: ** 1
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

token_type saved_token;          // global to hold last token saved by next token
string saved_lexeme;             // global to hold the lexeme of the last token saved by next token
bool token_available = false;    // indicate if token valid

//file stream to use
ifstream fin;


/////////////////////////////////////////////////SYNTAX ERROR FUNCTIONS
// Type of error: ** unexpected token in match()
// Done by: ** Andrew
void syntaxerror1( token_type expected,string lexeme)
{
  cout<<" Syntax error: expected "<< tokenName[expected] << "but found "<< lexeme <<endl;
  exit (1);
}
// Type of error: ** unexpected token in parser function
// Done by: ** Andrew
void syntaxerror2(string functionName, string lexeme)
{
   cout<< "Syntax error: expected "<<lexeme<< "found in" << functionName<< endl;
   exit(1);
}
///////////////////////////////////////////////End error functions


//************************************** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
// Purpose: **fetch next token from scanner unless 1 is saved already
// Done by: ** Andrew
token_type next_token()
{
 if( !token_available)
 {
   saved_token = scanner(saved_lexeme);   //scanner() should return token type
   token_available = true;
 }
 return saved_token;
}

// Purpose: **return the saved token and reset the saved variables
// Done by: ** Andrew
boolean match(tokentype expected) 
{
   if (next_token() != expected)
   {
      syntaxerror1(expected,saved_lexeme);
   }
   else
   {
      token_available=false; // consume token
      return true;
   }
   return false;                          // if pass if statement
}
//*********************************** end  of next token() and Match()*************


// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: ** <story> ::= <s> { <s> }
// Done by: ** Peter Morsch
void story() 
{
   cout << "Processing <story>" << endl;
   s();
   while(true) 
   {
      switch (next_token()) 
      {
         case CONNECTOR:
         case WORD1:
         case PRONOUN: 
            s();
            break;
         default:
            return; 
      }
   }
}

// Grammar: ** <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: ** Peter Morsch
void s()
{
   cout << "Processing <s>" << endl;
   if(next_token() == CONNECTOR)
   {
      match(CONNECTOR);
   }
   noun();
   match(SUBJECT);
   aftersubject();
}

// Grammar: ** <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: ** Peter Morsch
void aftersubject()
{
   cout << "Processing <aftersubject>" << endl;
   switch (next_token()) 
   {
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
      case WORD1:
      case PRONOUN:
         noun();
         afternoun();
         break;
      default:
         syntaxerror2("<aftersubject>", saved_lexeme);
   }
}

// Grammar: ** <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after object>
// Done by: ** Peter Morsch
void afternoun()
{
   cout << "Processing <afternoun>" << endl;
   switch (next_token())
   {
      case IS:
      case WAS:
         be();
         match(PERIOD);
         break;
      case DESTINATION:
         match(DESTINATION);
         verb();
         tense();
         match(PERIOD);
         break;
      case OBJECT:
         match(OBJECT);
         afterobject();
      default:
         syntaxerror2("<afternoun>", saved_lexeme);
   }
}

// Grammar: ** <after object> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: ** Peter Morsch
void afterobject()
{
   cout << "Processing <afterobject>" << endl;
   switch (next_token()) 
   {
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
      case WORD1:
      case PRONOUN:
         noun();
         match(DESTINATION);
         verb();
         tense();
         match(PERIOD);
         break;
      default:
         syntaxerror2("<afterobject>", saved_lexeme);
   }
}

// Grammar: ** <noun> ::= WORD1 | PRONOUN
// Done by: ** Peter Morsch
void noun() 
{
   cout << "Processing <noun>" << endl;
   switch (next_token()) 
   {
      case WORD1:
         match(WORD1);
         break;
      case PRONOUN:
         match(PRONOUN);
         break;
      default:
         syntaxerror2("<noun>", saved_lexeme);
   }
}

// Grammar: ** <verb> ::= WORD2
// Done by: ** Peter Morsch
void verb() 
{
   cout << "Processing <verb>" << endl;
   match(WORD2);
}

// Grammar: ** <be> ::= IS | WAS
// Done by: ** Peter Morsch
void be() 
{
   cout << "Processing <be>" << endl;
   switch (next_token()) 
   {
      case IS:
         match(IS);
         break;
      case WAS:
         match(WAS);
         break;
      default:
         syntaxerror2("<be>", saved_lexeme);
   }
}

// Grammar: ** <tense> := VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: ** Peter Morsch
void tense() 
{
   cout << "Processing <tense>" << endl;
   switch (next_token()) 
   {
      case VERBPAST:
         match(VERBPAST);
         break;
      case VERBPASTNEG:
         match(VERBPASTNEG);
         break;
      case VERB:
         match(VERB);
         break;
      case VERBNEG:
         match(VERBNEG);
         break;
      default:
         syntaxerror2("<tense>", saved_lexeme);
   }
}


//----------- Driver ---------------------------

string filename;
// The new test driver to start the parser
// Done by:  **
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
   story();
  //** closes the input file 
   fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

