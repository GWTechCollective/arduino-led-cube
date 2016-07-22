#define NUM_LEDS 9
#define NUM_PINS 12
#define NUM_LAYERS 3
#define DELAY 10

char layer = 0;
int patternIndex = 0;
int value = 0;
unsigned long milliCount = 0;

const char layer_mask[] = {0x02, 0x04, 0x08};  

// Paste the pattern array below

const char patternLength = 11*3;
const int patternArray[] = {

  0x0007,
  0x0007,
  0x0007,
  
  0x0038,
  0x0038,
  0x0038,
  
  0x01C0,
  0x01C0,
  0x01C0,
  
  0x0089,
  0x0089,
  0x0089,
  
  0x0128,
  0x0128,
  0x0128,
  
  0x1C00,
  0x1C00,
  0x1C00,
  
  0x0038,
  0x0038,
  0x0038,
  
  0x0007,
  0x0007,
  0x0007,
  
  0x0124,
  0x0124,
  0x0124,
  
  0x0092,
  0x0092,
  0x0092,
  
  0x0049,
  0x0049,
  0x0049
  /*
  0x0000,
  0x0000,
  0x0000,
  
  0x0001,
  0x0000,
  0x0000,

  0x001B,
  0x001B,
  0x0000,

  0xFFFF,
  0xFFFF,
  0xFFFF,

  0x0000,
  0x01B0,
  0x01B0,

  0x0000,
  0x0000,
  0x0100,

  0x0000,
  0x0000,
  0x0000 */
};

// Paste the pattern array above

void setup() {
    // set all digital pins to output
    DDRD = 0xFF;
    DDRB = 0xFF;

    // Configure timer interrupt
    cli();
    
    TCNT1 = 0;
    TCCR1A = 0x00;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = seconds_to_timer(1.0);
      
    sei();
        
}

// Update pattern index
ISR(TIMER1_COMPA_vect) {
  patternIndex += NUM_LAYERS;
  if (patternIndex > patternLength - NUM_LAYERS) patternIndex = 0;
}

int seconds_to_timer(float seconds) {
  return int(15625 * seconds - 1);
}

void loop() {    

    //delay(10);
    layer++;
    if(layer > NUM_LAYERS-1) layer = 0;

    PORTD = 0x00;
    PORTB = 0x00;

    // Select Layer
    PORTB |= layer_mask[layer];

    // Write pattern
    value = 0x01FF & patternArray[patternIndex + layer];
    PORTD |= (value & 0xFF);
    PORTB |= (value >> 8);
    
}    
