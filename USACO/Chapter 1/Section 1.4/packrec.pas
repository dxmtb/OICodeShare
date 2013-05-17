{
ID: dxmtb1
PROG: packrec
LANG: PASCAL
}
program packrec;
uses math;
var
 m,n,i,j,x,y,l,w,s,p,mins,k,q,o,e,r:longint;
 sq1,sq2,s1,s2:array[1..4]of longint;
 hash:array[1..200,1..200]of boolean;
 f1,f2:text;
procedure check;
 var a,b,i:longint;
 begin
  s:=w*l;
  if s<mins then begin
    mins:=s;if mins=36 then readln(i);
    fillchar(hash,sizeof(hash),false);
    a:=min(w,l);b:=w+l-a;hash[a,b]:=true;
    end
   else if s=mins then begin
    a:=min(w,l);b:=w+l-a;
    if hash[a,b] then exit else hash[a,b]:=true;
    end;
 end;
procedure change(a,b,c,d:integer);
 var t:longint;
 begin
  sq1:=s1;sq2:=s2;
  if a=1 then begin t:=sq2[1];sq2[1]:=sq1[1];sq1[1]:=t;end;
  if b=1 then begin t:=sq2[2];sq2[2]:=sq1[2];sq1[2]:=t;end;
  if c=1 then begin t:=sq2[3];sq2[3]:=sq1[3];sq1[3]:=t;end;
  if d=1 then begin t:=sq2[4];sq2[4]:=sq1[4];sq1[4]:=t;end;
 end;
function min(a,b:longint):longint;begin if a>b then min:=b else min:=a;end;
function max(a,b:longint):longint;begin if a>b then max:=a else max:=b;end;
procedure method2(a:longint);
 var bo:array[1..4]of boolean;b,c,d,i,q,o,e,r:longint;
 begin
 for q:=0 to 1 do
  for o:=0 to 1 do
   for e:=0 to 1 do
    for r:=0 to 1 do
     begin
      change(q,o,e,r);
      fillchar(bo,sizeof(bo),true);
      bo[a]:=false;
      for i:=1 to 4 do if bo[i] then begin bo[i]:=false;b:=i;break end;
      for i:=b+1 to 4 do if bo[i] then begin bo[i]:=false;c:=i;break end;
      for i:=c+1 to 4 do if bo[i] then begin bo[i]:=false;d:=i;break end;
      l:=max(max(sq2[b],sq2[c]),sq2[d])+sq1[a];
      w:=max(sq2[a],sq1[b]+sq1[c]+sq1[d]);
      check;
     end;
 end;
procedure method3(a,b,c,d:longint);
 var q,o,e,r:longint;
 begin
 for q:=0 to 1 do
  for o:=0 to 1 do
   for e:=0 to 1 do
    for r:=0 to 1 do
     begin
      change(q,o,e,r);
      l:=max(sq2[d],max(sq2[a],sq2[b])+sq1[c]);
      w:=max(sq1[a]+sq1[b],sq2[c])+sq1[d];
      check;
     end;
 end;
procedure method4(a,b:longint);
 var bo:array[1..4]of boolean;c,d,i,q,o,e,r:longint;
 begin
 for q:=0 to 1 do
  for o:=0 to 1 do
   for e:=0 to 1 do
    for r:=0 to 1 do
     begin
      change(q,o,e,r);
      fillchar(bo,sizeof(bo),true);
      bo[a]:=false;bo[b]:=false;
      for i:=1 to 4 do if bo[i] then begin c:=i;break end;
      d:=10-a-b-c;
      l:=max(sq2[a],max(sq2[d],sq2[b]+sq2[c]));
      w:=sq1[a]+sq1[d]+max(sq1[c],sq1[b]);
      check;
     end;
 end;
procedure method6(a,b,c,d:longint);
 var q,o,e,r:longint;
 begin
 for q:=0 to 1 do
  for o:=0 to 1 do
   for e:=0 to 1 do
    for r:=0 to 1 do
     begin
     change(q,o,e,r);
     if sq1[a]>sq1[b] then continue;
     l:=max(sq2[b]+sq2[a],sq1[c]+max(sq2[b],sq2[d]));
     w:=max(sq1[a]+sq2[c],sq1[b]+sq1[d]);
     check;
     end;
 end;
begin
 assign(f1,'packrec.in');reset(f1);
 assign(f2,'packrec.out');rewrite(f2);
 for i:=1 to 4 do
  begin
   readln(f1,x,y);
   if x>y then begin sq1[i]:=y;sq2[i]:=x;end
    else begin sq2[i]:=y;sq1[i]:=x;end;
  end;
 close(f1);
 s1:=sq1;s2:=sq2;mins:=maxlongint;
 fillchar(hash,sizeof(hash),false);
//====1====
 for q:=0 to 1 do
  for o:=0 to 1 do
   for e:=0 to 1 do
    for r:=0 to 1 do
     begin
      change(q,o,e,r);
      l:=0;
      for i:=1 to 4 do inc(l,sq1[i]);
      w:=maxintvalue(sq2);
      check;
     end;
//====2====
 for i:=1 to 4 do
  method2(i);
//====3=====
 for i:=1 to 4 do
  for j:=1 to 4 do
   if i<>j then
    for k:=1 to 4 do
     if (i<>k)and(j<>k) then
      method3(i,j,k,10-i-j-k);
//====4=====
 for i:=1 to 4 do
  for j:=1 to 4 do
   if i<>j then
    method4(i,j);
//====6=====
 for i:=1 to 4 do
  for j:=1 to 4 do
   if i<>j then
    for k:=1 to 4 do
     if (i<>k)and(j<>k) then
      method6(i,j,k,10-i-j-k);
//==========
 writeln(f2,mins);
 for i:=1 to 200 do
  for j:=1 to 200 do
   if hash[i,j] then
    writeln(f2,i,' ',j);
 close(f2);
end.
