# Aufgaben 7 bis 9

## Aufgabe 7
Der Zeiger ist mit dem `volatile`-Qualifizierer versehen, um sicherzustellen,
dass immer auf den eigentlichen Wert zugegriffen wird und keine Optimierungen
angewendet werden.

## Aufgabe 8
Ein `PORT` ist eine Zusammenfassung von i.A. 8 Bits zu einem Byte, damit ein
Zugriff über den Speicher möglich ist (die kleinstmögliche addressierbare
Einheit beim Speicherzugriff ist ein Byte).

## Aufgabe 9
Es gibt das `DDR#`-Register (zB: `DDR2`) zur Festlegung vom Eingabe oder
Ausgabe, `PORT#` zum Festlegen der Werte und `PIN#` zum Auslesen der anliegende
Werte an den Pins. Bei neueren `XMEGA` sind diese Register (und weitere wie
Kontrollregister) zu einem `struct` zusammengefasst.
