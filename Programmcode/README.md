Programmcode
====

Dieser Ordner enthält sämtlichen Programmcode, der in dem Roboterauto zum Einsatz kommt.
Zudem auch Programme zum testen ob diverse sensoren funktionieren. Zudem Backup Codes Im Fall von einer Änderung.

· [`Eröffnungsrennen`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/main_hinderniss_V01)

· [`Hindernissrennen`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/main_hinderniss_V01)

· [`Testprogramme`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/Test%20Programme)

· [`backup codes`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/alte_versionen/backup%20codes)

Allgemeines
===
Zuerst haben wir kleine kleine Testprogramme für die Bewegungen und Sensoren des Autos geschrieben. Dabei Haben wir uns an Beispielen von Funduino.de orientiert und Beispielprogramme der Sensorhersteller benutzt. Unsere neu geschriebenen Programme haben wir mit einer Versionsnummer im Namen gekennzeichnet. Zum Beispiel heisst die erste Version `main_OH_V1.ino`. Unsere Hauptdatei endet mit `.ino` und die untergeteilten Dateien mit `.h` 


Programmaufbau
===
als erstes habenm wir alle Libraries, welche für den Roboter und die einzelnen Komponenten wichtig waren hinzugefügt. Zunächst haben wir Globale Variablen sowie unsere eigenen Variablen definiert. Einer der wichtigsten Aspekte unseres Programmes sind die Eigenen erstellten Funktionen. Diese sind besonders wichtig um sowohl in der Loop als auch in dem Setup den ganzen Ablauf der Rennen zu Fahren. Nennenswert ist es auch dass durch die selbstgeschriebenen Funktionen es einfach war eine Änderung vorzunehmen falls ein Fehler aufgetreten ist. Das Ganze Programm haben wir in einzelne Module aufgeteilt um einen besseren Überblick auf die ganzen Funktionen zu haben. Zum Beispiel kommen Funktionen wie `Kamera_Start()` in eine `cam.h` Datei um zu wissen ob etwas passt oder nicht. Es gibt zum einen unsere eigenen Funktionen und dann die der Pixycam oder der IMU welche wir mithilfe der Testprogramme übernommen haben. Im Setup wird mit unseren eigenen funktionen alle wichtigen Komponenten wie Ultraschallsensor gestartet. Die ergebnisse werden dann auf den LCD screen gedruckt in einer anordnung um festzustellen ob die sensoren irgendwelche Probleme aufweisen. Anschließend in der Loop werden wieder verschieden Fuktionen aufgerufen um die Blöcke mithilfe der Pixycam zu erkennen um die dann auch vor dem fahren auf dem LCD anzuzeigen , dass im Endeffekt dann kein Fehlstart geschieht. Zum schluss werden Ecken berechnet um die geziehlten runden zu fahren. die Funktionen haben einen kurzen Satz, welcher als Beschreibung gilt.


Eröffnungsrennen
===
1.  `SpaceUS_L()` und `SpaceUS_R() `messen den Abstand des Fahrzeugs zur linken bzw. rechten Seite der Kurve.
2.  Die Funktion `IMU_getAngle()` aktualisiert die Orientierung des Fahrzeugs.
2a. wenn das auto direkt neben einer wand startet kann die FR sofort aus Abstand zu wand < 10cm bestimmt werden
3.  Das Programm bestimmt die Fahrtrichtung anhand der gemessenen Abstände zur Kurve. sonst bestimmt das Programm die FR sobald die Abstandssensoren auf einer seite keine wand mehr erkennen können. 
4.  Wenn das Fahrzeug geradeaus fährt, die fahrtrichtung noch nicht bekannt ist `(FR==K)` und der Abstand zur linken Seite der Kurve größer als 60 ist, ändert das Programm die Fahrtrichtung auf links `(FR = 'L')`. das gleiche für rechts auch
5.  Zunächst fährt das Fahrzeug geradeaus wenn der Abstand zur rechten Wand größer als 60 ist und die FR rechtsrum ist , fährt der bot eine rechtskurve `Kurve_R()`.
5a. dasselbe gilt auch für links. `Kurve_L()`
5b. nach jeder kurve wird die anzahl jeder ecken um eins erhöht und gespeichert. 
6.  Wenn das Fahrzeug nach links fahren soll und der Abstand zur linken Seite der Kurve größer als 60 ist, führt das Programm die `Kurve_L()` Funktion aus.
7.  Wenn das Fahrzeug nach rechts fahren soll und der Abstand zur rechten Seite der Kurve größer als 60 ist, führt das Programm die `Kurve_R()` Funktion aus.
8.  Die Funktion `Ausrichten()` sorgt dafür, dass das Fahrzeug in die richtige Ausrichtung gebracht wird. das versucht er durch die seitenabstände die gemessen wurden das auto in die mitte zu steuern.
8a. sobald `FR` bekannt ist orientiert sich der Roboter an der Innenbande aus mit einem festen Abstand von 25cm aus. Dafür haben wir die Funktionen `Ausrichten_L()` und `Ausrichten_R()`
9. Wenn der Abstand zur Kurve kleiner als 80cm ist, fährt das Fahrzeug langsamer.
10. Wenn das auto 12 ecken gefahren ist und diese gezählt hat, fährt er noch ein stück geradeaus und bleibt im geraden Abschnitt stehen.


![Diagramm_Eröffnung](https://github.com/biswro2023/smartiecar/assets/131591590/fbee0cb2-4aab-434d-a97d-d06e2026ba62)
#


Hindernissrennen
===
1. Zuerst  wird auf Hindernisse geprüft mit der `Finde_Block()` Funktion.
2. der Abstand nach Vorne wird mit `SpaceUS_V()` gemessen.
3. auf dem LCD werden dann die gefunden Blöcke angezeigt.
3a. je nach `BlockID` wird mit `lcd.setRGB()` die Farbe gesetzt. wenn kein Block in sicht ist wird der Bildschirm weiss gesetzt.
4. Die Pixy prüft ob gesehener Block im richtigen Bereich steht. Zudem wird geschaut ob der Bock zu nah ist. Wenn ja setzt der Roboter sich zurück durch rückwärtsfahren.  
4a. Wenn es keine Probleme gibt führt er die Funktion `Ausweichen_R()` aus.
5. das gleiche gilt für den grünen Block
6. Im Fall, dass kein Block in Sicht ist, welcher ausgewichen werden muss 
messen alle Sensoren noch einmal die Abstände aus allen Seiten.  
6a. Wenn zur Außenwand der `Abstand_R()` kleiner als 80cm beträgt wird `FR` auf Rechts gesetzt. Für links auch mit der Funktion `Abstand_L`
7. Anschließend wird dann wieder auf eine Kurve oder Wende geprüft
8. wenn kein Hinderniss erkannt wurde wird eine Notbremse gezogen mit der Funktion `runMotor_R()`
9. Am ende orientiert er sich wieder an der Aussenwand indem die `Abstand_R()` und `Abstand_l()` gleich den `SpaceUS_L` und `SpaceUS_R` gesetzt werden.
10. Sollte es trotzdem dazu kommen dass der Roboter kein Hinderniss erkennt dann "würfelt" er sich eine antwort mit einem Zufallsgenerator mit dem `int zufall`

![Diagramm_Hindernisse](https://github.com/biswro2023/smartiecar/assets/131591590/263c1bce-014c-4458-99a9-e519d6a30377)
