%{
#include <stdlib.h>
void yyerror(char *);
%}
%%
[0-9]	{putchar('n');return 0;}
.	{return 1;}
%%
int yywrap(void) {
return 1;
}

 int main(){
	 yylex();
 }
