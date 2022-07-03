#include "document_analyzer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char**** s_pa_document;

int load_document(const char* document)
{
    char buffer[1024];
    char* buffer_ptr = buffer;
    FILE* fp;
    char c;

    size_t paragraph_count = 10;
    char**** pa_document = malloc(sizeof(char***) * paragraph_count);
    char**** pa_document_ptr = pa_document;
    
    size_t sentence_count = 10;
    char*** pa_paragraph =malloc(sizeof(char**) * sentence_count);
    char*** pa_paragraph_ptr = pa_paragraph;
    
    size_t word_count = 10;
    char** pa_sentence = malloc(sizeof(char**) * word_count);
    char** pa_sentence_ptr = pa_sentence;   

    int read_success = TRUE;

    *pa_document_ptr = pa_paragraph_ptr;
    *(pa_document_ptr + 1) = NULL;
    *pa_paragraph_ptr = pa_sentence_ptr;
    *(pa_paragraph_ptr + 1) = NULL;
    *pa_sentence_ptr = NULL;

    fp = fopen(document, "r");

    if (fp == NULL) {
        return FALSE;
    }

    printf("File Open\n");

    c = fgetc(fp);
    while (c != EOF) {
        int next_c = fgetc(fp);

        if (c != ' ' && c != ',' && c != '.' && c != '!' && c != '?' && c != '\n') {
            *buffer_ptr++ = c;
        }

        if (c == '\n') {
            if (pa_document_ptr - pa_document >= (int)paragraph_count - 1) {
                char**** temp = realloc(pa_document,sizeof(char***) * paragraph_count * 2);
                if (temp != NULL) {
                    pa_document = temp;
                    pa_document_ptr = pa_document + paragraph_count - 1;
                    paragraph_count *= 2;
                } else {
                    read_success = FALSE;
                    break;
                }
            }
            *pa_document_ptr++ = pa_paragraph;
            *pa_document_ptr = NULL;
            sentence_count = 5;
            pa_paragraph = malloc(sizeof(char**) * sentence_count);
            *pa_paragraph = NULL;
            pa_paragraph_ptr = pa_paragraph;
        }

        if (c == '.' || c == '!' || c == '?') {
            if (pa_paragraph_ptr - pa_paragraph >= (int)sentence_count - 1) {
                char*** temp = realloc(pa_paragraph, sizeof(char**) * sentence_count * 2);
                if (temp != NULL) {
                    pa_paragraph = temp;
                    pa_paragraph_ptr = pa_paragraph + sentence_count - 1;
                    sentence_count *= 2;
                } else {
                    read_success = FALSE;
                    break;
                }
            }
            *pa_paragraph_ptr++ = pa_sentence;
            *pa_paragraph_ptr = NULL;
            word_count = 5;
            pa_sentence = malloc(sizeof(char*) * word_count);
            *pa_sentence = NULL;
            pa_sentence_ptr = pa_sentence;

        }

        if (c == ' ' || c == ',') {
            int word_len = buffer_ptr - buffer + 1;
            char* pa_word;
            if (word_len == 1) {
                goto label1;
            }
            pa_word = malloc(sizeof(char) * word_len);
            *buffer_ptr = '\0';
            strncpy(pa_word, buffer, word_len);
            buffer_ptr = buffer;
             
            if (pa_sentence_ptr - pa_sentence >= (int)word_count - 1) {
                char** temp = realloc(pa_sentence, sizeof(char*) * word_count * 2);
                if (temp != NULL) {
                    pa_sentence = temp;
                    pa_sentence_ptr = pa_sentence + sentence_count - 1;
                    word_count *= 2;
                } else {
                    free(pa_word);
                    read_success = FALSE;
                    break;
                }
            }
            *pa_sentence_ptr++ = pa_word;
            *pa_sentence_ptr = NULL;
            word_count++;
        }


label1:
        c = next_c;
    }

    if (*pa_sentence == NULL) {
        free(pa_sentence);
    }
    if(*pa_paragraph == NULL) {
        free(pa_paragraph);
    }


    fclose(fp);

    s_pa_document = pa_document;
    return read_success;
}

void dispose(void)
{
    char**** pa_document_ptr = s_pa_document;
    while (*pa_document_ptr != NULL) {
        char*** pa_paragraph_ptr = *pa_document_ptr;
        while (*pa_paragraph_ptr != NULL) {
            char** pa_sentence_ptr = *pa_paragraph_ptr;
            while (*pa_sentence_ptr != NULL) {
                char* pa_word = *pa_sentence_ptr;
                free(pa_word);
            }
            free(*pa_paragraph_ptr);
            pa_paragraph_ptr++;
        }
        free(*pa_document_ptr);
        pa_document_ptr++;
    }
    free(s_pa_document);
    s_pa_document = NULL;
}

unsigned int get_total_word_count(void)
{
    unsigned int count = 0;
    char**** pa_document_ptr = s_pa_document;

int i = 0;
int j = 0;
int k = 0;
    while (*pa_document_ptr != NULL) {
        char*** pa_paragraph_ptr = *pa_document_ptr;
printf("paragraph %d\n", i++);
        while (*pa_paragraph_ptr != NULL) {
            char** pa_sentence_ptr = *pa_paragraph_ptr;
printf("    sentence %d\n", j++);
            while (*pa_sentence_ptr != NULL) {
printf("        %s\n", *pa_sentence_ptr);
                count++;
                pa_sentence_ptr++;
            }

            pa_paragraph_ptr++;

        }
j = 0;
        pa_document_ptr++;
    }    
    return count;
}

unsigned int get_total_sentence_count(void)
{
    unsigned int count = 0;
    char**** pa_document_ptr = s_pa_document;

    while (*pa_document_ptr != NULL) {
        char*** pa_paragraph_ptr = *pa_document_ptr;
        while (*pa_paragraph_ptr != NULL) {
            count++;
            pa_paragraph_ptr++;
        }
        pa_document_ptr++;
    }    

    return count;
}

unsigned int get_total_paragraph_count(void)
{
    unsigned int count = 0;
    char**** pa_document_ptr = s_pa_document;

    while (*pa_document_ptr != NULL) {
        count++;
        pa_document_ptr++;
    }    

    return count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    return (const char***)*(s_pa_document + paragraph_index);
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    const char*** paragraph_ptr = paragraph;
    unsigned int count = 0;
    while (*paragraph_ptr != NULL) {
        const char** sentence_ptr = *paragraph_ptr;
        while (*sentence_ptr != NULL) {
            count++;
            sentence_ptr++;
        }
        paragraph_ptr++;
    }

    return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    const char*** paragraph_ptr = paragraph;
    unsigned int count = 0;
    while (*paragraph_ptr != NULL) {
        count++;
        paragraph_ptr++;
    }

    return count;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    return (const char**)*(*(s_pa_document + paragraph_index) + sentence_index);
}

unsigned int get_sentence_word_count(const char** sentence)
{
    const char** sentence_ptr = sentence;
    unsigned int count = 0;
    while (*sentence_ptr != NULL) {
        count++;
        sentence_ptr++;
    }
    return count;
}


int print_as_tree(const char* filename)
{



    return 0;
}








