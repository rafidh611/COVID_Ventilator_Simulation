#define value 110
void EnableInterrupts(void);  // Enable interrupts
void DisableInterrupts(void); // Disable interrupts
int Index = 0;
uint32_t Wave[] = {
8,   
9,
11,
12,
13,
14,
14,
15,
15,
15,
14,
14,
13,
12,
11,
9,
8,
7,
5,
4,
3,
2,
2,
1,
1,
1,
2,
2,
3,
4,
5,
7
};
int Button_Pressed()
{
	int t = GPIO_PORTE_DATA_R & 0x07;
	return t;
	
}
int Convert(int input){
	int y = ((input * value)/10000);
  return y; // replace this line with your Lab 8 solution
}


void Sound_Init(void){
 NVIC_ST_CTRL_R = 0;
 NVIC_ST_CURRENT_R = 0;
 NVIC_ST_RELOAD_R = 0;
 }

void Low_Pressure()
{
	int t = Button_Pressed();
	int Data = ADC_In();
	int p = Convert(Data);
	ST7735_PlotClear(0,50);
	int tracker1=0;
	while(t==0)
	{ 
		  t = Button_Pressed();
		  if(tracker1==128)
			{
				 ST7735_PlotClear(0,50);
					tracker1=0;
			}
		  Data = ADC_In();
			int p = Convert(Data);
			ST7735_PlotPoint(p);
		  ST7735_PlotNext();
			tracker1++;
			if(p>10)
				{
					break;
					
				}
		  for(int i = 0; i<2500 ; i++)
		   {
				 Sound_Play(500);
			 }
			 Sound_Play(0);
			 for(int i = 0; i<2500 ; i++)
		   {
				 Sound_Play(500);
			 }
			 Sound_Play(0);
			 for(int i = 0; i<2500 ; i++)
		   {
				 Sound_Play(500);
			 }
			 Sound_Play(0);
			 for(int i = 0; i<2500 ; i++)
		   {
				 Sound_Play(0);
			 }
		
	}
}

void High_Pressure()
{
	int t = Button_Pressed();
	int Data = ADC_In();
	int p = Convert(Data);
	ST7735_PlotClear(0,50);
	int tracker2=0;
	NVIC_ST_CTRL_R=7;
	while(t==0)
	{
		  t = Button_Pressed();
		   if(tracker2==128)
			{
				 ST7735_PlotClear(0,50);
					tracker2=0;
			}
		  Data = ADC_In();
			int p = Convert(Data);
			ST7735_PlotPoint(p);
		  ST7735_PlotNext();
			tracker2++;
			if(p<36)
			{
				break;
			}
		  Sound_Play(1000);
			for(int i=0;i<20000;i++)
			{
			}
	}
		
	
}
void Sound_Play(uint32_t freq){
  if(freq==0)
	{
		DAC_Out(0);
	}
	else{
  int waitperiod = 80000000/(freq*32);
	NVIC_ST_RELOAD_R = waitperiod;
	NVIC_ST_CTRL_R = 7;
	EnableInterrupts();
	}
}

void SysTick_Handler()
{
	DAC_Out(Wave[Index]);
	Index = Index + 1;
	if(Index == 32)
	{
		Index=0;
	}
}
