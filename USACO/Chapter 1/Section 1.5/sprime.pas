{
ID: dxmtb1
PROG: sprime
LANG: PASCAL
}
program sprime;
var
 m,n,i,j,mini:longint;
 p:array[1..8,0..10000]of longint;
 f1,f2:text;
function check(x:longint):boolean;
 var i,temp:longint;
 begin
  if x=0 then exit(true);
  if x=1 then exit(false);
  for i:=2 to trunc(sqrt(x)) do
   if (x mod i)=0 then exit(false);
  check:=check(x div 10);
 end;
procedure cal(x:longint);
 var i,j:longint;
 begin
  if x=1 then begin
   for i:=2 to 9 do if check(i) then begin
    inc(p[x,0]);p[x,p[x,0]]:=i;end end
    else
 begin
  for i:=1 to p[x-1,0] do
   begin
    if check(p[x-1,i]*10+1) then begin inc(p[x,0]);p[x,p[x,0]]:=p[x-1,i]*10+1;end;
    if check(p[x-1,i]*10+3) then begin inc(p[x,0]);p[x,p[x,0]]:=p[x-1,i]*10+3;end;
    if check(p[x-1,i]*10+7) then begin inc(p[x,0]);p[x,p[x,0]]:=p[x-1,i]*10+7;end;
    if check(p[x-1,i]*10+9) then begin inc(p[x,0]);p[x,p[x,0]]:=p[x-1,i]*10+9;end;
   end;
 end;
 end;
begin
 assign(f1,'sprime.in');reset(f1);
 assign(f2,'sprime.out');rewrite(f2);
 readln(f1,n);
 close(f1);
 mini:=1;fillchar(p,sizeof(p),0);
 for i:=1 to n-1 do mini:=mini*10;
 if mini=1 then mini:=2;
 for i:=1 to n do
  cal(i);
 for i:=1 to p[n,0] do
  writeln(f2,p[n,i]);
 close(f2);
end.
