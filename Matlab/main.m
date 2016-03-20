clear, clc
%diary log.txt

p(1) = 8.4E-6;
p(2) = 6.6667E-4;
p(3) = 1.7778E-5;
p(4) = 0.01;
p(5) = 2;
p(6) = 10; %100

count = 1;
j = 1; l = 1;
h2 = 1; h3 = 1;
flag2 = 0; flag3 = 0;
oldstable2 = 1; oldstable3 = 1;

syms x1 x2 t1 t2 t3 T X
T = [t1 t2 t3];

for k = 1:1:9
    
    y1 = (p(1)*x2-x1*x2+x1-x1^2)/p(2)-p(4)*x1;
    y2 = (-p(1)*x2-x1*x2+p(5)*x1/(p(4)+1))/p(3)+p(4)*(p(6)-x2);
    S = solve(y1,y2,x1,x2);
    x3 = S.x1/(p(4)+1);
    fprintf(1,'#%g) p4 = %g\n\n',count,p(4));
    count = count + 1;
    
    i = 1;
    if (double(S.x1(1)) > 0) && (double(S.x2(1)) > 0) && (double(x3(1)) > 0)
        M(i,:) = real([S.x1(1) S.x2(1) x3(1)]);
        i = i + 1;
    end
    if (double(S.x1(2)) > 0) && (double(S.x2(2)) > 0) && (double(x3(2)) > 0)
        M(i,:) = real([S.x1(2) S.x2(2) x3(2)]);
        i = i + 1;
    end
    if (double(S.x1(3)) > 0) && (double(S.x2(3)) > 0) && (double(x3(3)) > 0)
        M(i,:) = real([S.x1(3) S.x2(3) x3(3)]);
    end
    disp(vpa(M,10))

    gy1_1(j) = vpa(M(1,1),10);
    gy2_1(j) = vpa(M(1,2),10);
    gy3_1(j) = vpa(M(1,3),10);
    gx(j) = p(4);
    j = j + 1;
    
    u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
    u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
    u3 = t1-t3-p(4)*t3;
    X = [M(1,1) M(1,2) M(1,3)];
    fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
    fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
    fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
    
    A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
    A = subs(A,t1,M(1,1));
    A = subs(A,t2,M(1,2));
    A = vpa(A,10);
    [v,s] = eig(A);
    s = diag(s);

    if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        fprintf(1,' * устойчивая точка\n\n');
    elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
        fprintf(1,' * точка бифуркации\n\n');
    else
        fprintf(1,' * неустойчивая точка\n\n');
    end
    disp('------------------------')
    
    p(4) = p(4) + 0.01;
            
end


for k = 10:1:18
    
    y1 = (p(1)*x2-x1*x2+x1-x1^2)/p(2)-p(4)*x1;
    y2 = (-p(1)*x2-x1*x2+p(5)*x1/(p(4)+1))/p(3)+p(4)*(p(6)-x2);
    S = solve(y1,y2,x1,x2);
    x3 = S.x1/(p(4)+1);
    fprintf(1,'#%g) p4 = %g\n\n',count,p(4));
    count = count + 1;
    
    i = 1;
    if (double(S.x1(1)) > 0) && (double(S.x2(1)) > 0) && (double(x3(1)) > 0)
        M(i,:) = real([S.x1(1) S.x2(1) x3(1)]);
        i = i + 1;
    end
    if (double(S.x1(2)) > 0) && (double(S.x2(2)) > 0) && (double(x3(2)) > 0)
        M(i,:) = real([S.x1(2) S.x2(2) x3(2)]);
        i = i + 1;
    end
    if (double(S.x1(3)) > 0) && (double(S.x2(3)) > 0) && (double(x3(3)) > 0)
        M(i,:) = real([S.x1(3) S.x2(3) x3(3)]);
    end
    disp(vpa(M,10))

    gy1_1(j) = vpa(M(1,1),10);
    gy2_1(j) = vpa(M(1,2),10);
    gy3_1(j) = vpa(M(1,3),10);
    gx(j) = p(4);
    j = j + 1;
    
    u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
    u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
    u3 = t1-t3-p(4)*t3;
    X = [M(1,1) M(1,2) M(1,3)];
    fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
    fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
    fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
    
    A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
    A = subs(A,t1,M(1,1));
    A = subs(A,t2,M(1,2));
    A = vpa(A,10);
    [v,s] = eig(A);
    s = diag(s);

    if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        fprintf(1,' * устойчивая точка\n\n');
    elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
        fprintf(1,' * точка бифуркации\n\n');
    else
        fprintf(1,' * неустойчивая точка\n\n');
    end
    disp('------------------------')

    p(4) = p(4) + 0.1;
    
