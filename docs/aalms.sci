function[w,y,e,J]=aalms(x,dn,mu,M)
    N=length(x);
    y=zeros(1,N);
    w=zeros(1,M);
    printf('N=%d\n', N);
    for n=M:N
        x1=x(n:-1:n-M+1);
        disp(w)
        disp(x1)
        y(n)=w*x1';
        e(n)=dn(n)-y(n);
        w=w+2*mu*e(n)*x1;
        printf('n=%d, dn(n)=%f, y(n)=%f, e(n)=%f\n', n, dn(n), y(n), e(n));
    end;
    J=e.^2;
endfunction
[w,y,e,J]=aalms([zeros(1,M-1),x],[zeros(1,M-1),s],mu,M);
