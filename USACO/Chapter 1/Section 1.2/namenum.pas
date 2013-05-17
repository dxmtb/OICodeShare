{
ID: dxmtb1
PROG: namenum
LANG: PASCAL
}
program namenum;
var
 n,i,j,m,a,b,code,len:longint;
 nam:array[1..100]of string[12];
 num:array[1..12]of byte;
 ch:char;
 strt:string;
 you:boolean;
 f1,f2:text;
procedure init;
 begin
  assign(f1,'namenum.in');reset(f1);
  assign(f2,'namenum.out');rewrite(f2);
  n:=0;you:=false;
 end;
procedure check(str:string);
 var chrt:char;
 begin
  for i:=1 to len do
   begin
    chrt:=str[i];
     case chrt of
      'A'..'C':if num[i]=2 then else break;
      'D'..'F':if num[i]=3 then else break;
      'G'..'I':if num[i]=4 then else break;
      'J'..'L':if num[i]=5 then else break;
      'M'..'O':if num[i]=6 then else break;
      'P':if num[i]=7 then else break;
      'R'..'S':if num[i]=7 then else break;
      'T'..'V':if num[i]=8 then else break;
      'W'..'Y':if num[i]=9 then else break;
      else break;
      end;
    if i=len then begin writeln(f2,str);you:=true;end;
   end;
 end;
begin
 init;
 while not eof(f1) do
  begin
   read(f1,ch);
   if (ch>='2')and(ch<='9')
    then begin
         inc(n); val(ch,num[n],code);
         end
    else break;
  end;
 close(f1);
 assign(f1,'dict.txt');reset(f1);
 while not eof(f1) do
  begin
   readln(f1,strt);
   len:=length(strt);
   if len=n then check(strt);
  end;
 if you=false
   then writeln(f2,'NONE')
   else;
 close(f1);
 CLOSE(F2);
end.
