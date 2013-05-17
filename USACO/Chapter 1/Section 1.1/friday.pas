{
ID: dxmtb1
PROG: friday
LANG: PASCAL
}
program friday;
var
 m,n,i,j,first:longint;
 re:array[0..6]of longint;
 f1:text;
procedure count(x:longint);
 var
  i:longint;
  bo:boolean;
 begin
  if (x mod 4)=0
   then begin if (x mod 100)=0
               then  begin if (x mod 400)=0 then bo:=true
                                      else bo:=false; end
               else bo:=true;
        end
   else bo:=false;
{1}  inc(re[first]);first:=(first+31)mod 7;
{2}  inc(re[first]);if bo then first:=(first+29)mod 7 else first:=(first+28)mod 7;
{3}  inc(re[first]);first:=(first+31)mod 7;
{4}  inc(re[first]);first:=(first+30)mod 7;
{5}  inc(re[first]);first:=(first+31)mod 7;
{6}  inc(re[first]);first:=(first+30)mod 7;
{7}  inc(re[first]);first:=(first+31)mod 7;
{8}  inc(re[first]);first:=(first+31)mod 7;
{9}  inc(re[first]);first:=(first+30)mod 7;
{10} inc(re[first]);first:=(first+31)mod 7;
{11} inc(re[first]);first:=(first+30)mod 7;
{12} inc(re[first]);first:=(first+31)mod 7;
 end;
begin
 assign(f1,'friday.in');reset(f1);
 readln(f1,n);
 close(f1);
 fillchar(re,sizeof(re),0);
 first:=1;
 for i:=1900 to 1900+n-1 do
  count(i);
 assign(f1,'friday.out');rewrite(f1);
 for i:=1 to 6 do
  write(f1,re[i],' ');
 writeln(f1,re[0]);
 close(f1);
 end.