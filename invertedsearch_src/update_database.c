#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void remove_file_node(main_file **head, char *filename) {
    main_file *temp = *head, *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->filename, filename) == 0) {
            if (prev == NULL) *head = temp->next; // Patch tracking address constraints dynamically on structural removals
            else prev->next = temp->next;
            free(temp); // Liberate allocations explicitly to remove processed documents
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void update_node(hash_table_t *HT, main_file **head)
{
    char filename[50];
    printf("Enter the filename : ");
    scanf("%49s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Backup file not found\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] != '#') continue; // Enforce structural validation rules over parsing line strings

        char *end = strrchr(line, '#');
        if (end) *end = '\0'; // Sanitize row data formats by neutralizing validation flags

        char *token = strtok(line, ";");
        if (!token) continue;
        int index = atoi(token + 1); // Transform string index offset sequences to actual matrix ranges
        
        token = strtok(NULL, ";");
        if (!token) continue;
        char word[30];
        strncpy(word, token, sizeof(word) - 1);
        word[sizeof(word) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        int file_count = atoi(token);

        main_node_t *new_word = malloc(sizeof(main_node_t)); // Generate working object states from file definitions
        strcpy(new_word->word, word);
        new_word->file_count = file_count;
        new_word->sub_link = NULL;

        sub_node_t *last_file = NULL;
        for (int i = 0; i < file_count; i++)
        {
            char *fname = strtok(NULL, ";");
            char *fcount_str = strtok(NULL, ";");
            if (!fname || !fcount_str) break;

            sub_node_t *new_file = malloc(sizeof(sub_node_t)); // Build mapped dynamic child leaf node assignments
            strcpy(new_file->filename, fname);
            new_file->word_count = atoi(fcount_str);
            new_file->s_link = NULL;

            if (new_word->sub_link == NULL) {
                new_word->sub_link = new_file;
            } else {
                last_file->s_link = new_file;
            }
            last_file = new_file;

            remove_file_node(head, fname); // Evict restored tracking entities away from command line files list safely
        }

        new_word->main_link = HT->table[index]; // Complete restoration configurations back inside hash-matrix structures
        HT->table[index] = new_word;
    }
    fclose(fp);
    printf(GREEN "INFO : Database is updated successfully\n" RESET);
}