end


for k = 19:1:27
    
    y1 = (p(1)*x2-x1*x2+x1-x1^2)/p(2)-p(4)*x1;
    y2 = (-p(1)*x2-x1*x2+p(5)*x1/(p(4)+1))/p(3)+p(4)*(p(6)-x2);
    S = solve(y1,y2,x1,x2);
    x3 = S.x1/(p(4)+1);
    fprintf(1,'#%g) p4 = %g\n\n',count,p(4));
    count = count + 1;
     
    i = 1;
    if (double(S.x1(1)) > 0) && (double(S.x2(1)) > 0) && (double(x3(1)) > 0)
        M(i,:) = real([S.x1(1) S.x2(1) x3(1)]);
        disp(vpa(M(i,:),10))

        gy1_1(j) = vpa(M(i,1),10);
        gy2_1(j) = vpa(M(i,2),10);
        gy3_1(j) = vpa(M(i,3),10);
             
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
    
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
        end

        i = i + 1;
    end
    if (double(S.x1(2)) > 0) && (double(S.x2(2)) > 0) && (double(x3(2)) > 0)
        M(i,:) = real([S.x1(2) S.x2(2) x3(2)]);
        disp(vpa(M(i,:),10))
          
        gy1_2(l) = vpa(M(i,1),10);
        gy2_2(l) = vpa(M(i,2),10);
        gy3_2(l) = vpa(M(i,3),10);
             
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable2 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
            stable2 = 0;
            py1_2(h2) = gy1_2(l);
            py2_2(h2) = gy2_2(l);
            py3_2(h2) = gy3_2(l);
            flag2 = 1;
        end
        
        if oldstable2 ~= stable2
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable2 = stable2;

        i = i + 1;
    end
    if (double(S.x1(3)) > 0) && (double(S.x2(3)) > 0) && (double(x3(3)) > 0)
        M(i,:) = real([S.x1(3) S.x2(3) x3(3)]);
        disp(vpa(M(i,:),10))
   
        gy1_3(l) = vpa(M(i,1),10);
        gy2_3(l) = vpa(M(i,2),10);
        gy3_3(l) = vpa(M(i,3),10);
  
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable3 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
            stable3 = 0;
            py1_3(h3) = gy1_3(l);
            py2_3(h3) = gy2_3(l);
            py3_3(h3) = gy3_3(l);
            flag3 = 1;
        end
        
        if oldstable3 ~= stable3
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable3 = stable3;
    end

    gx(j) = p(4);
    j = j + 1;
    gx2(l) = p(4);
    l = l + 1;
    if flag2 == 1
        px2(h2) = p(4);
    	h2 = h2 + 1;
        flag2 = 0;
    end
    if flag3 == 1
        px3(h3) = p(4);
    	h3 = h3 + 1;
        flag3 = 0;
    end
    disp('------------------------')

    p(4) = p(4) + 1;
    
end


