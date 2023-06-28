 
Data            DIM             80
 
F               PLFORM          TNAV
Count           FORM            "0"
 
                FORMLOAD        F
                WebB.Navigate   Using "c:\sunbelt\sunbelt-plb-samples\legacy_demo\Test1.htm"
                EVENTREG        WebB,"250",CanNav,FastEvent
                LOOP
                EVENTWAIT
                REPEAT
                STOP
 
CanNav
                IF              (Count <> 0)
                RETURN
                ENDIF
                ADD             "1" To Count
                GETPROP         *Arg2,VarValue=Data
                DISPLAY         Data
                SETPROP         *Arg7,VARVALUE="-1"
                RETURN
