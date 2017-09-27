//
// Created by Greg Postnikoff
//

#ifndef ONEGINBRAT_FUNCTION_H
#define ONEGINBRAT_FUNCTION_H


int StrcmpReverse( const void * str1, const void * str2 ) {

    Text * s1 = (Text *) str1;
    Text * s2 = (Text *) str2;

    int leng = 0;

    int FirstPunct1 = 0, FirstPunct2 = 0;

    while (ispunct(s1->str[s1->len - 2 - FirstPunct1]))
        FirstPunct1++;
    while (ispunct(s2->str[s2->len - 2 - FirstPunct2]))
        FirstPunct2++;

    if ( s1->len < s2->len ) {
        leng = s1->len;
        for (int i = 0; i < leng - FirstPunct1; i++) {

            if (s1->str[leng - FirstPunct1 - (2 + i)] > s2->str[s2->len - FirstPunct2 - (2 + i)])
                return 1;
            if (s1->str[leng - FirstPunct1 - (2 + i)] < s2->str[s2->len - FirstPunct2 - (2 + i)])
                return -1;
        }
    }
    else {
        leng = s2->len;
        for ( int i = 0; i < leng - FirstPunct2; i++ ) {

            if (  s1->str[s1->len - FirstPunct1 - (2 + i)] >  s2->str[leng - FirstPunct2 - (2 + i)] )
                return 1;
            if (  s1->str[s1->len - FirstPunct1 - (2 + i)] <  s2->str[leng - FirstPunct2 - (2 + i)] )
                return -1;
        }


    }

    if ( s1->len < s2->len )
        return -1;
    if ( s1->len > s2->len )

        return 1;
    if ( s1->len == s2->len )
        return 0;

}


int OpenFile(FILE ** FileIn, const  char * filename) {

    *FileIn = fopen(filename, "r");

    if (!*FileIn) {

        return ERROR_OPEN_FILE;

    }

    return SUCCESS_OPEN_FILE;

}


int StringQuan( const char * buffer, const int size) {

    int strquan = 1;

    for (int i = 0; i < size; i++)
        if (buffer[i] == '\n')
            strquan++;

    return strquan;

}


void Devide(char * buffer, struct Text * text, const int size) {

    text[0].str = buffer;
    int current = 1;

    for (int i = 1; i < size; i++, text[current - 1].len++ )
        if (buffer[i] == '\n') {
            text[current].str = &buffer[i + 1];
            current++;
            buffer[i] = '\0';
        }

}


char * ReadFILE(FILE * FileIn, const int size) {

    char * buffer = (char *) calloc(size, sizeof(char));
    fread( buffer, sizeof(char), size , FileIn);

    return buffer;

}


int Strcmp( const void * str1, const void * str2 ) {

    struct Text * s1 = (struct Text *) str1;
    struct Text * s2 = (struct Text *) str2;

    int j = 0, m = 0;

    while (ispunct(s1->str[j]))
        j++;
    while (ispunct(s2->str[m]))
        m++;

    return strcmp( &s1->str[j], &s2->str[m] );

}


void CreateBuffer( char * filename, FILE * FileIn, struct DevidedBuffer * devided_buffer) {

    const int Result = OpenFile(&FileIn, filename);

    assert(Result == SUCCESS_OPEN_FILE);

    struct stat st = {};
    stat(filename, &st);

    char *buffer = ReadFILE(FileIn, st.st_size + 1);

    buffer[st.st_size] = '\n';

    const int strquan = StringQuan(buffer, st.st_size);

    struct Text * text = (struct Text *) calloc(strquan, sizeof(Text));

    Devide(buffer, text, st.st_size);

    devided_buffer->text = text;

    devided_buffer->strquan = strquan;

}


void PrintBuf(struct DevidedBuffer * devided_buffer) {

    for (int i = 0; i < devided_buffer->strquan; i++)
        if (devided_buffer->text[i].len > 2)
            printf("'%s'\n", devided_buffer->text[i].str);

}


#endif //ONEGINBRAT_FUNCTION_H
