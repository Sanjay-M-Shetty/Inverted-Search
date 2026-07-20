#ifndef STRUCT_H
#define STRUCT_H

// ANSI Color Escape Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Structure to store list of valid input files passed via command line
typedef struct main_file
{
    char filename[50];       
    struct main_file *next;  
} main_file;

// Structure to store file-specific frequency information for each indexed word
typedef struct sub_node
{
    char filename[50];       
    int word_count;          
    struct sub_node *s_link; 
} sub_node_t;

// Structure to store unique word data and head of its nested document list
typedef struct main_node
{
    char word[30];           
    int file_count;          
    sub_node_t *sub_link;    
    struct main_node *main_link; 
} main_node_t;

// Hash table encapsulation containing 26 elements mapping to alphabets 'a' through 'z'
typedef struct hash_table_t
{
    main_node_t *table[26];
} hash_table_t;

// Core processing function declarations
void insert_node_data(hash_table_t *HT, char *filename);
void update_file_name(main_node_t *wnode, char *filename);
void search_word(hash_table_t *HT, char *word);
void display(hash_table_t *HT);
void save_function(hash_table_t *HT);
void update_node(hash_table_t *HT, main_file **head);

#endif