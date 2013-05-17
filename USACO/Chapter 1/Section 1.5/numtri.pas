{
ID: dxmtb1
PROG: numtri
LANG: PASCAL
}
program numtri;
var
 m,n,i,j,r,re:longint;
 num,ans:array[0..1000,0..1000]of longint;
 f1,f2:text;
function max(a,b:longint):longint;
 begin
  if a>b then max:=a else max:=b;
 end;
begin
 assign(f1,'numtri.in');reset(f1);
 assign(f2,'numtri.out');rewrite(f2);
 readln(f1,r);
 fillchar(ans,sizeof(ans),0);
 readln(f1,num[1,1]);
 ans[1,1]:=num[1,1];
 for i:=2 to r do
  for j:=1 to i do
   begin
    read(f1,num[i,j]);
    ans[i,j]:=max(ans[i-1,j],ans[i-1,j-1])+num[i,j];
   end;
 close(f1);
 re:=0;
 for i:=1 to r do
  if ans[r,i]>re then re:=ans[r,i];
 writeln(f2,re);
 close(f2);
end.
