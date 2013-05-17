{
ID: dxmtb1
PROG: gift1
LANG: PASCAL
}
program gift1;
var
 np,i,j,m,n,k:longint;
 nam:array[1..10]of string[15];
 money,send,reci:array[1..10]of longint;
 amo:array[1..10]of byte;
 resu:array[1..10]of longint;
 tem2:longint;
 tem1:string;
 f1:text;
function getnum(x:string):longint;
 var i:longint;
 begin
  for i:=1 to n do if nam[i]=x then exit(i);
 end;
begin
 fillchar(reci,sizeof(reci),0);
 assign(f1,'gift1.in');reset(f1);
 readln(f1,n);
 for i:= 1 to n do
  readln(f1,nam[i]);
 for i:=1 to n do
  begin
   readln(f1,tem1);
   k:=getnum(tem1);
   readln(f1,money[k],amo[k]);
   if amo[k]<>0 then begin
   send[k]:=money[k]-(money[k] mod amo[k]);
   tem2:=money[k] div amo[k];
   for j:=1 to amo[k] do
    begin
    readln(f1,tem1);
    inc(reci[getnum(tem1)],tem2);
    end; end;{if}
  end;
 close(f1);
 for i:=1 to n do
   resu[i]:=reci[i]-send[i];
 assign(f1,'gift1.out');rewrite(f1);
 for i:=1 to n do
  writeln(f1,nam[i],' ',resu[i]);
 close(f1);
end.
