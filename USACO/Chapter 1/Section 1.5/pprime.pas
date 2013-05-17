{
ID: dxmtb1
PROG: pprime
LANG: PASCAL
}
program pprime;
var
 m,n,i,j,a,b,a1,b1,l,d1,d2,d3,d4,d5,code:longint;
 new:longint;
 s:string;
 f1,f2:text;
procedure check(x:longint);
 var i:longint;
 begin
  if (x<a)or(x>b) then exit;
  for i:=2 to trunc(sqrt(x)) do
   if (x mod i)=0 then exit;
  writeln(f2,x);
 end;
{function pa(x:longint):boolean;
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
 end;  }
procedure search(s1:string;l:longint;s2:string);
 var i,n:longint;s:string;
 begin
  if l=0 then begin s:=s1+s2;val(s,n,code);check(n);exit;end;
  if l=1 then begin
   s:=s1+'0'+s2;val(s,n,code);check(n);
   s:=s1+'1'+s2;val(s,n,code);check(n);
   s:=s1+'2'+s2;val(s,n,code);check(n);
   s:=s1+'3'+s2;val(s,n,code);check(n);
   s:=s1+'4'+s2;val(s,n,code);check(n);
   s:=s1+'5'+s2;val(s,n,code);check(n);
   s:=s1+'6'+s2;val(s,n,code);check(n);
   s:=s1+'7'+s2;val(s,n,code);check(n);
   s:=s1+'8'+s2;val(s,n,code);check(n);
   s:=s1+'9'+s2;val(s,n,code);check(n);exit;end;
  search(s1+'0',l-2,'0'+s2);
  search(s1+'1',l-2,'1'+s2);
  search(s1+'2',l-2,'2'+s2);
  search(s1+'3',l-2,'3'+s2);
  search(s1+'4',l-2,'4'+s2);
  search(s1+'5',l-2,'5'+s2);
  search(s1+'6',l-2,'6'+s2);
  search(s1+'7',l-2,'7'+s2);
  search(s1+'8',l-2,'8'+s2);
  search(s1+'9',l-2,'9'+s2);
 end;
begin
 assign(f1,'pprime.in');reset(f1);
 assign(f2,'pprime.out');rewrite(f2);
 readln(f1,a,b);
 close(f1);
{ for i:=2 to b do
  if p[i] then
    for j:=2 to trunc(b div i) do
     p[j*i]:=false; }
 str(a,s);
 a1:=length(s);
 str(b,s);
 b1:=length(s);
 l:=a1;
 while l<=b1 do
  begin
   if l<>1 then begin
   search('1',l-2,'1');
   search('3',l-2,'3');
   search('7',l-2,'7');
   search('9',l-2,'9'); end
   else search('',1,'');
   inc(l);
  end;
 close(f2);
end.
