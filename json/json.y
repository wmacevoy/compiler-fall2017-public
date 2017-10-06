%token OPEN_CURLY CLOSE_CURLEY COMMA OPEN_BRACE CLOSE_BRACE COLON
       STRING NUMBER TRUE FALSE NULL

object:
  OPEN_CURLY optional_name_value_pairs CLOSE_CURLEY
;

optional_name_value_pairs :
  /* empty */
|
  name_value_pairs
;

name_value_pairs :
  name_value
|
  name_value_pairs COMMA name_value
;

name_value:
   string COLON value
;

array:
  OPEN_BRACE optional_values CLOSE_BRACE
  ;

optional_values :
  /* empty */
|
  values
  ;

values :
  value
  |
  values COMMA value
  ;

value :
  string | number | object | array | TRUE | FALSE | NULL ;

string : STRING ; 
number : NUMBER ;


