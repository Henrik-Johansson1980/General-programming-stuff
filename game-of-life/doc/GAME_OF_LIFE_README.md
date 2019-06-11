# Game Of Life

 Av: Anna Hansson, Henrik Johansson & Marcus Stenroos

---

## Inledning 

---

Detta projekt är en implementation av John Conways cellulära Automat %Game Of Life skriven i C++, för Mittuniversitetets
kurs DT042G, Metoder och verktyg i mjukvaruprojekt vårterminen 2016.

---

## Spelet

---
Game Of Life är ett så kallat zero-player-game då det inte tar emot någon input från användaren under spelets gång. Utvecklingen
bestäms istället av starttillståndet och de regler som appliceras (tillståndet manipuleras dock vid vissa generationer om
våra specialregler används). Spelplanen består av ett tvådimensionellt rutnät där varje cell/ruta antingen är död eller levande. 
Vid ett generationsskifte bestäms en cells överlevnad och födelse av dess grannars tillstånd och vilka regler som appliceras, 
enligt Conways regler föds en cell som har exakt tre levande grannar och en cell överlever om den har exakt två eller tre 
levande grannar.

---

## Verktyg

---

För att skapa projektet användes följande verktyg.
 
 + Cmake
 + Qt creator - Utvecklingsmiljö
 + Doxygen - Dokumentation
 + Git - Versionshantering
 + Bitbucket -Versionshantering
 + Slack - Kommunikation
 + Memstat - För att leta minnesläckor
 + Catch - Ramverk för enhetstestning
 
 
 ---
 
# Manual
 
 ---
 
## Bygga programmet
 
 ---

  För att bygga programmet krävs minst version 3.2 av cmake

---
 
### Ange argument

---
 
 Det är möjligt att ange argument under "Command Line Arguments" innan programmet körs. Programmet tar följande argument:
 
 + -h 
 
    Genom att ange detta argument visas programmets hjälpmeny, programmet avslutas efter körning med detta argument. 
	
 + -s *BREDDxHÖJD* 
 
	Ange detta argument på formen -s BreddxHöjd för att ange storleken på spelpanen. Defaultstorleken är 80x24.
	
	**Exempel:**
	
		 -s 80x24
		 
 
 + -er *REGELNAMN*
 
   Detta argument används för att välja vilken regel som ska gälla för jämna generationer (even rule).
   Anges inte argumentet används Conways originalregler.
   
   Programmet tar Följande Regelnamn: **HENRIK**, **ANNA**, **MARCUS**. Själva regelnamnet behöver inte ges med stora bokstäver.
   
   **Exempel:**
		
		-er HENRIK 
		-er ANNA
		-er MARCUS
		
		Använd tillsammans med en udda Regel
		
		-er MARCUS -or ANNA
		
		Använd samma regel för både jämna och udda generationer
		
		-er HENRIK -or HENRIK
		
		Använd ej ensamt utan regelnamn
		
		-er
		
 
 + -or *REGELNAMN*
 
   Detta argument används på samma sätt som -er ovan, med skillnaden att regeln gäller för udda generationer.
   Används inte argumentet används Conways originalregler. 
   
   Det är möjligt att ange en regel för udda och en för jämna samtidigt.
   Programmet tar Följande Regelnamn: **HENRIK**, **ANNA**, **MARCUS**. Själva regelnamnet behöver inte ges med stora bokstäver.
   
    **Exempel:**
		
		-or HENRIK 
		-or ANNA
		-or MARCUS
		
		Använd tillsammans med en jämn Regel
		
		-or HENRIK -er ANNA
		
		Använd samma regel för både udda och jämna generationer.
		
		-or ANNA -er ANNA
		
		Använd ej ensamt utan efterföljande regelnamn
		
		-or

 
 
 + -g *HELTAL*
 
	Ange argumentet -g följt av ett heltal för att bestämma hur många generationer som ska köras. Default antal generationer är 500.
	
	**Exempel:**
		
		-g 100


 
 + -f *FILNAMN*

	Ange argumentet -f följd av filens sökväg för att läsa in argument från fil. [Mer info om filformatet](@ref md_doc_textfiles). Kan användas om man t.ex. inte vill köra programmet i default läge.
	
	**Exempel:**
		
		-f filnamn.txt
		
		
---