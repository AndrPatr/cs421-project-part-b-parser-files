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
// Done by: ** 
void syntaxerror1( token_type expected,string lexeme)
{
  cout<<" Syntax error: expected "<< tokenName[expected] << "but found "<< lexeme <<endl;
  exit (1);
}
// Type of error: ** unexpected token in parser function
// Done by: ** 
void syntaxerror2(string functionName, string lexeme)
{
   cout<< "Syntax error: expected "<<lexeme<< "found in" << functionName<< endl;
   exit(1);
}
///////////////////////////////////////////////End error functions


//************************************** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
// Purpose: **fetch next token from scanner unless 1 is saved already
// Done by: **
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
// Done by: **
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







// Grammar: **
// Done by: **


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
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
