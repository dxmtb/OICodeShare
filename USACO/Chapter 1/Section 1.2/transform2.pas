{
ID: dxmtb1
PROG: transform
LANG: PASCAL
}
program transform;
type
 map=array[1..10,1..10]of byte;
var
 x,y,m,n,p,q:longint;
 map1,map2,mpt:map;
 ch:char;
 f1,f2:text;
 note:boolean;
function turn(mapx:map):map;
 var mapt:map; i,j:longint;
 begin
  for i:=1 to n do
   for j:=1 to n do
    mapt[i,j]:=mapx[j,n+1-i];
  exit(mapt);
 end;
function fan(mapx:map):map;
 var mapt:map; i,j:longint;
 begin
  for i:=1 to n do
   for j:=1 to n do
    mapt[i,j]:=mapx[n-i+1,j];
  exit(mapt);
 end;
procedure tran(way:longint);
 begin
  case way of
   1:mpt:=turn(map1);
   2:mpt:=turn(turn(map1));
   3:mpt:=turn(turn(turn(map1)));
   4:mpt:=fan(map1);
   51:mpt:=turn(fan(map1));
   52:mpt:=turn(turn(fan(map1)));
   53:mpt:=turn(turn(turn(fan(map1))));
   6:mpt:=map1;
   7:begin writeln(f2,7);close(f2);halt;end;
   end;{case}
 end;
{=========================================}
begin
 assign(f1,'transform.in');reset(f1);
 assign(f2,'transform.out');rewrite(f2);
 readln(f1,n);
 for y:=1 to n do
  begin
  for x:=1 to n do
   begin
   read(f1,ch);
   if ch='@'then map1[x,y]:=1 else map1[x,y]:=2;
   end;
  readln(f1);
  end;
 for y:=1 to n do
  begin
  for x:=1 to n do
   begin
   read(f1,ch);
   if ch='@'then map2[x,y]:=1 else map2[x,y]:=2;
   end;
  readln(f1);
  end;
 close(f1);
 for x:=1 to 4 do
    begin
    tran(x);
    note:=true;
    for y:=1 to n do
     for m:=1 to n do
      if mpt[y,m]=map2[y,m]
        then
        else begin note:=false;break;end;
    if note
       then
         begin
          writeln(f2,x);close(f2);halt;
         end;
    end;
  for x:=51 to 53 do
    begin
    tran(x);
    note:=true;
    for y:=1 to n do
     for m:=1 to n do
      if mpt[y,m]=map2[y,m]
        then
        else begin note:=false;break;end;
    if note
       then
         begin
          writeln(f2,5);close(f2);halt;
         end;
    end;
  for x:=6 to 7 do
    begin
    tran(x);
    note:=true;
    for y:=1 to n do
     for m:=1 to n do
      if mpt[y,m]=map2[y,m]
        then
        else begin note:=false;break;end;
    if note
       then
         begin
          writeln(f2,x);close(f2);halt;
         end;
    end;
    close(f1);
    close(f2);
end.
