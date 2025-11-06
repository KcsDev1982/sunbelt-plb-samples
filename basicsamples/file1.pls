*===========================================================
. Simple FILE Example
. Demonstrates writing and reading sequential records
*===========================================================

MyFile       FILE
LineOut      DIM         50
LineIn       DIM         50
Seq          FORM        "-1"

             CALL        Main
             STOP

*-----------------------------------------------------------
. Main Routine
*-----------------------------------------------------------
Main         LFUNCTION
             ENTRY

*--- Create or open a data file
             PREPARE     MyFile, "simple.dat"

*--- Write a few sample records
             MOVE        "Sunbelt PL/B Tutorial" TO LineOut
             WRITE       MyFile,Seq;LineOut

             MOVE        "Sequential File Example" TO LineOut
             WRITE       MyFile,Seq;LineOut

             MOVE        "End of Data" TO LineOut
             WRITE       MyFile,Seq;LineOut

*--- Reposition to the beginning for reading
             CLOSE       MyFile
             OPEN        MyFile, "simple.dat"

*--- Read and display each record sequentially
ReadLoop     READ        MyFile,Seq;LineIn
             IF          OVER
                 GOTO     Done
             ENDIF

             DISPLAY     *N, "Record: ", LineIn
             GOTO        ReadLoop

Done         CLOSE       MyFile
             DISPLAY     *N, "All records displayed.", *W2
             FUNCTIONEND
