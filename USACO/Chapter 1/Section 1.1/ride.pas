{
ID: dxmtb1
PROG: ride
LANG: PASCAL
}
program ride;
var
 str1,str2:string;
 l1,l2,j1,j2,i:longint;
 f1:text;
begin
 assign(f1,'ride.in');reset(f1);
 readln(f1,str1);
 readln(f1,str2);
 close(f1);
 assign(f1,'ride.out');rewrite(f1);
 l1:=length(str1);
 l2:=length(str2);
 j1:=1;j2:=1;
 for i:=1 to l1 do
  j1:=j1*(ord(str1[i])-64);
 for i:=1 to l2 do
  j2:=j2*(ord(str2[i])-64);
 if (j1 mod 47)=(j2 mod 47)
  then writeln(f1,'GO')
  else writeln(f1,'STAY');
 close(f1);
 end.
