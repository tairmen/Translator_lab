# Translator_lab
This is simple translator for signal language

BNF 

1. signal-program --> program 
2. program --> PROGRAM procedure-identifier ; <block>. | PROCEDURE procedure-identifier parameters-list ; block ; 
3. block --> declarations BEGIN statementslist END 
4. declarations --> label-declarations 
5. label-declarations --> LABEL unsignedinteger labels-list; | empty 
6. labels-list --> , unsigned-integer labelslist | empty
7. parameters-list --> ( declarations-list ) |  empty
8. declarations-list --> empty 
9. statements-list --> empty
10. procedure-identifier --> identifier 
11. identifier --> letter string
12. string --> letter string | digit string | empty
13. unsigned-integer --> digit digits-string 
14. digits-string --> digit digits-string | empty 
15. digit --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
16. letter --> A | B | C | D | ... | Z 
