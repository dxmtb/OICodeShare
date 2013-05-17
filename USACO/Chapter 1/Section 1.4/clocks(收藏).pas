{
ID: dxmtb1
PROG: clocks
LANG: PASCAL
}
program clocks;
const
  INV:array[3..12] of byte =(1, 0, 0, 2, 0, 0, 3, 0, 0, 0);

var inp,ou:text;
    a,b,c,d,e,f,g,h,i:integer;
    ax,bx,cx,dx,ex,fx,gx,hx,ix,l:integer;
    t,an:array[1..100] of integer;
begin
    assign(inp,'clocks.in');
    reset (inp);
    readln(inp, ax, bx, cx);
    readln(inp, dx, ex, fx);
    readln(inp, gx, hx, ix);close(inp);
    a:=inv[ax]; b:=inv[bx]; c:=inv[cx]; d:=inv[dx];
    e:=inv[ex]; f:=inv[fx]; g:=inv[gx]; h:=inv[hx];
    i:=inv[ix];
    t[1] := (8+a+2*b+c+2*d+2*e-f+g-h) mod 4;
    t[2] := (a+b+c+d+e+f+2*g+    2*i) mod 4;
    t[3] := (8+  a+2*b+  c  -d+2*e+2*f      -h+  i) mod 4;
    t[4] := (    a+  b+2*c+  d+  e+      g+  h+2*i) mod 4;
    t[5] := (4+  a+2*b+  c+2*d  -e+2*f+  g+2*h+  i) mod 4;
    t[6] := (  2*a+  b+  c+      e+  f+2*g+  h+  i) mod 4;
    t[7] := (8+  a  -b+    2*d+2*e  -f+  g+2*h+  i) mod 4;
    t[8] := (  2*a+    2*c+  d+  e+  f+  g+  h+  i) mod 4;
    t[9] := (8      -b+  c  -d+2*e+2*f+  g+2*h+  i) mod 4;
    assign(ou, 'clocks.out'); rewrite(ou);
    for a := 1 to 9 do
	for b := 1 to t[a] do Begin
	    inc(l);
	    an[l]:=a;
	end;
    for a:=1 to l-1 do
	write(ou,an[a],' ');
    write(ou,an[l]);
    writeln(ou); close(ou)
end.

