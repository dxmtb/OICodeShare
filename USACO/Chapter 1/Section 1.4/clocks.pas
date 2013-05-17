{
ID: dxmtb1
PROG: clocks
LANG: PASCAL
}
program clocks;
type
 numtype=array[1..9]of integer;
 node=record
  num:numtype;
  me:array[1..9]of integer;
  end;
var
 m,n,i,j,top,a,b,tail,head:longint;
 hash:array[0..3,0..3,0..3,0..3,0..3,0..3,0..3,0..3,0..3]of boolean;
 q:array[1..270000]of node;
 temp,final,x:node;
 f1,f2:text;
procedure print;
 var i,j,k:longint;
 begin
  for i:=1 to 9 do if temp.me[i]<>0 then begin
   write(f2,i);
   for j:=2 to temp.me[i] do
    write(f2,' ',i);;
   k:=i+1;break;
   end;
  for i:=k to 9 do if temp.me[i]<>0 then
   for j:=1 to temp.me[i] do
    write(f2,' ',i);
  writeln(f2);close(f2);
  halt;
 end;
function com(a,b:numtype):boolean;
 var i:longint;
 begin
  for i:=1 to 9 do
   if not (a[i]=b[i]) then exit(false);
  exit(true);
 end;
procedure check;
 var i:longint;
 begin
  if com(temp.num,final.num) then print;
  for i:=1 to 9 do if temp.me[i]>3 then exit;
  if hash[temp.me[1],temp.me[2],temp.me[3],temp.me[4],temp.me[5],temp.me[6],temp.me[7],temp.me[8],temp.me[9]]
    then exit;
  hash[temp.me[1],temp.me[2],temp.me[3],temp.me[4],temp.me[5],temp.me[6],temp.me[7],temp.me[8],temp.me[9]]:=true;
  q[tail]:=temp;inc(tail);
  if tail>270000 then tail:=tail-270000;
 end;
begin
//////////initialization
 assign(f1,'clocks.in');reset(f1);
 assign(f2,'clocks.out');rewrite(f2);
 for i:=1 to 9 do
  begin
   read(f1,a);
   x.num[i]:=a div 3-1;
   final.num[i]:=3;
  end;
 close(f1);
 fillchar(hash,sizeof(hash),false);
 hash[0,0,0,0,0,0,0,0,0]:=true;
 head:=1;tail:=1;if com(x.num,final.num) then print;
////////////////////
 temp:=x;inc(temp.me[1]);
 temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
 temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
 check;
 temp:=x;inc(temp.me[2]);
 temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[3]:=(temp.num[3]+1) mod 4;
 temp.num[2]:=(temp.num[2]+1) mod 4;
 check;
 temp:=x;inc(temp.me[3]);
 temp.num[3]:=(temp.num[3]+1) mod 4;temp.num[6]:=(temp.num[6]+1) mod 4;
 temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
 check;
 temp:=x;inc(temp.me[4]);
 temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
 temp.num[7]:=(temp.num[7]+1) mod 4;
 check;
 temp:=x;inc(temp.me[5]);
 temp.num[6]:=(temp.num[6]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
 temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
 temp.num[8]:=(temp.num[8]+1) mod 4;
 check;
 temp:=x;inc(temp.me[6]);
 temp.num[6]:=(temp.num[6]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
 temp.num[3]:=(temp.num[3]+1) mod 4;
 check;
 temp:=x;inc(temp.me[7]);
 temp.num[7]:=(temp.num[7]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
 temp.num[8]:=(temp.num[8]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
 check;
 temp:=x;inc(temp.me[8]);
 temp.num[7]:=(temp.num[7]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
 temp.num[8]:=(temp.num[8]+1) mod 4;
 check;
 temp:=x;inc(temp.me[9]);
 temp.num[5]:=(temp.num[5]+1) mod 4;temp.num[6]:=(temp.num[6]+1) mod 4;
 temp.num[8]:=(temp.num[8]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
 check;
 while true do begin
  if tail=head then begin writeln(f2,'No Answer');close(f2);halt;end;
  temp:=q[head];inc(head);if head>270000 then head:=head-270000;
  x:=temp;
  /////////////////
  temp:=x;inc(temp.me[1]);
  temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
  temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
  check;
  temp:=x;inc(temp.me[2]);
  temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[3]:=(temp.num[3]+1) mod 4;
  temp.num[2]:=(temp.num[2]+1) mod 4;
  check;
  temp:=x;inc(temp.me[3]);
  temp.num[3]:=(temp.num[3]+1) mod 4;temp.num[6]:=(temp.num[6]+1) mod 4;
  temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
  check;
  temp:=x;inc(temp.me[4]);
  temp.num[1]:=(temp.num[1]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
  temp.num[7]:=(temp.num[7]+1) mod 4;
  check;
  temp:=x;inc(temp.me[5]);
  temp.num[6]:=(temp.num[6]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
  temp.num[2]:=(temp.num[2]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
  temp.num[8]:=(temp.num[8]+1) mod 4;
  check;
  temp:=x;inc(temp.me[6]);
  temp.num[6]:=(temp.num[6]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
  temp.num[3]:=(temp.num[3]+1) mod 4;
  check;
  temp:=x;inc(temp.me[7]);
  temp.num[7]:=(temp.num[7]+1) mod 4;temp.num[4]:=(temp.num[4]+1) mod 4;
  temp.num[8]:=(temp.num[8]+1) mod 4;temp.num[5]:=(temp.num[5]+1) mod 4;
  check;
  temp:=x;inc(temp.me[8]);
  temp.num[7]:=(temp.num[7]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
  temp.num[8]:=(temp.num[8]+1) mod 4;
  check;
  temp:=x;inc(temp.me[9]);
  temp.num[5]:=(temp.num[5]+1) mod 4;temp.num[6]:=(temp.num[6]+1) mod 4;
  temp.num[8]:=(temp.num[8]+1) mod 4;temp.num[9]:=(temp.num[9]+1) mod 4;
  check;
  end;
end.
