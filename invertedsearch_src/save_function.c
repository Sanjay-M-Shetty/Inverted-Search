#include <stdio.h>
#include "struct.h"

void save_function(hash_table_t *HT)
{
    char filename[50];
    printf(CYAN "Enter the filename to save database : " RESET);
    scanf("%49s", filename);

    FILE *fp = fopen(filename, "w"); // Open target system output stream tracking configuration
    if (fp == NULL)
    {
        printf(RED "Error: Cannot create backup output file.\n" RESET);
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        main_node_t *temp = HT->table[i]; // Access corresponding top level element bucket indices
        while (temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->file_count); // Format write structural metadata tokens
            
            sub_node_t *sub = temp->sub_link;
            while (sub != NULL)
            {
                fprintf(fp, "%s;%d;", sub->filename, sub->word_count); // Format append nested file tracking indices
                sub = sub->s_link;
            }
            fprintf(fp, "#\n"); // Terminate record mapping line definitions
            temp = temp->main_link;
        }
    }
    fclose(fp); // Safely close and flush file contents to disk
    printf(GREEN "INFO : Database saved successfully in %s\n" RESET, filename);
}