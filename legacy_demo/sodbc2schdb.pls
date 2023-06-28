*****************************************************
. sqlite schema initialization sample program
. creates a runtime schema from a sunodbc schema
. 
.   By: Matthew Lake
.   Copyright 2010 Sunbelt Computer Systems, Inc.
. 
. 9.4A  corrected some bugs that prevented it from running 
.       "out of the box".
*****************************************************
.
.  This loadmod has two calls, one to initialize a schema database and
.  one to import a SunODBC schema.
.  
.  To use this module, call initialize passing in the name of the 
.  schema database you would like to use.  If one is not specified, it
.  uses the default sunschema.db that is automatically created by the
.  runtime.
.  
.  After calling initialize, call the ImportFromODBCSchema function
.  passing in the name of the SunODBC schema.ini file.
.
. Syntax:
.
.  CALLS "sodbc2schdb;INITIALIZE" using schemaDBname
.  CALLS "sodbc2schdb;IMPORTFROMODBCSCHEMA" using odbcschema
.
. Where:
.  schemaDBname optional DIM variable containing the sqlite db name to 
.    use to contain the runtime schema information
.    
.  odbcschema required dim variable containing the sunodbc schema.ini
.    filename
.
. Example Code:
. 
fname           DIM             60
fpath           DIM             200
odbcschema      DIM             260

                GETFNAME        OPEN,"Select ODBC Schema.ini file",fname,fpath,"ini"
                PACK            odbcschema,fpath,fname
.
                CALL            INITIALIZE // USING "c:\sunbelt\plbwin.95\code\sunschema.db"
                CALL            ImportFromODBCSchema using odbcschema
.
                STOP
.
.***************************************************************************
.  Loadmod begins here...
.***************************************************************************
.
db              DBFILE
tm              FORM            "5"
.
INITIALIZE      FUNCTION
schemadb        DIM             260
                ENTRY

haveView        FORM            1
havecolumns     FORM            1
havedatabases   FORM            1
field           DIM             80
sys             DIM             250
host            DIM             300
.
. initialize schema database
. 
                TYPE            schemadb
                IF              EOS
                MOVE            "PLB_SYSTEM",sys
                CLOCK           INI,sys
                IF              OVER
                CLEAR           sys
                ELSE
                ENDSET          sys
                CMATCH          "\",sys
                IF              NOT EQUAL
                APPEND          "\",sys
                ENDIF
                RESET           sys
                ENDIF
                PACK            schemadb,sys,"sunschema.db"
                ENDIF
.
                PACK            host,"SQLITE;;",schemadb
                DBCONNECT       db,host,"",""
.
. get existing table definitions
.
                DBSEND          db;"SELECT name FROM sqlite_master ":
                                "WHERE type='table' ":
                                "ORDER BY name;"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT

. figure out what is there

                LOOP
                DBFETCH         db,tm;field
                UNTIL           OVER
                LOWERCASE       field
                SWITCH          field
                CASE            "sun_views"
                SET             haveview
                CASE            "sun_databases"
                SET             havedatabases
                CASE            "sun_columns"
                SET             havecolumns
                ENDSWITCH
                REPEAT

. create missing tables

                IF              ( !haveview ) 
                DBSEND          db;"CREATE TABLE sun_views ( id integer, name text not null unique, description text );"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                ENDIF
 
                IF              ( !havecolumns )
 
                DBSEND          db;"CREATE TABLE sun_columns ( id integer primary key, ":
                                "view_id integer, ":
                                "name text not null,":
                                "description text,":
                                "type integer,":
                                "offset integer,":
                                "length integer,":
                                "scale integer,":
                                "element_count integer,":
                                "sql_type integer,":
                                "key_value integer,":
                                "nullable integer,":
                                "zero_fill integer,":
                                "empty_null integer,":
                                "selectivity integer,":
                                "format_mask text,":
                                "default_value text );"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT

                ENDIF
 
                IF              ( !havedatabases )
                DBSEND          db;"CREATE TABLE sun_databases ":
                                "( id integer, name text, databasefile text );"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                ENDIF
                FUNCTIONEND

GETNEXTVIEWID   FUNCTION
                ENTRY
                
nextid          FORM            4
                DBSEND          db;"SELECT MAX(id) FROM sun_views"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                DBFETCH         db,tm;nextid
                INCR            nextid
                FUNCTIONEND     USING nextid

GETNEXTCID      FUNCTION
                ENTRY
                
nextid          FORM            4
                DBSEND          db;"SELECT MAX(id) FROM sun_columns"
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                DBFETCH         db,tm;nextid
                INCR            nextid
                FUNCTIONEND     USING nextid

GETIDOFVIEW     FUNCTION
vname           DIM             80
                ENTRY
sql             DIM             200
vid             FORM            4
                CHOP            vname
                PACK            sql,"SELECT id FROM sun_views WHERE name LIKE '",vname,"';"
                DBSEND          db;sql
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                DBFETCH         db,tm;vid
                IF              OVER
                MOVE            "-1",vid
                ENDIF
.
                FUNCTIONEND     USING vid

ImportFromODBCSchema FUNCTION
fname           DIM             250
                ENTRY
FILE            FILE
SEQ             FORM            "-1"
data            DIM             1000
vname           DIM             80
sql             DIM             1000
vid             FORM            4
vidd            DIM             4
.
cid             FORM            4
cidd            DIM             4
cname           DIM             80
otype           DIM             30
ctype           DIM             1
csize           FORM            4 //column size
csized          DIM             4
coffset         FORM            10 //column offset
coffsetd        DIM             10
cscale          FORM            2
cscaled         DIM             2
mask            DIM             25
fm4             FORM            4
.
zf              DIM             1
null            DIM             1
primary         DIM             1
res             DIM             10
.
. quick notes
.   sunodbc schema file mappings:
.   [tables] = sun_views
.   [{tablename}] = sun_columns where {tablename} is view_id 
.      ( foreighn key to sun_views.id )
.   
.   
                OPEN            file,fname,read
                LOOP
                READ            file,seq;data
                UNTIL           OVER
                UPPERCASE       data
