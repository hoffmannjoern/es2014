# Aufgabe 1.5

Zeigen Sie den analogen Wert von SLIDER3 auf der 7-Segment-Anzeige im
Intervall (0..1) an.

1. **Wie wurde die 7-Segementanzeige angesprochen?**
    Die Werte wurde mittels `shiftOut(serial, clock, byte_order, value)` in das
    Schieberegister geschrieben, an dessen 8 Ausgängen die LEDs der
    7-Segment-Anzeige angeschlossen sind. (7 Segemente + 1 Dezimalpunk)
2. **Wie wurden die analogen Werte konvertiert?**
    Die analogen Werte ([0,1023]) wurden einfach durch 102 geteilt und
    anschließend überprüft, dass der Wert zwischen 0 und 9 liegt.
