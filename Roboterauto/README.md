Roboterauto
====

Dieser Ordner muss sechs Bilder des Roboterautos enthalten, die alle Seiten zeigen.

READ ME

Wir haben  uns für das Totem Maker Bausystem entschieden, um das Chassie zu bauen. Andere Teile, die wir benötigten, haben wir selbst angefertigt.
Unsere Grundidee für das Eröffnungsrennen war, dass wir uns mit Hilfe von drei Sensoren (rechts,links, vorne) an den Abständen zur Spielfeldbbegerenzungen zu orientieren.
Zusätzlich haben wir für das fahren für der Kurven einen Farbsensor und ein Gyroskop eingebaut. Im Eröffnungsrennenbenutzen wir nur das Gyroskop.
Zuerst haben wir einen Rahen aus Teilen des Totem Maker Bausystem angefertigt. Anschließend schnitten wir aus einer 4mm Plastikplatte die Bodenplatte aus und befestigten den Rahem darauf.
Nachdem die Vorderachse fertig war, zeichneten wir auf Millimeterpapier ein Lenkdreieck, um die Position der Hinterachse zu bestimmmen. 
Für die Stromversorgung verwenden wir eine 12 Volt Lipo Batterie, die wir auf dem hinteren Teil unseres Autos befestigen.
Den Motor, den wir verwenden, haben wir aus dem Totem Maker Bausystem erhalten. Für die Steuerung des Motors und der Sensoren verwenden wir einen Arduino Nano. 
Ein LCD Monitor gibt uns Feedback zu dem aktuell laufendem Programm. 
Vorne auf dem Auto haben wir einen Kameraturm mit der Husky Lens montiert.


Prozess:


Zu Beginn haben wir die ersten Schritte der im Totem Maker Bausystem beigelegten Bauanleitung befolgt, um einen stabilen rahemn für das Auto zu erhalten. 

![Frame](https://user-images.githubusercontent.com/131177565/235680006-affdd363-4297-4a06-9caa-a8125de43fb9.png)

Da das Auto, das die Anleitung beschreibt zu breit ist, mussten wir die vorderachse kürzen, damit unser Auto die vorgeschriebene Breite nicht überschreitet.

![image1](https://user-images.githubusercontent.com/131177565/235680801-dcf372b3-89f4-4a34-b5b8-66f85cb70028.jpeg)

Die 3d gedruckten Teile, der Vorderachse stammen aus der STL-Libary von Totem Maker.
Zu dem Zeitpunkt haben wir die standard Reifen des Totem Maker Beusets verwendet. 
Danach haben wir eine Bodenplatte aus 4mm dickem Kunststoff geschnitten und an das auto geschraubt.
Wir haben eine 4mm Platte genommen, da wir vermuteten, dass eine Platte, die nur 2mm dick ist, schnell brechen würde.
Um die Position der Hinterachse zu bestimmen haben wir mit Hilfe einer Bauzeichnung  unsere Bodenplatte ein Lenkdreieck gezeichnet.

![Bodenplatte-1](https://user-images.githubusercontent.com/131177565/235682426-33cb649e-8ef1-453e-b3f9-9b506c7610f3.png)

Die hinterachse mit dem Motor haben wir dann auf die Bodenplatte geschraubt.
Der Motor ist mit einer 1:1 Überetzung mit zwei Zahnrädern an der Hinterachse angeschlossen.
Anschließend haben wir uns überlegt und ausprobiert, wie wir die elektronischen Bauteile auf dem Auto befestigen. 
Der Motorkontroller so wie unseren Hauptstromschalter haben wir auch auf der Bodenplatte befestigt. 
Der Lipo-Akku liegt auf dem Rahmen unseres Autos.

Bei den ersten Testfahrten ist uns aufgefallen, dass unser Auto in den Kurven oft über den Boden rutscht und die Reifen durchdrehen.
Danach sind wir auf die Reifen des Funduino Baukastens ungestiegen, die härter waren und mehr Bodenkontakt durch das kleinere Profil besitzen.
Das Problem war dadurch teilweise gelöst.
Die Reifen rutschten weniger, aber die Reifen drehten manchmal immernoch durch, weshalb unsere kurven ungenau wurden.
Jetzt und Final verwenden wir Reifen, die sehr hart sind und kein Profil besitzen, wodurch der Bodenkontakt maximiert wird.
Diese Reifen haben wir aus dem Modellbauladen erhalten.

Bild (Reifen)

Damit wir den Arduino auf dem Auto befestigen können, haben wir zuerst eine vorgeschnitte Kunststoffplatte aus dem Funduino Bauset benutzt. 
Diese ist aber leider gebrochen, weshalb wir eine neue Platte aus enem dickerem Kunststoff schneiden mussten.
Der Aurduino ist nun mit Kunststoff Abständen an dieser Platte fest geschraubt.

Bild(Arduino)

Als der Ardunio befestigt war konnten wir schließlich Programme für das Auto schreiben und ausprobieren.
Um auch Feedback zu Problemen oder Erfolgen zu erhalten, haben wir ein LCD-Monitor auf dem Auto befestigt.
Dieser Monitor gibt sowohl am Anfang des Programmes Informationen über die Sensoren als Text, als auch durch den verschieden farbigen Hintergrund Informationen über den Aktuellen Status des Programmes.
Als wir den Monitor zum erstem mal angeschlossen hatten, konten wir nichts erkennen. der Monitor zeigte kein Text oder Farbe.
Wir fanden herraus, dass der Monitor 5 Volt benötigt, wir ihn aber nur 4.7 Volt angeschlossen hatten.
Deshalb haben wir sowohl für die Stromversorgung des LCD-Monitors als auch für die Stromversorgungs unseres Lenkservos eine extra Stromversorgungsleiste eingebaut

Bild(Stromleiste)

Oben auf unserem Auto haben wir neben dem LCD-Monitor und der Stromleiste außerdem auch noch den Button für den Start und den Gyro für die Kurven montiert.
Zu Beginn hatten wir einen anderen größeren Button verwendet. Weil der jedoch einen großen Wiederstandhatte, der das Auto beim drücken mit nach unten drückte, und weil er nicht gut erreichbar montiert war,
haben wir den Button ausgetauscht zu dem Button, den wir jetzt verwenden.
Anschließend haben wir uns um das Kabelmanagement gekümmert. Wir haben die wichtigen Anschlüsse des Hauptsromsystems an der Außenseite mit schnell verschlüssen befestigt, da mit wir das Auto schnell warten 
und reparieren können.

![image](https://user-images.githubusercontent.com/131177565/236902868-fe6987f2-450b-4a82-ad03-88c99bf6b534.png)


LCD Feedback
LCD Schrift (5V - 4.7V) Extra Stromleiste


