// This program calculates the reading level of a text written by the user
// using the Coleman-Liau index.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define MAX_LIMIT 500

int count_letters(char *text);
int count_words(char *text);
int count_sentences(char *text);
int index(char *text);

int main(void)
{
    char text[MAX_LIMIT];
    printf("Text: ");
    fgets(text, MAX_LIMIT, stdin); // Assuming the text won't be longer than 500 characters.
    int grade_level = index(text);
    if (grade_level < 1){
        printf("Before Grade 1\n");
    }
    else if (grade_level > 15){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %d\n", grade_level);
    }
    return 0;
}

int count_letters(char *text){
    int len = strlen(text);
    int count = 0;
    for (int i = 0; i < len; i++){
        if(isalpha(text[i])){
            count++;
        }
    }
    return count;
}

int count_words(char *text){
    int len = strlen(text);
    int count = 0;
    bool word_started = false; // Boolean value indicating if a word is currently being read.
    for (int i = 0; i < len; i++){
        // If we encounter a space then the variable is set to false because no words are currently being read.
        if(text[i] == ' '){
            if(word_started){
                word_started = false;
            }
        }
        // If the character we are checking is alphabetic and the variable is set to false we set it to true and increase the count.
        else if (isalpha(text[i]) && !word_started){
            word_started = true;
            count++;
        }
    }
    return count;
}

int count_sentences(char *text){
    // The algorithm is the exact same as the one for counting words, except for the fact
    // that it counts '.', '!' and '?' as sentence terminators.
    int len = strlen(text);
    int count = 0;
    bool sentence_started = false;
    for (int i = 0; i < len; i++){
        if(text[i] == '.' || text[i] == '!' || text[i] == '?'){
            if(sentence_started){
                sentence_started = false;
            }
        }
        else if (isalpha(text[i]) && !sentence_started){
            sentence_started = true;
            count++;
        }
    }
    return count;
}

int index(char *text){
    int letters, words, sentences;
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    float L, S;
    L = ((float) letters / (float) words) * 100;
    S = ((float) sentences / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // Return the index rounded to the closest integer
    float rounded_index = roundf(index);
    return (int)rounded_index;
}
