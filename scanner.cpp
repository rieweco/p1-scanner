#include <map>
#include <iostream>
#include "scanner.h"
#include "utility.h"

using namespace std;

const string SUPPORTED_ALPHABET = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789=<>!:+-*/%.(){}[],;"; 

const int FSA_TABLE_ROW_INDEX_END_OF_FILE = 0;
const int FSA_TABLE_ROW_INDEX_IDENTIFIER = 1;
const int FSA_TABLE_ROW_INDEX_INTEGER = 2;
const int FSA_TABLE_ROW_INDEX_OPERATOR_ASSIGN = 3;
const int FSA_TABLE_ROW_INDEX_OPERATOR_LESS_THAN = 4;
const int FSA_TABLE_ROW_INDEX_OPERATOR_GREATER_THAN = 5;
const int FSA_TABLE_ROW_INDEX_OPERATOR_COLON = 6;
const int FSA_TABLE_ROW_INDEX_OPERATOR_ADDITION = 7;
const int FSA_TABLE_ROW_INDEX_OPERATOR_SUBTRACTION = 8;
const int FSA_TABLE_ROW_INDEX_OPERATOR_MULTIPLICATION = 9;
const int FSA_TABLE_ROW_INDEX_OPERATOR_DIVISION = 10;
const int FSA_TABLE_ROW_INDEX_OPERATOR_MODULO = 11;
const int FSA_TABLE_ROW_INDEX_OPERATOR_CONCATENATION = 12;
const int FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_PARENTHESIS = 13;
const int FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_PARENTHESIS = 14;
const int FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_CURLY_BRACE = 15;
const int FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_CURLY_BRACE = 16;
const int FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_SQUARE_BRACKET = 17;
const int FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_SQUARE_BRACKET = 18;
const int FSA_TABLE_ROW_INDEX_DELIMITER_COMMA = 19;
const int FSA_TABLE_ROW_INDEX_DELIMITER_SEMICOLON = 20;

const map<const TOKEN_IDENTIFIER, const int> TOKEN_IDENTIFIER_TO_FSA_TABLE_ROW_INDEX_MAP = {
        {END_OF_FILE,                       FSA_TABLE_ROW_INDEX_END_OF_FILE},
        {IDENTIFIER,                        FSA_TABLE_ROW_INDEX_IDENTIFIER},
        {INTEGER,                           FSA_TABLE_ROW_INDEX_INTEGER},
        {OPERATOR_EQUALS,                   FSA_TABLE_ROW_INDEX_OPERATOR_ASSIGN},
        {OPERATOR_LESS_THAN,                FSA_TABLE_ROW_INDEX_OPERATOR_LESS_THAN},
        {OPERATOR_GREATER_THAN,             FSA_TABLE_ROW_INDEX_OPERATOR_GREATER_THAN},
        {OPERATOR_COLON,                    FSA_TABLE_ROW_INDEX_OPERATOR_COLON},
        {OPERATOR_PLUS,                     FSA_TABLE_ROW_INDEX_OPERATOR_ADDITION},
        {OPERATOR_MINUS,                    FSA_TABLE_ROW_INDEX_OPERATOR_SUBTRACTION},
        {OPERATOR_ASTERISK,                 FSA_TABLE_ROW_INDEX_OPERATOR_MULTIPLICATION},
        {OPERATOR_FORWARD_SLASH,            FSA_TABLE_ROW_INDEX_OPERATOR_DIVISION},
        {OPERATOR_PERCENT,                  FSA_TABLE_ROW_INDEX_OPERATOR_MODULO},
        {DELIMITER_PERIOD,                  FSA_TABLE_ROW_INDEX_OPERATOR_CONCATENATION},
        {DELIMITER_LEFT_PARENTHESIS,        FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_PARENTHESIS},
        {DELIMITER_RIGHT_PARENTHESIS,       FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_PARENTHESIS},
        {DELIMITER_LEFT_CURLY_BRACE,        FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_CURLY_BRACE},
        {DELIMITER_RIGHT_CURLY_BRACE,       FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_CURLY_BRACE},
        {DELIMITER_LEFT_SQUARE_BRACKET,     FSA_TABLE_ROW_INDEX_DELIMITER_LEFT_SQUARE_BRACKET},
        {DELIMITER_RIGHT_SQUARE_BRACKET,    FSA_TABLE_ROW_INDEX_DELIMITER_RIGHT_SQUARE_BRACKET},
        {DELIMITER_COMMA,                   FSA_TABLE_ROW_INDEX_DELIMITER_COMMA},
        {DELIMITER_SEMICOLON,               FSA_TABLE_ROW_INDEX_DELIMITER_SEMICOLON}
};

