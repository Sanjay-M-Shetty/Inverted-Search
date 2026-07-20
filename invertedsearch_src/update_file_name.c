#include <stdlib.h>
#include <string.h>
#include "struct.h"

void update_file_name(main_node_t *wnode, char *filename)
{
    sub_node_t *temp = wnode->sub_link;

    if (temp == NULL)
    {
        sub_node_t *new_node = malloc(sizeof(sub_node_t)); // Instantiate secondary tracking entry reference
        strcpy(new_node->filename, filename);
        new_node->word_count = 1; 
        new_node->s_link = NULL;

        wnode->sub_link = new_node;
        wnode->file_count++; // Step overall referencing tracking counter boundaries
        return;
    }

    sub_node_t *prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            temp->word_count++; // Found file occurrence duplicate, step instance count parameter
            return;
        }
        prev = temp;
        temp = temp->s_link;
    }

    sub_node_t *new_node = malloc(sizeof(sub_node_t)); // Append subsequent node down linear structure tracking chain
    strcpy(new_node->filename, filename);
    new_node->word_count = 1; 
    new_node->s_link = NULL;

    prev->s_link = new_node;
    wnode->file_count++;
}