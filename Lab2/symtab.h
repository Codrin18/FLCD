/* maximum size of hash table */
#define SIZE 211
 
/* maximum size of tokens-identifiers */
#define MAXTOKENLEN 40
 
/* token types */
#define INT_TYPE 0
#define REAL_TYPE 1
#define STR_TYPE 2
#define LIST_TYPE 3
#define UNDEF 4
 
/* how parameter is passed */
#define BY_VALUE 1
#define BY_REFER 2


//  cuurent scope 
int cur_scope = 0;
//int poz = 0;
 
/* parameter struct */
typedef struct Param{
    int par_type;
    char param_name[MAXTOKENLEN];
    // to store value
    int ival; double fval; char *st_sval;
    int passing; // value or reference
}Param;
 
/* a linked list of references (lineno's) for each variable */
typedef struct RefList{ 
    int lineno;
    struct RefList *next;
    int type;
}RefList;
 
// struct that represents a list node
typedef struct list_t{
    char st_name[MAXTOKENLEN];
    int st_size;
    int scope;
    RefList *lines;
    // to store value and sometimes more information
    int st_ival; double st_fval; char *st_sval;
    // type
    int st_type;
    int inf_type; // for arrays (info type) 
    // array stuff
    int *i_vals; double *f_vals; char **s_vals;
    int array_size;
    // function parameters
    Param *parameters;
    int num_of_pars;
    // pointer to next item in the list
    struct list_t *next;
}list_t;
 
/* the hash table */
static list_t **hash_table;
 
// Function Declarations
void init_hash_table(); // initialize hash table
unsigned int hash(char *key); // hash function 
void insert(char *name, int len, int type, int lineno); // insert entry
list_t *lookup(char *name); // search for entry
list_t *lookup_scope(char *name, int scope); // search for entry in scope
void hide(); // hide the current scope
void hide_scope(int scope); // hide a specific scope
void symtab_dump(FILE *of); // dump file