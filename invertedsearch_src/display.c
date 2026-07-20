#include <stdio.h>
#include "struct.h"

void display(hash_table_t *HT)
{
    // Print clear, explicit table header bounds
    printf(GREEN "\n+-------+-----------------+------------+-----------------+------------+\n" RESET);
    printf(BLUE "| %-5s | %-15s | %-10s | %-15s | %-10s |\n" RESET, "Index", "Word", "File Count", "File Name", "Word Count");
    printf(GREEN "+-------+-----------------+------------+-----------------+------------+\n" RESET);

    for (int i = 0; i < 26; i++)
    {
        main_node_t *temp = HT->table[i];
        if (temp == NULL) continue;

        while (temp != NULL)
        {
            // Print the main node components
            printf("| [%-3d] | %-15s | %-10d | ", i, temp->word, temp->file_count);
            
            sub_node_t *temp1 = temp->sub_link;
            if (temp1 != NULL)
            {
                // Print the first file details on the same line
                printf("%-15s | %-10d |\n", temp1->filename, temp1->word_count);
                temp1 = temp1->s_link;
            }
            else
            {
                // Handle edge case where main node has no sub links
                printf("%-15s | %-10s |\n", "N/A", "0");
            }

            // Print subsequent files aligned in blocks underneath
            while (temp1 != NULL)
            {
                // Structural padding gaps to skip Index, Word, and File Count columns perfectly
                printf("|       |                 |            | %-15s | %-10d |\n", temp1->filename, temp1->word_count);
                temp1 = temp1->s_link;
            }
            
            printf(GREEN "+-------+-----------------+------------+-----------------+------------+\n" RESET);
            temp = temp->main_link;
        }
    }
}