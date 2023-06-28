+------------------------------------------------------------------------------
. The intent of this PROGRAM is to provide SAMPLE logic which can
. be used as an example for Reindexing or Reaamdexing data files for an
. application. 
.
. This logic has intentional ERRORs built in which require the user
. to modify for a given application.
.
INPUT           FILE            BUFFER=8192
SEQ             FORM            "-1"
VAR1            DIM             5
VAR2            DIM             5
.
. Other variables would go here.
.
VARLIST         VARLIST         VAR1,VAR2 // ,VAR3,...
.------------------------------------------------------------------------------
. IFILE definition that will be used to PREP the new ISAM and TXT file.
.
. This must be modified to supply the correct record length if greater
. than 256
.
. If you need an AAM file instead of an ISI file, change IFILE to AFILE.
.
INDEX1          IFILE           FIXED=256
KEYLEN1         FORM            "10"         ;Change to match INDEX1 key length
RECLEN		FORM		"256"
KEY1		DIM		10
.------------------------------------------------------------------------------
. Additional IFILE or AFILE file declarations go here if there are
. secondary indices on the file.  Since an AAM or ISAM prep will cause
. the TXT file to be truncated to a zero length file, any reindexes
. must create any secondary AAM or ISI files at the same time that
. the original file is created.
.
.INDEX2  IFILE    FIXED=256
.KEYLEN2 FORM    "20"         ;Change to match INDEX2 key length
.
.INDEX3  AFILE    FIXED=256
.KEYSPC3 INIT    "U,1-10,11-20,22"   ;Change to match INDEX3 key specs
.------------------------------------------------------------------------------
. Working variables.
.
COUNT           FORM            5
COUNT2          FORM            2
.------------------------------------------------------------------------------
. Step 1. Make sure the temporary file does not exist.
.
                DISPLAY         *HD,"PL/B Sample Indexing Program"
                TRAP            IGNORE IF IO
                ERASE           "SAMPLE.OLD"
                TRAPCLR         IO
.------------------------------------------------------------------------------
. Step 2. RENAME the data file to another name.
.
                RENAME          "SAMPLE.TXT","SAMPLE.OLD"
.------------------------------------------------------------------------------
. Step 3. OPEN the RENAMEd data file in EXCLUSIVE mode for faster access.
.
                OPEN            INPUT,"SAMPLE.OLD",EXCLUSIVE
.------------------------------------------------------------------------------
. Step 4. PREP all of the indices that are required.
.
                DISPLAY         "Indexing SAMPLE.TXT"
                PREP            INDEX1,"SAMPLE.TXT","SAMPLE.ISI",KEYLEN1,RECLEN
.....  PREP    INDEX2,"SAMPLE.TXT","SAMPLE.IS2",KEYLEN2,RECLEN
.....  PREP    INDEX3,"SAMPLE.TXT","SAMPLE.AAM",KEYSPEC3,RECLEN
.------------------------------------------------------------------------------
. Step 5. Read the RENAMEd data file sequentially.
.
                LOOP
                READ            INPUT,SEQ;VARLIST
                UNTIL           OVER
.------------------------------------------------------------------------------
. Step 6. If an INDEX1 is an ISAM file, then create the key.
.
                PACK            KEY1,VAR1,VAR2
.------------------------------------------------------------------------------
. Step 7. WRITE the record to INDEX1.
.
                WRITE           INDEX1,KEY1;VARLIST
.------------------------------------------------------------------------------
. Step 8. Build any other keys and perform any required INSERTs.
.
.....    PACK      KEY2,VAR3,VAR1,VAR2
.....    INSERT    INDEX2,KEY2       ;ISAM FILE INSERT
.....    INSERT    INDEX3        ;AAM FILE INSERT
.------------------------------------------------------------------------------
. Step 9. Display record counter.
.
                ADD             "1",COUNT
                MOVE            COUNT,COUNT2
                IF              OVER
                DISPLAY         "Records: ",COUNT,*C;
                ENDIF
.------------------------------------------------------------------------------
. Step 10. Repeat the process with the next record.
.
                REPEAT
.------------------------------------------------------------------------------
. When an OVER is detected on the input file, we will come here.
.
                CLOSE           INPUT
                CLOSE           INDEX1
.....  CLOSE    INDEX2
.....  CLOSE    INDEX3
.------------------------------------------------------------------------------
. The REINDEX and/or REAAMDEX is now finished.
.
                STOP
.------------------------------------------------------------------------------
. Trap to ignore an I/O error on the ERASE statement.
.
IGNORE
                RETURN
