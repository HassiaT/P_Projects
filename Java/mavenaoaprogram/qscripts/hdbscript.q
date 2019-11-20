x:.z.x 1
s:`                   	  / default all symbols
x
show "Starting mounting HDB on disk"
if[1>count .z.x; show"Supply directory of historical database"; exit 0;]
show "Initializing hdb directory"
hdb: .z.x 0
show hdb
mytables:`rates`lastupdates
\l c:/q/HDBHisto/histdb
[{system"l ",hdb};hdb;{show "Error message - ",hdb;exit 0}];
\t 120000
h:hopen `::5010           / connect to tickerplant
{h(".u.sub";x;s)} each mytables;

/ show only
if[x~"show";
 tabcount:()!();
 / count the incoming updates
 upd:{[mytables;x] tabcount+::(enlist mytables)!enlist count x};
 / show the dictionary every t milliseconds   
  .z.ts:{-1"current total received record counts at time ",string .z.T;
	 show tabcount;
	 -1"";}];

