#include "markov_chain.h"

#include <string.h>

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
//generate random number given maximum value.
{
    return rand() % max_number;
}

Node *get_node_from_database(MarkovChain *markov_chain, void *data_ptr){
    //go through all nodes and returning the requested node or null if it doesn't exist.
    Node * current=markov_chain->database->first;
    while  (current!=NULL) {
        if (markov_chain->comp_func(data_ptr, current->data->data)==0){
            return current;
            }
        current = current->next;
    }
    return NULL;
}

Node *add_to_database(MarkovChain *markov_chain, void *data_ptr){
    // check if node exists in database and if not inserts it to database.
    Node *new_node = get_node_from_database(markov_chain, data_ptr);
    if (new_node != NULL)
    {
        //already exists
        return new_node;
    }
    MarkovNode *new_markov_node = malloc(sizeof(MarkovNode));
    if (new_markov_node == NULL) {
        return NULL;
    }
    void* new_data = markov_chain->copy_func(data_ptr);
    if (new_data == NULL) {
        free ( new_markov_node );
        return NULL;
    }
    // copies data from input to new char* and inserts it as a new markov node.
    new_markov_node->data= new_data;
    new_markov_node->frequency_list=NULL;
    new_markov_node->frequency_list_length=0;
    if (add(markov_chain->database, new_markov_node)==1) { //connects the new markov node to the last empty node in the markov chain node list(database).
        free ( new_markov_node->data );
        free ( new_markov_node );
        return NULL;
    }
    return markov_chain->database->last; //returns the added node.
}


int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode *second_node) { //add second markov node to first node frequency list
    if (first_node == NULL || second_node == NULL) {
        return 1; // Invalid input
    }

    //case frequency list is empty
    if (first_node->frequency_list == NULL) {
        first_node->frequency_list = malloc(sizeof(MarkovNodeFrequency));
        if (first_node->frequency_list == NULL) {
            return 1;
        }
        first_node->frequency_list[0].markov_node = second_node;
        first_node->frequency_list[0].frequency = 1;
        first_node->frequency_list_length = 1;
        return 0;
    }

    //case second_node already exists in the frequency list
    for (int i = 0; i < first_node->frequency_list_length; i++) {
        if (first_node->frequency_list[i].markov_node == second_node) {
            first_node->frequency_list[i].frequency++;
            return 0;
        }
    }

    //case second node doesn't exist in the frequency list, expand the frequency list
    MarkovNodeFrequency *new_frequency_list = realloc(
        first_node->frequency_list,
        sizeof(MarkovNodeFrequency) * (first_node->frequency_list_length + 1)
    );
    if (new_frequency_list == NULL) {
        return 1;
    }

    // Add the new node to the reallocated list
    first_node->frequency_list = new_frequency_list;
    first_node->frequency_list[first_node->frequency_list_length].markov_node = second_node;
    first_node->frequency_list[first_node->frequency_list_length].frequency = 1;
    first_node->frequency_list_length++;

    return 0;
}


void free_database(MarkovChain **ptr_chain) {
    if (ptr_chain == NULL || *ptr_chain == NULL) { //check if exists.
        return;
    }
    LinkedList *database = (*ptr_chain)->database;
    if (database == NULL) { //case database is empty
        free(*ptr_chain);
        *ptr_chain = NULL;
        return;
    }
    Node *current = database->first;
    while (current) { //go through each node and free its markov node values and then the node itself.
        MarkovNode *markov_node = current->data;
        free(markov_node->frequency_list);
        (*ptr_chain)->free_data(current->data->data);
        free(markov_node);
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(database); // free the linked list
    free(*ptr_chain); //free the markov chain
    *ptr_chain = NULL;
}


MarkovNode *get_first_random_node(MarkovChain *markov_chain){
    //gets first random node of given markov chain
    if (markov_chain == NULL || markov_chain->database == NULL || markov_chain->database->size == 0) { //validates input
        return NULL;
    }
    int size= markov_chain->database->size;
    while(1) { //runs until a legal word is returned
        int random = get_random_number(size);
        Node *node = markov_chain->database->first;
        for (int i=0; i<random; i++) { //go through linked list(database) until reaching the random number.
            node = node->next;
        }
        if (markov_chain->is_last(node->data->data)==false) { //validate the random data isn't a last data
            return node->data;
        }
    }
}
MarkovNode* get_next_random_node(MarkovNode *cur_markov_node) {
    //returns the next random markov node based on the given node frequency list.
    int total_frequencies = 0;
    for (int j = 0; j < cur_markov_node->frequency_list_length; j++) { //sums total frequencies of the given markov node
        total_frequencies += cur_markov_node->frequency_list[j].frequency;
    }
    if (total_frequencies==0) {
        return NULL;
    }
    int rand_value = get_random_number(total_frequencies); // generated random node
    int running_total = 0;

    for (int k = 0; k < cur_markov_node->frequency_list_length; k++) {//reach random word based on the total frequencies.
        running_total += cur_markov_node->frequency_list[k].frequency;// sum frequencies as you go to reach the correct word.
        if (rand_value < running_total) {
            return cur_markov_node->frequency_list[k].markov_node;
        }
    }

    return NULL;
}



void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *first_node, int max_length){
    if (first_node == NULL) { //validate input
        return;
    }
    int counter=0;
    MarkovNode *node = first_node;
    while (counter<max_length) { // go until the data counter reaches maximum or end data is reached
        if (node==NULL) {
            break;
        }
        if (markov_chain->is_last(node)==true) { //check if data is an end data.
            markov_chain->print_func(node->data);
            break;
        }
        markov_chain->print_func(node->data);
        counter++;
        node = get_next_random_node(node);
    }
}

