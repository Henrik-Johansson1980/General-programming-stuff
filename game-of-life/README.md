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