const int FSA_TABLE_COLUMN_INDEX_END_OF_FILE = 0;
const int FSA_TABLE_COLUMN_INDEX_WHITE_SPACE = 1;
const int FSA_TABLE_COLUMN_INDEX_LETTER = 2;
const int FSA_TABLE_COLUMN_INDEX_DECIMAL = 3;
const int FSA_TABLE_COLUMN_INDEX_EQUAL = 4;
const int FSA_TABLE_COLUMN_INDEX_LESS_THAN = 5;
const int FSA_TABLE_COLUMN_INDEX_GREATER_THAN = 6;
const int FSA_TABLE_COLUMN_INDEX_COLON = 7;
const int FSA_TABLE_COLUMN_INDEX_PLUS = 8;
const int FSA_TABLE_COLUMN_INDEX_MINUS = 9;
const int FSA_TABLE_COLUMN_INDEX_ASTERISK = 10;
const int FSA_TABLE_COLUMN_INDEX_FORWARD_SLASH = 11;
const int FSA_TABLE_COLUMN_INDEX_PERCENT = 12;
const int FSA_TABLE_COLUMN_INDEX_PERIOD = 13;
const int FSA_TABLE_COLUMN_INDEX_LEFT_PARENTHESIS = 14;
const int FSA_TABLE_COLUMN_INDEX_RIGHT_PARENTHESIS = 15;
const int FSA_TABLE_COLUMN_INDEX_LEFT_CURLY_BRACE = 16;
const int FSA_TABLE_COLUMN_INDEX_RIGHT_CURLY_BRACE = 17;
const int FSA_TABLE_COLUMN_INDEX_LEFT_SQUARE_BRACKET = 18;
const int FSA_TABLE_COLUMN_INDEX_RIGHT_SQUARE_BRACKET = 19;
const int FSA_TABLE_COLUMN_INDEX_COMMA = 20;
const int FSA_TABLE_COLUMN_INDEX_SEMICOLON = 21;

