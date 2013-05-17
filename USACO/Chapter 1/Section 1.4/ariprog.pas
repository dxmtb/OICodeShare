{
ID: dxmtb1
PROG: ariprog
LANG: PASCAL
}
program ariprog;
var
 m,n,i,j,a,b,t:longint;
 flag,boo:boolean;
 bo:array[0..125000]of boolean;
 num:array[0..125000]of longint;
 f1,f2,f3:text;
procedure sort1(l,r:longint);
 var i,j,x,y:longint;
 begin
   i:=l;j:=r;
   x:=num[random(r-l+1)+l];
   repeat
    while num[i]<x do inc(i);
    while num[j]>x do dec(j);
    if not (i>j) then
     begin
      y:=num[i];
      num[i]:=num[j];
      num[j]:=y;
      inc(i);dec(j);
     end;
    until i>j;
   if l<j then sort1(l,j);
   if i<r then sort1(i,r);
 end;
begin
 assign(f1,'ariprog.in');reset(f1);
 assign(f2,'ariprog.out');rewrite(f2);
 read(f1,n,m);
 close(f1);
 fillchar(bo,sizeof(bo),false);
 t:=-1;dec(n);
 for i:=0 to m do
  for j:=0 to m do begin
   inc(t);
   num[t]:=i*i+j*j;
   if bo[num[t]]=true then dec(t) else bo[num[t]]:=true;
   end;
 sort1(0,t);
 flag:=false;
 for b:=1 to 2*m*m div n do
  for a:=0 to t do
   if num[a]<=(num[t]-b*n) then
   begin
    boo:=true;
    for i:=0 to n do
     if not bo[num[a]+i*b]
      then begin boo:=false;break;end;
    if boo then begin writeln(f2,num[a],' ',b);flag:=true;end;
   end else break;
 if not flag then writeln(f2,'NONE');
 close(f2);
end.
