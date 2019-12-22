#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// Type for linked list nodes in hash map

int param = 0;
long hashcode(char key[]){ // provided code 
  union {
    char str[8];
    long num;
  } strnum;
  strnum.num = 0;

  for(int i=0; i<8; i++){
    if(key[i] == '\0'){
      break;
    }
    strnum.str[i] = key[i];
  }
  return strnum.num;
}

// Compute a simple hash code for the given character
// string. The code is "computed" by casting the first 8 characters of
// the string to a long and returning it. The empty string has hash
// code 0. If the string is a single character, this will be the ASCII
// code for the character (e.g. "A" hashes to 65).  Longer strings
// will have numbers which are the integer interpretation of up to
// their first 8 bytes.  ADVANTAGE: constant time to compute the hash
// code. DISADVANTAGE: poor distribution for long strings; all strings
// with same first 8 chars hash to the same location.

void hashmap_init(hashmap_t *hm, int table_size){
    int size = table_size; // for less confusion
    hm -> table =  malloc((size)*sizeof(hashnode_t)); //initialize table array has a bit size of size times hashnode_t. An array of hashnode_t's.
    memset(hm-> table, NULL, size*sizeof(hashnode_t));//all index to NULL. This is the initial state. 
    hm -> table_size = size; // now set the table size to size. 
     hm -> item_count = 0;
};
// Initialize the hash map 'hm' to have given size and item_count
// 0. Ensures that the 'table' field is initialized to an array of
// size 'table_size' and filled with NULLs. 

int hashmap_put(hashmap_t *hm, char key[], char val[]){

  hashnode_t *node; //node pointer
  if (hm == NULL){
    return 1; // no table exists? 
  }
  node = (hashnode_t**) malloc(sizeof(hashnode_t)); // node to be inserted
  strcpy(node -> key,key); // create the node to be added. copy value and keys
  strcpy(node -> val ,val);//set the value variable to val
  int i = hashcode(node->key)% (hm->table_size); // index of table that will point to a linked list.
  hashnode_t *p = hm -> table[i]; // temporary node that points to the table location to insert the node
  hashnode_t *prev = p; // pointer to the node that p previously pointed to
  if (hm -> table[i] != NULL){//if the table location points to something > insert the node
      p = hm -> table[i]; // if the pointed pointer is the last one p will be NULL
      while(p != NULL){ // keep traversing the linked list until p points to a null location
        if(strcmp(p->key, node->key) == 0){ // if existing nodes key and node to be inserted's key is equal break the loop
          break;
        }
        prev = p; // now prev points to the node that p points to 
        p = p -> next;// moves to the next node in the linked list, thus p is a node ahead of prev
      }
      if (p == NULL){//if p is null that means it is at the end of the linked list
        prev -> next = node; // so the last node is prev's node. by pointing the next of last node  I can add the provided node to the end of the linekd list.
        node -> next = NULL; //last node should point to null
        hm -> item_count++; //after adding a node increase the item_count
        return 1;
      }
      else{
        strcpy(p->val ,node->val); // copy node value to p's value. overwrite the previous value of the node that has the same key with the provided node
        return 0; //return zero. 
      }
  }
  else{
    node->next = NULL; //node next points to null. 
    hm->table[i] = node; // the table index i points to the node which is the initial node.moo.
    hm -> item_count++; //after adding a node increase the item_count
    return 1;
  }
};
// Adds given key/val to the hash map. 'hashcode(key) modulo
// table_size' is used to calculate the position to insert the
// key/val.  Searches the entire list at the insertion location for
// the given key. If key is not present, a new node is added. If key
// is already present, the current val is altered in place to the
// given value "val" (no duplicate keys are every introduced).  If new
// nodes are added, increments field "item_count".  Makes use of
// standard string.h functions like strcmp() to compare strings and
// strcpy() to copy strings. Lists in the hash map are arbitrarily
// ordered (not sorted); new items are always appended to the end of
// the list.  Returns 1 if a new node is added (new key) and 0 if an
// existing key has its value modified.

char *hashmap_get(hashmap_t *hm, char key[]){

  int i = hashcode(key)% (hm->table_size); // index of table that will point to a linked list.
  hashnode_t *p = hm -> table[i]; // temporary node that points to the table location to insert the node
  if (hm -> table[i] != NULL){//if the table location points to somethong > insert the node
      p = hm -> table[i]; // if the pointed index is empty p will be NULL
      while(p != NULL){ // keep traversing the linked list until p points to a null location
        if(strcmp(p->key, key) == 0){ // if existing nodes key and node to be inserted's key is equal break the loop
          return p-> val; //return pointer value
        }
        p = p -> next;// moves to the next node in the linked list
      }
   }  
  return NULL; //Otherwise returns NULL to indicate no associated
// key is present.
};
// Looks up value associated with given key in the hashmap. Uses
// hashcode() and field "table_size" to determine which index in table
// to search.  Iterates through the list at that index using strcmp()
// to check for matching key. If found, returns a pointer to the
// associated value.  Otherwise returns NULL to indicate no associated
// key is present.

