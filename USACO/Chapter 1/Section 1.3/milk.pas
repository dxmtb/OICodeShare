{
ID: dxmtb1
PROG: milk
LANG: PASCAL
}
program milkn;
type
 two=array[1..2]of longint;
var
 m,n,i,j,money:longint;
 milk:array[1..5000]of two;
 f1,f2:text;
procedure sort(l,r:longint);
 var i,j,x:longint;y:two;
 begin
  i:=l;j:=r;
  x:=milk[random(j-i+1)+i][1];
  repeat
   while milk[i][1]<x do
     inc(i);
   while milk[j][1]>x do
     dec(j);
   if not(i>j) then
    begin
     y:=milk[i];
     milk[i]:=milk[j];
     milk[j]:=y;
     inc(i);dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
 end;
begin
 assign(f1,'milk.in');reset(f1);
 assign(f2,'milk.out');rewrite(f2);
 randomize;
 readln(f1,n,m);
 for i:=1 to m do
  readln(f1,milk[i][1],milk[i][2]);
 close(f1);
 sort(1,m);i:=1;money:=0;
 while n<>0 do
  begin
   if milk[i][2]>=n
    then begin
          money:=milk[i][1]*n+money;n:=0;
         end
    else begin
          money:=milk[i][1]*milk[i][2]+money;
          n:=n-milk[i][2]; inc(i);
         end;
  end;
 writeln(f2,money);
 close(f2);
end.
