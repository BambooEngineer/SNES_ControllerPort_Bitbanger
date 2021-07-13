#define Latch 6
#define clk 7
#define Data 8

unsigned char b = 1; 
unsigned char y = 1; 
unsigned char select = 1; 
unsigned char start = 1; 
unsigned char up = 1; 
unsigned char down = 1; 
unsigned char left = 1; 
unsigned char right = 1; 
unsigned char a = 1; 
unsigned char x = 1; 
unsigned char l = 1; 
unsigned char r = 1; 

unsigned char Buttons[] = {b, y, select, start, up, down, left, right, a, x, l, r, 1, 1, 1, 1}; // SNES clocks 16 pulses, for some reason there are 4 on the end even though theres only 12 buttons



boolean chigh= false; 
boolean push = true;




void setup() {
  pinMode(Latch, INPUT); // latch 6
  pinMode(clk, INPUT); // clock 7
  pinMode(Data, OUTPUT); // data 8
  pinMode(10, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);

  //Serial.begin(9600);

}

int inc = 0;

void bitbangData(){ 
   
  while(true){ 
    // after latch goes low the first button should be present, then the clock's rising edge should increment the button array 

    // Instead of looking for the clocks rising edge to increment like before, the data timing is matched using the _delay_us() function 
    
    //!(PIND &(0b10000000))    clk LOW
    //PIND &(0b10000000)       clk HIGH
    
    PORTB |= Buttons[inc];
    PORTB &= ~(!(Buttons[inc])); // Changes the pin value depending on the array variable value 
    _delay_us(9); // Timing seems alot better 
    inc++; // DOWN is still static but the rest of the buttons seem fine 
    if(inc >= 16){  
       inc = 0; 
       break; 
     }
    
   
    /*
    if(!(PIND &(0b10000000))){ // when clk is low chigh is true 
     
    chigh = true; // chigh is used to detect a rising edge
    
    }
    else{
      PORTB |= 1;
    }*/
    
   /* if((PIND &(0b10000000)) && chigh){ // Data pulses seem to be lagging on the scope 

     
     inc++;
    
     
     if(inc >= 16){  
       inc = 0; 
       chigh = false;
       break; 
     }
     
     chigh = false; 
     
      
    }*/

  }
}
                  // TRY DIFFERENT PIN FOR X & TEST
void BData(){
  for(int i=0; i<16;i++){
        Buttons[i] = 1;
      }
      
      if(!(PINB &(0b000100))){ // digital pin 10
        Buttons[3] = 0; // start 
       // Serial.println("start");
      }
      if(!(PIND &(0b00000100))){ // digital pin 2
        Buttons[6] = 0; // left
        //Serial.println("left");
      }
      
      if(!(PIND &(0b00001000))){ // digital pin 3 
        Buttons[4] = 0; // up
       // Serial.println("up");
      }
      
      if(!(PIND &(0b00010000))){ // digital pin 4 
        Buttons[7] = 0; // right
       // Serial.println("right");
      }
     
      if(!(PIND &(0b00100000))){ // digital pin 5
        Buttons[5] = 0; // down
        //Serial.println("down");
      }
      if(!(PINB &(0b000010))){ // digital pin 9
        Buttons[8] = 0; // a 
       // Serial.println("a");
      }
      if(!(PINB &(0b001000))){ // digital pin 11 
        Buttons[0] = 0; // b 
       // Serial.println("b");
      }
      if(!(PINB &(0b010000))){ // digital pin 12
        Buttons[1] = 0; // y 
       // Serial.println("y");
      }
      if(!(PINC &(0b000001))){ // Analog pin A0, ( digital pin 13 caused ghosting )   
        Buttons[9] = 0; // x
        // Serial.println("x");
      }
}



void loop() {
   
 
 
  //////////////////////////////////////////////////
  
  if(PIND &(0b01000000)){ // if Latch is high just read button pins
    while(true){
      
      
      BData(); // check buttons
      
      ///////////////////
      
      if(!(PIND &(0b01000000))){ // if Latch goes LOW
        bitbangData(); 
        break; // break loop to wait for next latch when finished
      }
    }
  }
  
  
  
}