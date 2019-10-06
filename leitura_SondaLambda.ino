
#include <SRyLul/Scale.h>
#include <SRyLul/BPL.h>

// MAF, Mass air flow
float maf_inLimits[2] = {0.00, 1023.00}; // Analog in 0-5V
float maf_outLimits[2] = {0.00, 150.00}; // Air, grams/s
int maf_In;
float maf_Out;
Scale maf;

// Enginetemp
float temp_inLimits[2] = {0.00, 1023.00}; // Analog in 0-5V
float temp_outLimits[2] = {-50.00, 150.00}; // Temp -50-150 GrC
int temp_In;
float temp_Out;
Scale temp;

// Pedal position
float pedal_inLimits[2] = {0.00, 1023.00}; // Analog in 0-5V
float pedal_outLimits[2] = {0.00, 150.00}; // Pelalpos  0-100 %
int pedal_In;
float pedal_Out;
Scale pedal;

// Injector, open relative to mass air flow
float injector_X[10] = {5.00, 12.00, 16.00, 24.00, 32.00, 40.00, 48.00, 64.00, 80.00}; // open %
float injector_Y[10] = {0.00, 10.0, 20.00, 40.0, 60.00, 75.0, 90.00, 120.00, 150.00}; // 0-150 g/s
float injector_Min[2] = {5.00, 0.00};
float injector_Max[2] = {80.00, 150.00};
float injector_In;
float injector_Out;
BPL injector(10);

// Enginetemp, add fuel if cold engine
float enginetemp_X[10] = {25.00, 23.00, 20.00, 10.00, 10.00, 5.00, 0.00, 00.00, 00.00}; // open %
float enginetemp_Y[10] = {0.00, 5.00, 10.00, 30.00, 40.00, 50.00, 60.00, 800.00, 100.00}; // 0-100 GrC
float enginetemp_Min[2] = {25.00, 0.00};
float enginetemp_Max[2] = {0.00, 100.00};
float enginetemp_In;
float enginetemp_Out;
BPL enginetemp(10);

// Acceration, add fuel if "Pedal to the metal"
float acc_X[10] = {0.00, 1.00, 2.00, 4.00, 5.00, 6.00, 8.00, 9.00, 10.00}; // open %
float acc_Y[10] = {0.00, 10.00, 20.00, 40.0, 50.00, 60.00, 80.0, 90.00, 100.00}; // 0-100 % acc
float acc_Min[2] = {0.00, 0.00};
float acc_Max[2] = {10.00, 100.00};
float acc_In;
float acc_Out;
BPL acc(10);


// Lambda, narrowbandsond
float lambda_X[10] = {0.88, 0.84, 0.79, 0.66, 0.15, 0.08, 0.05, 0.03}; // 0-1V
float lambda_Y[10] = {0.68, 0.80, 0.90, 0.99, 1.01, 1.11, 1.20, 1.30}; // Petrol 10-19 afr
float lambda_Min[2] = {0.88, 0.68};
float lambda_Max[2] = {0.03, 1.30};
float lambda_In;
float lambda_Out;
BPL lambda(10);

int MafPin;
int TempPin;
int PedalPin;
int LambdaPin;
float Injector;


void setup()
{
 MafPin = 1;
 TempPin = 2;
 PedalPin = 3;
 LambdaPin = 4;
 
}

void loop()
{
   maf_In = analogRead(MafPin);
   temp_In = analogRead(TempPin);
   pedal_In = analogRead(PedalPin);
   lambda_In = analogRead(LambdaPin);

 
 maf_Out = maf.calc(maf_In, maf_inLimits, maf_outLimits);
 temp_Out = temp.calc(temp_In, temp_inLimits, temp_outLimits);
 pedal_Out = pedal.calc(pedal_In, pedal_inLimits, pedal_outLimits);


 injector_In = maf_Out;
 injector_Out = injector.calc(temp_In, injector_X, injector_Y, injector_Min, injector_Max);

 enginetemp_In = temp_Out;
 enginetemp_Out = enginetemp.calc(enginetemp_In, enginetemp_X, enginetemp_Y, enginetemp_Min, enginetemp_Max);
 
 acc_In = pedal_Out;
 acc_Out = acc.calc(acc_In, acc_X, acc_Y, acc_Min, acc_Max);

 lambda_Out = lambda.calc(lambda_In, lambda_X, lambda_Y, lambda_Min, lambda_Max);
 
 Injector = (injector_Out + enginetemp_Out + acc_Out)/ lambda_Out;

 delay(200);
}
