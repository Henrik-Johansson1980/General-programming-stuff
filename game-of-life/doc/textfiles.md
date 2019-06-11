# Information om de olika textfilerna.
  Author: Henrik Johansson, Filformat skapat av Marcus Stenroos
  
## Inledning
 I katalogen textfiles ligger en samling av textfiler som kan användas tillsammans med programmet.
 De olika textfilerna innehåller diverse olika startpositioner för cellerna som tillsammans med 
 Conways spelregler formar några av de klassiska Game of Life mönstren, som exempelvis blinkers, 
 gliders med flera.
 
## Användarinstruktioner
 För att använda filerna i programmet anger man ett argument av modellen -f filnamn.txt när man bygger
 spelet. Om filerna inte ligger i byggkatalogen måste man ange korrekt sökväg till filen.
 
## Filformat
 För att en textfil (filnamn.txt) ska läsas in ordentligt ska de ha följande format:
 
		0
		0
		500
		00000000000000000000000000000000000000000000000000
		00001000000000000000000000000000000000000000000000
		00001000000000000000000000000000000000000000000000
		00001000000000000000000000000000000000000000000000
		00000000000000000000000000000000000000000000000000
		00000000000000000000000000000000000000000000000000
		00000000000000000000000000000000000000000000000000
		00000000000000000000000000000000000000000000000000
 

### Rad 1 Regel för udda generationer
  Den översta raden sätter en regel i intervallet (0-4) som ska köras för ojämna generationer. Noll är default och kör Conway. 
  De övriga är utvecklarnas specialregeler. Regellistan är som följer:
  
  0. Conway
  1. Henrik
  2. Anna
  3. Marcus


### Rad 2 Regel för jämna generationer
Den andra raden sätter regel i intervallet (0-4) som ska köras för jämna generationer. Reglerna är samma som ovan.

### Rad 3 Antal generationer som ska köras.
Här anger man hur många generationer som ska köras.

### Spelbrädet
De övriga raderna utgör spelbrädet och sätter storleken på detta. Så det antal tecken som sätts på en rad motsvarar spelbrädets bredd
och antalet rader anger dess höjd. För att markera om cellen lever eller inte sätter man siffran 0 eller ett. Där en nolla motsvarar en död cell
och en etta motsvarar en levande cell.


 