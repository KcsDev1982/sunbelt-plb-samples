*..........................................................................
. Example Program: ODBC.PLS
.
. This program is a simple example of the PL/B SQL statements. It
.  allows the user to connect to a remote database via ODBC.  ODBC must
.  be installed before this program is executed.
.
.  The following function are performed:
.     1. Connects to ODBC remote database.
.     2. Sets up a database query.
.     3. Executes the database query.
.     4. Checks the status of the database query.
.     5. Fetches all of the data selected by the query and displays it.
.     6. Disconnects from the ODBC remote database.
.
. Copyright @ 1997-1999 Sunbelt Computer Systems, Inc.
. All Rights Reserved.
*............................................................................
.
D               DBFILE
Reply           DIM             1
R               FORM            4
ID              DIM             5
NAME            DIM             40
*
. Column Data Retrieved from the Selected Table
. (These should be modified to match your database specifications.)
.
ORDID           FORM            2
ORDCUS          DIM             5
ORDPID          INTEGER         4
ORDDT           DIM             10
ORDQT           DIM             4
*..........................................................................
. Connect to the Database
.
. The DBCONNECT statement allows a program to connect to a remote
. database and associate that connection with a DBFILE declaration.
.
. There are four required parameters and two optional parameters for
. this statement.
.
. FORMAT:
.  DBCONNECT   <dbfile>,<host>,<user>,<pass>[,<conn>,<ext>]
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.  <host>    -  defines the name of the data source.
.  <user>    -  defines the name of the user.
.  <pass>    -  defines the user's password.
.  <conn>    -  optional parameter to define additional login info.
.  <ext>    -  optional parameter to define the database extension.
.
                DBCONNECT       D,"","",""    // Since the name of the <host>
                                // parameter is null, this statement
                                // envokes a standard dialog to identify
                                // the database to be connected to.
                                // The <host> parameter could also
                                // be specified like in the variables
                                // 'L1' and 'L2' above.
*..........................................................................
. Issue the SQL Statement
.
. The DBSEND statement is used to send a query or a portion of a query
. to the ODBC system driver.  Note that the query is simply buffered by
. the DBSEND statements.  The actual execution of the query does not
. take place until DBEXECUTE is performed.
.
. FORMAT:
.  DBSEND      <dbfile>;<list>
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.  <list>    -  defines a comma delimited list of controls, variables,
.        and literals.  The list is similiar to a DISPLAY.
.
.
.
.The Table name should be changed as appropriate
.
                DBSEND          D;"SELECT * from orders"
*..........................................................................
. Execute the Query
.
. The DBEXECUTE statment is used to execute the query specified by the
. DBSEND statement(s). Note that if the DBEXECUTE initiates the query
. ok, then it can return before the query is completed.  The program
. should use the DBSTATE statement to determine the status of the query
. before executing a DBFETCH statement.
.
. FORMAT:
.  DBEXECUTE   <dbfile>
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.
.
                DBEXECUTE       D
.
*............................................................................
. Wait for the Query to Complete
.
. The following logic is waiting for the status of the last query to
. indicate when it is completed.  This logic is using the DBSTATE statement
. to determine when the query is complete.
.
. The DBSTATE statment is used to determine the current state of a remote
. database.  The actual state is provided via the flags LESS and EQUAL.
. When the LESS is set, then a query is currently executing at the remote
. database. Otherwise, it is cleared.  The EQUAL flag is set when the
. remote database has data that can be obtained using the DBFETCH
. statement.
.
. FORMAT:
.  DBSTATE     <dbfile>
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.
.
                DISPLAY         *HD,*R,"Waiting.";
                LOOP
                DISPLAY         ".";
                DBSTATE         D
                REPEAT          WHILE LESS
                DISPLAY         *N;
*............................................................................
. Fetch Data
.
. The following logic is looping through the current query selection
. data using the DBFETCH statement.  The DBFETCH statement sets the
. OVER when there are no more rows of information to be retreived.
. This should give the user a feel like a READ statement.  There is also
. a timeout value which can be given for the DBFETCH operation.  The LESS
. flag is set if the timeout value expires before an item is received from
. the remote database. If the timeout value is -1, this disables the
. the timeout feature.
.
. FORMAT:
.  DBFETCH     <dbfile>,<timeout>;<list>[<;>]
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.  <timeout> -  defines the timeout value to be used for data being
.        retrieved.  A value is specified in seconds.  If
.        the value is a "-1", then the timeout feature is
.        not used.
.  <list>    -  defines a comma delimited list of controls and variables
.        into which the data is returned. This is very
.        similiar to a READ statement.
.  <;>    -  a semi-colon is optional at the end of a DBFETCH
.        statement.  This can be used to retrieve a partial
.        number of columns from a row.  Note that a
.        DBFETCH will not proceed to the next row until a
.        DBFETCH is executed without a semi-colon.
.
                LOOP
                DBFETCH         D,"1";ORDID,ORDCUS,ORDPID,ORDDT,ORDQT
                UNTIL           OVER
                DISPLAY         ORDID,":",ORDCUS," : ",ORDPID," : ",ORDDT," : ",ORDQT
                REPEAT
*.............................................................................
. Disconnect the Database
.
. The DBDISC or DBDISCONNECT statement is used to disconnect from the
. remote database.
.
. FORMAT:
.  DBDISCONNECT <dbfile>
.
.  where:
.
.  <dbfile>  -  defines the DBFILE associated with the connection.
.
                DBDISCONNECT    D
*............................................................................
. Terminate Execution
.
                KEYIN           *HD,*R,"Database Closed. ",Reply
