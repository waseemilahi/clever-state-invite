/* The Token Parser. */
# include "get_var.h"

int main(int argc, char **argv)
{

  int ch;
  FILE *input;
  char line[MAX_LENGTH];
  int i,j,k;
  int statement_number = 0;
  char statements[MAX_LENGTH][MAX_LENGTH];
  char tokens[MAX_LENGTH][MAX_LENGTH];
  int total_tokens = 0;

  if(argc != 2){
    fprintf(stderr, "\n Usage: get_var file_name.\n\n");
    exit(1);
  }


  for(i =0; i < MAX_LENGTH; i++)
    for(j =0; j < MAX_LENGTH; j++){
      statements[i][j] = '\0';
      tokens[i][j] = '\0';
    }

  for(i = 0; i < MAX_LENGTH; i++)
    line[i] = '\0';
  
  if((input = fopen( argv[1], "r" )) == NULL)
    {
      fprintf(stderr, "\n File Could not be opened for reading. \n\n");
      exit(1);
    }
 
  ch = getc( input );
  while( ch != EOF ) {

    if( (ch == '}')||  (ch == '{') || (ch == ';') ){

      if(statement_number >= MAX_LENGTH)break;

      strcpy(statements[statement_number] , line);
      
      statement_number ++;
      
      for(i = 0; i < MAX_LENGTH; i++)
	line[i] = '\0';
      
      ch = getc( input );
	       
      continue;
    }


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
    
    line[strlen(line)] = ch;
    
    ch = getc( input );
  }
  for(i = 0; i < MAX_LENGTH; i++){
    if( (j = findsubstr(statements[i] , "fprintf"))  == 1)
      for(k = 0; k < MAX_LENGTH; k++)
	statements[i][k] = '\0';
  }
  
  const char delimeters[] = "";
  char *running;
  char *token;
  
  for(i = 0; i <  statement_number; i++){
    
    running = strdup(statements[i]);
    
    token = strtok(running , delimeters);
    while(token != NULL){
      
      char *tmpt = token;
      if(token != NULL){
	while(*tmpt != '\0'){
	  sprintf(tokens[total_tokens],"%s%c",tokens[total_tokens],*tmpt);
	  tmpt++;
	}
	total_tokens++;
      }
      token = strtok(NULL,delimeters);
    }
  }
  
  char token_statements[total_tokens][MAX_LENGTH];
  for (i = 0; i < total_tokens; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      token_statements[i][j] = '\0';
  int t_statements_number = 0;
  
  int d_statements_number = 0;
  char declare_statements[total_tokens][MAX_LENGTH];
  
  for (i = 0; i < total_tokens; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      declare_statements[i][j] = '\0';
  
  for(i = 0; i < total_tokens; i++){
    if( ( ((findsubstr(tokens[i] , "int")) == 1) || ((findsubstr(tokens[i] , "float")) == 1) || ((findsubstr(tokens[i] , "double")) == 1)
	  ||((findsubstr(tokens[i] , "char")) == 1) || ((findsubstr(tokens[i] , "long")) == 1) || ((findsubstr(tokens[i] , "short")) == 1)
	  ||((findsubstr(tokens[i] , "struct")) == 1)		) &&(findsubstr(tokens[i] , "(")) == 0){
      strcpy(declare_statements[d_statements_number] , tokens[i]);
      d_statements_number++;
    }
  }
  
  for(i = 0; i < total_tokens; i++){
    if( (findsubstr(tokens[i] , "=")) == 1){
      strcpy(token_statements[t_statements_number] , tokens[i]);
      t_statements_number++;
    }
  }
  
  char truncated_statements[t_statements_number][MAX_LENGTH];
  for (i = 0; i < t_statements_number; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      truncated_statements[i][j] = '\0';
  
  int truncated_number = 0;
  char *tmp;
  char tmpstr[MAX_LENGTH];
  for(i = 0; i < MAX_LENGTH; i++)
    tmpstr[i] = '\0';
  
  /* We have all the '=' statements. Lets remove the left hand side of each. */
  for( i = 0; i < t_statements_number; i++){
    strcpy(tmpstr ,token_statements[i]);
    if( ((j = findsubstr(tmpstr,"(")) == 0) && ((k = findsubstr(tmpstr,",")) == 0)){     
      tmp = strstr(tmpstr,"=");
      tmp++;
      strcpy(truncated_statements[truncated_number],tmp);
      truncated_number++;
    }
  }  
  
  char all_vars[MAX_LENGTH][MAX_LENGTH];
  for (i = 0; i < MAX_LENGTH; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      all_vars[i][j] = '\0';
  
  int total_vars = 0;
  
  const char delims[] = "=-+*/% \\\"\'";
  
  for(i = 0; i < truncated_number; i++){
    
    running = strdup(truncated_statements[i]);
    
    token = strtok(running , delims);
    while(token != NULL){
      
      char *tmpt = token;
      if(token != NULL){
	while(*tmpt != '\0'){
	  sprintf(all_vars[total_vars],"%s%c",all_vars[total_vars],*tmpt);
	  tmpt++;
	}
	total_vars++;
      }
      token = strtok(NULL,delims);
    }
  }
  
  char d_truncated_statements[d_statements_number][MAX_LENGTH];
  for (i = 0; i < d_statements_number; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      d_truncated_statements[i][j] = '\0';
  
  int d_truncated_number = 0;
  
  int t = 0 ;
  const char del[] = "=";
  for( i = 0; i < d_statements_number; i++){
    strcpy(tmpstr ,declare_statements[i]);
    tmp = strtok(tmpstr,del);t =0;
    
    strcpy(d_truncated_statements[d_truncated_number],tmp);
    d_truncated_number++;
    
  }  
  
  char declare_vars[MAX_LENGTH][MAX_LENGTH];
  for (i = 0; i < MAX_LENGTH; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      declare_vars[i][j] = '\0';
  
  int declared_vars = 0;
  
  const char delim[] = " ,*";
  
  
  for(i = 0; i < d_truncated_number; i++){
    
    running = strdup(d_truncated_statements[i]);
    
    token = strtok(running , delim);
    while(token != NULL){
      if( (strcmp(token , "int") != 0) && (strcmp(token , "char") != 0) && (strcmp(token , "float") != 0)
	  &&(strcmp(token , "double") != 0) && (strcmp(token , "long") != 0) && (strcmp(token , "short") != 0)
	  &&(strcmp(token , "struct") != 0) &&(strcmp(token , "*") != 0)   ){
	char *tmpt = token;
	if(token != NULL){
	  while(*tmpt != '\0'){
	    sprintf(declare_vars[declared_vars],"%s%c",declare_vars[declared_vars],*tmpt);
	    tmpt++;
	  }
	  declared_vars++;
	}
      }
      
      token = strtok(NULL,delim);
    }
  }  
  
  int total_real_vars = 0;
  
  for (i = 0; i < total_vars; i++){
    for(j = 0; j < MAX_LENGTH; j++){
      if(all_vars[i][j] == ' '){
	continue;
      }
      else if( (all_vars[i][j] < 48) || (all_vars[i][j] > 57)){
	total_real_vars++;
	break;
      }
      else break;
    }
  }
  
  char real_vars[total_real_vars][MAX_LENGTH];
  for (i = 0; i < total_real_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      real_vars[i][j] = '\0';
  
  char *pp;
  k = 0;
  for(i = 0 ; i < total_vars; i++){
    pp = all_vars[i];
    for(j = 0; j < MAX_LENGTH; j++){
      
      if(all_vars[i][j] == ' '){
	pp++;continue;
      }
      else if((all_vars[i][j] < 48) || (all_vars[i][j] > 57)){
	strcpy(real_vars[k++],pp);//all_vars[i]);
	break;
      }
      else break;
    }
  }
  
  int unique_real_vars = 0;
  int found = 0;
  
  char real_unique_vars[total_real_vars][MAX_LENGTH];
  for (i = 0; i < total_real_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      real_unique_vars[i][j] = '\0';
  
  for(i = 0; i < total_real_vars; i++){
    found = 0;
    for(j = 0; j < total_real_vars; j++){
      if( (strcmp(real_unique_vars[j],real_vars[i])) == 0){
	found = 1;
	break;
      }
    }
    if(found == 1)continue;
    else strcpy(real_unique_vars[unique_real_vars++] , real_vars[i]);
    
  }
  
  char dd_truncated_statements[declared_vars][MAX_LENGTH];
  for (i = 0; i < declared_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      dd_truncated_statements[i][j] = '\0';
  
  int dd_truncated_number = 0;
  
  const char de[] = "[]";
  for( i = 0; i < declared_vars; i++){
    strcpy(tmpstr ,declare_vars[i]);
    tmp = strtok(tmpstr,de);
    
    strcpy(dd_truncated_statements[dd_truncated_number],tmp);
    dd_truncated_number++;
    
  }  
  
  char external_vars[unique_real_vars][MAX_LENGTH];
  for (i = 0; i < unique_real_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      external_vars[i][j] = '\0';
  
  int external_unique_vars = 0;
  
  for(i = 0; i < unique_real_vars; i++){
    found = 0;
    for(j = 0; j < dd_truncated_number; j++){
      if( (strcmp(real_unique_vars[i],dd_truncated_statements[j])) == 0){
	found = 1;
	break;
      }
    }
    if(found == 1)continue;
    else strcpy(external_vars[external_unique_vars++] , real_unique_vars[i]);
    
  }

  /*
    for(i = 0; i < statement_number; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(statements[i]),statements[i]);
  


    for(i = 0; i < total_tokens; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(tokens[i]),tokens[i]);
    
    for(i = 0; i < t_statements_number; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(token_statements[i]),token_statements[i]);
    
    for(i = 0; i < t_statements_number; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(truncated_statements[i]),truncated_statements[i]);
    
    for(i = 0; i < total_vars; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(all_vars[i]),all_vars[i]);
    
    for(i = 0; i < total_real_vars; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(real_vars[i]),real_vars[i]);
    
    for(i = 0; i < declared_vars; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(declare_vars[i]),declare_vars[i]);


    for(i = 0; i < dd_truncated_number; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(dd_truncated_statements[i]),dd_truncated_statements[i]);

    for(i = 0; i < unique_real_vars; i++ )
    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(real_unique_vars[i]),real_unique_vars[i]);


  fprintf(stdout, "\n\n --------------------------------------\n\n");

  */
  
  fprintf(stdout, "\n");
  
  for(i = 0; i < external_unique_vars; i++ )
    fprintf(stdout, "%d: %s  \n\n",i+1,external_vars[i]);
  
  fprintf(stdout, "\n Total External(required) Variable(s) = %d \n",external_unique_vars);
  
  fprintf(stdout, "\n");
  
  fclose(input);
  
  return 0;
}

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
