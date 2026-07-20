#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdio.h> 
#include "struct.h" 

void insert_node_data(hash_table_t *HT, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return;

    char raw_word[50];

    while (fscanf(fp, "%49s", raw_word) != EOF)
    {
        int len = strlen(raw_word);
        while (len > 0 && ispunct((unsigned char)raw_word[len - 1])) {
            raw_word[len - 1] = '\0'; // Trim trailing punctuation marks dynamically
            len--;
        }

        if (len == 0) continue;

        for (int i = 0; raw_word[i]; i++) {
            raw_word[i] = tolower((unsigned char)raw_word[i]); // Force lowercase transformation parameters
        }

        char ch = raw_word[0];
        if (ch < 'a' || ch > 'z') continue;

        int index = ch - 'a'; // Derive target database hashing offset
        main_node_t *temp = HT->table[index];
        int found = 0;

        while (temp != NULL)
        {
            if (strcmp(temp->word, raw_word) == 0)
            {
                update_file_name(temp, filename); // Append file target attributes onto duplicate entries
                found = 1;
                break;
            }
            temp = temp->main_link; 
        }

        if (!found)
        {
            main_node_t *new_node = malloc(sizeof(main_node_t)); // Instantiate unique structural dictionary node
            strcpy(new_node->word, raw_word);
            new_node->file_count = 0; 
            new_node->sub_link = NULL;
            new_node->main_link = HT->table[index]; // Insert new mapping elements at head of bucket index lists
            HT->table[index] = new_node;

            update_file_name(new_node, filename);
        }
    }
    fclose(fp);
}