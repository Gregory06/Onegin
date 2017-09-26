#include <iostream>
#include <sys/stat.h>
#include <assert.h>


const int SUCCESS_OPEN_FILE = 1;
const int ERROR_OPEN_FILE = 0;


int OpenFile(FILE ** FileIn, char * filename);

int StringQuan(char * buffer, int size);

void Devide(char * buffer, char ** text, int size);

char * CopyFILE(FILE *FileIn, int size);

int Strcmp( const void * str1, const void * str2 );

int StrcmpRevers ( const void * str1, const void * str2 );



int main() {


    setlocale(LC_ALL, "RUSSIAN");

    FILE * FileIn = NULL;

    printf("###Gregory Postnikov (c) 2017\n"
                   "###Evgeny Onegin\n");

    printf("Please, enter file for sort _ ");

    char filename[256] = {};
    scanf("%s", filename);

    int Result = OpenFile(&FileIn, filename);

    assert(Result == SUCCESS_OPEN_FILE);

    struct stat st = {};
    stat( filename, &st);

    char * buffer = CopyFILE( FileIn, st.st_size + 1 );

    buffer[st.st_size] = '\n';

    int strquan = StringQuan(buffer, st.st_size);

    char * text[strquan];

    Devide(buffer, text,
           st.st_size);
    printf("\n");

    qsort ( text, strquan, sizeof(char *), Strcmp );

    printf("Sort in right order:\n\n");

    for ( int i = 0; i < strquan; i++)
        if ( strlen(text[i]) > 2 )
            printf("'%s'\n", text[i]);

    printf("\n");

    qsort ( text, strquan, sizeof(char *), StrcmpRevers );

    printf("Sort in reverse order:\n\n");

    for ( int i = 0; i < strquan; i++)
        if (strlen(text[i]) > 2)
            printf("'%s'\n", text[i]);

    return 0;

}



int StrcmpRevers( const void * str1, const void * str2 ) {

    char * s1 = * (char **) str1;
    char * s2 = * (char **) str2;

    int leng = 0;

    int j = 0;

    while ( ispunct(s1[strlen(s1) - 1 - j]))
        j++;

    if ( strlen(s1) < strlen(s2)) {
        leng = strlen(s1);
        for (int i = 0; i < leng - j; i++) {

            if (s1[leng - j - (1 + i)] > s2[strlen(s2) - j - (1 + i)])
                return 1;
            if (s1[leng - j - (1 + i)] < s2[strlen(s2) - j - (1 + i)])
                return -1;
        }
    }
    else {
        leng = strlen(s2);
        for ( int i = 0; i < leng; i++ ) {

                if (  s1[strlen(s1) - j - (1 + i)] >  s2[leng - j - (1 + i)] )
                    return 1;
                if (  s1[strlen(s1) - j - (1 + i)] <  s2[leng - j - (1 + i)] )
                    return -1;
        }


    }

    if ( strlen(s1) < strlen(s2) )
        return -1;
    if ( strlen(s1) > strlen(s2) )

        return 1;
    if ( strlen(s1) == strlen(s2) )
        return 0;

}



int OpenFile(FILE ** FileIn, char * filename) {

    *FileIn = fopen(filename, "r");

    if (!*FileIn) {

        return ERROR_OPEN_FILE;

    }

    return SUCCESS_OPEN_FILE;

}


int StringQuan(char * buffer, int size) {

    int strquan = 1;

    for (int i = 0; i < size; i++)
        if (buffer[i] == '\n')
            strquan++;

    return strquan;

}


void Devide(char * buffer, char ** text, int size) {

    text[0] = buffer;
    int current = 1;

    for (int i = 1; i < size;) {
        if (buffer[i] == '\n') {
            text[current] = &buffer[i + 1];
            current++;
            buffer[i] = '\0';
        }
        i++;
    }
}


char * CopyFILE(FILE * FileIn, int size) {

    char * buffer = (char *) calloc(size, sizeof(char));
    fread( buffer, sizeof(char), size , FileIn);

    return buffer;

}


int Strcmp( const void * str1, const void * str2 ) {

    return strcmp( * (char **) str1, * (char **) str2 );

}
