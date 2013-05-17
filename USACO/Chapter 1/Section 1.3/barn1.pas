{
ID: dxmtb1
PROG: barn1
LANG: PASCAL
}
program barn1;
type
 two=array[1..2]of longint;
var
 m,n,i,j,s,c,po,p2,min,temp,former,re:longint;
 p:array[1..200]of boolean;
 qu,he:array[1..200]of two;
 f1,f2:text;
begin
 assign(f1,'barn1.in');reset(f1);
 assign(f2,'barn1.out');rewrite(f2);
 readln(f1,m,s,c);
 fillchar(p,sizeof(p),false);
 for i:=1 to c do
  begin
   readln(f1,j);
   p[j]:=true;
  end;
 close(f1);
 fillchar(qu,sizeof(qu),0);
 po:=1;
 for i:=1 to s do
  if p[i] then
    begin
     qu[po][1]:=i;
     qu[po][2]:=i;
     break;
    end;
 for i:=qu[po][1]+1 to s do
  begin
   if p[i] then
    if p[i-1]
     then qu[po][2]:=i
     else begin inc(po);qu[po][1]:=i;qu[po][2]:=i;end;
  end;
 p2:=po;
 while po>m do
  begin
   min:=1000;
   for i:=1 to p2-1 do
    begin
     temp:=qu[i+1][1]-qu[i][2];
     if (temp<min)and(temp<>0)
      then begin min:=temp;j:=i;end;
    end;
   qu[j][2]:=qu[j+1][1];
   dec(po);
  end;
 re:=qu[1][2]-qu[1][1]+1;former:=qu[1][2];
 for i:=2 to p2 do
  begin
   if qu[i][1]<>former
    then re:=re+qu[i][2]-qu[i][1]+1
    else re:=re+qu[i][2]-qu[i][1];
   former:=qu[i][2];
  end;
 writeln(f2,re);
 close(f2);
end.
