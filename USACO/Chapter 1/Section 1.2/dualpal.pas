{
ID: dxmtb1
PROG: dualpal
LANG: PASCAL
}
program pal;
const
 list='0123456789ABCDE';
var
 m,n,i,j,p,q,code,s:longint;

 f1,f2:text;
procedure init;
 begin
  assign(f1,'dualpal.in');reset(f1);
  assign(f2,'dualpal.out');rewrite(f2);
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
 readln(f1,n,s);
 close(f1);
 m:=0;s:=s+1;
 while m<n do
  begin
   p:=0;
   if check(change(s,10)) then inc(p);
   for i:=2 to 9 do
    if check(change(s,i)) then
      begin inc(p);
            if p>1 then begin writeln(f2,s);m:=m+1; break;end
      end;
   inc(s);
  end;
  close(f2);
end.