.
.   put together the views table
.
                MATCH           "[TABLES]",data
                IF              EQUAL
                LOOP
                READ            file,seq;data
                UNTIL           OVER
                MATCH           "[",data
                BREAK           IF EQUAL
                EXPLODE         data,"=",vname
..
                CALL            GETIDOFVIEW giving vid using vname
                CONTINUE        IF (vid!="-1") // view already exists!!
..
                CALL            GETNEXTVIEWID giving vid
                MOVE            vid,vidd
                SQUEEZE         vidd,vidd
                PACK            sql,"INSERT INTO sun_views (id,name) VALUES('",vidd,"','",vname,"');"
                DBSEND          db;sql
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                REPEAT
                ENDIF
.
.   build columns table
.
                MATCH           "[",data
                IF              EQUAL
nxt_tbl         MOVE            "1",coffset // each table offset starts at 1
.
.     get the view and view_id
.     
                BUMP            data
                EXPLODE         data,"]",vname
                CALL            GETIDOFVIEW giving vid using vname
                CONTINUE        IF (vid="-1") //column not found in views
                MOVE            vid,vidd
                SQUEEZE         vidd,vidd
.
                LOOP
                READ            file,seq;data
                UNTIL           over
.
.       open bracket is start of next view
                MATCH           "[",data
                GOTO            nxt_tbl IF EQUAL
.
                UPPERCASE       data
                MATCH           "COL",data
                CONTINUE        IF NOT EQUAL
.
.       get column ID
                BUMP            data,3
                PARSE           data,cidd,"09"
                MOVE            cidd,cid
                BUMP            data
.
                PARSE           data,cname,"AZ"  //column name
..
..       does column already exist in view?
..       
                PACK            sql,"SELECT id FROM sun_columns WHERE view_id='",vidd,"' AND name LIKE '",cname,"';"
                DBSEND          db;sql
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                IF              ZERO
.         if the select returned any data, we have a problem
                DBFETCH         db,tm;fm4
                BREAK           IF NOT OVER
                ENDIF
..
..  Get next available ID
..
                CALL            GETNEXTCID giving cid
..
                PARSE           data,otype,"AZ09" //column type or res num
                IF              LESS   // reached end of definition,
                CLEAR           mask //assume we got column type and no mask
                ELSE
                TYPE            otype
                IF              EQUAL
                MOVE            otype,res // got restriction number
                PARSE           data,otype,"AZ" // get column type next
                ELSE
                MOVE            "0",res
                ENDIF
..         
                PARSE           data,mask,"AZ//''" //"Width" or mask
                ENDIF
                CLEAR           cscale
.
                SWITCH          otype
                CASE            "INTEGER"
                MOVE            "1",ctype //form
                MOVE            "0",cscale
                PARSE           data,csized,"09"
                MOVE            csized,csize
.
                CASE            "FLOAT"
                MOVE            "1",ctype //form
                PARSE           data,csized,"09.."
                EXPLODE         csized,".",csize,cscale
.
                CASE            "DATE"
                NOBREAK
                CASE            "TIME"
                NOBREAK
                CASE            "TIMESTAMP"
                MOVE            "0",ctype //dim
                TYPE            mask
                IF              NOT EOS
                COUNT           csize,mask
                SUB             "2",csize // compensate for quotes
                ELSE
                IF              (ctype="TIMESTAMP")
                MOVE            "14",csize
                ELSE
                MOVE            "8",csize
                ENDIF
                ENDIF
.         
                DEFAULT
                MOVE            "0",ctype //dim
                PARSENUM        data,csize
                ENDSWITCH
.
..       get ODBC Options from remainder of column data
                WHEREIS         "NULL",data
                IF              NOT ZERO
                MOVE            "1",null
                ELSE
                MOVE            "0",null
                ENDIF
.
                WHEREIS         "PRIMARY",data
                IF              NOT ZERO
                MOVE            "1",primary
                ELSE
                MOVE            "0",primary
                ENDIF
.
                WHEREIS         "ZF",data
                IF              NOT ZERO
                MOVE            "1",zf
                ELSE
                WHEREIS         "ZEROFILL",data
                IF              NOT ZERO
                MOVE            "1",zf
                ELSE
                MOVE            "0",zf
                ENDIF
                ENDIF
..
                MOVE            coffset,coffsetd
.
                ADD             cscale,csize
                IF              (CSCALE)  // decimal point 
                ADD             "1",csize
                ENDIF
.
.       pack up data for SQL statement
.       
                ADD             csize,coffset
                MOVE            csize,csized
                MOVE            cscale,cscaled
                MOVE            cid,cidd
                SQUEEZE         cidd,cidd
                SQUEEZE         coffsetd,coffsetd
                SQUEEZE         csized,csized
                SQUEEZE         cscaled,cscaled
                PACK            sql,"INSERT INTO sun_columns ":
                                "values ":
                                "(",cidd,",",vidd,",'",cname,"','',",ctype,",",coffsetd,",",csized,",",cscaled,",1,0,",primary,",0,",zf,",",null,",",res,",'','');"
                DBSEND          db;sql
                DBEXECUTE       db
                LOOP
                DBSTATE         db
                UNTIL           NOT LESS
                REPEAT
                REPEAT
                ENDIF
                REPEAT

                FUNCTIONEND
