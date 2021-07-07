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
  pinMode(13, INPUT_PULLUP);

}

int inc = 0;

void bitbangData(){ 
  
  PORTB |= Buttons[inc]<<0; // first button on data line after latch
  PORTB &= ~(!(Buttons[inc])<<0); // Changes the pin value depending on the array variable value 

  
  while(true){ 
    // after latch goes low the first button should be present, then the clock's rising edge should increment the button array 

    
     
     PORTB |= Buttons[inc]<<0; //pull data high if button is not pressed  ---    Array bitbangers
     PORTB &= ~(!(Buttons[inc])<<0); // pull data low if it is pressed
    
    //!(PIND &(0b10000000))    clk LOW
    //PIND &(0b10000000)       clk HIGH

   

    if(!(PIND &(0b10000000))){ // when clk is low chigh is true 
      
    
    chigh = true; // chigh is used to detect a rising edge
    
    }
    
    if((PIND &(0b10000000)) && chigh){ // Data pulses seem to be lagging on the scope 
     
     inc++;
     
    
     
     
     if(inc >= 16){  
       inc = 0; 
       chigh = false;
       break; 
     }
     
     chigh = false; 
     
      
    }

  }
}

void BData(){
  for(int i=0; i<16;i++){
        Buttons[i] = 1;
      }
      
      if(!(PINB &(0b000100))){ // digital pin 10
        Buttons[3] = 0; // start 
      }
      if(!(PIND &(0b00000100))){ // digital pin 2
        Buttons[6] = 0; // left
      }
      
      if(!(PIND &(0b00001000))){ // digital pin 3 
        Buttons[4] = 0; // up
      }
      
      if(!(PIND &(0b00010000))){ // digital pin 4 
        Buttons[7] = 0; // right
      }
     
      if(!(PIND &(0b00100000))){ // digital pin 5
        Buttons[5] = 0; // down
      }
      if(!(PINB &(0b000010))){ // digital pin 9
        Buttons[8] = 0; // a 
      }
      if(!(PINB &(0b001000))){ // digital pin 11
        Buttons[0] = 0; // b 
      }
      if(!(PINB &(0b010000))){ // digital pin 12
        Buttons[1] = 0; // y 
      }
      if(!(PINB &(0b100000))){ // digital pin 13
        Buttons[9] = 0; // x
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
        break; // break loop to wait for next latch when done parsing
      }
    }
  }
  
  
  
}
