Roboterauto
====


Prozess:

Wir haben uns für die Konstruktion des Autos für das Totem Maker Bausystem (siehe Quellen) entschieden. Das Auto, dass auf der Website vorgeschlagen ist, ist zu groß und hat einen nicht erlaubten Antrieb. Deswegen haben wir unser Chassis neu konstruiert und nur teilweise auf die Anleitung zurückgegriffen.
Zu Beginn haben wir die ersten Schritte, der im Totem Maker Bausystem vorgeschlagenem Bauanleitung befolgt, um eine stabile Vorderachse zu erhalten.
Da das Auto, das die Anleitung beschreibt zu breit ist, mussten wir die Vorderachse kürzen. So überschreitet unser Auto die vorgegebenen Maße nicht.


![image1](https://github.com/biswro2023/smartiecar/assets/131591590/8c653eb3-eba5-4a73-b68e-20d79b029bfa)


Die Vorderachse beinhalted 3D gedruckte Teile, die jedoch von Totem Maker gedruckt und beigelegt wurden.
Die 3D gedruckten Teile, der Vorderachse stammen aus der STL-Libary von Totem Maker.
Zu dem Zeitpunkt haben wir die standard Reifen des Totem Maker Bausystems verwendet. 
Danach haben wir eine Bodenplatte aus 4mm dickem Kunststoff geschnitten und an die Vorderachse geschraubt.
Wir haben eine 4mm Platte genommen, da wir vermuteten, dass eine Platte, die nur 2mm dick ist, schnell brechen würde.
Um die Position der Hinterachse zu bestimmen haben wir mit Hilfe einer Bauzeichnung  unserer Bodenplatte ein Lenkdreieck gezeichnet.


![Bodenplatte-1](https://user-images.githubusercontent.com/131177565/235682426-33cb649e-8ef1-453e-b3f9-9b506c7610f3.png)


Die Hinterachse und den Motor haben wir dann auf die Bodenplatte geschraubt.
Der Motor ist mit einer 1:1 Überetzung mit zwei Zahnrädern an der Hinterachse angeschlossen.
Anschließend haben wir uns überlegt und ausprobiert, wie wir die elektronischen Bauteile auf dem Auto befestigen. 
Der Motorkontroller so wie unseren Hauptstromschalter haben wir auch auf der Bodenplatte befestigt. 
Der Lipo-Akku liegt auf dem Rahmen unseres Autos.

Bei den ersten Testfahrten ist uns aufgefallen, dass unsere Reifen, die wir aus dem Totem Maker Bausystem genommen haben, zu groß sind und am 
Rahmen schleifen. Die zweiten Reifen aus dem Funduino Bauset waren kleiner und härter, aber sie übersteuerten oft wenn das Auto zu sehr einlenk.
Das Problem war dadurch teilweise gelöst.
Jetzt und Final verwenden wir Reifen, die weicher sind und kein Profil besitzen, wodurch der Bodenkontakt maximiert wird.
Diese Reifen haben wir aus einem Modellbauladen erhalten.


![image0 (1)](https://github.com/biswro2023/smartiecar/assets/131177565/c86c0d01-40ef-4458-8a59-f7c86a03f72b)


Damit wir den Arduino auf dem Auto befestigen können, haben wir zuerst eine vorgeschnitte Kunststoffplatte aus dem Funduino Bauset benutzt. 
Diese ist aber leider gebrochen, weshalb wir eine neue Platte aus enem dickerem Kunststoff schneiden mussten.
Der Aurduino ist nun mit Kunststoff Abständen an dieser Platte fest geschraubt.


![Links](https://github.com/biswro2023/smartiecar/assets/131177565/8c6c1879-a27a-4534-aaba-69cf2ef00b81)


Als der Ardunio befestigt war konnten wir schließlich Programme für das Auto schreiben und ausprobieren.
Um auch Feedback zu Problemen oder Erfolgen zu erhalten, haben wir ein LCD-Monitor auf dem Auto befestigt.
Dieser Monitor gibt sowohl am Anfang des Programmes Informationen über die Sensoren als Text, als auch durch den verschieden farbigen Hintergrund Informationen über den Aktuellen Status des Programmes.

Als wir den Monitor zum erstem mal angeschlossen hatten, konten wir nichts erkennen. der Monitor zeigte kein Text oder Farbe.
Wir fanden herraus, dass der Monitor 5 Volt benötigt, wir ihn aber nur 4.7 Volt angeschlossen hatten.
Deshalb haben wir sowohl für die Stromversorgung des LCD-Monitors als auch für die Stromversorgungs unseres Lenkservos eine extra Stromversorgungsleiste eingebaut


![237098416-ef6eb164-e023-4361-834d-cc200a337ebe](https://github.com/biswro2023/smartiecar/assets/131591590/9290e95d-9778-4164-b21f-74ed072e3c0a)


Oben auf unserem Auto haben wir neben dem LCD-Monitor und der Stromleiste außerdem auch noch den Button für den Start und den Gyro für die Kurven montiert.
Zu Beginn hatten wir einen anderen größeren Button verwendet. Weil der jedoch einen großen Wiederstandhatte, der das Auto beim drücken mit nach unten drückte, und weil er nicht gut erreichbar montiert war,
haben wir den Button ausgetauscht zu dem Button, den wir jetzt verwenden.
Anschließend haben wir uns um das Kabelmanagement gekümmert. Wir haben die wichtigen Anschlüsse des Hauptsromsystems an der Außenseite mit schnell verschlüssen befestigt, da mit wir das Auto schnell warten 
und reparieren können.


![Bild SV](https://github.com/biswro2023/smartiecar/assets/131177565/a73ba44c-52b8-4dde-ab65-c6c7560cb832)


Damit wir die Kurven gut fahren können haben wir außerdem neben dem Button ein Gyroskop eingebaut.
Das Gyroskop hilft uns genaue Kurven mit immer gleich bleibendem Winkel zu fahren.
Für das Hindernissrennen wollten wir anschließend auch eine Kamera an unserem Auto montieren.
Wir hatten zwei verschiedene Kameras zu auswahl: Die HHUSKYLENS und die PIXY CAM 2.

![image0 (1)](https://github.com/biswro2023/smartiecar/assets/131177565/883c4d95-4bc7-4951-97ae-d3c51a035d14)

Wir haben beide Kameras ausprobiert und sind schließlich bei der PIXY CAM geblieben.
Obwohl die HHUSKYLENS die Hindernisse und Linien gut erkennen konnte, hat die PIXY CAM ein größeres Blickfeld und mehr kofiguratiosns Möglichkeiten in dem zugehörigem Programm. Dadurch können wir viel mehr abstimmen und Feintuning betreiben.

Für die Energeiversorgung, die wir uns schon zu Beginn zurechtgelegt haben, benutzen wir eine 11,5 Volt Lipo Batterie.
Die Batterie gibt zwischen 9,4 und 12,4 Volt aus. Da der Motor 12 Volt benötigt und der zugehörige Motortreiber gleichzeitig auch noch 1,4 Volt bezieht, haben wir einen Step Up Converter einegbaut, der die Spannung auf 13.4 Volt erhöht.
So erhält der Motor immer die richtige Spannung. Da die eine Hälfte des Stroms zu dem Motor geleitet wird, wird die andere Hälfte zu einem Step Down Converter geleitet. Dieser reduziert die Spannung auf 5 Volt. Das ist wichtig, weil der Arduino nicht mit dem 13,4 Volt umgehen kann.
Diese 5 Volt leiten wir anschließend in einen USB-Hub der gleichzeitig auch als Voltmeter dient.
Aus diesem USB-Hub geht eine Stromleitung dierekt zu dem Arduino und die andere zur Hauptstromleiste. Diese mussten wir installieren, weil 
die 5 Volt ausgabe des Arduinos nicht genau 5 Volt ausgibt. Sowohl der LCD Monitor als auch der Lenkservo benötigen nämlich mindestens 5 Volt.


![238084341-53173d58-f437-4e53-b33c-3225937c58c4](https://github.com/biswro2023/smartiecar/assets/131591590/da4db8a2-8d09-4db8-a71d-653b116fd0f1)


Nach dem ersten Wettbewerb in Chemitzt haben wir beschlossen die Halterung für die Kamera und die Ultraschallsensoren umzubauen.
Die alte Halterung hat sich schnell gelöst und verschoben. Nun ist die neu Halterung fest an den Rahmen des Autos befestigt.


![IMG_6399](https://github.com/biswro2023/smartiecar/assets/131177565/b6915354-6bd5-4f34-a280-85a809945a8f)


Außerde haben wir für die Ultraschallsensoren neue Halterungen verwendet, damit sie stabiler sitzten und einfacher zu montieren sind.
Durch diese neuen Halterungen der Sensoren, waren diese jedoch leicht nach oben geneigt, was manchmal zu fehlmessungen führte.
Deshalb haben wir Kabelbinder verwendet, um die Sensoren zusammen zu binden und unten zu halten.
Da der Farbsensor, den wir zuvor an unserem Auto befestigt hatten die Farben des Spielfeldes immer wieder falsch erkannte,
haben wir uns dafür entschieden diesen zu entfernen, da er so keien Nutzen für uns hat.

Zusätzlich haben wir versucht ein neues Getriebe in das Auto einzubauen (zuvor 1:1). Wir wollten eine größere Übersetzung der Zahnräder dazu verwenden
unser Auto langsam fahren zu lassen, ohne, dass es stecken bleibt. Den zuvor konnten wir dies nur verhindern, indem wir schneller fuhren,
was das ganze Rennen ungenauer machte.Schließlich hat aber das neue Getriebe mehr neue Probleme hervorgebracht als alte gelöst.


![IMG_5992](https://github.com/biswro2023/smartiecar/assets/131177565/e34ba7ce-fe0b-46ae-a5f0-6f5dfa4a5b01)


Während der vielen Testrunden die wir gefahren sind ist neben Sensoren und Arduinos auch unser Lenkserveo einmal kaputt gegangen.
Die Kontruktionsweise des Autos behinderte den Austausch etwas, jedoch haben wir die Gelegenheit genutz gleichzeitig auch noch Teile Auszutauschen, an
die man sonst nicht so leicht dran kommt.


![IMG_6400](https://github.com/biswro2023/smartiecar/assets/131177565/e23a8204-81a6-4e5f-acc2-7981690d5138)




