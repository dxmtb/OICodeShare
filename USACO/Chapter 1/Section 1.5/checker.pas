{
ID: dxmtb1
PROG: checker
LANG: PASCAL
}
program checker;
var
 m,n,i,j,re:longint;
 ans:array[1..13]of longint;
 co,ro:array[1..13]of boolean;
 d1,d2:array[1..25]of boolean;
 f1,f2:text;
procedure search(x:longint);
 var i:longint;
 begin
  if re=3 then exit;
  if x>n then begin
   inc(re);
   if re>3 then exit;
   write(f2,ans[1]);
   for i:=2 to n do
    write(f2,' ',ans[i]);
   writeln(f2);
   end
  else
  for i:=1 to n do
   if (co[i])and(d1[x+i-1])and(d2[n-x+i]) then begin
    co[i]:=false;
    d1[x+i-1]:=false;
    d2[n-x+i]:=false;
    ans[x]:=i;
    search(x+1);
    co[i]:=true;
    d1[x+i-1]:=true;
    d2[n-x+i]:=true;
    end;
 end;
procedure search2(x:longint);
 var i:longint;
 begin
  if x>n then inc(re,2)
  else
  for i:=1 to n do
   if (co[i])and(d1[x+i-1])and(d2[n-x+i]) then begin
    co[i]:=false;
    d1[x+i-1]:=false;
    d2[n-x+i]:=false;
    search2(x+1);
    co[i]:=true;
    d1[x+i-1]:=true;
    d2[n-x+i]:=true;
    end;
 end;
procedure search3(x:longint);
 var i:longint;
 begin
  if not ro[x] then begin search3(x+1);exit end;
  if x>n then inc(re,8)
  else
  for i:=1 to n do
   if (co[i])and(d1[x+i-1])and(d2[n-x+i]) then begin
    co[i]:=false;
    d1[x+i-1]:=false;
    d2[n-x+i]:=false;
    ans[x]:=i;
    search3(x+1);
    co[i]:=true;
    d1[x+i-1]:=true;
    d2[n-x+i]:=true;
    ans[x]:=0;
    end;
 end;
procedure search4(x:longint);
 var i:longint;
 begin
  if not ro[x] then begin search4(x+1);exit end;
  if x>n then inc(re)
  else
  for i:=1 to n do
   if (co[i])and(d1[x+i-1])and(d2[n-x+i]) then begin
    co[i]:=false;
    d1[x+i-1]:=false;
    d2[n-x+i]:=false;
    ans[x]:=i;
    search4(x+1);
    co[i]:=true;
    d1[x+i-1]:=true;
    d2[n-x+i]:=true;
    ans[x]:=0;
    end;
 end;
begin
 assign(f1,'checker.in');reset(f1);
 assign(f2,'checker.out');rewrite(f2);
 readln(f1,n);
 close(f1);
 fillchar(co,sizeof(co),true);
 fillchar(ro,sizeof(ro),true);
 fillchar(d1,sizeof(d1),true);
 fillchar(d2,sizeof(d2),true);
 re:=0;
 search(1);fillchar(ans,sizeof(ans),0);
 re:=0;
 if n mod 2 =0 then begin
  for i:=1 to n shr 1 do
   if (co[i])and(d1[1+i-1])and(d2[n-1+i]) then begin
    co[i]:=false;
    d1[1+i-1]:=false;
    d2[n-1+i]:=false;
    search2(2);
    co[i]:=true;
    d1[1+i-1]:=true;
    d2[n-1+i]:=true;
    end end
  else begin
    for i:=1 to (n shr 1)-1 do
      begin
       ro[(n shr 1)+1]:=false;
       co[i]:=false;
       d1[n div 2+i]:=false;
       d2[n-n div 2-1+i]:=false;
       ans[n div 2+1]:=i;
       for j:=i+1 to n div 2 do
        if (ro[j])and(co[n div 2+1])and(d1[j+n div 2])
         and(d2[n+n div 2+1-j]) then
          begin
          ro[j]:=false;
          co[n div 2+1]:=false;
          d1[j+n div 2]:=false;
          d2[n+n div 2+1-j]:=false;
          ans[j]:=n div 2+1;
          search3(1);
          ro[j]:=true;
          co[n div 2+1]:=true;
          d1[j+n div 2]:=true;
          d2[n+n div 2+1-j]:=true;
          ans[j]:=0;
          end;
       ro[n div 2+1]:=true;
       co[i]:=true;
       d1[n div 2+i]:=true;
       d2[n-n div 2-1+i]:=true;
       ans[n div 2+1]:=0;
      end;
       ro[(n shr 1)+1]:=false;
       co[(n shr 1)+1]:=false;
       d1[(n shr 1)+1+(n shr 1)]:=false;
       d2[n]:=false;
       ans[(n shr 1)+1]:=(n shr 1)+1;
       search4(1);
      end;
 writeln(f2,re);
 close(f2);
end.
