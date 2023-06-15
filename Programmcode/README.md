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
Als erstes haben wir alle erforderlichen Bibliotheken für den Roboter und die einzelnen Komponenten hinzugefügt. Anschließend haben wir globale Variablen sowie unsere eigenen Variablen definiert. Eine der wichtigsten Aspekte unseres Programms sind die selbst erstellten Funktionen. Diese sind entscheidend, um den gesamten Ablauf des Rennens sowohl in der Schleife (Loop) als auch im Setup zu steuern. Es ist erwähnenswert, dass durch die selbstgeschriebenen Funktionen Änderungen leicht vorgenommen werden konnten, falls ein Fehler auftrat. Das gesamte Programm wurde in einzelne Module aufgeteilt, um einen besseren Überblick über die verschiedenen Funktionen zu haben. Zum Beispiel werden Funktionen wie `Kamera_Start()` in einer `cam.h`-Datei abgelegt, um den Zustand der Funktionen zu überprüfen. Es gibt unsere eigenen Funktionen sowie Funktionen für die PixyCam oder die IMU, die wir mithilfe von Testprogrammen übernommen haben.

Im Setup werden mithilfe unserer eigenen Funktionen alle wichtigen Komponenten wie der Ultraschallsensor gestartet. Die Ergebnisse werden dann auf dem LCD-Bildschirm angezeigt, um festzustellen, ob die Sensoren irgendwelche Probleme aufweisen. In der Schleife (Loop) werden verschiedene Funktionen aufgerufen, um die Blöcke mithilfe der PixyCam zu erkennen und sie vor dem Fahren auf dem LCD-Bildschirm anzuzeigen, um letztendlich einen fehlerfreien Start zu gewährleisten. Schließlich werden die Kurvenberechnungen durchgeführt, um gezielte Runden zu fahren. Die Funktionen sind mit kurzen Sätzen beschrieben, die als Beschreibung dienen.

Eröffnungsrennen
===
1. `SpaceUS_L()` und `SpaceUS_R()` messen den Abstand des Fahrzeugs zur linken bzw. rechten Seite der Kurve.
2. Die Funktion `IMU_getAngle()` aktualisiert die Orientierung des Fahrzeugs.
2a. Wenn das Auto direkt neben einer Wand startet, kann die FR sofort als Abstand zur Wand < 10 cm bestimmt werden.
3. Das Programm bestimmt die Fahrtrichtung anhand der gemessenen Abstände zur Kurve. Ansonsten bestimmt das Programm die FR, sobald die Abstandssensoren auf einer Seite keine Wand mehr erkennen können.
4. Wenn das Fahrzeug geradeaus fährt, die Fahrtrichtung noch nicht bekannt ist `(FR == K)` und der Abstand zur linken Seite der Kurve größer als 60 ist, ändert das Programm die Fahrtrichtung auf links `(FR = 'L')`. Das Gleiche gilt auch für rechts.
5. Zunächst fährt das Fahrzeug geradeaus. Wenn der Abstand zur rechten Wand größer als 60 ist und die FR rechtsrum ist, fährt der Bot eine Rechtskurve `Kurve_R()`.
5a. Das Gleiche gilt auch für links: `Kurve_L()`.
5b. Nach jeder Kurve wird die Anzahl der Ecken um eins erhöht und gespeichert.
6. Wenn das Fahrzeug nach links fahren soll und der Abstand zur linken Seite der Kurve größer als 60 ist, führt das Programm die `Kurve_L()` Funktion aus.
7. Wenn das Fahrzeug nach rechts fahren soll und der Abstand zur rechten Seite der Kurve größer als 60 ist, führt das Programm die `Kurve_R()` Funktion aus.
8. Die Funktion `Ausrichten()` sorgt dafür, dass das Fahrzeug in die richtige Ausrichtung gebracht wird, indem es versucht, das Auto in die Mitte zu steuern, basierend auf den gemessenen Seitenabständen.
8a. Sobald `FR` bekannt ist, orientiert sich der Roboter an der Innenbande mit einem festen Abstand von 25 cm. Dafür haben wir die Funktionen `Ausrichten_L()` und `Ausrichten_R()`.
9. Wenn der Abstand zur Kurve kleiner als 80 cm ist, fährt das Fahrzeug langsamer.
10. Wenn das Auto 12 Ecken gefahren ist und diese gezählt hat, fährt es noch ein Stück geradeaus und bleibt im geraden Abschnitt stehen.

![Diagramm_Eröffnung](https://github.com/biswro2023/smartiecar/assets/131591590/fbee0cb2-4aab-434d-a97d-d06e2026ba62)
#


Hindernissrennen
===
1. Zuerst wird auf Hindernisse geprüft mit der `Finde_Block()` Funktion.
2. Der Abstand nach vorne wird mit `SpaceUS_V()` gemessen.
3. Auf dem LCD werden dann die gefundenen Blöcke angezeigt.
3a. Je nach `BlockID` wird mit `lcd.setRGB()` die Farbe gesetzt. Wenn kein Block in Sicht ist, wird der Bildschirm weiß gesetzt.
4. Die Pixy prüft, ob der gesehene Block im richtigen Bereich steht. Zudem wird überprüft, ob der Block zu nah ist. Wenn ja, setzt sich der Roboter zurück durch Rückwärtsfahren.
4a. Wenn es keine Probleme gibt, führt er die Funktion `Ausweichen_R()` aus.
5. Das Gleiche gilt für den grünen Block.
6. Im Fall, dass kein Block in Sicht ist, der ausgewichen werden muss, messen alle Sensoren noch einmal die Abstände aus allen Seiten.
6a. Wenn der `Abstand_R()` zur Außenwand kleiner als 80 cm beträgt, wird `FR` auf Rechts gesetzt. Für links auch mit der Funktion `Abstand_L()`.
7. Anschließend wird wieder auf eine Kurve oder Wende geprüft.
8. Wenn kein Hindernis erkannt wurde, wird eine Notbremse mit der Funktion `runMotor_R()` gezogen.
9. Am Ende orientiert er sich wieder an der Außenwand, indem `Abstand_R()` und `Abstand_L()` gleich `SpaceUS_L()` und `SpaceUS_R()` gesetzt werden.
10. Sollte es trotzdem dazu kommen, dass der Roboter kein Hindernis erkennt, "würfelt" er sich eine Antwort mit einem Zufallsgenerator mit der Variable `int zufall`.

![Diagramm_Hindernisse](https://github.com/biswro2023/smartiecar/assets/131591590/263c1bce-014c-4458-99a9-e519d6a30377)