const map<const char, const int> CHARACTER_TO_FSA_TABLE_COLUMN_INDEX_MAP = {
        {' ',  FSA_TABLE_COLUMN_INDEX_WHITE_SPACE},
        {'\n', FSA_TABLE_COLUMN_INDEX_WHITE_SPACE},
        {'a',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'b',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'c',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'d',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'e',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'f',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'g',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'h',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'i',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'j',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'k',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'l',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'m',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'n',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'o',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'p',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'q',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'r',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'s',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'t',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'u',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'v',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'w',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'x',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'y',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'z',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'A',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'B',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'C',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'D',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'E',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'F',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'G',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'H',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'I',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'J',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'K',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'L',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'M',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'N',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'O',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'P',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'Q',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'R',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'S',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'T',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'U',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'V',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'W',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'X',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'Y',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'Z',  FSA_TABLE_COLUMN_INDEX_LETTER},
        {'0',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'1',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'2',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'3',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'4',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'5',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'6',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'7',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'8',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'9',  FSA_TABLE_COLUMN_INDEX_DECIMAL},
        {'=',  FSA_TABLE_COLUMN_INDEX_EQUAL},
        {'<',  FSA_TABLE_COLUMN_INDEX_LESS_THAN},
        {'>',  FSA_TABLE_COLUMN_INDEX_GREATER_THAN},
        {':',  FSA_TABLE_COLUMN_INDEX_COLON},
        {'+',  FSA_TABLE_COLUMN_INDEX_PLUS},
        {'-',  FSA_TABLE_COLUMN_INDEX_MINUS},
        {'*',  FSA_TABLE_COLUMN_INDEX_ASTERISK},
        {'/',  FSA_TABLE_COLUMN_INDEX_FORWARD_SLASH},
        {'%',  FSA_TABLE_COLUMN_INDEX_PERCENT},
        {'.',  FSA_TABLE_COLUMN_INDEX_PERIOD},
        {'(',  FSA_TABLE_COLUMN_INDEX_LEFT_PARENTHESIS},
        {')',  FSA_TABLE_COLUMN_INDEX_RIGHT_PARENTHESIS},
        {'{',  FSA_TABLE_COLUMN_INDEX_LEFT_CURLY_BRACE},
        {'}',  FSA_TABLE_COLUMN_INDEX_RIGHT_CURLY_BRACE},
        {'[',  FSA_TABLE_COLUMN_INDEX_LEFT_SQUARE_BRACKET},
        {']',  FSA_TABLE_COLUMN_INDEX_RIGHT_SQUARE_BRACKET},
        {',',  FSA_TABLE_COLUMN_INDEX_COMMA},
        {';',  FSA_TABLE_COLUMN_INDEX_SEMICOLON}
};

const int FINAL_STATE_END_OF_FILE = 100;
const int FINAL_STATE_IDENTIFIER = 101;
const int FINAL_STATE_INTEGER = 102;
const int FINAL_STATE_OPERATOR_EQUALS = 103;
const int FINAL_STATE_OPERATOR_LESS_THAN = 104;
const int FINAL_STATE_OPERATOR_GREATER_THAN = 105;
const int FINAL_STATE_OPERATOR_COLON = 106;
const int FINAL_STATE_OPERATOR_PLUS = 107;
const int FINAL_STATE_OPERATOR_MINUS = 108;
const int FINAL_STATE_OPERATOR_ASTERISK = 109;
const int FINAL_STATE_OPERATOR_FORWARD_SLASH = 110;
const int FINAL_STATE_OPERATOR_PERCENT = 111;
const int FINAL_STATE_OPERATOR_PERIOD = 112;
const int FINAL_STATE_DELIMITER_LEFT_PARENTHESIS = 113;
const int FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS = 114;
const int FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE = 115;
const int FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE = 116;
const int FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET = 117;
const int FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET = 118;
const int FINAL_STATE_DELIMITER_COMMA = 119;
const int FINAL_STATE_DELIMITER_SEMICOLON = 120;

const int INITIAL_STATE = 0;
const int INTERMEDIATE_STATE_IDENTIFIER = 1;
const int INTERMEDIATE_STATE_INTEGER = 2;
const int INTERMEDIATE_STATE_OPERATOR_EQUALS = 3;
const int INTERMEDIATE_STATE_OPERATOR_LESS_THAN = 4;
const int INTERMEDIATE_STATE_OPERATOR_GREATER_THAN = 5;
const int INTERMEDIATE_STATE_OPERATOR_COLON = 6;
const int INTERMEDIATE_STATE_OPERATOR_PLUS = 7;
const int INTERMEDIATE_STATE_OPERATOR_MINUS = 8;
const int INTERMEDIATE_STATE_OPERATOR_ASTERISK = 9;
const int INTERMEDIATE_STATE_OPERATOR_FORWARD_SLASH = 10;
const int INTERMEDIATE_STATE_OPERATOR_PERCENT = 11;
const int INTERMEDIATE_STATE_OPERATOR_PERIOD = 12;
const int INTERMEDIATE_STATE_DELIMITER_LEFT_PARENTHESIS = 13;
const int INTERMEDIATE_STATE_DELIMITER_RIGHT_PARENTHESIS = 14;
const int INTERMEDIATE_STATE_DELIMITER_LEFT_CURLY_BRACE = 15;
const int INTERMEDIATE_STATE_DELIMITER_RIGHT_CURLY_BRACE = 16;
const int INTERMEDIATE_STATE_DELIMITER_LEFT_SQUARE_BRACKET = 17;
const int INTERMEDIATE_STATE_DELIMITER_RIGHT_SQUARE_BRACKET = 18;
const int INTERMEDIATE_STATE_DELIMITER_COMMA = 19;
const int INTERMEDIATE_STATE_DELIMITER_SEMICOLON = 20;


