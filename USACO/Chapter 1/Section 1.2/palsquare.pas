{
ID: dxmtb1
PROG: palsquare
LANG: PASCAL
}
program pal;
const
 list='0123456789ABCDEFGHIJKLMN';
var
 m,n,i,j,p,q,code,s,b:longint;

 f1,f2:text;
procedure init;
 begin
  assign(f1,'palsquare.in');reset(f1);
  assign(f2,'palsquare.out');rewrite(f2);
 end;
function change(num,be:longint):string;
 var chr:char;temp:string;a:longint;
 begin
  if be=10 then
      begin str(num,temp);exit(temp);end;
  temp:='';
  repeat
   a:=num mod be;
   temp:=list[a+1]+temp;
   num:=(num-a) div be;
  until num=0;
  exit(temp);
 end;
function check(str:string):boolean;
 var h,t:longint;
 begin
  t:=length(str);h:=1;
  while h<t do
    if str[h]=str[t] then begin inc(h);dec(t); end
                        else exit(false);
  check:=true;
 end;
begin
 init;
 readln(f1,b);
 close(f1);
 for i:=1 to 300 do
   if check(change(i*i,b))
     then writeln(f2,change(i,b),' ',change(i*i,b));
 close(f2);
end.
