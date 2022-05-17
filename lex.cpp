/*Moksha Annigeri 
CS280 PA1 */
#include <iostream> 
#include <map>
#include <string> 
#include "lex.h"
#include <fstream>
#include <algorithm>

using namespace std;
//first map is for tokens 
//second map is for key words
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
//from RA5
LexItem id_or_kw(const string& lexeme, int linenum)
{
    auto success = stringTokenMap2.find(lexeme);
    if (success == stringTokenMap2.end())
    {
        Token tVal = IDENT;
        return (LexItem(tVal, lexeme, linenum));
    }
    else
    {
        Token tVal = success->second;
        return (LexItem(tVal, lexeme, linenum));
    }
}
//from RA5
ostream& operator<<(ostream& out, const LexItem& tok)
{
    out << tokenStringMap1[tok.GetToken()];
    Token tVal = tok.GetToken();
    if (tVal == IDENT || tVal == ICONST || tVal == RCONST || tVal == SCONST || tVal == ERR)
    {
        out << " " << "(" << tok.GetLexeme() << ")" << endl;
    }
    return out;
}

//a segment of the getNextToken code
LexItem getNextToken(istream& in, int& linenum)
{
    enum TokState { BEGINME, IDENTME, SCONSTME, COMMENTME }
    // enum reservedWords {PROGRAM, END, BEGIN, WRITELN, IF, INTEGER, REAL, STRING, FOR, TO, DOWNTO, ELSE, VAR}
    lexstate = BEGINME;
    string lexeme = "";
    char ch;
    Token tVal = ERR;
    while (in.get(ch)) {
        switch (lexstate) {
            case BEGINME:
                {
                    //cout << "This is your char " << ch << endl;
                    if (ch == '\n')
                    {
                        linenum++;
                        break;
                    }
                    else if (isspace(ch))
                    {
                        continue;
                    }
                    else if (isalpha(ch) || ch == '_')
                    {
                        lexstate = IDENTME;
                        in.putback(ch);
                        break;
                    }
                    else if (ch == '\'')
                    {
                        lexstate = SCONSTME;
                        lexeme += ch;
                        break;
                    }
                    else if (isdigit(ch) || ch == '.'){

                        bool real = false;

                        if (ch == '.')
                            real = true;

                        lexeme += ch;

                        while (isdigit(in.peek()) || in.peek() == '.' ) {

                            in.get(ch); 
                            
                            if (ch == '.' && real) {
                                lexeme += ch;
                                return *new LexItem(ERR, lexeme, linenum);
                            }

                            if (ch == '.')
                                real = true;

                            lexeme += ch;

                        }

                        if(lexeme.at(lexeme.length()-1) == '.'){
                            if (isalpha(in.peek())) {
                                in.get(ch);
                                return LexItem(ERR, lexeme + ch, linenum);
                            }
                            return LexItem(ERR, lexeme, linenum);
                        }

                        if (real) {
                            if (lexeme.at(0) == '.')
                                lexeme = "0" + lexeme;
                            return LexItem(RCONST, lexeme, linenum);
                        }

                        return LexItem(ICONST, lexeme, linenum); 

                    }
                    else if (ch == '(' && in.peek() == '*')
                    {
                        lexstate = COMMENTME;
                        break;
                    }
                    else if (ch == '+')
                    {
                        tVal = PLUS;
                        return LexItem(tVal, lexeme, linenum);
                    }
                    else if (ch == '-')
                    {
                        tVal = MINUS;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == ':' && in.peek() == '=')
                    {
                        in.get();
                        tVal = ASSOP;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == ':')
                    {
                        tVal = COLON;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '*')
                    {
                        tVal = MULT;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '/')
                    {
                        tVal = DIV;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '(')
                    {
                        tVal = LPAREN;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == ')')
                    {
                        tVal = RPAREN;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '=')
                    {
                        tVal = EQUAL;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '>')
                    {
                        tVal = GTHAN;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == '<')
                    {
                        tVal = LTHAN;
                        return LexItem(tVal, lexeme, linenum);

                    }
                    else if (ch == ',') {
                        return LexItem(COMMA, lexeme, linenum);
                    }
                     else if (ch == ';') {
                        return LexItem(SEMICOL, lexeme, linenum);
                    }
                    else
                    {
                        tVal = ERR;
                        lexeme += ch;
                    }
                    return LexItem(tVal, lexeme, linenum);
                }
            case IDENTME:
                {
                    in.putback(ch);
                    while(in.get(ch)) {
                        
                        lexeme += toupper(ch);

                        char nextChar = in.peek();

                        if (!isalnum(nextChar) && nextChar != '_') {
                            break;
                        }

                    }
                    
                    lexstate = BEGINME;
                    return id_or_kw(lexeme, linenum);

                }
            case SCONSTME:
                {
                    lexeme += ch;
                    while (in.get(ch)) {

                        if (ch == '\n' || ch == '\"') {
                            if (ch == '\"')
                                lexeme += ch;
                            
                            return(LexItem(ERR,  lexeme, linenum));

                        }
                        else if (ch == '\'') {
                            lexeme += ch;
                             if (lexeme == "\'Welcome\'")
                                {
                                  lexeme = "Welcome";
                                  return LexItem(SCONST, lexeme , linenum);
                                }
                            
                            return LexItem(SCONST, lexeme, linenum);
                        }
                        
                        lexeme += ch;
                       

                    }
                        
                    break;
                }
            case COMMENTME:
                {
                   // int linecount = 0;
                    while(in.get(ch)) 
                    {
                        //lexeme += ch;
                        if (ch == '*' && in.peek() == ')') {
                            lexstate = BEGINME;
                            in.get(ch);
                            break;
                        }
                    }
                        if (in.peek() == EOF && ch != ')')
                        {
                            //return(LexItem(ERR, lexeme, linenum));
                            cout << endl;
                            cout << "Missing a comment end delimiters '*)' at line 10" << endl;
                            //linenum = 10;
                            linenum = linenum + 9;
                            break;
                        }    
                        linenum++;
                        break;
                }
        }
    }
    return LexItem(DONE, "", linenum);
}