const int FSA_TABLE[QUANTITY_TOKENS][QUANTITY_CHARACTER_CLASSES] = {
	{FINAL_STATE_END_OF_FILE,	INITIAL_STATE,	INTERMEDIATE_STATE_IDENTIFIER,	INTERMEDIATE_STATE_INTEGER,	INTERMEDIATE_STATE_OPERATOR_EQUALS,	INTERMEDIATE_STATE_OPERATOR_LESS_THAN,	INTERMEDIATE_STATE_OPERATOR_GREATER_THAN,	INTERMEDIATE_STATE_OPERATOR_COLON,	INTERMEDIATE_STATE_OPERATOR_PLUS,	INTERMEDIATE_STATE_OPERATOR_MINUS,	INTERMEDIATE_STATE_OPERATOR_ASTERISK,	INTERMEDIATE_STATE_OPERATOR_FORWARD_SLASH,	INTERMEDIATE_STATE_OPERATOR_PERCENT,	INTERMEDIATE_STATE_OPERATOR_PERIOD,	INTERMEDIATE_STATE_DELIMITER_LEFT_PARENTHESIS,	INTERMEDIATE_STATE_DELIMITER_RIGHT_PARENTHESIS,	INTERMEDIATE_STATE_DELIMITER_LEFT_CURLY_BRACE,	INTERMEDIATE_STATE_DELIMITER_RIGHT_CURLY_BRACE,	INTERMEDIATE_STATE_DELIMITER_LEFT_SQUARE_BRACKET,	INTERMEDIATE_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,	INTERMEDIATE_STATE_DELIMITER_COMMA,	INTERMEDIATE_STATE_DELIMITER_SEMICOLON},

        {FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	INTERMEDIATE_STATE_IDENTIFIER,	INTERMEDIATE_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER,	FINAL_STATE_IDENTIFIER, FINAL_STATE_IDENTIFIER},

        {FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	INTERMEDIATE_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER,	FINAL_STATE_INTEGER},

        {FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS,	FINAL_STATE_OPERATOR_EQUALS},

        {FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN,	FINAL_STATE_OPERATOR_LESS_THAN, FINAL_STATE_OPERATOR_LESS_THAN},
	
        {FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN,	FINAL_STATE_OPERATOR_GREATER_THAN},
	
        {FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON,	FINAL_STATE_OPERATOR_COLON},
	
        {FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS,	FINAL_STATE_OPERATOR_PLUS},
	
        {FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS,	FINAL_STATE_OPERATOR_MINUS},
	
        {FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK,	FINAL_STATE_OPERATOR_ASTERISK},
	
        {FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,            FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH,	FINAL_STATE_OPERATOR_FORWARD_SLASH},
	
        {FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT,	FINAL_STATE_OPERATOR_PERCENT},
	
        {FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD,	FINAL_STATE_OPERATOR_PERIOD},

        {FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,	FINAL_STATE_DELIMITER_LEFT_PARENTHESIS},

        {FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,	FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,              FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,                  FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,        FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,        FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,       FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,	FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,	FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS},

        {FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,	FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,               FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,                   FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,         FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,         FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,        FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE},

        {FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,              FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,                  FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,        FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,        FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,       FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE},

        {FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,	FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,            FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,                FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,      FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,      FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET},

        {FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,	FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,           FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,               FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,     FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,    FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET},

        {FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA,	FINAL_STATE_DELIMITER_COMMA},

        {FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON,	FINAL_STATE_DELIMITER_SEMICOLON}
};

