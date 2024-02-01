::===============================================================
::
:: Re-index AGENDA files
::
::===============================================================
@echo off 
:: 
:: 
::
::  Aamdexing the Users File
::
sunaamdx agendau.data,agendau.aam,L91 -U,P1#'*',1-10,11-16,17-36,43-47
echo ===============================================================
::
::  Indexing & Ammdexing the Appointments File
::
sunindex agenda.data,agenda.isi,L98 -1-17
sunaamdx agenda.data,agenda.aam,L98 -U,1-6,44-98
echo ===============================================================
::
:: Indexing the Appointment Graph File
::
sunindex agendag.data,agendag.isi,L109 -1-11
echo ===============================================================
::
::  Indexing the Messages File
::
sunindex agendam.data,agendam.isi,L387 -1-18,S,V
echo ===============================================================
::
::  Aamdexing the Directory File
::
sunaamdx agendad.data,agendad.aam,L186 -U,1-6,7-36,157-186
echo ===============================================================
::
::  Indexing & Aamdexing the Notepad & Alarms File
::
sunindex agendan.data,agendan.isi,L94 -1-20
sunaamdx agendan.data,agendan.aam,L94 -U,P1='2',2-7,40-94
echo ===============================================================
::
::  Indexing the Meeting Planner File
:: 
sunindex agendap.data,agendap.isi,L152 -1-17,P1#*
sunindex agendap.data,agendap1.isi,L152 -18-23,7-17,1-6,P1#*
echo ===============================================================
::
::  Indexing the Help File
:: 
sunindex agendah.data,agendah.isi -2-5,P1=*,S,V 
echo ===============================================================
::
echo Complete