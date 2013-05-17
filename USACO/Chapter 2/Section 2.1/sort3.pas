{
ID: dxmtb1
PROG: sort3
LANG: PASCAL
}
program sort3;
const maxn=1000;
var
 n,i,j:longint;
 num:array[1..maxn]of longint;
 t:array[0..3]of longint;
 flag:boolean;
 f1,f2:text;
procedure change(a,b:longint);
 var x:longint;
 begin
  x:=num[a];
  num[a]:=num[b];
  num[b]:=x;
 end;
function search(i:longint):longint;
 var j:longint;
 begin
  if (i>n) then exit(0);
  if(t[num[i]-1]<i)and(i<=t[num[i]])
   then exit(search(i+1));
  for j:=i+1 to n do
   if(t[num[j]-1]<i)and(i<=t[num[j]])
     and(t[num[i]-1]<j)and(j<=t[num[i]])
      then begin
       change(i,j);
       exit(search(i+1)+1);
       end;
  for j:=i+1 to n do
   if(t[num[j]-1]<i)and(i<=t[num[j]])
    and not((t[num[j]-1]<j)and(j<=t[num[j]]))
    then begin
      change(i,j);exit(search(i+1)+1);
      break;
     end;
 end;
begin
 assign(f1,'sort3.in');reset(f1);
 assign(f2,'sort3.out');rewrite(f2);
 fillchar(t,sizeof(t),0);
 readln(f1,n);
 for i:=1 to n do begin
  readln(f1,num[i]);
  inc(t[num[i]]);
  end;
 close(f1);
 t[0]:=0;
 inc(t[2],t[1]);
 inc(t[3],t[2]);
 writeln(f2,search(1));
 close(f2);
end.
