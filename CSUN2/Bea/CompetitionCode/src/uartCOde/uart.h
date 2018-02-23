
task main()
{
rcvChar = getChar(uartTwo);
 if (rcvChar == -1)
 {
 // No character available

 wait1Msec(3); // Don't want to consume too much CPU time. Waiting eliminates CPU consumption for this task.
 continue;
 }
 ++nLastRcvChar;
 nLastRcvChar %= 256;
 if (nLastRcvChar != rcvChar)
 ++nTotalRcvOutOfSequence;

 nLastRcvChar = rcvChar;
 rcvChars[nRcvIndex] = rcvChar;
 ++nTotalRcvChars;
 ++nRcvIndex;
 if (nRcvIndex >= sizeof(rcvChars))
 nRcvIndex = 0;
 }
}


}
