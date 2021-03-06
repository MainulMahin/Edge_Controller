// Pin Number and Variabe decaration for Input
const int rls = 0;                          // Right Limit Switch
const int cls = 1;                          // Center Switch
const int lls = 2;                          // Left Limit Switch
const int enable = 3;                       // Enable Signal from Main PLC 
const int photocell = 4;                    // Photocell input from Edge Dtector
const int mode_change = 5;                  // Mode Change Input From Auto Manual Switch
const int manual_left = 6;                  // Push Button Switch for run the Motor Left Direction 
const int manual_right = 7;                 // Push Button Switch for run the Motor Left Direction 
// Pin Number and Variabe decaration for OutPut
const int drive_enable_relay = 8;           //Drive Enable relay to enable the Motor Drive
const int motor_left = 9;                   //Output Signal to H-Bridge to Run Motor in Left Direction
const int motor_right = 10;                 //Output Signal to H-Bridge to Run Motor in Right Direction
const int right_limit_indicator = 11;       //Right Side Limit Switch to Stop the Motor 
const int left_limit_indicator = 12;        //Left Side Limit Switch to Stop the Motor

// variable for reading the Input status of Input Switch, Initially all the variable are set to Zero
int rls_state = 0;              
int cls_state = 0;                
int lls_state = 0;               
int enable_state = 0;
int photocell_state = 0;
int mode_change_state = 0;
int manual_left_state = 0;
int manual_right_state = 0;


void setup() {
  // Declaration the port as Input
  pinMode(rls, INPUT);
  pinMode(cls, INPUT);
  pinMode(lls, INPUT);
  pinMode(enable, INPUT);
  pinMode(photocell, INPUT);
  pinMode(mode_change, INPUT);
  pinMode(manual_left, INPUT);
  pinMode(manual_right, INPUT);
  // Declaration the port as Output
  pinMode(drive_enable_relay, OUTPUT);
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);
  pinMode(left_limit_indicator, OUTPUT);
  pinMode(right_limit_indicator, OUTPUT);
}

void loop() {
  //Read the enable signal from PLC, if Enable signal is High it goes to Anable active function, or It will dancine Indicator!
  enable_state = digitalRead(enable);
  if(enable_state == HIGH){
    digitalWrite(drive_enable_relay, HIGH);
    enable_mode_active();
    }
  if(enable_state == LOW){
    digitalWrite(drive_enable_relay, LOW);
    blink_indicator_seq();
    }
}

  // It will check the mode of function, and decide to go automatic or Manual,
void enable_mode_active(){
  mode_change_state = digitalRead(mode_change);
    if(mode_change_state == HIGH){
       automatic_mode();
    }
     if(mode_change_state == LOW){
       manual_mode();
    }
  }
    // Flashing the indicator to show that the controller is not active yet or there is no signal from PLC.
void  blink_indicator_seq(){
  digitalWrite(right_limit_indicator, HIGH);
  digitalWrite(left_limit_indicator, HIGH);
  delay(500);
  digitalWrite(right_limit_indicator, LOW);
  digitalWrite(left_limit_indicator, LOW);
  delay(500);
  }

  
void manual_mode(){
  manual_left_state = digitalRead(manual_left);
  manual_right_state = digitalRead(manual_right);
  lls_state = digitalRead(lls);
  rls_state = digitalRead(rls);
  
  // For the left Manual Pushbutton
  if((manual_left_state == HIGH)&&(lls_state == HIGH)){
      digitalWrite(motor_left, HIGH);
      }else{
        digitalWrite(motor_left, LOW);
        }
  if(lls_state == LOW){
     digitalWrite(left_limit_indicator, HIGH);
    }else{
      digitalWrite(left_limit_indicator, LOW);
      }
      
  // For the Right Manual Pushbutton
  if((manual_right_state == HIGH)&&(rls_state == HIGH)){
      digitalWrite(motor_right, HIGH);
      }else{
        digitalWrite(motor_right, LOW);
        }
  if(rls_state == LOW){
     digitalWrite(right_limit_indicator, HIGH);
    }else{
      digitalWrite(right_limit_indicator, LOW);
      }
  }
  
  void automatic_mode(){
  photocell_state = digitalRead(photocell);
  lls_state = digitalRead(lls);
  rls_state = digitalRead(rls);

  // Photocell state high and move the motor left direction
  if((photocell_state == HIGH)&&(lls_state == HIGH)){
      digitalWrite(motor_left, HIGH);
      }else{
        digitalWrite(motor_left, LOW);
        }
  if(lls_state == LOW){
     digitalWrite(left_limit_indicator, HIGH);
    }else{
      digitalWrite(left_limit_indicator, LOW);
      }
      
    // Photocell state Low and move the motor Right direction 
  if((photocell_state == LOW)&&(rls_state == HIGH)){
      digitalWrite(motor_right, HIGH);
      }else{
        digitalWrite(motor_right, LOW);
        }
  if(rls_state == LOW){
     digitalWrite(right_limit_indicator, HIGH);
    }else{
      digitalWrite(right_limit_indicator, LOW);
      }    
    }
