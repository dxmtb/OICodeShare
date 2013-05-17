{
ID: dxmtb1
PROG: checker
LANG: PASCAL
}
program checker;
var
 m,n,i,j,re,te,upperlim:longint;
 ans:array[1..13]of longint;
 q:array[1..13,1..13]of boolean;
 co:array[1..13]of boolean;
 d1,d2:array[1..25]of boolean;
 f1,f2:text;
procedure search(x:longint);
 var i:longint;
 begin
  if x>n then begin
   inc(re);
   if re>3 then exit;
   write(f2,ans[1]);
   for i:=2 to n do
    write(f2,' ',ans[i]);
   writeln(f2);
   end
  else
  for i:=1 to n do
   if (co[i])and(q[x,i])and(d1[x+i-1])and(d2[n-x+i]) then begin
    q[x,i]:=false;
    co[i]:=false;
    d1[x+i-1]:=false;
    d2[n-x+i]:=false;
    ans[x]:=i;
    search(x+1);
    q[x,i]:=true;
    co[i]:=true;
    d1[x+i-1]:=true;
    d2[n-x+i]:=true;
    end;
 end;
//procedure test(row,ld,rd:longint);
//var
//       pos,p:longint;
//begin
//
//{ 1}   if row<>upperlim then
//{ 2}   begin
//{ 3}     pos:=upperlim and not (row or ld or rd);
//{ 4}     while pos<>0 do
//{ 5}     begin
//{ 6}         p:=pos and -pos;
//{ 7}         pos:=pos-p;
//{ 8}         test(row+p,(ld+p)shl 1,(rd+p)shr 1);
//{ 9}     end;
//{10}   end
//{11}   else inc(re);

//end;

begin
 assign(f1,'checker.in');reset(f1);
 assign(f2,'checker2.out');rewrite(f2);
 readln(f1,n);
 close(f1);
 fillchar(q,sizeof(q),true);
 fillchar(co,sizeof(co),true);
 fillchar(d1,sizeof(d1),true);
 fillchar(d2,sizeof(d2),true);
 re:=0;
 search(1);
 writeln(f2,re);
 close(f2);
end.
