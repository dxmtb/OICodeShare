/*
ID: dxmtb
PROG: 最小密度路径
TIME: 2010.11.18
STATE: Solved
MEMO: floyd
*/
const
	oo:longint=1000000000;
var
	N,M,Q,i,j,k,a,b,w,t,X,Y:longint;
	d:array[0..55,0..55,0..55] of longint;
	re:extended;
procedure Min2(var x:extended;y:extended);
begin
	if (y<x) then x:=y;
end;
procedure Min1(var x:longint;y:longint);
begin
	if (y<x) then x:=y;
end;
begin
	assign(input,'path.in');reset(input);
	assign(output,'path.out');rewrite(output);
	read(N,M);
	for i:=0 to N do
		for j:=1 to N do
			for k:=1 to N do
				d[i][j][k]:=oo;
	for i:=1 to N do
		d[0][i][i]:=0;
	for i:=0 to M-1 do
	begin
		read(a,b,w);
		Min1(d[1][a][b],w);
	end;
	for t:=2 to N do
		for k:=1 to N do
			for i:=1 to N do
				for j:=1 to N do
					Min1(d[t][i][j],d[t-1][i][k]+d[1][k][j]);
	read(Q);
	while(Q>0) do
	begin
		dec(Q);
		read(X,Y);
		re:=oo;
		for t:=1 to N do
			Min2(re,d[t][X][Y]/t);
		if (re>=oo/1000) then writeln('OMG!')
		else writeln(re:0:3);
	end;
end.