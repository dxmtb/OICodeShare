{
ID: dxmtb1
PROG: crypt1
LANG: PASCAL
}
program crypt1;
var
 m,n,i,j,re:longint;
 num:array[1..9]of boolean;
 f1,f2:text;
function check(x:longint):boolean;
 var tem:longint;bo:boolean;
 begin
  while x<>0 do
   begin
    bo:=false;
    tem:=x mod 10;
    if not num[tem] then exit(false);
    x:=x div 10;
   end;
  check:=true;
 end;
begin
 assign(f1,'crypt1.in');reset(f1);
 assign(f2,'crypt1.out');rewrite(f2);
 readln(f1,n);
 fillchar(num,sizeof(num),false);
 for i:=1 to n do
  begin read(f1,m);num[m]:=true;end;
 close(f1);
 re:=0;
 for i:=100 to 999 do
  for j:=10 to 99 do
   if (i*(j mod 10)<1000)and(i*(j div 10)<1000)and(i*j<10000)
    and(check(i))and(check(j))and(check(i*(j mod 10)))and(check(i*(j div 10)))
    and(check(i*j))
     then inc(re);
  writeln(f2,re);
  close(f2);
end.

