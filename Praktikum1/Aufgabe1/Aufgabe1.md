#Aufgabenblatt 1
##Aufgabe1
###Lassen Sie LED1 dauerhaft leuchten
1. **Wie ist ein Arduino-Sketch Programm aufgebaut?**
    * `setup()`
> The `setup()` function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc. The setup function will only run once, after each powerup or reset of the Arduino board.
After creating a `setup()` function, the `loop()` function does precisely what its name suggests, and loops consecutively, allowing your program to change and respond as it runs. Code in the `loop()` section of your sketch is used to actively control the Arduino board.
    * `loop()`
> The code below won't actually do anything, but it's structure is useful for copying and pasting to get you started on any sketch of your own. It also shows you how to make comments in your code.
Any line that starts with two slashes (//) will not be read by the compiler, so you can write anything you want after it. Commenting your code like this can be particularly helpful in explaining, both to yourself and others, how your program functions step by step.

Quelle: [http://arduino.cc/en/Tutorial/BareMinimum](http://arduino.cc/en/Tutorial/BareMinimum)

2. **Wie wurde die Ausgabe realisiert**


###Benutzt
* LED1 -> D6
