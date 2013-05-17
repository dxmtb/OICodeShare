{
ID: dxmtb1
PROG: milk3
LANG: PASCAL
}
program milk3;
type
 node=array[1..3]of integer;
var
 m,n,i,j,h,top:longint;
 cap:array[1..3]of integer;
 ha:array[1..8000]of node;
 re:array[0..20]of boolean;
 temp:node;
 f1,f2:text;
procedure print;
 var i,j:longint;
 begin
  for i:=0 to 20 do
   if re[i] then begin write(f2,i);j:=i;break;end;
  for i:=j+1 to 20 do
   if re[i] then write(f2,' ',i);
  writeln(f2);
  close(f2);
 end;
function change(x:node;a,b:integer):node;
 var temp:node;
 begin
  if (x[a]+x[b])>cap[b]
   then begin temp[a]:=x[a]-cap[b]+x[b];temp[b]:=cap[b]end
   else begin temp[a]:=0;temp[b]:=x[a]+x[b];end;
  temp[6-a-b]:=x[6-a-b];
  exit(temp);
 end;
function compare(a,b:node):boolean;
 var i:longint;bo:boolean;
 begin
  for i:=1 to 3 do
   if not(a[i]=b[i]) then exit(true);
  exit(false);
 end;
procedure search(x:node);
 var i:longint;temp:node;
 begin
  for i:=1 to h-1 do
   if not compare(x,ha[i])
    then exit;
  ha[h]:=x;
  inc(h);
  if x[1]=0 then
   re[x[3]]:=true;
  if x[1]<>0 then
   begin
    if x[2]<>cap[2] then
     search(change(x,1,2));
    if x[3]<>cap[3] then
     search(change(x,1,3));
   end;
  if x[2]<>0 then
   begin
    if x[1]<>cap[1] then
     search(change(x,2,1));
    if x[3]<>cap[3] then
     search(change(x,2,3));
   end;
  if x[3]<>0 then
   begin
    if x[2]<>cap[2] then
     search(change(x,3,2));
    if x[1]<>cap[3] then
     search(change(x,3,1));
   end;
 end;
begin
 assign(f1,'milk3.in');reset(f1);
 assign(f2,'milk3.out');rewrite(f2);
 readln(f1,cap[1],cap[2],cap[3]);
 close(f1);
 fillchar(re,sizeof(re),false);
 temp[1]:=0;
 temp[2]:=0;
 temp[3]:=cap[3];
 h:=1;
 search(temp);
 print;
end.
