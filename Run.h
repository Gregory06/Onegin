//
// Created by Greg Postnikoff
//

#ifndef ONEGINBRAT_RUN_H
#define ONEGINBRAT_RUN_H


#include <iostream>
#include <sys/stat.h>
#include <assert.h>

struct Text {

    char * str = NULL;
    int len = 0;

};

struct DevidedBuffer {

    struct Text * text = NULL;

    int strquan = 0;

};

#include "Functions_Name.h"

const int SUCCESS_OPEN_FILE = 1;
const int ERROR_OPEN_FILE = 0;

void Run(char * filename) {

    FILE *FileIn = NULL;

    printf("###Gregory Postnikov (c) 2017\n"
                   "###Evgeny Onegin\n");

    printf("Please, enter file for sort _ ");

    struct DevidedBuffer devided_buffer;

    CreateBuffer(filename, FileIn, &devided_buffer);

    printf("\n");

    qsort(devided_buffer.text, devided_buffer.strquan, sizeof(struct Text), Strcmp);

    printf("Sort in right order:\n\n");

    PrintBuf(&devided_buffer);

    qsort(devided_buffer.text, devided_buffer.strquan, sizeof(struct Text), StrcmpReverse);

    printf("Sort in Reversee order:\n\n");

    PrintBuf(&devided_buffer);

}

#include "Function.h"


#endif //ONEGINBRAT_RUN_H
