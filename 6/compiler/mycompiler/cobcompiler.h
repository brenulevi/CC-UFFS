#pragma once

#define STR(x) #x

enum LexicalIdentifier
{
    None,
    Keyword = 26,
    Identifier = 28,
    Semicolon = 30,
    Plus = 37,
    OpenBracket = 33,
    CloseBracket = 34,
    Greater = 29,
    GreaterEqual = 40,
    Less = 31,
    LessEqual = 32,
    Equal = 35,
    Porcent = 36
};

void cobcompiler(char* file);