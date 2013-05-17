{
ID: dxmtb1
PROG: beads
LANG: PASCAL
}
program beads;
var
 str:array[1..350]of char;
 i,j,m,n,re,len,max,tem,a:longint;
 temp:char;
 f1:text;
function t(x:longint):longint;
 begin
  if x=0 then exit(len);
  if x=len+1 then exit(1);
  exit(x);
 end;
function make(x:longint):longint;
 var
  tem,m,n,j1,j2:longint;
  tong1,tong2:char;
 begin
  n:=t(x-1); m:=x;
  j1:=0;j2:=0;

  while str[m]='w' do
      begin m:=t(m+1);inc(j1);end;
  tong1:=str[m];
  while (str[m]=tong1)or(str[m]='w') do
      begin m:=t(m+1);inc(j1);end;

  while str[n]='w' do
      begin n:=t(n-1);inc(j2);end;
  tong2:=str[n];
  while (str[n]=tong2)or(str[n]='w') do
      begin n:=t(n-1);inc(j2);end;

  if j1+j2>=len then begin writeln(f1,len);close(f1);halt;end
                 else exit(j1+j2);
 end;
begin
 assign(f1,'beads.in');
 reset(f1);
 readln(f1,len);
 for i:=1 to len do read(f1,str[i]);
 close(f1);
 assign(f1,'beads.out');
 rewrite(f1);
 temp:='n';
 m:=0;
 for i:=1 to len do if str[i]=str[1] then else m:=m+1;
 if m=len then  begin writeln(f1,len);close(f1);halt;end;
 for i:=1 to len do
      if str[i]<>'w' then begin  temp:=str[i];break; end;
 if temp='n' then begin writeln(f1,len);close(f1);halt;end;
 i:=1;
 while ((str[i]='w') or (str[i]=temp)) and (i<=len) do inc(i);
 dec(i);
 if i=len then begin writeln(f1,len);close(f1);halt;end;
 max:=0;
 tem:=0;
 for a:=1 to len do
  begin
   tem:=make(a);
   if tem>max then max:=tem;
  end;
 writeln(f1,max);
 close(f1);
end.
