#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING_LEN 50

void my_strcpy(char* destination, char* source){
    if (destination == NULL || source == NULL)
        return;

    char* d = destination;
    char* s = source;
    size_t count = 0;

    while (*s != '\0') {
        if (count > MAX_STRING_LEN) {
            fputs("Unable to find end of string or string too long\n", stderr);
            exit(EXIT_FAILURE);
        }
        *d = *s;
        d++;
        s++;
        count++;
    }
    *d = '\0';
}



size_t my_strlen(const char* s) {
    if (s == NULL)
        return 0;

    const char* p = s;
    size_t count = 0;

    while (*p != '\0') {
        if (count > MAX_STRING_LEN) {
            fputs("Unable to find end of string or string too long\n", stderr);
            exit(EXIT_FAILURE);
        }
        p++;
        count++;
    }

    return (size_t)(p - s);
}



bool starts_with_word(char* sentence, char* word) {
    if (sentence == NULL || word == NULL)
        return false;

    size_t sentence_len = my_strlen(sentence);
    size_t word_len     = my_strlen(word);

    if (sentence_len < word_len)
        return false;

    char* sp = sentence;
    char* wp = word;

    while (*wp != '\0') {
        if (*sp != *wp)
            return false;
        sp++;
        wp++;
    }
    return true;
}



bool overwrite_with_word(char* start, char* replacement) {
    if (start == NULL || replacement == NULL)
        return false;

    size_t start_len       = my_strlen(start);
    size_t replacement_len = my_strlen(replacement);

    if (start_len < replacement_len)
        return false;

    char* sp = start;
    char* rp = replacement;

    while (*rp != '\0') {
        *sp = *rp;
        sp++;
        rp++;
    }
    return true;
}




void overwrite_all_words(char* sentence, char* word, char* replacement) {
    if (sentence == NULL || word == NULL || replacement == NULL) {
        fputs("Unable to process your input\n", stderr);
        exit(EXIT_FAILURE);
    }

    size_t sentence_len    = my_strlen(sentence);
    size_t word_len        = my_strlen(word);
    size_t replacement_len = my_strlen(replacement);

    if (word_len != replacement_len)
        return;

    if (word_len > sentence_len || replacement_len > sentence_len)
        return;

    char* p = sentence;

    while (*p != '\0') {
        if (starts_with_word(p, word)) {
            /* Confirm whole-word boundary: char after match must be space or '\0' */
            char* after = p + word_len;
            if (*after == ' ' || *after == '\0') {
                overwrite_with_word(p, replacement);
            }
        }
        p++;
    }
}



/* This function iterates over a string until it reaches the end
    or finds a newline character. If it finds a newline, it replaces
    it with a null terminator and return immediately.
*/
void remove_end_newline(char* s){
    char* p = s;
    while (*p != '\0') {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        ++p;
    }
}



/*  This main function provides 2 modes of operation: interactive and command-line.
    In interactive mode, the user is prompted to enter a sentence, a word to replace, 
    and a replacement word. 
    In command-line mode, the user provides these three pieces of information as 
    command-line arguments when running the program. That's the mode required by 
    the instuctions, but the interactive mode is provided for your convenience while 
    testing.
    The program then validates the input according to the specifications and performs 
    the word replacement in the sentence, finally printing the modified sentence to 
    standard output.
*/
int main(int argc, char** argv) {

    char sentence[MAX_STRING_LEN * 2 + 1];      // the sentence to be worked on
    char word[MAX_STRING_LEN * 2 + 1];          // the word to be replaced
    char replacement[MAX_STRING_LEN * 2 + 1];   // the replacement word

    bool interactive = false; // whether to run in interactive mode or command-line mode

    if (argc == 1) {
        // if we have no command-line arguments, run in interactive mode
        interactive = true;
    } else if (argc != 4) {
        // if we don't have exactly 3 command-line arguments, print usage 
        // message and exit with failure
        fputs("Usage: ./a.out \"<sentence>\" \"<word>\" \"<replacement>\"\n", stdout);
        fputs("   or: ./a.out\n", stdout);
        exit(EXIT_FAILURE);
    }

    if(interactive){
        printf("Original sentence (max length %d): ", MAX_STRING_LEN);
        
        // The fgets function is another way to read an entire line
        fgets(sentence, (int)sizeof(sentence), stdin);
        // fgets reads everything on the line, including the newline 
        // character at the end. We don't want that, so we call this 
        // helper function to remove it.
        remove_end_newline(sentence);         

        fputs("\nWord to replace: ", stdout);
        fgets(word, (int)sizeof(word), stdin);
        remove_end_newline(word); 

        fputs("\nReplacement: ", stdout);
        fgets(replacement, (int)sizeof(replacement), stdin);
        remove_end_newline(replacement); 
    } else {
        // In non-interactive mode, we use the command line arguments
        my_strcpy(sentence, argv[1]);
        my_strcpy(word, argv[2]);
        my_strcpy(replacement, argv[3]);
    }

    /* Validate according to spec */
    size_t len_sentence    = my_strlen(sentence);
    size_t len_word        = my_strlen(word);
    size_t len_replacement = my_strlen(replacement);
    
    if (len_sentence == 0 || len_word == 0 || len_replacement == 0) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    if (len_word != len_replacement) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    if (len_sentence < len_word || len_sentence < len_replacement) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    // we call our primary function:
    overwrite_all_words(sentence, word, replacement);
    
    // Display a message before the resulting string (only in interactive mode):
    if(interactive) fputs("\nModified string: ", stdout);

    // Displays the modified sentence: 
    fputs(sentence, stdout);
    fputc('\n', stdout);

    return EXIT_SUCCESS;
}
