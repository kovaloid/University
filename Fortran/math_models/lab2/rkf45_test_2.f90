include 'rkf45.f90'
include 'functions.f90'

program rkf45_test_2

  implicit none

  integer, parameter :: neqn = 20
  external func
  integer i, iflag, iwork(5)
  real abserr, relerr
  real t, t_out, t_print, t_final
  real work(6*neqn+3)
  real y(neqn), er(neqn), u(neqn)
  real er_max

  abserr = 0.0
  relerr = 0.1E-06

  iflag = 1

  t_final = 12.0
  t_print = 1.0

  t = 0.0
  t_out = t

  do i = 1, neqn
    y(i) = 1.0 + real(i)/real(neqn)
  end do

  write ( *, '(a)' ) ' '
  write ( *, '(a)' ) '  RKF45 TEST 2'
  write ( *, '(a)' ) ' '


   10 call rkf45 ( func, neqn, y, t, t_out, relerr, abserr, iflag, work, iwork )
      go to (80,20,30,40,50,60,70,80), iflag
   20 t_out = t + t_print
      if ( t < t_final ) go to 10
      go to 111
   30 go to 10
   40 go to 10
   50 abserr=0.1E-07
      go to 10
   60 relerr=relerr*10.0
      iflag = 2
      go to 10
   70 iflag = 2
      go to 10
   80 print *,'RKF45 ERROR'
      stop


  111 write ( *, '(a5,i4,a10,i2,a7,f10.6)' ) 'N =', neqn, 'FLAG =', iflag, 'T =', t
      write ( *, '(a)' ) ' '
      write ( *, '(a)' ) '   i        u           v            e'
      write ( *, '(a)' ) ' '

      do i = 1, neqn
        u(i) = 1.0 + real(i)/real(neqn) + t
        er(i)=ABS(y(i)-u(i))
        write(*,'(i4,2f12.6,e16.6)') i, u(i), y(i), er(i)
      end do

      write ( *, '(a)' ) ' '
      write ( *, '(a7,i5)' ) 'NFUN =',IWORK(1)
      er_max = er(1)
      do i=1, neqn
        if( er(i) > er_max ) er_max = er(i)
      end do
      write ( *, '(a9,e14.6)' ) 'MAXERR =',er_max

end


!функции k(r), q(r), f(r) и граничные условия v1(t), v2(t)
real function K(R,t)
    real R, t
    K=R+1.0
end

real function Q(R,t)
    real R, t
    Q=3.0*R*R+7.0*t*t
end

real function F(R,t)
    real R, t
    F=-2.0-2.0/R+(3.0*R*R+7.0*t*t)*(R+t)
end

real function V1(t)
    real t
    V1=1.0+t
end

real function V2(t)
    real t
    V2=2.0+t
end
