{
ID: dxmtb1
PROG: calfflac
LANG: PASCAL
}
program calfflac;
var
 m,n,i,j,p,l,r,len1,len2,ml,mr,max:longint;
 te:array[1..40000]of char;
 f1,f2:text;
begin
 assign(f1,'calfflac.in');reset(f1);
 assign(f2,'calfflac.out');rewrite(f2);
 p:=0;
 while not eof(f1) do
  begin inc(p);read(f1,te[p]);end;
 close(f1);
 max:=0;
 for i:=2 to p do
  begin
   l:=i-1;r:=i+1;len1:=1;len2:=0;
   while (l>0) and (r<p) do
    begin
      if ((te[l]>='a')and(te[l]<='z')) or ((te[l]>='A')and (te[l]<='Z'))
       then if ((te[r]>='a')and(te[r]<='z')) or ((te[r]>='A')and(te[r]<='Z'))
              then if (te[l]=te[r])or(abs(ord(te[l])-ord(te[r]))=32)
                      then begin len1:=len1+2;inc(r);dec(l);end
                      else break
              else inc(r)
       else dec(l);
    end;
   if len1>max then begin max:=len1;ml:=l+1;mr:=r-1;end;
   l:=i-1;r:=i;
   while (l>0) and (r<p) do
    begin
      if ((te[l]>='a')and(te[l]<='z')) or ((te[l]>='A')and (te[l]<='Z'))
       then if ((te[r]>='a')and(te[r]<='z')) or ((te[r]>='A')and(te[r]<='Z'))
              then if (te[l]=te[r])or(abs(ord(te[l])-ord(te[r]))=32)
                      then begin len2:=len2+2;inc(r);dec(l);end
                      else break
              else inc(r)
       else dec(l);
    end;
   if len2>max then begin max:=len2;ml:=l+1;mr:=r-1;end;
  end;
  while not(((te[ml]>='a')and(te[ml]<='z')) or ((te[ml]>='A')and (te[ml]<='Z')))
    do inc(ml);
  while not(((te[mr]>='a')and(te[mr]<='z')) or ((te[mr]>='A')and (te[mr]<='Z')))
    do dec(mr);
  max:=0;
  for i:=ml to mr do
    if ((te[i]>='a')and(te[i]<='z')) or ((te[i]>='A')and (te[i]<='Z'))
      then inc(max);
  writeln(f2,max);
  for i:=ml to mr do
   write(f2,te[i]);
  writeln(f2);
  close(f2);
end.

