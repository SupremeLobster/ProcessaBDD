# ProcessaBDD
Programa en C++ que processa una base de dades de vols i avions i permet que s'hi entrin comandes per fer consultes a aquesta Base de Dades.

Per utilitzar-lo, cal executar la comanda "bin/Release/S4.exe" i passar-li els fitxer de dades que es volen utilitzar. Donem fitxers d'exemple a dins del directori "data". L'últim fitxer a entrar és el de consultes, on s'hi escriuen les consultes que es volen fer a la base de dades.

Per exemple:

"COUNT ROUTES"

"MOST USED PLANE", "VN"

...


Al directori arrel donem un fitxer anomenat "queries.txt" amb consultes d'exemple.
Per facilitat d'execució, si es vol es pot executar el programa amb 

"bin/Release/S4.exe" <files.txt

que ja carregarà tots els fitxers d'exemple necessàris i també carregarà el fitxer de "queries.txt" d'exemple de consultes.
