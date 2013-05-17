{
ID: dxmtb1
PROG: milk2
LANG: PASCAL
}
program milk2;
var
 n,i,j,m,p,q,temi,a,b:longint;
 qu,re:array[1..5000,1..2]of longint;
 f1:text;
procedure init;
 begin
  assign(f1,'milk2.in');
  reset(f1);
 end;
begin
 init;
 readln(f1,n,qu[1,1],qu[1,2]);
 for i:=2 to n do
  begin
   readln(f1,a,b);
   make(a,b);
  end;
 close(f1);
 assign(f1,'milk2.out');rewrite(f1);
 for i:=

end.