void hashmap_free_table(hashmap_t *hm){
 hashnode_t *p; // node ponter to traverse the linked list.
 for (int i = 0; i < hm->table_size; ++i) // visit every table index 
 {
    p = hm -> table[i]; // temporary node that points to the table location to free the node
    if (hm -> table[i] != NULL){//if the table location points to something > traverse the linked list
        while(p != NULL){ // keep traversing the linked list until p points to a null location
          p = p -> next;// moves to the next node in the linked list 
          free(hm->table[i]); // free the node pointer
          hm->table[i] = p; // now
        }
    } 
    free(hm->table[i]); // free the table index
    hm->table[i] = NULL; // reinitialize it to null
 }
 free(hm->table);  // free the whole table malloced at init function
 if (param == 0){ // this how I get around of the limitation of setting a parameter. If the param is 1 then function is called by load
    hashmap_init(hm,5); // now create a new table and initialize to default value
 }
};
// De-allocates the hashmap's "table" field. Iterates through the
// "table" array and its lists de-allocating all nodes present
// there. Subsequently de-allocates tmake test-p3he "table" field and sets all
// fields to 0 / NULL. Does NOT attempt to free 'hm' as it may be
// stack allocated.

void hashmap_show_structure(hashmap_t *hm){
 printf("item_count: %d\n", hm-> item_count);  // show item count
 printf("table_size: %d\n",hm->table_size) ;// show table size
 float load_factor = (float)(hm->item_count)/(float)(hm->table_size); // calculate the load factor
 printf("load_factor: %.4f\n", load_factor); // show the load factor
 for (int i = 0; i < hm->table_size; i++) // for index of the hashmap table visit that table index
  {
    printf("%3d : ", i); // indec number
    hashnode_t *p = hm -> table[i]; // temporary node that points to the table location to insert the node
    if (hm -> table[i] != NULL){//if the table location points to somethong > insert the node
        p = hm -> table[i]; // if the pointed index is empty p will be NULL
        while(p != NULL){ // keep traversing the linked list until p points to a null location
          printf("{(%ld) %s : %s} ",hashcode(p->key), p->key, p->val); // print hashcode key and value as per the format instructions
          p = p -> next;// moves to the next node in the linked list
        }
      printf(" \n"); // new line
     }
     else
     {printf(" \n");} //new line
  }
};
// Displays detailed structure of the hash map. Shows stats for the
// hash map as below including the load factor (item count divided
// by table_size) to 4 digits of accuracy.  Then shows each table
// array index ("bucket") on its own line with the linked list of
// key/value pairs on the same line. The hash code for keys is appears
// prior to each key.  EXAMPLE:
// 
// item_count: 6
// table_size: 5
// load_factor: 1.2000
//   0 : {(65) A : 1} 
//   1 : 
//   2 : {(122) z : 3} {(26212) df : 6} 
//   3 : {(98) b : 2} {(25443) cc : 5} 
//   4 : {(74) J : 4} 
//
// NOTES:
// - Use format specifier "%2d : " to print the table indices
// - Show the following information for each key/val pair
//   {(25443) cc : 5}
//     |      |    |
//     |      |    +-> value
//     |      +-> key
//     +-> hashcode("cc"), print using format "%ld" for 64-bit longs

void hashmap_write_items(hashmap_t *hm, FILE *out){
  for (int i = 0; i < hm->table_size; i++) // iterate until table size is reached
  {
    hashnode_t *p = hm -> table[i]; // temporary node that points to the table location to insert the node
    if (hm -> table[i] != NULL){//if the table location points to somethong > insert the node
        p = hm -> table[i]; // if the pointed index is empty p will be NULL
        while(p != NULL){ // keep traversing the linked list until p points to a null location
          fprintf(out,"%12s : %s\n", p->key, p->val);
          p = p -> next;// moves to the next node in the linked list
        }
     }
  }
};
// Outputs all elements of the hash table according to the order they
// appear in "table". The format is
// 
//       Peach : 3.75
//      Banana : 0.89
//  Clementine : 2.95
// DragonFruit : 10.65
//       Apple : 2.25
// 
// with each key/val on a separate line. The format specifier
//   "%12s : %s\n"
// 
// is used to achieve the correct spacing. Output is done to the file
// stream 'out' which is standard out for printing to the screen or an
// open file stream for writing to a file as in hashmap_save().

