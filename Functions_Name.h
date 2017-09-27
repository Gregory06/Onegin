//
// Created by Greg Postnikoff
//

#ifndef ONEGINBRAT_FUNCTIONS_H
#define ONEGINBRAT_FUNCTIONS_H


int OpenFile(FILE ** FileIn, const char * filename);

int StringQuan( const char * buffer, const int size);

void Devide(char * buffer, Text * text, const int size);

char * ReadFILE(FILE *FileIn, const int size);

int Strcmp( const void * str1, const void * str2 );

int StrcmpReverse ( const void * str1, const void * str2 );

void CreateBuffer( char * filename, FILE * FileIn, struct DevidedBuffer * devided_buffer);

void PrintBuf(struct DevidedBuffer * devided_buffer);

#endif //ONEGINBRAT_FUNCTIONS_H
