# Specialregel: Henrik

## Inledning 
 Denna sektion beskriver Henriks specialregel i denna version av %Game of Life. Regeln uppför sig lite annorlunda
 beroende på om den körs som regel för jämna eller ojämna generationer. Själva beteendet är dock detsamma. Den snabba
 förökningstakten och de många överlevnads chanserna gör att de påminner lite om myror som irrar omkring. För att 
 det hela skulle bli lite roligare rensas ett område av planen efter ett antal generationer, detta kallar jag fotavtrycket.
 Detta utförs då generationen är jämt delbar med 16 eller 17 beroende på om regeln är satt att köras som jämn eller ojämn. 
 Därefter kan man titta när de små liven kravlar sig tilbaka in i det utrensade området.

 När regeln körs skrivs det ut ett H, i grön färg där det finns aktiva celler. När fotavtrycket kommer växlar färgen på planen
 till rött och texten till gult för den generationen. 
 
 
### Födelseregler
 En ny cell föds om den har en granne i någon omkringliggande ruta.

### Överlevnadsregler
 En cell överlever om den har 3 2,3,6 eller 8 grannar.

### Använda Terminalfärger
 Grön, röd och gul och vit om man räknar standarden.
 
### Odd Rule
 Om regeln sätts att köras som ojämn regel kommer rensningen att ske när antalet generationer är jämt delbart med 17.
 
### Even Rule
 Om regeln sätts att köras som jämn regel sker rensningen när antalet generationer är jämt delbart med 16.