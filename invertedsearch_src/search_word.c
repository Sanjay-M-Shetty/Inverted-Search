#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

void search_word(hash_table_t *HT, char *word)
{
    char ch = tolower((unsigned char)word[0]); // Normalize character entry case variants safely
    if (ch < 'a' || ch > 'z') 
    {
        printf(RED "Word not found in database.\n" RESET);
        return; 
    }

    int index = ch - 'a'; // Derive targeted dictionary index positioning 
    main_node_t *temp = HT->table[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0) // Look for string sequence match across tracking records
        {
            printf( YELLOW "\nword %s is present in %d files\n" RESET, temp->word, temp->file_count);
            sub_node_t *tf = temp->sub_link;
            while (tf != NULL)
            {
                printf(BLUE "In file: %s %d times\n" RESET, tf->filename, tf->word_count);
                tf = tf->s_link; 
            }
            return;
        }
        temp = temp->main_link; 
    }
    printf(RED "Word not found in database.\n" RESET);
}