const map<const int, const TOKEN_IDENTIFIER> STATE_TO_TOKEN_IDENTIFIER_MAP = {
        {FINAL_STATE_END_OF_FILE,                                  END_OF_FILE},
        {FINAL_STATE_IDENTIFIER,                                   IDENTIFIER},
        {FINAL_STATE_INTEGER,                                      INTEGER},
        {FINAL_STATE_OPERATOR_EQUALS,                              OPERATOR_EQUALS},
        {FINAL_STATE_OPERATOR_LESS_THAN,                           OPERATOR_LESS_THAN},
        {FINAL_STATE_OPERATOR_GREATER_THAN,                        OPERATOR_GREATER_THAN},
        {FINAL_STATE_OPERATOR_COLON,                               OPERATOR_COLON},
        {FINAL_STATE_OPERATOR_PLUS,                                OPERATOR_PLUS},
        {FINAL_STATE_OPERATOR_MINUS,                               OPERATOR_MINUS},
        {FINAL_STATE_OPERATOR_ASTERISK,                            OPERATOR_ASTERISK},
        {FINAL_STATE_OPERATOR_FORWARD_SLASH,                       OPERATOR_FORWARD_SLASH},
        {FINAL_STATE_OPERATOR_PERCENT,                             OPERATOR_PERCENT},
        {FINAL_STATE_OPERATOR_PERIOD,                              DELIMITER_PERIOD},
        {FINAL_STATE_DELIMITER_LEFT_PARENTHESIS,                   DELIMITER_LEFT_PARENTHESIS},
        {FINAL_STATE_DELIMITER_RIGHT_PARENTHESIS,                  DELIMITER_RIGHT_PARENTHESIS},
        {FINAL_STATE_DELIMITER_LEFT_CURLY_BRACE,                   DELIMITER_LEFT_CURLY_BRACE},
        {FINAL_STATE_DELIMITER_RIGHT_CURLY_BRACE,                  DELIMITER_RIGHT_CURLY_BRACE},
        {FINAL_STATE_DELIMITER_LEFT_SQUARE_BRACKET,                DELIMITER_LEFT_SQUARE_BRACKET},
        {FINAL_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,               DELIMITER_RIGHT_SQUARE_BRACKET},
        {FINAL_STATE_DELIMITER_COMMA,                              DELIMITER_COMMA},
        {FINAL_STATE_DELIMITER_SEMICOLON,                          DELIMITER_SEMICOLON},
        {INITIAL_STATE,                                            END_OF_FILE},
        {INTERMEDIATE_STATE_IDENTIFIER,                            IDENTIFIER},
        {INTERMEDIATE_STATE_INTEGER,                               INTEGER},
        {INTERMEDIATE_STATE_OPERATOR_EQUALS,                       OPERATOR_EQUALS},
        {INTERMEDIATE_STATE_OPERATOR_LESS_THAN,                    OPERATOR_LESS_THAN},
        {INTERMEDIATE_STATE_OPERATOR_GREATER_THAN,                 OPERATOR_GREATER_THAN},
        {INTERMEDIATE_STATE_OPERATOR_COLON,                        OPERATOR_COLON},
        {INTERMEDIATE_STATE_OPERATOR_PLUS,                         OPERATOR_PLUS},
        {INTERMEDIATE_STATE_OPERATOR_MINUS,                        OPERATOR_MINUS},
        {INTERMEDIATE_STATE_OPERATOR_ASTERISK,                     OPERATOR_ASTERISK},
        {INTERMEDIATE_STATE_OPERATOR_FORWARD_SLASH,                OPERATOR_FORWARD_SLASH},
        {INTERMEDIATE_STATE_OPERATOR_PERCENT,                      OPERATOR_PERCENT},
        {INTERMEDIATE_STATE_OPERATOR_PERIOD,                       DELIMITER_PERIOD},
        {INTERMEDIATE_STATE_DELIMITER_LEFT_PARENTHESIS,            DELIMITER_LEFT_PARENTHESIS},
        {INTERMEDIATE_STATE_DELIMITER_RIGHT_PARENTHESIS,           DELIMITER_RIGHT_PARENTHESIS},
        {INTERMEDIATE_STATE_DELIMITER_LEFT_CURLY_BRACE,            DELIMITER_LEFT_CURLY_BRACE},
        {INTERMEDIATE_STATE_DELIMITER_RIGHT_CURLY_BRACE,           DELIMITER_RIGHT_CURLY_BRACE},
        {INTERMEDIATE_STATE_DELIMITER_LEFT_SQUARE_BRACKET,         DELIMITER_LEFT_SQUARE_BRACKET},
        {INTERMEDIATE_STATE_DELIMITER_RIGHT_SQUARE_BRACKET,        DELIMITER_RIGHT_SQUARE_BRACKET},
        {INTERMEDIATE_STATE_DELIMITER_COMMA,                       DELIMITER_COMMA},
        {INTERMEDIATE_STATE_DELIMITER_SEMICOLON,                   DELIMITER_SEMICOLON},
};

