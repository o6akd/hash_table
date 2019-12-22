#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char const *argv[])
{
	int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
	if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
	  echo=1;
	}

	printf("Hashmap Demo\n");
	printf("Commands:\n");
	printf("  hashcode <key>   : prints out the numeric hash code for the given key (does not change the hash map)\n");
	printf("  put <key> <val>  : inserts the given key/val into the hash map, overwrites existing values if present\n");
	printf("  get <key>        : prints the value associated with the given key or NOT FOUND\n");
	printf("  print            : shows contents of the hashmap ordered by how they appear in the table\n");
	printf("  structure        : prints detailed structure of the hash map\n");
	printf("  clear            : reinitializes hash map to be empty with default size\n");
	printf("  save <file>      : writes the contents of the hash map the given file\n");
	printf("  load <file>      : clears the current hash map and loads the one in the given file\n");
	printf("  next_prime <int> : if <int> is prime, prints it, otherwise finds the next prime and prints it\n");
	printf("  expand           : expands memory size of hashmap to reduce its load factor\n");
	printf("  quit             : exit the program\n");

	char cmd[128];// user input stuff
    hashmap_t *hashmap = malloc(sizeof(hashmap_t)); // allocate memory , hashmap points to this memory location
	int success;
	hashmap_init(hashmap, 5);// initialize the default hashmap to size 5

	while(1){ // persistent until something breaks the loop
	  printf("HM> ");                 // print prompt
	  success = fscanf(stdin,"%s",cmd); // read a command
	  if(success==EOF){                 // check for end of input
	    printf("\n");                   // found end of input
	    break;                          // break from loop
	  }

	  if( strcmp("quit", cmd)==0 ){     // check for exit command
	   if(echo){
       	 printf("quit\n");
      }
	    break;                          // break from loop
	  }

	  else if( strcmp("hashcode", cmd)==0 ){   // print command
	    fscanf(stdin,"%s",cmd); 
	    long hcode = hashcode(cmd); // call the hashcode function and save the result to hcode
	    if(echo){
       	 	printf("hashcode %s\n",cmd);
      	}	
	    printf("%ld\n", hcode);
	  }

	  else if(strcmp("put", cmd)==0 ){ // insertion
	  	char key[128], val[128];
	    fscanf(stdin,"%s %s",key,val);            // read string to insert
	    success = hashmap_put(hashmap, key, val); // call list function	  
	     if(echo){
       	 	printf("put %s %s\n", key, val);
      	}	
	    if(echo && success==0){                      // check for success
	      	printf("Overwriting previous key/val\n");
	   	}
	   }
	  else if( strcmp("get", cmd)==0 ){     // get command
	    char key[128];
	    fscanf(stdin,"%s", key);          // read an integer
	    char *value = hashmap_get(hashmap, key); // call list function
	    if(echo){
       	 	printf("get %s\n", key);
      	}	
	    if(value == NULL){                    // check for success
	      printf("NOT FOUND\n");
	    }
	    else {
	      printf("FOUND: %s\n",value);
	    }
	  }

	  else if( strcmp("print", cmd)==0 ){   // print command
	  	if(echo){
       	 	printf("print\n");
      	}
	   hashmap_write_items(hashmap, stdout); // write to stdout 
	  }

 	  else if( strcmp("structure", cmd)==0 ){   // print command
 	  	if(echo){
       	 	printf("structure\n");
      	}
	    hashmap_show_structure(hashmap); // show structure 
	  }


	  else if( strcmp("clear", cmd)==0 ){   // clear command
	  	if(echo){
       	 	printf("clear\n");
      	}
	    hashmap_free_table(hashmap); // free the table
	  }

 	  else if( strcmp("save", cmd)==0 ){   // clear command
	    fscanf(stdin,"%s",cmd); 
	    if(echo){
       	 	printf("save %s\n",cmd);
      	}
		hashmap_save(hashmap, cmd); // call save hashmap to save
	  }

	  // case for "contains" command

 	  else if( strcmp("load", cmd)==0 ){   // clear command
	    fscanf(stdin,"%s",cmd); 
	    if(echo){
       	 	printf("load %s\n",cmd);
      	}

		success = hashmap_load(hashmap,cmd); // load 
		if (success != 0 ) // if success is not 0 load failed
		{
			printf("load failed\n");
		}
	  }

	 else if(strcmp("next_prime", cmd)==0 ){   // clear command
	    int prime;
	    fscanf(stdin,"%d",&prime); // read cmd to prime number variable
	    int np=  next_prime(prime);// call next_prime() to find the next prime number
	    if(echo){
       	 	printf("next_prime %d\n",prime); //if echo is open print 
      	}
	    printf("%d\n",np );// print the above functions value 
	  }
	
	 else if( strcmp("expand", cmd)==0 ){   // clear command
		if(echo){
       	 	printf("expand\n"); //if echo is open 
      	}
	    hashmap_expand(hashmap); // expand
	  }

	  else{   
	  	if(echo){
       	 	printf("%s\n",cmd);
      	}                              // unknown command
	    printf("unknown command %s\n",cmd);
	  }
	}  

	// end main while loop
	hashmap_free_table(hashmap); //free everything
	free((hashmap -> table)); // free the table
	free(hashmap);  // clean up the hashmap
	/* code */
	return 0;
}