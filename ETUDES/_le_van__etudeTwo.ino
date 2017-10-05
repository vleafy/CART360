/**********************ETUDE 2 CART 360 2017*******************************
 * WELCOME!
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK.
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE,
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)
 * 
 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];
int mode = 0; // start at off

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  Serial.begin(9600);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS:
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable
 * 
 **************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0.
 * (i.e. if mode ==2 and we press, then mode ==3) ...
 **************************************************************************/
void chooseMode() {
  //if mode is reset and button is pressed switch to live mode 
  if ((digitalRead(BUTTON_MODE_PIN) == HIGH) && (mode == 0))
  {
    mode = 1;
  }
  //if mode is live and button is pressed switch to record mode 
  else if ((digitalRead(BUTTON_MODE_PIN) == HIGH) && (mode == 1))
  {
    mode = 2;
  }
  //if mode is record and button is pressed switch to play mode 
  else if ((digitalRead(BUTTON_MODE_PIN) == HIGH) && (mode == 2))
  {
    mode = 3;
  }
  //if mode is play and button is pressed switch to loopMode 
  else if ((digitalRead(BUTTON_MODE_PIN) == HIGH) && (mode == 3))
  {
    mode = 4;
  }
  //if mode is loopMode and button is pressed switch to reset mode 
  else if ((digitalRead(BUTTON_MODE_PIN) == HIGH) && (mode == 4))
  {
    mode = 0;
  }
  //delay so that button isn't read too fast
  delay(duration);
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
 **************************************************************************/
void setRGB()
{
  if (mode == 0)
  {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, LOW);
  }
  else if (mode == 1)
  {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, HIGH);
  }
  else if (mode == 2)
  {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, LOW);
  }
  else if (mode == 3)
  {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, HIGH);
    digitalWrite(LED_PIN_B, LOW);
  }
  else if (mode == 4)
  {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, HIGH);
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS:
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes
 * to the user pressing the respective buttons.
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded,
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)
 * 
 ******************************************************************************/
void selectMode()
{
  if (mode == 0) {
    reset();
  }
  else if (mode == 1) {
    live();
  }
  else if (mode == 2) {
    record();
  }

  else if (mode == 3) {
    play();
  }

  else if (mode == 4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
 **************************************************************************/
void reset()
{
  countNotes = 0; // resets countNotes to zero and clears array

}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
 **************************************************************************/
void live()
{
  //if note buttons are pressed...
  if (analogRead(NOTE_IN_PIN) > 0)
  {
    //...speaker plays the varying analog values recieved from the buttons
    tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration); 
  }
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
 **************************************************************************/
void record()
{
  //if note buttons are pressed...
  if (analogRead(NOTE_IN_PIN) > 0)
  {
    //...and number of notes pressed so far is less than 16...
    if (countNotes < 16) {
      //...analog values of notes pressed will be stored in array... 
      notes[countNotes] = analogRead(NOTE_IN_PIN);
      //...at every increment of 1 up until 16
      countNotes = countNotes + 1;
      //analog values are sent to buzzer to play corresponding sound
      tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration); //IMPLEMENT
      //print ln to check if buttons are working
      Serial.println(countNotes);
    }
    //delay so that buttons aren't read too fast
    delay(duration);
  }
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
 **************************************************************************/
void play()
{
  //replay recorded notes calling array values in 
  //each position increasing at increments of 1
  //send values at each position to buzzer
  for (int i=0; i < 16; i++){
    tone(BUZZER_PIN,notes[i], duration);
    delay(duration);

  } 
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
 **************************************************************************/
void loopMode()
{
  //replay recorded notes calling array values at every third increment (3,6,9,12,15)
  for (int i=0; i < 16; i=i+3){
    tone(BUZZER_PIN,notes[i], duration);
    //delay for 400 miliseconds at increment 9
    if (i==9){
    delay(duration*2);
    } else{
    delay(duration);
    }
  } 

}

/**************************************************************************/






