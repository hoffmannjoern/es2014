# Praktikum 3
## Aufgabe 1
__Aufgabenstellung:__ Erläutern Sie das Konzept des Interrupt Betriebs. Gehen Sie bei Ihrer Erklärung auf die folgende Konzepte ein: Interrupt, Interrupt-Anforderung, Interrupt-Maskierung, Interrupt- Priorität, Interrupt-Tabelle, Interrupt-Vektor, Interrupt-Service-Routine, Interrupt-Kontext (Sichern / Wiederherstellen)

- __Interruptbetrieb:__
    TO-DO

- __Interrupt-Anforderung__
    Als `Interrupt-Anforderung` (engl. `Interrupt-Request`, `IRQ`)  wird jenes Ereignis bezeichnet, welches eine vorübergehende Unterbrechung des laufenden Prozesses anfordert. Nach einer erfolgten Unterbrechung wird die `Unterbrechungsroutine` (engl. `Interrupt-Service-Routine`, `ISR`) ausgeführt. Im Anschluss wird der unterbrochene Aufgabe forgesetzt. `Interrupt-Anforderungen` können maskiert (ignoriert) werden.

- __Interrupt-Maskierung__
    Da Interrupts asynchron angefordert werden,  muss es eine Möglichkeit geben eine Unterbrechung zu deaktivieren. Diese Möglichkeit wird durch die `Interrupt-Maskierung` gegeben. Während die selektive Maskierung die Unterbrechung durch eine speziellen `IRQ` verhindert, verhindert eine generelle Maskierung die Unterbrechung durch alle maskierbaren Interrupts. Nicht-maskierbar ist u.a. der RESET-Interrupt.

    Quelle: [Struktur von Mikrorechnern](https://www.uni-due.de/~hl271st/Lehre/SMR/smr_uebung_kapitel5.pdf), Stand: 22.01.2015

- __Interrupt-Priorität__
    Als `Interrupt-Priorität` bezeichnet man die Priorität mit der ein Interrupt angefordert wird. Sollte ein niederpriorer `IRQ` den Aufruf einer `ISR` gestartet haben, so würde der Aufruf eines höherprioren `IRQ` diese `ISR` unterbrechen.

    _Maskiert der `ATmega328` möglichweise alle Interrupts, wenn er in der `ISR` ist?_

    Quelle: [I/O Grundlagen](http://www.bjoern-koester.de/iogrundlagen/), Stand: 22.01.2015


- __Interrupt-Tabelle__
    Die `Interrupt-Tabelle` ist eine Liste aller `Interrupt-Vektoren` inklusive der  zugehörigen Sprungadressen. Die Reihenfolge spiegelt die `Interrupt-Prioriät` der Interrupts wieder.
    [Abbildung von Interrupt-Vector-Table für ATmega328 & ATmega328P ](http://narwhaledu.com/AVRwiki/index.php?title=Interrupt_Vectors_in_ATmega328_and_ATmega328P)

    Quelle: [Wikipedia: Interrupt-Vektor](http://de.wikipedia.org/wiki/Interruptvektor), Stand: 22.01.2015

- __Interrupt-Vektor__
    Als `Interrupt-Vektor` bezeichnet man die Adresse, zu der bei einem `IRQ` gesprungen wird.  Diese Adresse kennzeichnet die Position jener `ISR`, die auf den `IRQ` antwortet. Jede Interrupt-Quelle hat genau einen `Interrupt-Vektor`, um die jeweils spezifische `ISR` referenzieren zu können.

    Quelle: [Wikipedia: Interrupt-Vektor](http://de.wikipedia.org/wiki/Interruptvektor), Stand: 22.01.2015

- __Interrupt-Service-Routine__
    Die `Interrupt-Service-Routine` (kurz `ISR`) ist ein Abfolge von Befehlen, die bei erfolgreichem `IRQ` zur Ausführung in der CPU erzwungen wird. Der Stand des durch den `IRQ ` unterbrochenen Programms wird vor der Unterbrechung gespeichert und im Anschluss weitergeführt.

    Quelle: [Wikipedia: Interrupt-Vektor](http://de.wikipedia.org/wiki/Interruptvektor), Stand: 22.01.2015

- __Interrupt-Kontext (Sichern / Wiederherstellen)__
    TO-DO

##Lesenswert:
* [Artikel zu Interrupts: _We interrupt this program to bring you a tutorial on… Arduino interrupts_](http://www.engblaze.com/we-interrupt-this-program-to-bring-you-a-tutorial-on-arduino-interrupts/dg)
* [Interrupts und die zugehörigen Register](http://www.mikrocontroller.net/articles/AVR-Tutorial:_Interrupts#INT0.2C_INT1_und_die_zugeh.C3.B6rigen_Register)
