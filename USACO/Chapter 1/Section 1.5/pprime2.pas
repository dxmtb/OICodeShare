{
ID: dxmtb1
PROG: pprime
LANG: PASCAL
}
program pprime;
var
 m,n,i,j,a,b,a1,b1,l,d1,d2,d3,d4,d5,code:longint;
 p:array[1..100000000]of boolean;
 new:longint;
 s:string;
 f1,f2:text;
function prim(x:longint):boolean;
 var i:longint;
 begin
  for i:=2 to trunc(sqrt(x)) do
   if (x mod i)=0 then exit(false);
  exit(true);
 end;
function pa(x:longint):boolean;
 var s:string;i,j:integer;
 begin
  str(x,s);
  i:=1;j:=length(s);
  while s[i]=s[j] do
   begin
    inc(i);dec(j);
    if i>j then exit(true);
   end;
  pa:=false;
 end;
begin
 assign(f1,'pprime.in');reset(f1);
 assign(f2,'pprime2.out');rewrite(f2);
 readln(f1,a,b);
 close(f1);
 fillchar(p,sizeof(p),true);
 for i:=2 to b do
  if p[i] then
    for j:=2 to trunc(b div i) do
     p[j*i]:=false;
 for i:=a to b do
  if p[i] then
   if pa(i) then
    writeln(f2,i);
 close(f2);
end.