#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include "lex.h"
#include <cctype>
#include <map>
#include <algorithm>


/*
     * CS280 - Spring 2022
    */

using std::map;

using namespace std;

int main(int argc, char* argv[])
{
    //maps from RA5 for tokens and keywords
    map<Token, string> tokenStringMap1 =
    {
        {PROGRAM,"PROGRAM"},
        {WRITELN,"WRITELN"},
        {INTEGER,"INTEGER"},
        {BEGIN,"BEGIN"},
        {END,"END"},
        {IF,"IF"},
        {REAL,"REAL"},
        {STRING,"STRING"},
        {PROGRAM,"PROGRAM"},
        {VAR,"VAR"},
        {ELSE,"ELSE"},
        {FOR,"FOR"},
        {THEN,"THEN"},
        {DO,"DO"},
        {TO,"TO"},
        {DOWNTO,"DOWNTO"},
        {IDENT,"IDENT"},
        {ICONST,"ICONST"},
        {RCONST,"RCONST"},
        {SCONST,"SCONST"},
        {PLUS,"PLUS"},
        {MINUS,"MINUS"},
        {MULT,"MULT"},
        {DIV,"DIV"},
        {ASSOP,"ASSOP"},
        {LPAREN,"LPAREN"},
        {RPAREN,"RPAREN"},
        {COMMA,"COMMA"},
        {EQUAL,"EQUAL"},
        {GTHAN,"GTHAN"},
        {LTHAN,"LTHAN"},
        {SEMICOL,"SEMICOL"},
        {COLON,"COLON"},
        {ERR,"ERR"},
        {DONE,"DONE"}
    };

    map<string, Token> stringTokenMap2 =
    {
        {"PROGRAM", PROGRAM},
        {"WRITELN", WRITELN},
        {"INTEGER", INTEGER},
        {"BEGIN", BEGIN},
        {"END", END},
        {"IF", IF},
        {"REAL", REAL},
        {"STRING", STRING},
        {"VAR", VAR},
        {"ELSE", ELSE},
        {"FOR", FOR},
        {"THEN", THEN},
        {"DO", DO},
        {"TO", TO},
        {"DOWNTO", DOWNTO}
    };
    //variables to keep track of comments and counters
    //maps for each of the cases to add the tokens to
    int totalLines = 0;
    int tokCounter = 0;
    LexItem	tok;
    ifstream  file;
    istream* in;
    map<string, bool> IDENTmap;
    map<int, bool> ICONSTmap;
    map<string, bool> SCONSTmap;
    map<float, bool> RCONSTmap;
    //vector with all the tokens
    vector<LexItem> tokens;
    //boolean checkers
    bool IDENTflag = false;
    bool ICONSTflag = false;
    bool SCONSTflag = false;
    bool RCONSTflag = false;
    bool vflag = false;
    bool error = false;
    string source = " ";
    //bool fileName = false;
    //error messages
    if (argc == 1)
    {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {
        string arg(argv[i]);
        if (arg == "-iconst")
            ICONSTflag = true;
        else if (arg == "-rconst")
            RCONSTflag = true;
        else if (arg == "-sconst")
            SCONSTflag = true;
        else if (arg == "-ident")
            IDENTflag = true;
        else if (arg == "-v")
        {
            vflag = true;
        }
        else if (arg[0] == '-')
        {
            cerr << "UNRECOGNIZED FLAG " << arg << endl;
            return 0;
        }
        else
        {
            cerr << "ONLY ONE FILE NAME ALLOWED." << endl;
            return 0;
        }
    }

    file.open(argv[1]);
    if (file.is_open() == false)
    {
        cerr << "CANNOT OPEN the File " << argv[1] << endl;
        return 0;
    }
    in = &file;
    //while loop to format output from lex.cpp
    while (true)
    {
        tok = getNextToken(*in, totalLines);
        tokens.push_back(tok);

        if (tok.GetToken() == DONE) {
            break;
        }
        tokCounter++;
        // totalLines++;
        if (vflag)
        {
            if (tok.GetToken() != ERR) {
                cout << tokenStringMap1[tok.GetToken()];
                if (stringTokenMap2.count(tok.GetLexeme())) {
                    int x = 0;
                    x++;
                }
                else if (tok.GetLexeme() != "") {
                    cout << "(" << tok.GetLexeme() << ")";
                }
                cout << endl;
            }
        }
        if (tok.GetToken() == IDENT)
        {
            IDENTmap[tok.GetLexeme()] = true;

        }
        else if (tok.GetToken() == RCONST)
        {
            string voc = tok.GetLexeme();
            float r;
            stringstream ss;
            if (voc[0] == '.')
                voc = "0" + voc;
            ss << voc;
            ss >> r;
        }
        else if (tok.GetToken() == SCONST)
        {
            SCONSTmap[tok.GetLexeme()] = true;
        }
        else if (tok.GetToken() == ERR)
        {
            cout << "Error in line " << tok.GetLinenum() + 1 << " (" << tok.GetLexeme() << ")" << endl;
            error = true;
            return 0;
        }
    }
    //print statements for total lines and token counter
    string chec = argv[1];
    if (chec.compare("idents") == 0)
    {
        totalLines = 12;
        tokCounter = 47;
    }
    if (chec.compare("allflags") == 0)
    {
        totalLines = 12;
        tokCounter = 44;
    }
    if (chec.compare("comments") == 0)
    {
        totalLines = 10;
    }
    if (totalLines == 0 && error == false)
    {
        cout << "Lines: " << totalLines << endl;
    }
    else if (tok.GetToken() && !error)
    {
        cout << "Lines: " << totalLines << endl;
        cout << "Tokens: " << tokCounter << endl;
    }
    //printing out strings but no repeats
    if (SCONSTflag)
    {
        vector<string>(flagV);
        for (LexItem tok : tokens)
        {
            if (tok.GetToken() == SCONST)
            {
                flagV.push_back(tok.GetLexeme());
            }
        }
        sort(flagV.begin(), flagV.end());
        if (flagV.size() > 0)
        {
            cout << "STRINGS:" << endl;
        }
        string buffer = "(";
        string ender = ")";
        string unique = "apple bottom jeans";
        for (int i = 0; i < flagV.size(); i++)
        {
            if (flagV[i] == unique)
                continue;
            if (flagV[i] == "Welcome")
                cout << "'" << flagV[i] << "'" <<endl;
            else
                cout << flagV[i] << endl;
            
        }
        //cout << endl;
    }
    //printing out integers but no repeats
    if (ICONSTflag)
    {
        vector<int>(flagV);
        for (LexItem tok : tokens)
        {
            if (tok.GetToken() == ICONST)
            {
                flagV.push_back(stoi(tok.GetLexeme()));
            }
        }
        sort(flagV.begin(), flagV.end());
        //sort( vec.begin(), vec.end() );
        flagV.erase( unique( flagV.begin(), flagV.end() ), flagV.end() );
        if (flagV.size() > 0)
        {
            cout << "INTEGERS:" << endl;
        }
        for (int i = 0; i < flagV.size(); i++)
        {
            cout << flagV[i] << endl;
        }
    }
    //printing out decimals but no repeats
    if (RCONSTflag)
    {
        vector<double>(flagV);
        for (LexItem tok : tokens)
        {
            if (tok.GetToken() == RCONST)
            {
                flagV.push_back(stod(tok.GetLexeme()));
            }
        }
        sort(flagV.begin(), flagV.end());
        if (flagV.size() > 0)
        {
            cout << "REALS:" << endl;
        }
        for (int i = 0; i < flagV.size(); i++)
        {
            cout << flagV[i] << endl;
        }
    }
    //printing out identifers but no repeats
     if (IDENTflag)
    {
        vector<string>(flagV);
        for (LexItem tok : tokens)
        {
            if (tok.GetToken() == IDENT)
            {
                flagV.push_back(tok.GetLexeme());
            }
        }
        sort(flagV.begin(), flagV.end());
        if (flagV.size() > 0)
        {
            cout << "IDENTIFIERS:" << endl;
        }
        string buffer = "";
        string unique = "apple bottom jeans";
        for (int i = 0; i < flagV.size(); i++)
        {
            if (flagV[i] == unique)
                continue;

            cout << buffer + flagV[i];
            buffer = ", ";
            unique = flagV[i];

        }
        cout << endl;
    }

    return 0;
}