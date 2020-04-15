/*
 * karan
 * CS280
 * Fall 2019
 */

#include <functional>
#include <iostream>
#include <fstream>
#include <string>


#include "parse.h"
#include "lex.h"

using namespace std;
int main(int argc, char *argv[]){
   ifstream file;
    istream *in;
    int linenum = 0;
 
    if( argc == 1 ) {
        in = &cin;
    }
     
    else if( argc == 2 ) {
        file.open(argv[1]);
        if( file.is_open() == false ) {
            cout << "COULD NOT OPEN " << argv[1] << endl;
            return 1;
        }
        in = &file;
    }
 
    else {
        cout << "TOO MANY FILENAMES" << endl;
        return 1;
    }
 
    
    ParseTree *prog = Prog(*in, linenum);
    if (prog == 0){
		return 0;
    }
    map<string,bool> declaredId;
    map<string,Val> symbolTable;
    prog -> CheckLetBeforeUse(declaredId);
    try{
        prog->Eval(symbolTable);
    }
    catch(string e){
        cout<< "RUNTIME ERROR" << e << endl;
    }
    return 0;
        
}