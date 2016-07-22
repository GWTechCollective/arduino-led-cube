#define MAX_UINT 65535 // This is the maximum value of an unsigned integer
#define DELAY_CONST 200 // This gives ~ a 0.5s delay
#define NUM_LEDS 9 // This is how many LEDs there are in a layer
#define NUM_PINS 12 // This is how many pins are used in total
#define NUM_LAYERS 3 // This the the edge dimension of the cube 

char layer = 0; // This tracks which layer is currently on, the bottom is layer 0
char patternIndex = 0; // This tracks which step of the pattern the Arduino is on
int fastCount = 0; // This counts with each cycle to act as a timer

// Paste the pattern array below

const char arrayLength = 6*3;
const char patternArray[6*3][9] = {

    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
   
    {1, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
   
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 1},
    
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1}
};

// Paste the pattern array above

void setup() {
    
    // Set the Arduinos pins to output mode
    for(int led=0; led < NUM_PINS; led++)
        pinMode(led, OUTPUT); 
        
}

void loop() {    
    
    // Select the current layer (SELECT input for multiplexing)
    select_layer(layer);
    
    // Write the pattern for the current layer to the pins (DATA input for multiplexing)
    for(int led=0; led<NUM_LEDS; led++)  // Write the logic for each led to the pins of the Arduino
        digitalWrite(led, patternArray[patternIndex+layer][led]);
    
    // Increment values to step through the layers, reset if at the last layer
    layer++;
    if(layer > NUM_LAYERS-1) layer = 0;
    
    // Increment timer to determine when to change to the next step in the pattern
    fastCount++;
    if(fastCount == DELAY_CONST) {
        fastCount = 0;
        patternIndex += NUM_LAYERS; // increment to the next set of values for the cube in the pattern
        if(patternIndex > arrayLength-NUM_LAYERS) patternIndex = 0; // return to the beginning of pattern when it gets to the end
        
    }  
   
    // just because, certain patterns break without this
   delay(1);
    
}    
    
void select_layer(int layer) {

    switch(layer) {
        
        case 0:
            digitalWrite(9, HIGH);
            digitalWrite(10, LOW);
            digitalWrite(11, LOW);
            break;
            
        case 1:
            digitalWrite(9, LOW);
            digitalWrite(10, HIGH);
            digitalWrite(11, LOW);
            break;
            
        case 2:
            digitalWrite(9, LOW);
            digitalWrite(10, LOW);
            digitalWrite(11, HIGH);
            break;
            
        default:
            break;

    }
}
