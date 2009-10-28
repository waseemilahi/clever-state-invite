#include "get_var.h"


/* The Find Substring Function. */
int findsubstr( char *str, char *substr)
{
  if ( !*substr )
    {
      return 0;
    }
  for ( ; *str; ++str )
    {
      if ( *str == *substr )
	{
	  const char *h, *n;
	  for ( h = str, n = substr; *h && *n; ++h, ++n )
	    {
	      if ( *h != *n )
		{
		  break;
		}
	    }
	  if ( !*n )return 1;	    
	}
    }
  
  return 0;
}

/*Get the input and put it into an array of strings.*/
int get_input(char (*statements)[MAX_LENGTH], char *filename)
{
	char ch;
	int i;
	char line[MAX_LENGTH];
	int statement_number = 0;
	FILE *input;

 for(i = 0; i < MAX_LENGTH; i++)
    line[i] = '\0';
  
  if((input = fopen( filename, "r" )) == NULL)
    {
      fprintf(stderr, "\n File Could not be opened for reading. \n\n");
      exit(1);
    }

	ch = getc( input );

	while( ch != EOF ) {

	    if(ch == '\n'){
	      ch = getc(input);
	      continue;
	    }

	    if(ch == '#'){
	      while(1){
		ch = getc( input );
		if(ch == '\n'){
		  ch = getc(input);
		  break;
		}
      }
      continue;
    }

    if(ch == '/'){
      ch = getc(input);
      if( ch  == '/'){
	while(1){
	  ch = getc( input );
	  if(ch == '\n'){
	    ch = getc(input);
	    break;
	  }
	}
     	continue;
      }
      else if( ch  == '*'){
	while(1){
	  ch = getc( input );
	  if(ch == '*'){
	    if( (ch = getc(input)) == '/'){
	      ch = getc(input);
	      break;
	    }
	  }
	}
	continue;
      }
    }
    
    if(ch == '\t'){
      ch = getc(input);
      continue;
    }
    
    if(ch == '"'){
      while(1){
	ch = getc( input );
	if(ch == '"'){
	  ch = getc(input);
	  break;
	}
      }
      continue;
    }
    
    
    if( (ch == '}') || (ch == '{') || (ch == ';') ){
      
      if(statement_number >= MAX_LENGTH)break;
      
      strcpy(statements[statement_number] , line);
      
      statement_number ++;
      
      for(i = 0; i < MAX_LENGTH; i++)
	line[i] = '\0';
      
      ch = getc( input );
	       
      continue;
    }

    line[strlen(line)] = ch;
    
    ch = getc( input );
  }

fclose(input);
return statement_number;
}

