// Asks for the input from two players and calculates the winner
// according to the value of the letters in each word.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int scrabble(char *word){
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int total = 0;
    size_t len = strlen(word);
    for (int i = 0; i < len; i++){
        if (isupper(word[i])){
            word[i] = tolower(word[i]);
        }
        char num = word[i] - 'a';
        if (num >= 0 && num <= 26){
            total += scores[(int) num];
        }
    }
    return total;
}

int main (int argc, char *argv[]){
    char *str1 = NULL;
    char *str2 = NULL;
    str1 = (char *)malloc(100 * sizeof(char));
    if (str1 == NULL) {
        printf("Memory allocation for str1 failed\n");
        return 1;
    }
    str2 = (char *)malloc(100 * sizeof(char));
    if (str2 == NULL) {
        printf("Memory allocation for str2 failed\n");
        return 1;
    }
    int score1, score2;
    printf("Insert the words\n");
    printf("Player one:\n");
    scanf("%s", str1);
    printf("Player two:\n");
    scanf("%s", str2);
    score1 = scrabble(str1);
    score2 = scrabble(str2);
    if (score1 > score2){
        printf("Player 1 wins!\n");
    }
    else{
    if (score1 < score2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
    }
    free(str1);
    free(str2);
    return 0;
}
