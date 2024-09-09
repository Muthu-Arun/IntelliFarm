
#include<math.h>
#include<iostream>
#include<chrono>

/******************************************************************
 * Network Configuration - customized per network 
 ******************************************************************/
#define m1p1 6
#define m1p2 7
#define m2p1 8
#define m2p2 9
#define pwm1 12
#define pwm2 13
#define trigPin 5 // D2 connect all trig pins to D2
#define echoPin_left 10 //d7
#define echoPin_center 11 //d8
#define echoPin_right 12 //d9
// long duration_left,duration_right,duration_center;
// int distance_left,distance_center,distance_right;
const int PatternCount = 8;
const int InputNodes = 3;
const int HiddenNodes = 5;
const int OutputNodes = 2;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0004;

const float Input[PatternCount][InputNodes] = {
  {0.99,0.99,0.99},//senor all clear                           1
  {0.99,0.50,0.99},// only in front                             2
  {0.20,0.99,0.20},// all clear in front but side restricted     3
  {0.40,0.50,0.20},                                             //4  
  {0.30,0.50,0.40},                                           //  5
  {0.60,0.50,0.20},
  {0.20,0.50,0.60},
  {0.60,0.15,1.60}
};


const float Target[PatternCount][OutputNodes] = {
  {0.99,0.99 }, // Output for motors 
  {0.99,0.99 },
  {0.75,0.75},
  {0.2,0.2},
  {0.2,0.2},
  {0.3,0.7},
  {0.7,0.3},
  {0.2,0.2}

};

/******************************************************************
 * End Network Configuration
 ******************************************************************/
int distance_1 , distance_2 , distance_3;
long duration_1,duration_2,duration_3;
float test_output[3] = {0.0,0.0,0.0};
int i, j, p, q, r;
int ReportEvery1000;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando= 0;
float Error= 0;
float Accum =0;


float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];
float OutputWeights[HiddenNodes+1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes+1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes+1][OutputNodes];
void train();
void drive_vehicle();
void drive_nn();
void get_input();
void run_sim();

