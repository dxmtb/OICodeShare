Program ex;
var
 use:array[1..9] of boolean;
 ans:longint;
 
Procedure init;
var
 i,n,x:integer;
begin
 assign(input,'crypt1.in');
 reset(input) ;
 
 read(n) ;
 fillchar(use,sizeof(use),false)  ;
 for i := 1 to n do
  begin
   read(x) ;
   use[x] := true ;
  end;
 
 close(input)  ;
end;
 
Function check(x:longint):boolean;
BEGIN
 while x > 0 do
  begin
   if x mod 10=0 then exit(false);
   if not use[x mod 10] then exit(false) ;
   x := x div 10 ;
  end;
 exit(true) ;
END;
 
Procedure search;
var
 i,j:integer;
begin
 For i := 111 to 999 do
  if check(i) then
   for j := 11 to 99 do
    if check(j) and check(i*j) then
    if ((i * (j mod 10)) div 1000 = 0) and (check(i*(j mod 10))) then
    if ((i * (j div 10)) div 1000 = 0) and (check(i*(j div 10))) then
     inc(ans) ;
end;
 
Procedure outp;
begin
 assign(output,'crypt1.out') ;
 rewrite(output) ;
 
 writeln(ans) ;
 
 close(output) ;
end;
 
BEGIN
 init;
 search;
 outp;
END.
