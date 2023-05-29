Programmcode
====

Dieser Ordner enthält sämtlichen Programmcode, der in dem Roboterauto zum Einsatz kommt.
Als auch programme zum testen ob diverse sensoren funktionieren. Zudem Backup Codes Im Fall von einer Änderung.

· [`Eröffnungsrennen`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/main_hinderniss_V01)

· [`Hindernissrennen`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/main_hinderniss_V01)

· [`Ultraschall_test_L`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/Ultraschall_test_L)

· [`Ultraschall_test_R`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/Ultraschall_test_R)

· [`Ultraschall_test_V`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/Ultraschall_test_V)

· [`backup codes`](https://github.com/biswro2023/smartiecar/tree/master/Programmcode/backup%20codes)

Allgemeines
===
Zuerst haben wir kleine kleine Testprogramme für die Bewegungen und Sensoren des Autos geschrieben. Dabei Haben wir uns an Beispielen von Funduino.de orientiert und Beispielprogramme der Sensorhersteller benutzt. Unsere neu geschrieben Programme haben wir mit einer Versionsnummer im Namen gekennzeichnet. Zum Beispiel heisst die erste Version main_OH_V1.

Programmaufbau
===
als erstes habenm wir alle Libraries, welche für den Roboter und die einzelnen Komponenten wichtig waren hinzugefügt. Zunächst haben wir Globale Variablen sowie unsere eigenen Variablen definiert. Einer der wichtigsten Aspekte unseres Programmes sind die Eigenen erstellten Funktionen. Diese sind besonders wichtig um sowohl in der Loop als auch in dem Setup den ganzen Ablauf der Rennen zu Fahren. Nennenswert ist es auch das mit den eigenen funktionen die wir erstellt haben, dass wenn mal ein Fehler oder eine Änderung vorgenommen werden sollte diese keine umständlichkeit haben. Es gibt zum einen unsere eigenen Funktionen und dann die der Pixycam oder der IMU welche wir mithilfe der testprogramme übernommen haben. Im Setup wird mit unseren eigenen funktionen alle wichtigen Komponenten wie Ultraschallsensor gestartet. Die ergebnisse werden dann auf unser LCD screen gedruckt in einer anordnung num festzustellen ob die sensoren irgendwelche Probleme aufweisen. Anschließend in der Loop werden wieder verschieden Fuktionen aufgerufen um die Blöcke mithilfe der Pixycam zu erkennen um die dann auch vor edm fahren auf dem LCD anzuzeigen , dass im Endeffekt dann kein Fehlstart geschieht. Zum schluss werden Ecken berechnet um die geziehlten runden zu fahren.


Eröffnungsrennen
===
1.  zu beginn fängt Die Funktion SpaceUS_V() den Abstand des Fahrzeugs zur Kurve zu messen.
2.  SpaceUS_L() und SpaceUS_R() messen den Abstand des Fahrzeugs zur linken bzw. rechten Seite der Kurve.
3.  Die Funktion IMU_getAngle() aktualisiert die Orientierung des Fahrzeugs.
3a. wenn das auto direkt neben einer wand startet kann die FR sofort aus Abstand zu wand < 10cm bestimmt werden
4.  Das Programm bestimmt die Fahrtrichtung anhand der gemessenen Abstände zur Kurve. sonst bestimmt das Programm die FR sobald die Abstandssensoren auf einer seite keine wand mehr erkennen können. 
5.  Wenn das Fahrzeug geradeaus fährt, die fahrtrichtung noch nicht bekannt ist (FR==K)und der Abstand zur linken Seite der Kurve größer als 60 ist, ändert das Programm die Fahrtrichtung auf links (FR = 'L').
5a. genau das gleiche geschieht für Rechts.
6.  Zunächst fährt das Fahrzeug geradeaus wenn der Abstand zur rechten Wand größer als 60 ist und die FR rechtsrum ist , fährt der bot eine rechtskurve Kurve_R().
6a. dasselbe gilt auch für links. Kurve_L()
6b. nach jeder kurve wird die anzahl jeder ecken um eins erhöht und gespeichert. 
7.  Wenn das Fahrzeug nach links fahren soll und der Abstand zur linken Seite der Kurve größer als 60 ist, führt das Programm die Kurve_L() Funktion aus.
8.  Wenn das Fahrzeug nach rechts fahren soll und der Abstand zur rechten Seite der Kurve größer als 60 ist, führt das Programm die Kurve_R() Funktion aus.
9.  Die Funktion Ausrichten() sorgt dafür, dass das Fahrzeug in die richtige Ausrichtung gebracht wird. das versucht er durch die seitenabstände die gemessen wurden das auto in die mitte zu steuern.
9a. sobald FR bekannt ist orientiert sich der Roboter an der Innenbande aus mit einem festen Abstand von 25cm aus. Dafür haben wir die Funktionen Ausrichten_L() und Ausrichten_R()
10. Wenn der Abstand zur Kurve kleiner als 80cm ist, fährt das Fahrzeug langsamer.
11. Wenn das auto 12 ecken gefahren ist und diese gezählt hat, fährt er noch ein stück geradeaus und bleibt im geraden Abschnitt stehen.


![Diagramm_Eröffnung](https://github.com/biswro2023/smartiecar/assets/131591590/fbee0cb2-4aab-434d-a97d-d06e2026ba62)


Hindernissrennen
===
![Diagramm_Hindernisse](https://github.com/biswro2023/smartiecar/assets/131591590/263c1bce-014c-4458-99a9-e519d6a30377)