Scanner::Scanner() = default;

Scanner::~Scanner() = default;


Token *Scanner::getNextToken(const std::string &rawData, int currentIndex, int currentLineNumber) const {
    int state = INITIAL_STATE;
    TOKEN_IDENTIFIER candidateToken = END_OF_FILE;
    string value;
    bool stateIsNotFinal = true;

    while (stateIsNotFinal) {
        char nextChar = rawData[currentIndex];
        if (nextChar && nextChar != '&') {
            try {
                state = FSA_TABLE[TOKEN_IDENTIFIER_TO_FSA_TABLE_ROW_INDEX_MAP.at(candidateToken)][CHARACTER_TO_FSA_TABLE_COLUMN_INDEX_MAP.at(nextChar)];
		cout << "char: " << nextChar << endl;
                candidateToken = STATE_TO_TOKEN_IDENTIFIER_MAP.at(state);
            } catch (std::out_of_range &exception) {
                cerr << string("Scanner Error: Character not in alphabet, \"") + nextChar + "\", on line \"" + to_string(currentLineNumber) + "\".\n";
                exit(-1);
            }
        } else {
            state = FINAL_STATE_END_OF_FILE;
        }

        if (state >= INITIAL_STATE) {
            if (state < FINAL_STATE_END_OF_FILE) {

                value += nextChar;

                currentIndex++;
            } else {
                stateIsNotFinal = false;
            }
        } else {
            cerr << string("Scanner Error: Invalid token, \"" + TOKEN_IDENTIFIER_TO_TOKEN_NAME_MAP.at(candidateToken) + "\",  on line \"" + to_string(currentLineNumber) + "\".\n");
            exit(-1);
        }
    }

    if (candidateToken == IDENTIFIER) {
        const string &trimmedValue = trim(value);

        if (KEYWORD_LITERAL_TO_KEYWORD_TOKEN_IDENTIFIER_MAP.find(trimmedValue) != KEYWORD_LITERAL_TO_KEYWORD_TOKEN_IDENTIFIER_MAP.end()) {
            candidateToken = KEYWORD_LITERAL_TO_KEYWORD_TOKEN_IDENTIFIER_MAP.at(trimmedValue);
        }
    }
    Token *token = new Token(candidateToken, value, to_string(currentLineNumber));
    
    return token;
}