for k = 28:1:36
    
    y1 = (p(1)*x2-x1*x2+x1-x1^2)/p(2)-p(4)*x1;
    y2 = (-p(1)*x2-x1*x2+p(5)*x1/(p(4)+1))/p(3)+p(4)*(p(6)-x2);
    S = solve(y1,y2,x1,x2);
    x3 = S.x1/(p(4)+1);
    fprintf(1,'#%g) p4 = %g\n\n',count,p(4));
    count = count + 1;
    
    i = 1;
    if (double(S.x1(1)) > 0) && (double(S.x2(1)) > 0) && (double(x3(1)) > 0)
        M(i,:) = real([S.x1(1) S.x2(1) x3(1)]);
        disp(vpa(M(i,:),10))
           
        gy1_1(j) = vpa(M(i,1),10);
        gy2_1(j) = vpa(M(i,2),10);
        gy3_1(j) = vpa(M(i,3),10);
            
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
        	fprintf(1,' * точка бифуркации\n\n');
        else
        	fprintf(1,' * неустойчивая точка\n\n');
        end
        
        i = i + 1;
    end
    if (double(S.x1(2)) > 0) && (double(S.x2(2)) > 0) && (double(x3(2)) > 0)
        M(i,:) = real([S.x1(2) S.x2(2) x3(2)]);
        disp(vpa(M(i,:),10))
           
        gy1_2(l) = vpa(M(i,1),10);
        gy2_2(l) = vpa(M(i,2),10);
        gy3_2(l) = vpa(M(i,3),10);
            
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable2 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
        	fprintf(1,' * точка бифуркации\n\n');
        else
        	fprintf(1,' * неустойчивая точка\n\n');
            stable2 = 0;
            py1_2(h2) = gy1_2(l);
            py2_2(h2) = gy2_2(l);
            py3_2(h2) = gy3_2(l);
            flag2 = 1;
        end
        
        if oldstable2 ~= stable2
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable2 = stable2;
        
        i = i + 1;
    end
    if (double(S.x1(3)) > 0) && (double(S.x2(3)) > 0) && (double(x3(3)) > 0)
        M(i,:) = real([S.x1(3) S.x2(3) x3(3)]);
        disp(vpa(M(i,:),10))
        
        gy1_3(l) = vpa(M(i,1),10);
        gy2_3(l) = vpa(M(i,2),10);
        gy3_3(l) = vpa(M(i,3),10);

        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [M(i,1) M(i,2) M(i,3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable3 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
        	fprintf(1,' * точка бифуркации\n\n');
        else
        	fprintf(1,' * неустойчивая точка\n\n');
            stable3 = 0;
            py1_3(h3) = gy1_3(l);
            py2_3(h3) = gy2_3(l);
            py3_3(h3) = gy3_3(l);
            flag3 = 1;
        end
        
        if oldstable3 ~= stable3
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable3 = stable3;
    end
    
    gx(j) = p(4);
    j = j + 1;
    gx2(l) = p(4);
    l = l + 1;
    if flag2 == 1
        px2(h2) = p(4);
    	h2 = h2 + 1;
        flag2 = 0;
    end
    if flag3 == 1
        px3(h3) = p(4);
    	h3 = h3 + 1;
        flag3 = 0;
    end
    disp('------------------------')
             
    p(4) = p(4) + 10;
    
end


for k = 37:1:46
    
    y1 = (p(1)*x2-x1*x2+x1-x1^2)/p(2)-p(4)*x1;
    y2 = (-p(1)*x2-x1*x2+p(5)*x1/(p(4)+1))/p(3)+p(4)*(p(6)-x2);
    S = solve(y1,y2,x1,x2);
    x3 = S.x1/(p(4)+1);
    fprintf(1,'#%g) p4 = %g\n\n',count,p(4));
    count = count + 1;
    
    i = 1;
    if (double(S.x1(1)) > 0) && (double(S.x2(1)) > 0) && (double(x3(1)) > 0)
        M(i,:) = real([S.x1(1) S.x2(1) x3(1)]);
        disp(vpa(M(i,:),10))

        gy1_1(j) = vpa(M(i,1),10);
        gy2_1(j) = vpa(M(i,2),10);
        gy3_1(j) = vpa(M(i,3),10);
        
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [S.x1(1) S.x2(1) x3(1)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
        end
        
        i = i + 1;
    end
    if (double(S.x1(2)) > 0) && (double(S.x2(2)) > 0) && (double(x3(2)) > 0)
        M(i,:) = real([S.x1(2) S.x2(2) x3(2)]);
        disp(vpa(M(i,:),10))
        
        gy1_2(l) = vpa(M(i,1),10);
        gy2_2(l) = vpa(M(i,2),10);
        gy3_2(l) = vpa(M(i,3),10);
            
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [S.x1(2) S.x2(2) x3(2)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable2 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
            stable2 = 0;
            py1_2(h2) = gy1_2(l);
            py2_2(h2) = gy2_2(l);
            py3_2(h2) = gy3_2(l);
            flag2 = 1;
        end
        
        if oldstable2 ~= stable2
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable2 = stable2;

        i = i + 1;
    end
    if (double(S.x1(3)) > 0) && (double(S.x2(3)) > 0) && (double(x3(3)) > 0)
        M(i,:) = real([S.x1(3) S.x2(3) x3(3)]);
        disp(vpa(M(i,:),10))
        
        gy1_3(l) = vpa(M(i,1),10);
        gy2_3(l) = vpa(M(i,2),10);
        gy3_3(l) = vpa(M(i,3),10);
            
        u1 = (p(1)*t2-t1*t2+t1-t1^2)/p(2)-p(4)*t1;
        u2 = (-p(1)*t2-t1*t2+p(5)*t3)/p(3)+p(4)*(p(6)-t2);
        u3 = t1-t3-p(4)*t3;
        X = [S.x1(3) S.x2(3) x3(3)];
        fprintf(1,'\b\b - погрешность dx1/dt: %g\n',real(double(subs(u1,T,X))));
        fprintf(1,' - погрешность dx2/dt: %g\n',real(double(subs(u2,T,X))));
        fprintf(1,' - погрешность dx3/dt: %g\n',real(double(subs(u3,T,X))));
        
        A = [diff(u1,t1) diff(u1,t2) diff(u1,t3) ; diff(u2,t1) diff(u2,t2) diff(u2,t3) ; diff(u3,t1) diff(u3,t2) diff(u3,t3)];
        A = subs(A,t1,M(i,1));
        A = subs(A,t2,M(i,2));
        A = vpa(A,10);
        [v,s] = eig(A);
        s = diag(s);

        if (real(double(s(1))) < 0) && (real(double(s(2))) < 0) && (real(double(s(3))) < 0)
        	fprintf(1,' * устойчивая точка\n\n');
            stable3 = 1;
        elseif (real(double(s(1))) == 0) || (real(double(s(2))) == 0) || (real(double(s(3))) == 0)
            fprintf(1,' * точка бифуркации\n\n');
        else
            fprintf(1,' * неустойчивая точка\n\n');
            stable3 = 0;
            py1_3(h3) = gy1_3(l);
            py2_3(h3) = gy2_3(l);
            py3_3(h3) = gy3_3(l);
            flag3 = 1;
        end
        
        if oldstable3 ~= stable3
            if (imag(double(s(1))) == 0) && (imag(double(s(2))) == 0) && (imag(double(s(3))) == 0)
                fprintf(1,'\b ! РЯДОМ ТОЧКА ВЕЩЕСТВЕННОЙ БИФУРКАЦИИ !\n\n');
            else
                fprintf(1,'\b ! РЯДОМ ТОЧКА КОМПЛЕКСНОЙ БИФУРКАЦИИ !\n\n');
            end
        end
        oldstable3 = stable3;
    end
    
    gx(j) = p(4);
    j = j + 1;
    gx2(l) = p(4);
    l = l + 1;
    if flag2 == 1
        px2(h2) = p(4);
    	h2 = h2 + 1;
        flag2 = 0;
    end
    if flag3 == 1
        px3(h3) = p(4);
    	h3 = h3 + 1;
        flag3 = 0;
    end
    disp('------------------------')

    p(4) = p(4) + 100;
    
end


subplot(3,3,1)
    semilogx(gx,gy1_1,'-+r')
    title('Графики зависимости x1(p4):')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x1-1')
subplot(3,3,2)
    semilogx(gx,gy2_1,'-+g')
    title('Графики зависимости x2(p4):')
    xlabel('Параметр p4')
    ylabel('Стац. точка x2-1') 
subplot(3,3,3)
    semilogx(gx,gy3_1,'-+b')
    title('Графики зависимости x3(p4):')
    xlabel('Параметр p4')
    ylabel('Стац. точка x3-1')
    

subplot(3,3,4)
    semilogx(gx2,gy1_2,'-+r',px2,py1_2,'*k')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x1-2')
subplot(3,3,5)
    semilogx(gx2,gy2_2,'-+g',px2,py2_2,'*k')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x2-2')
    legend('устойчивые точки','неустойчивые точки')
subplot(3,3,6)
    semilogx(gx2,gy3_2,'-+b',px2,py3_2,'*k')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x3-2')


subplot(3,3,7)
    semilogx(gx2,gy1_3,'-+r',px3,py1_3,'*k')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x1-3')
subplot(3,3,8)
    semilogx(gx2,gy2_3,'-+g',px3,py2_3,'*k')
    xlabel('Параметр p4')
    ylabel('Стац. точка x2-3')
subplot(3,3,9)
    semilogx(gx2,gy3_3,'-+b',px3,py3_3,'*k')
    xlabel('Параметр p4') 
    ylabel('Стац. точка x3-3')
