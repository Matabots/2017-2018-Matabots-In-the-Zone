#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int nRcvIndex = 0;
long nTotalRcvChars = 0;
long nTotalRcvOutOfSequence = 0;
int rcvChar;
unsigned char rcvChars[23];

task sendConeSelection(){
	while(true){
		sendChar(UART1, '1');
	}
}
 task UARTReceive()
{
 while (true)
 {
 // Loop forever getting characters from the "receive" UART. Validate that they arrive in the expected
 // sequence.

 static int nLastRcvChar = 0;

 rcvChar = getChar(UART1);

 if (rcvChar == -1)
 {
 // No character available

 wait1Msec(3); // Don't want to consume too much CPU time. Waiting eliminates CPU consumption for this task.
 continue;
 }
 if(rcvChar != '#' && rcvChar != '�'){
 writeDebugStream("%c", rcvChar);
}else{
	writeDebugStreamLine("\n");
}
 ++nLastRcvChar;
 nLastRcvChar %= 256;
 if (nLastRcvChar != rcvChar)
 ++nTotalRcvOutOfSequence;

 nLastRcvChar = rcvChar;
 rcvChars[nRcvIndex] = rcvChar;
 ++nTotalRcvChars;
 ++nRcvIndex;
 if (nRcvIndex >= sizeof(rcvChars)){
   //writeDebugStreamLine("%s\n", rcvChars);
 		//writeDebugStream(rcvChars);
	 	nRcvIndex = 0;
	}
 }
}

task main(){
	startTask(UARTReceive);
	startTask(sendConeSelection);
	while(true){

	}
}
