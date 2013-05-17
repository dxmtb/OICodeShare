{
ID: dxmtb1
PROG: frac1
LANG: PASCAL
}
program frac1;
var
 m,n,i,j,num:longint;
 re:array[1..25600]of real;
 ans:array[1..25600,1..2]of longint;
 f1,f2:text;
function gcd(x,y:longint):longint;
 begin
  if y=0 then exit(x);
  if x=0 then exit(y);
  gcd:=gcd(y,x mod y);
 end;
procedure sort(l,r:longint);
 var i,j,z:longint;x,y:real;
 begin
 i:=l;j:=r;
 x:=re[random(j-i+1)+i];
 repeat
  while re[i]<x do inc(i);
  while re[j]>x do dec(j);
  if not (i>j) then begin
  z:=ans[i,1];
  ans[i,1]:=ans[j,1];
  ans[j,1]:=z;
  z:=ans[i,2];
  ans[i,2]:=ans[j,2];
  ans[j,2]:=z;
  y:=re[i];
  re[i]:=re[j];
  re[j]:=y;
  inc(i);dec(j);
  end;
 until i>j;
 if i<r then sort(i,r);
 if l<j then sort(l,j);
 end;
begin
 assign(f1,'frac1.in');reset(f1);
 assign(f2,'frac1.out');rewrite(f2);
 readln(f1,n);
 close(f1);
 num:=0;
 for i:=0 to n-1 do
  for j:=i+1 to n do
   begin
    if gcd(i,j)=1 then begin
     inc(num);
     ans[num,1]:=i;
     ans[num,2]:=j;
     re[num]:=i/j;
    end;
   end;
 randomize;
 sort(1,num);
 inc(num);
 ans[num,1]:=1;
 ans[num,2]:=1;
 for i:=1 to num do
  writeln(f2,ans[i,1],'/',ans[i,2]);
 close(f2);
end.