void hashmap_save(hashmap_t *hm, char *filename){
  FILE *fp = fopen(filename,"w"); // open the file in write mode
  char ts[128]; // table size and item count below
  char ic[128];
  sprintf(ts, "%d", hm->table_size); // save table size value to the ts variable
  sprintf(ic,"%d", hm->item_count); // save table's item count to the ic cariable
  fprintf(fp, "%s %s\n",ts, ic); // now save the ic and ts as instructed
  hashmap_write_items(hm,fp);// save everything else by passing file pointer to write function. this "writes" into the file
  fclose(fp); // close the file
};
// Writes the given hash map to the given 'filename' so that it can be
// loaded later.  Opens the file and writes its 'table_size' and
// 'item_count' to the file. Then uses the hashmap_write_items()
// function to output all items in the hash map into the file.
// EXAMPLE FILE:
// 
// 5 6
//            A : 2
//            Z : 2
//            B : 3
//            R : 6
//           TI : 89
//            T : 7
// 
// First two numbers are the 'table_size' and 'item_count' field and
// remaining text are key/val pairs.

int hashmap_load(hashmap_t *hm, char *filename){
  FILE *fp = fopen(filename,"r"); // try to open the file
  if (fp == NULL){ // couldn't open the file so the pointer is null
    fprintf(stdout,"ERROR: could not open file '%s'\n",filename);
    return 1; // error
  }
  else{
    char ts[128]; // table size
    char ic[128];//item count
    fscanf(fp,"%s %s\n",ts,ic); // sacan file for table size and item count information
    int table_size = atoi(ts); //convert ts to integer type
    param = 1; // set param 1 to indicate that it is called from l
    hashmap_free_table(hm); // first free the table without initiali
    param = 0;
    hashmap_init(hm,table_size); // initialize the table to the read files table size
    char key[128]; // key and value strings
    char val[128]; 
    while (fscanf(fp,"%s : %s\n",key,val)!= EOF){ //read until the eof
      hashmap_put(hm,key,val);  //as kkey value pairs read, put them to the hashmap
    }
    fclose(fp);//close the file
    return 0;
  }
};
// Loads a hash map file created with hashmap_save(). If the file
// cannot be opened, prints the message
// 
// ERROR: could not open file 'somefile.hm'
// 
// and returns 0 without changing anything. Otherwise clears out the
// current hash map 'hm', initializes a new one based on the size
// present in the file, and adds all elements to the hash map. Returns
// 0 on successful loading. This function does no error checking of
// the contents of the file so if they are corrupted, it may cause an
// application to crash or loop infinitely.

int next_prime(int num){
  if (num == 2) //smallest prime number
  {
    return 2; // return 2
  }
  for (int i = 2; i <= (int)(num/2); i++)
  { // check if any of the numbers between 2 and num/2 can be divided to the given number
     if((num%i == 0)){ //if it can be divided it is not a prime number
        return next_prime(num+1);; // check recursively for the next number to see if it is a prime number
    }
  }
	return num;
};
// If 'num' is a prime number, returns 'num'. Otherwise, returns the
// first prime that is larger than 'num'. Uses a simple algorithm to
// calculate primeness: check if any number between 2 and (num/2)
// divide num. If none do, it is prime. If not, tries next odd number
// above num. Loops this approach until a prime number is located and
// returns this. Used to ensure that hash table_size stays prime which
// theoretically distributes elements better among the array indices
// of the table.

void hashmap_expand(hashmap_t *hm){
  int new_table_size = next_prime(2*(hm->table_size)+1); //new_table_size is a good table size that provides lower load_factor <1
  hm->table_size = new_table_size; // change the table size to the new size
  char filename[128] ="./tempo.hm"; //buffer file. 
  hashmap_save(hm,filename);//first save the old file data
  hashmap_free_table(hm);// free the current table
  hashmap_load(hm,filename);//now create it again with the new table_size
  remove(filename); // remove the buffer file
};
// Allocates a new, larger area of memory for the "table" field and
// re-adds all items currently in the hash table to it. The size of
// the new table is next_prime(2*table_size+1) which keeps the size
// prime.  After allocating the new table, all entries are initialized
// to NULL then the old table is iterated through and all items are
// added to the new table according to their hash code. The memory for
// the old table is de-allocated and the new table assigned to the
// hashmap fields "table" and "table_size".  This function increases
// "table_size" while keeping "item_count" the same thereby reducing
// the load of the hash table. Ensures that all memory associated with
// the old table is free()'d (linked nodes and array). Cleverly makes
// use of existing functions like hashmap_init(), hashmap_put(),
// and hashmap_free_table() to avoid re-writing algorithms
// implemented in those functions.
