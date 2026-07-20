

/*

NAME : SANJAY M SHETTY
ADMISSION N0 : 25048_56
DATE : 09-JULY-2026
TOPIC : INVERTED SEARCH PROJECT
DESCRIPTION : This project implements an inverted search system in C that indexes words 
              from multiple text files using a hash table.It allows efficient word searching,
              file-wise frequency counting, and supports saving and updating the index.


Project Overview:

Title: Inverted Search
Type: Individual / Advanced Data Structures Project
Core Objective: Implement a high-performance full-text search mechanism using an inverted index database created via hashing and indexing algorithms. 
It replicates the core foundational technology used by modern search engines for rapid document retrieval.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Core Architecture & Mechanisms:

1. Indexing (Database Creation):

The project processes a set of input files/documents to extract individual words and build a centralized directory.
* Forward Indexing: Words are parsed from text and stored dynamically using linked lists or hash tables alongside their source file names. 
Duplicate words are consolidated rather than duplicated.
* Inverted Index Transformation: The dataset maps distinct words directly to all document locations where they appear. 

2. Querying (Search Engine):

Once the database is indexed, users can execute search queries:
* The search term is parsed into words.
* To prevent repetitive, slow disk I/O, the index file is loaded into main memory (RAM) as a hash table or linked list structure.
* The system scans the structural database, references the target word, maps out all matching source files, filters them by relevance (match frequency), and returns the ranked results.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

// Checks if a given file name already exists in the validated file linked list to prevent duplication
int is_duplicate(main_file *head, char *filename) {
    while (head != NULL) {
        if (strcmp(head->filename, filename) == 0) return 1;
        head = head->next;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Verifies that at least one document filename is passed as a command-line argument
    if (argc < 2)
    {
        printf(RED "Error: Invalid command. Provide validation files.\n"RESET);
        return 1;
    }

    // Initializes the inverted index hash table array to all NULL pointers
    hash_table_t HT = { {NULL} };
    main_file *head = NULL;
    main_file *temp = NULL;

    // Loops through each command-line argument to validate and filter input files
    for (int i = 1; i < argc; i++)
    {
        // Extracts the file extension and rejects files that do not end in '.txt'
        char *ext = strrchr(argv[i], '.');
        if (!ext || strcmp(ext, ".txt") != 0) {
            printf("INFO: %s => This file is not a .txt file\n", argv[i]);
            continue;
        }

        // Drops the argument if the file name has already been processed in a previous iteration
        if (is_duplicate(head, argv[i])) {
            printf("INFO: %s => This file is repeated\n", argv[i]);
            continue;
        }

        // Tries opening the target file and flags an error if it does not exist or lacks read permissions
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("INFO: %s => This file does not exist\n", argv[i]);
            continue;
        }

        // Checks the size of the file and skips it if it contains 0 bytes of data
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0) {
            printf("INFO: %s => This file is empty\n", argv[i]);
            fclose(fp);
            continue;
        }
        fclose(fp);

        // Allocates memory for a new list node to catalog the valid file name
        main_file *new_node = malloc(sizeof(main_file));
        strcpy(new_node->filename, argv[i]);
        new_node->next = NULL;

        // Appends the newly verified file node to the end of the tracking linked list
        if (head == NULL) {
            head = new_node;
            temp = new_node;
        } else {
            temp->next = new_node;
            temp = new_node;
        }
        printf("INFO: Successful: Inserting file name %s into list\n", argv[i]);
    }

    // Iterates through and visually prints the linked list of all valid, registered source files
    printf("\n");
    main_file *print_ptr = head;
    while (print_ptr != NULL)
    {
        printf(GREEN "%s -> " RESET, print_ptr->filename);
        print_ptr = print_ptr->next;
    }
    printf(GREEN "NULL\n" RESET);

    int option; 
    char find_word[50];
    int index_created = 0;
    int update_flag = 0;

    // Keeps the interactive console menu looping until the user explicitly selects option 6 to exit
    while (1)
    {
        printf("\n######## INVERTED SEARCH OPERATION ########\n" );
        printf("\nSelect your choice among following operations:\n"
               "1. Create Database\n"
               "2. Display Database\n"
               "3. Update Database\n"
               "4. Search\n"
               "5. Save Database\n"
               "6. Exit\n"
               "Enter your choice: ");
                      
        if (scanf("%d", &option) != 1) break;

        switch (option)
        {
            // Parses the validated files list and indexes their words into the hash table structure
            case 1:
                if (index_created) {
                    printf(YELLOW "INFO: Database is already created\n" RESET);
                    break;
                }
                main_file *curr = head;
                if (curr == NULL) {
                    printf(RED "INFO: No valid files to index.\n" RESET);
                    break;
                }
                while (curr != NULL)
                {
                    insert_node_data(&HT, curr->filename);
                    printf(GREEN "INFO : Successful : Creation of DATABASE for file: %s\n" RESET, curr->filename);
                    curr = curr->next;
                }
                index_created = 1;
                break;

            // Renders the structured, tabular format of words, indices, and file metrics to the screen
            case 2:
                if (update_flag) { display(&HT); break; }
                if (!index_created) { printf(RED "Please create or update database first.\n" RESET); break; }
                display(&HT);
                break;

            // Reloads a previously exported database backup file back into the runtime hash table structure
            case 3:
                update_node(&HT, &head);
                update_flag = 1;
                break;

            // Performs a constant-time hashing lookup to find a word and print its sub-node occurrences
            case 4:
                if (!index_created) { printf(RED "Please create or update database first.\n" RESET); break; }
                printf(CYAN "Enter the word to search : " RESET);
                scanf("%s", find_word);
                search_word(&HT, find_word);
                break;

            // Serializes the full hash table structure into a formatted plain-text backup file on disk
            case 5:
                if (!index_created) { printf(RED "Please create or update database first.\n" RESET); break; }
                save_function(&HT);
                break;

            // Terminates program execution immediately and returns control to the operating system
            case 6:
                return 0;

            // Flags an error if the user enters an option numerical range outside of 1 through 6
            default:
                printf(RED "Invalid choice\n" RESET);
                break;
        }
    }
    return 0;
}