int random(int max) {
    // Seed the random number generator with the current time
    
    
    // Generate a random number between 0 and max (inclusive)
    return std::rand() % (max);
}
int constrain(int distance,int ul,int ll){

}
void setup(){
  
  // randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for( p = 0 ; p < PatternCount ; p++ ) {    
    RandomizedIndex[p] = p ;
  }
     train();// Train druing every startup
}  
void toTerminal()
{

  for( p = 0 ; p < PatternCount ; p++ ) { 
    // Serial.println(); 
    // Serial.print ("  Training Pattern: ");
    // Serial.println (p);      
    // Serial.print ("  Input ");
    std::cout<<"training pattern  "<< p <<"\n";

    for( i = 0 ; i < InputNodes ; i++ ) {
      // Serial.print (Input[p][i], DEC);
      // Serial.print (" ");
      std::cout<< Input[p][i]<<" ";
    }
    // Serial.print ("  Target ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      // Serial.print (Target[p][i], DEC);
      // Serial.print (" ");
      std::cout<<Target[p][i]<<" ";
    }
    
/******************************************************************
* Compute hidden layer activations
******************************************************************/

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
    }
    // Serial.print ("  Output ");
    std::cout<<"Output\n";
    for( i = 0 ; i < OutputNodes ; i++ ) {  
      printf("%.5f ",Output[i]);     
      // Serial.print (Output[i], 5);
      // Serial.print (" ");
      // std::cout<<Output[i]
    }
  }


}
void train() {
  /******************************************************************
    Initialize HiddenWeights and ChangeHiddenWeights
  ******************************************************************/
  // prog_start = 0;
  //  digitalWrite(LEDYEL, LOW);
  for ( i = 0 ; i < HiddenNodes ; i++ ) {
    for ( j = 0 ; j <= InputNodes ; j++ ) {
      ChangeHiddenWeights[j][i] = 0.0 ;
      Rando = float(random(100)) / 100;
      HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
  //  digitalWrite(LEDYEL, HIGH);
  /******************************************************************
    Initialize OutputWeights and ChangeOutputWeights
  ******************************************************************/
  //  digitalWrite(LEDRED, LOW);
  for ( i = 0 ; i < OutputNodes ; i ++ ) {
    for ( j = 0 ; j <= HiddenNodes ; j++ ) {
      ChangeOutputWeights[j][i] = 0.0 ;
      Rando = float(random(100)) / 100;
      OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
  //  digitalWrite(LEDRED, HIGH);
  //SerialUSB.println("Initial/Untrained Outputs: ");
  //toTerminal();
  /******************************************************************
    Begin training
  ******************************************************************/

  for ( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++) {

    /******************************************************************
      Randomize order of training patterns
    ******************************************************************/

    for ( p = 0 ; p < PatternCount ; p++) {
      q = random(PatternCount);
      r = RandomizedIndex[p] ;
      RandomizedIndex[p] = RandomizedIndex[q] ;
      RandomizedIndex[q] = r ;
    }
    Error = 0.0 ;
    /******************************************************************
      Cycle through each training pattern in the randomized order
    ******************************************************************/
    for ( q = 0 ; q < PatternCount ; q++ ) {
      p = RandomizedIndex[q];

      /******************************************************************
        Compute hidden layer activations
      ******************************************************************/
      //  digitalWrite(LEDYEL, LOW);
      for ( i = 0 ; i < HiddenNodes ; i++ ) {
        Accum = HiddenWeights[InputNodes][i] ;
        for ( j = 0 ; j < InputNodes ; j++ ) {
          Accum += Input[p][j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0 / (1.0 + exp(-Accum)) ;
      }
      //  digitalWrite(LEDYEL, HIGH);

      /******************************************************************
        Compute output layer activations and calculate errors
      ******************************************************************/
      //  digitalWrite(LEDRED, LOW);
      for ( i = 0 ; i < OutputNodes ; i++ ) {
        Accum = OutputWeights[HiddenNodes][i] ;
        for ( j = 0 ; j < HiddenNodes ; j++ ) {
          Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0 / (1.0 + exp(-Accum)) ;
        OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;
        Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;
      }
      //SerialUSB.println(Output[0]*100);
      //  digitalWrite(LEDRED, HIGH);
      /******************************************************************
        Backpropagate errors to hidden layer
      ******************************************************************/
      //  digitalWrite(LEDYEL, LOW);
      for ( i = 0 ; i < HiddenNodes ; i++ ) {
        Accum = 0.0 ;
        for ( j = 0 ; j < OutputNodes ; j++ ) {
          Accum += OutputWeights[i][j] * OutputDelta[j] ;
        }
        HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
      }
      //  digitalWrite(LEDYEL, HIGH);

      /******************************************************************
        Update Inner-->Hidden Weights
      ******************************************************************/

      //  digitalWrite(LEDRED, LOW);
      for ( i = 0 ; i < HiddenNodes ; i++ ) {
        ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i] ;
        HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i] ;
        for ( j = 0 ; j < InputNodes ; j++ ) {
          ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
          HiddenWeights[j][i] += ChangeHiddenWeights[j][i] ;
        }
      }
      //  digitalWrite(LEDRED, HIGH);
      /******************************************************************
        Update Hidden-->Output Weights
      ******************************************************************/
      //  digitalWrite(LEDYEL, LOW);
      for ( i = 0 ; i < OutputNodes ; i ++ ) {
        ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i] ;
        OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i] ;
        for ( j = 0 ; j < HiddenNodes ; j++ ) {
          ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i] ;
          OutputWeights[j][i] += ChangeOutputWeights[j][i] ;
        }
      }
      //  digitalWrite(LEDYEL, HIGH);
    }

    /******************************************************************
      Every 100 cycles send data to terminal for display and draws the graph on OLED
    ******************************************************************/
    ReportEvery1000 = ReportEvery1000 - 1;
    if (ReportEvery1000 == 0)
    {
      int graphNum = TrainingCycle / 100;
      int graphE1 = Error * 1000;
      // int graphE = map(graphE1, 3, 80, 47, 0);
      // ErrorGraph[graphNum] = graphE;
      // u8g2.firstPage();
      // do {
      //   drawGraph();
      // } while ( u8g2.nextPage() );

      // SerialUSB.println();
      // SerialUSB.println();
      // SerialUSB.print ("TrainingCycle: ");
      // SerialUSB.print (TrainingCycle);
      // SerialUSB.print ("  Error = ");
      // SerialUSB.println (Error, 5);
      // SerialUSB.print ("  Graph Num: ");
      // SerialUSB.print (graphNum);
      // SerialUSB.print ("  Graph Error1 = ");
      // SerialUSB.print (graphE1);
      // SerialUSB.print ("  Graph Error = ");
      // SerialUSB.println (graphE);

      toTerminal();

      if (TrainingCycle == 1)
      {
        ReportEvery1000 = 99;
      }
      else
      {
        ReportEvery1000 = 100;
      }
    }


    /******************************************************************
      If error rate is less than pre-determined threshold then end
    ******************************************************************/

    if ( Error < Success ) break ;
  }
}
void get_input(){
    //  digitalWrite(trigPin, LOW);
    //  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
    //  digitalWrite(trigPin, HIGH);
    //  delayMicroseconds(10);
    //  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
    // duration_1 = pulseIn(echoPin_left, HIGH);
    // duration_2 = pulseIn(echoPin_right, HIGH);
    // duration_3 = pulseIn(echoPin_center, HIGH);
    // distance_1 = duration_1 * 0.034 / 2;
    // distance_2 = duration_2 * 0.034 / 2;
    // distance_3 = duration_3 * 0.034 / 2;
    // if(distance_1 >= 100)
    //   distance_1 = 100;

    // if(distance_2 >= 100)
    //   distance_2 = 100;
    
    // if(distance_3 >= 100)
    //   distance_3 = 100;
    

  // Prints the distance on the // Serial Monitor
    // // Serial.print("Distance: ");
    // // Serial.println(distance_1);
    // // Serial.println(distance_2);
    // // Serial.println(distance_3);
}
void real(){
  get_input();
  drive_nn();
  drive_vehicle();
}
void simulate(){
  run_sim();
  drive_nn();
  drive_vehicle();
  // delay(2000);
}
void loop(){
  // simulate();
  real();
}
void run_sim(){
  distance_1 = random(100);
  distance_2 = random(100);
  distance_3 = random(100);
}
void drive_nn(){
  distance_1 = constrain(distance_1, 0, 100);
  distance_2 = constrain(distance_2, 0, 100);
  distance_3 = constrain(distance_3, 0, 100);

  test_output[0] = float(distance_1) / 100;
  test_output[1] = float(distance_2) / 100;
  test_output[2] = float(distance_3) / 100;

  // Serial.println(distance_1);
  // Serial.println(distance_2);
  // Serial.println(distance_3);
  
    for ( i = 0 ; i < HiddenNodes ; i++ ) {
    Accum = HiddenWeights[InputNodes][i] ;
    for ( j = 0 ; j < InputNodes ; j++ ) {
      Accum += test_output[j] * HiddenWeights[j][i] ;
    }
    Hidden[i] = 1.0 / (1.0 + exp(-Accum)) ;
  }

  /******************************************************************
    Compute output layer activations and calculate errors
  ******************************************************************/

  for ( i = 0 ; i < OutputNodes ; i++ ) {
    Accum = OutputWeights[HiddenNodes][i] ;
    for ( j = 0 ; j < HiddenNodes ; j++ ) {
      Accum += Hidden[j] * OutputWeights[j][i] ;
    }
    Output[i] = 1.0 / (1.0 + exp(-Accum)) ;
  }
}
void motor_1(int x, int y){
  if(x == 0 && y == 1 ){
    //  digitalWrite(m1p1,HIGH);
    //  digitalWrite(m1p2,LOW);
    // Serial.println("LEFT MOTOR FORWARD");
  }
  else{
    //  digitalWrite(m1p1, LOW);
    //  digitalWrite(m1p2, HIGH);
    // Serial.println("LEFT MOTOR BACKWARD");
  }

}
void motor_2(int x, int y){
  if(x == 0 && y == 1){
    //  digitalWrite(m2p1,HIGH);
    //  digitalWrite(m2p2, LOW);
    // Serial.println("RIGHT MOTOR FORWARD");
  }
  else{
    //  digitalWrite(m2p1,LOW);
    //  digitalWrite(m2p2, HIGH);
    // Serial.println("RIGHT MOTOR BACKWARD");
  }
  
  
}
void drive_vehicle(){
  if(Output[0] >= 0.50){
    motor_1(0,1);
    // // Serial.println("LEFT MOTOR FORWARD");
  }
  else if(Output [0] < 0.50){
    motor_1(1,0);
    // // Serial.println("LEFT MOTOR BACKWARD");
  }
  if(Output[1] >= 0.50){
    motor_2(0,1);
    // // Serial.println("RIGHT MOTOR FORWARD");
  }
  else if(Output[1] < 0.50){
    motor_2(1,0);
    // // Serial.println("RIGHT MOTOR BACKWARD");
  }

  // Serial.println(Output[0]);
  // Serial.println(Output[1]);
  // Serial.println();
  // Serial.println();
  // Serial.println();
}


int main(){
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  setup();

}