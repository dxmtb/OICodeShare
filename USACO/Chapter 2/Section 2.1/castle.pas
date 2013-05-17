{
ID: dxmtb1
PROG: castle
LANG: PASCAL
}
program castle;
uses math;
label 1;
var
 m,n,i,j,k,temp,x,num,maxs,mcs,rx,ry:longint;
 rz:char;
 gra:array[0..51,0..51,1..4]of boolean;
 g:array[1..2500,1..2500]of boolean;
 b:array[1..2500]of integer;
 s:array[1..2500]of longint;
 f1,f2:text;
procedure search(x:integer);
 var i:longint;
 begin
  b[x]:=num;
  inc(s[num]);
  for i:=1 to n*m do
   if g[i,x] and (b[i]=-1)then
    search(i);
 end;
begin
 assign(f1,'castle.in');reset(f1);
 assign(f2,'castle.out');rewrite(f2);
 readln(f1,m,n);
 fillchar(gra,sizeof(gra),true);
 fillchar(g,sizeof(g),false);
 for i:=1 to n do
  for j:=1 to m do
   begin
    read(f1,x);
    temp:=x mod 2;
    if temp=0 then gra[i,j,2]:=false;
    x:=x shr 1;
    temp:=x mod 2;
    if temp=0 then gra[i,j,1]:=false;
    x:=x shr 1;
    temp:=x mod 2;
    if temp=0 then gra[i,j,4]:=false;
    x:=x shr 1;
    temp:=x mod 2;
    if temp=0 then gra[i,j,3]:=false;
   end;
 close(f1);
 fillchar(b,sizeof(b),-1);
 fillchar(s,sizeof(s),0);
 for i:=1 to n do
  for j:=1 to m do
   begin
    if not gra[i,j,1] and not gra[i-1,j,3] then
     begin g[(i-1)*m+j,(i-2)*m+j]:=true;g[(i-2)*m+j,(i-1)*m+j]:=true;end;
    if not gra[i,j,2] and not gra[i,j-1,4] then
     begin g[(i-1)*m+j,(i-1)*m+j-1]:=true;g[(i-1)*m+j-1,(i-1)*m+j]:=true;end;
    if not gra[i,j,3] and not gra[i+1,j,1] then
     begin g[(i-1)*m+j,i*m+j]:=true;g[i*m+j,(i-1)*m+j]:=true;end;
    if not gra[i,j,4] and not gra[i,j+1,2] then
     begin g[(i-1)*m+j,(i-1)*m+j+1]:=true;g[(i-1)*m+j+1,(i-1)*m+j]:=true;end;
   end;
 num:=0;
 for i:=1 to n*m do
  if b[i]=-1 then
   begin
    inc(num);
    b[i]:=num;
    search(i);
   end;
 maxs:=maxintvalue(s);
 writeln(f2,num);
 writeln(f2,maxs);
////////////////////////
 mcs:=0;
  for j:=1 to m do
   for i:=n downto 1 do
    begin
     {k=1}
     if (i=1) or (b[(i-1)*m+j]=b[(i-2)*m+j]) then goto 1;
     temp:=s[b[(i-1)*m+j]]+s[b[(i-2)*m+j]];
     if temp>mcs then begin mcs:=temp;rx:=i;ry:=j;rz:='N'end;
     {k=4}
1:   if (j=m) or (b[(i-1)*m+j]=b[(i-1)*m+j+1])then continue;
     temp:=s[b[(i-1)*m+j]]+s[b[(i-1)*m+j+1]];
     if temp>mcs then begin mcs:=temp;rx:=i;ry:=j;rz:='E'end;
    end;
 writeln(f2,mcs);
 writeln(f2,rx,' ',ry,' ',rz);
 close(f2);
end.
