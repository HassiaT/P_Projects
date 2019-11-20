echo Starting batch script to launch q processes
c:
cd c:\q\start\tick
echo Starting ticker plant process
start "TICKERPLANT PROCESS" ..\..\w32\q.exe C:\q\start\tick\tick.q sym ./HDB/Logfiles/ -t 4000 -p 5010
start "HISTORICAL DATABASE" ..\..\w32\q.exe C:\q\start\tick\tick\hdbscript.q C:\q\HDBHisto\histdb\ show -p 5012
start "RDB - REAL TIME SUSCRIBER"  ..\..\w32\q.exe C:\q\start\tick\tick\r.q :5010 :5012 -p 5011
exit
