# grais-fidgetboard
silly board with 3 keys and 3 5mm LEDs to fidget with where buttons correspond to the LEDs in order from left to right  
the firmware will definitely chain after assembly - expect revisions!  
![3d model of Grais, made in kicad 9](https://github.com/solswiss/grais-fidgetboard/blob/main/assets/pcb-3d.png)
<sup><sub>🔊🎭📜can you figure out what the inscriptions mean?</sub><sup>

## modes
upon setup, the LEDs will flash from left to right and then all at once. that is code for the user to choose a mode.

### default
select by pressing the left button when prompted
the buttons light up the matching LED while pressed

### memory game
select by pressing the middle button when prompted
remember an ever-growing pattern of LEDs!  
1. a random LED will be chosen and added to a pattern
2. the pattern will be displayed with a brief pause between to let the individual LED light up then turn off
3. player should press the corresponding buttons, matching the pattern displayed
when the player messes up, the game will stop and the score will be displayed in the form of individual digits; 025 would be 2 blinks of the middle LED and 5 blinks of the rightmost LED
theoretically the game can last as long as power is supplied and/or the score remains below 1000!  
