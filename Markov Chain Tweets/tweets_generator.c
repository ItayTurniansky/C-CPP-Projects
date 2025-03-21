//Don't change the macros!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "markov_chain.h"
#include "linked_list.h"
#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"
#define DEFAULT_MAX (-999)

#define DELIMITERS " \n\t\r"
#define MAX_LINE 1000
#define ARG_COUNT_MAX 5
#define ARG_COUNT_MIN 4
#define FILE_ARG 3
#define TWEET_COUNT_ARG 2
#define BASE 10
#define TWEET_MAX_LENGTH 20

int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain) {
    // goes through file lines and fills the markov chain database.
    char line[MAX_LINE] = {0};
    int word_counter = 0;
    while (fgets(line, MAX_LINE, fp)) {
        // goes through each line.
        char *first_word = strtok(line, DELIMITERS);
        MarkovNode *old_node =NULL;
        while (first_word != NULL) {
            //goes through each word
            if (words_to_read!= DEFAULT_MAX && word_counter>=words_to_read) {
                return EXIT_SUCCESS;
            }
            // adds new word to database.
            Node *current_node = add_to_database(markov_chain, first_word);
            MarkovNode *current_markov_node = current_node->data;

            if (current_markov_node==NULL) {
                free_database(&markov_chain);
                return EXIT_FAILURE;
            }
            if (old_node!=NULL&& old_node->data[strlen(old_node->data)-1] != '.') {
                // adds the current word to the previous word frequency list while checking if the word finishes a sentence.
                if (add_node_to_frequency_list(old_node, current_markov_node)==1) {
                    free_database(&markov_chain);
                    return EXIT_FAILURE;
                }
            }
            //goes to next word
            old_node = current_markov_node;
            first_word = strtok(NULL, DELIMITERS);
            word_counter++;
        }
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != ARG_COUNT_MAX && argc != ARG_COUNT_MIN ) { //check input arguments
        printf(NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    int status=0;
    FILE* in_file = fopen(argv[FILE_ARG], "r"); //open file
    if (in_file == NULL) {
        printf(FILE_PATH_ERROR);
        return EXIT_FAILURE;
    }
    char *endptr;
    int seed= strtol(argv[1], &endptr, BASE);
    srand(seed);
    const int tweets_num= strtol(argv[TWEET_COUNT_ARG], &endptr, BASE);

    MarkovChain *markov_chain= malloc(sizeof(MarkovChain)); // allocate markov chain and set values
    if (markov_chain == NULL) {
        return EXIT_FAILURE;
    }

    markov_chain->database=malloc(sizeof(LinkedList));
    if (markov_chain->database == NULL) {
        free(markov_chain);
        return EXIT_FAILURE;
    }
    markov_chain->database->first=NULL;
    markov_chain->database->last=NULL;
    markov_chain->database->size=0;
    if (argc==ARG_COUNT_MAX) { // case max is input
        int max_words= strtol(argv[ARG_COUNT_MIN], &endptr,BASE) ;
        status = fill_database(in_file, max_words, markov_chain);

    }else { //case no max wa input
        status = fill_database(in_file, DEFAULT_MAX, markov_chain);
    }
    if (status==0) { // database filled successfully
        for (int i=1; i<=tweets_num; i++) { //print tweets
            MarkovNode *markov_node= get_first_random_node(markov_chain);
            printf("Tweet %d: ", i);
            generate_tweet(markov_node, TWEET_MAX_LENGTH);
            printf("\n");
        }
    }
    free_database(&markov_chain);//free database after tweets.
}