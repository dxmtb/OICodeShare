{
ID: dxmtb1
PROG: milk2
LANG: PASCAL
}
program milk2;
type
 quj=array[1..2]of longint;
var
 n,i,j,m,p,q,po,num,lm,nm,former:longint;
 qu,re:array[1..5000]of quj;
 f1:text;
procedure sort(l,r:longint);
 var i,j,x:longint;y:quj;
 begin
  i:=l;
  j:=r;
  x:=qu[random(j-i+1)+i][1];
  repeat
   while qu[i][1]<x do
     inc(i);
   while qu[j][1]>x do
     dec(j);
   if not(j<i) then
    begin
     y:=qu[i];
     qu[i]:=qu[j];
     qu[j]:=y;
     inc(i);
     dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
 end;
begin
 assign(f1,'milk2.in');
 reset(f1);
 readln(f1,n);
 for i:=1 to n do
   readln(f1,qu[i][1],qu[i][2]);
 close(f1);
 assign(f1,'milk2.out');rewrite(f1);
 randomize;
 sort(1,n);
 po:=1;
 re[1]:=qu[1];
 for i:=2 to n do
  begin
   if qu[i][1]>re[po][2]
    then
     begin
      inc(po);
      re[po]:=qu[i];
     end
    else
     if qu[i][2]>re[po][2] then
      re[po][2]:=qu[i][2];
  end;
 lm:=0;nm:=0;former:=re[1][1];
 for i:=1 to po do
  begin
   if re[i][2]-re[i][1]>lm
    then lm:=re[i][2]-re[i][1];
   if re[i][1]-former>nm
    then nm:=re[i][1]-former;
   former:=re[i][2];
  end;
 writeln(f1,lm,' ',nm);
 close(f1);
end.
