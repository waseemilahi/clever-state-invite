#include "CSInvite.h"


/* The Find Substring Function. (acquired from an online forum*/
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

/* Acquired from online blog. */
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;

}

/* Split the string in two. */
int split(char *original, char * split1, char * split2 , int scope)
{
  int i = 0;
  int j = 0;
  int flag = 0;

  while (original[i] != '\0')
  {
		if (flag == 0)
		{
			if ((original[i] == '{') || (original[i] == '}'))
			{
				flag = 1;
				split1[i] = '\0';
				
				if(original[i] == '{')
				{
					scope = scope + 1;
				}
				else if(original[i] == '}')
				{
					scope = scope - 1;
				}
			}
			else
			{
				split1[i] = original[i];
			}
		}
		else
		{
			split2[j++] = original[i];
		}
		i++;
  }
  if(flag == 0)
  {
	split1[i] = '\0';
	return -1;
  }

  return scope;
}
