# Arabica

Compiler to create binaries for the AraBiCa VM.

## Bytecode

|Instr.|Args|Pop|Description|
|------|----|---|-----------|
|01|4|0|LOAD_VAL <valeur> : Empile une valeur numérique (int32) sur la pile.|
|02|1|0|READ_VAR <identifiant> : Empile la valeur de la variable spécifiée(uint8 pour l'ID de la variable).|
|03|1|1|STORE_VAR <identifiant> : Stocke la valeur du sommet de la pile dans la variable (uint8 pour l'ID de la variable).
|04|0|2|ADD : Additionne les deux valeurs numériques (int32) au sommet de la pile.|
|05|0|2| SUB : Soustrait les deux valeurs numériques (int32) au sommet de la pile. |
|06|0|2|MUL : Multiplie les deux valeurs numériques (int32) au sommet de la pile.|
|07|0|2|DIV : Divise les deux valeurs numériques (int32) au sommet de la pile.|
|08|0|2|MOD : Modulo des deux valeurs numériques (int32) au sommet de la pile.|
|09|4|0|JMP <offset> : Saute à l'instruction en se décalant de la valeur de l'offset (int32).|
|0A|4|1|JMP_IF_ZERO <offset> : Saute à l'instruction en se décalant de la valeur de l'offset si la valeur du sommet est zéro (int32).|
|0B|4|1|JMP_IF_TRUE <offset> : Saute à l'instruction en se décalant de la valeur de l'offset si la valeur du sommet est non nulle(int32).|
|0C|0|2|EQ : Empile 1 si les deux valeurs au sommet (int32) sont égales, sinon 0.|
|0D|0|2|NEQ : Empile 1 si les deux valeurs au sommet (int32) ne sont pas égales, sinon 0.|
|0E|0|2|GT : Empile 1 si la valeur en sous-sommet (int32) est plus grande que celle au sommet, sinon 0.|
|0F|0|2|LT : Empile 1 si la valeur en sous-sommet (int32) est inférieure à celle au sommet, sinon 0.|
|10|0|2|GTE : Empile 1 si la valeur en sous-sommet (int32) est plus grande ou égale à celle au sommet, sinon 0.|
|11|0|2|LTE : Empile 1 si la valeur en sous-sommet (int32) est inférieure ou égale à celle au sommet, sinon 0.|
|12|0|1|PRINT_VAL : Dépile une valeur de la pile (int32) et l'imprime.|
|13|0|0|INPUT_VAL : Lit une valeur numérique (int32) de l'entrée utilisateur et l'empile.|
|14|0|0|HALT : Arrête l'exécution de la machine virtuelle.|
|15|1+var.|0|LOAD_STR <taille, chaîne> : Empile une chaîne de caractères (uint8 pour sa taille, suivi de la chaîne elle-même, pas terminée par un NUL).|
|16|0|1|PRINT_STR : Dépile une référence à une chaîne et l'imprime.|
|17|0|0|INPUT_STR : Lit une chaîne de l'entrée utilisateur et empile une référence à celle-ci (uint8).|
|18|0|1|STR_LEN : Dépile une référence à une chaîne et empile la longueur de celle-ci (int32).|
|19|0|2|CONCAT : Dépile deux références à des chaînes, les concatène et empile la référence au résultat.|
|1A|0|1|GET_CHAR : Dépile une référence à une chaîne (uint8) et un indice (uint8), puis empile le caractère à cet indice (char).|
|1B|0|3|SET_CHAR : Dépile un caractère (char), un indice (uint8) et une référence à une chaîne (uint8), et insère le caractère à l'indice spécifié.|
|1C|0|2|STR_CMP : Dépile deux références à des chaînes, les compare et empile le résultat.|


The compiled file must have one header formatted like the following:
- 4 bytes "CODE"
- 4 bytes indicating the size of the code itself (header excluded)
- 16 bytes for the program name
Totalling an amount of 24 bytes.
(')