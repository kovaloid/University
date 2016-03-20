
      SUBROUTINE LSODE (F, NEQ, Y, T, TOUT, ITOL, RTOL, ATOL, ITASK, &
                        ISTATE, IOPT, RWORK, LRW, IWORK, LIW, JAC, MF)
      EXTERNAL F, JAC
      INTEGER NEQ, ITOL, ITASK, ISTATE, IOPT, LRW, IWORK, LIW, MF
      REAL Y, T, TOUT, RTOL, ATOL, RWORK
      DIMENSION NEQ(*), Y(*), RTOL(*), ATOL(*), RWORK(LRW), IWORK(LIW)
      EXTERNAL SPREPJ, SSOLSY
      REAL RUMACH, SVNORM

      INTEGER INIT, MXSTEP, MXHNIL, NHNIL, NSLAST, NYH, IOWNS, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      INTEGER I, I1, I2, IFLAG, IMXER, KGO, LF0, &
         LENIW, LENRW, LENWM, ML, MORD, MU, MXHNL0, MXSTP0
      REAL ROWNS, &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND
      REAL ATOLI, AYI, BIG, EWTI, H0, HMAX, HMX, RH, RTOLI, &
         TCRIT, TDIST, TNEXT, TOL, TOLSF, TP, SIZE, SUM, W0
      DIMENSION MORD(2)
      LOGICAL IHIT
      CHARACTER*80 MSG
      SAVE MORD, MXSTP0, MXHNL0

      COMMON /SLS001/ ROWNS(209), &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND, &
         INIT, MXSTEP, MXHNIL, NHNIL, NSLAST, NYH, IOWNS(6), &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU

      DATA  MORD(1),MORD(2)/12,5/, MXSTP0/500/, MXHNL0/10/

      IF (ISTATE .LT. 1 .OR. ISTATE .GT. 3) GO TO 601
      IF (ITASK .LT. 1 .OR. ITASK .GT. 5) GO TO 602
      IF (ISTATE .EQ. 1) GO TO 10
      IF (INIT .EQ. 0) GO TO 603
      IF (ISTATE .EQ. 2) GO TO 200
      GO TO 20
 10   INIT = 0
      IF (TOUT .EQ. T) RETURN
 20   IF (NEQ(1) .LE. 0) GO TO 604
      IF (ISTATE .EQ. 1) GO TO 25
      IF (NEQ(1) .GT. N) GO TO 605
 25   N = NEQ(1)
      IF (ITOL .LT. 1 .OR. ITOL .GT. 4) GO TO 606
      IF (IOPT .LT. 0 .OR. IOPT .GT. 1) GO TO 607
      METH = MF/10
      MITER = MF - 10*METH
      IF (METH .LT. 1 .OR. METH .GT. 2) GO TO 608
      IF (MITER .LT. 0 .OR. MITER .GT. 5) GO TO 608
      IF (MITER .LE. 3) GO TO 30
      ML = IWORK(1)
      MU = IWORK(2)
      IF (ML .LT. 0 .OR. ML .GE. N) GO TO 609
      IF (MU .LT. 0 .OR. MU .GE. N) GO TO 610
 30   CONTINUE
      IF (IOPT .EQ. 1) GO TO 40
      MAXORD = MORD(METH)
      MXSTEP = MXSTP0
      MXHNIL = MXHNL0
      IF (ISTATE .EQ. 1) H0 = 0.0E0
      HMXI = 0.0E0
      HMIN = 0.0E0
      GO TO 60
 40   MAXORD = IWORK(5)
      IF (MAXORD .LT. 0) GO TO 611
      IF (MAXORD .EQ. 0) MAXORD = 100
      MAXORD = MIN(MAXORD,MORD(METH))
      MXSTEP = IWORK(6)
      IF (MXSTEP .LT. 0) GO TO 612
      IF (MXSTEP .EQ. 0) MXSTEP = MXSTP0
      MXHNIL = IWORK(7)
      IF (MXHNIL .LT. 0) GO TO 613
      IF (MXHNIL .EQ. 0) MXHNIL = MXHNL0
      IF (ISTATE .NE. 1) GO TO 50
      H0 = RWORK(5)
      IF ((TOUT - T)*H0 .LT. 0.0E0) GO TO 614
 50   HMAX = RWORK(6)
      IF (HMAX .LT. 0.0E0) GO TO 615
      HMXI = 0.0E0
      IF (HMAX .GT. 0.0E0) HMXI = 1.0E0/HMAX
      HMIN = RWORK(7)
      IF (HMIN .LT. 0.0E0) GO TO 616
 60   LYH = 21
      IF (ISTATE .EQ. 1) NYH = N
      LWM = LYH + (MAXORD + 1)*NYH
      IF (MITER .EQ. 0) LENWM = 0
      IF (MITER .EQ. 1 .OR. MITER .EQ. 2) LENWM = N*N + 2
      IF (MITER .EQ. 3) LENWM = N + 2
      IF (MITER .GE. 4) LENWM = (2*ML + MU + 1)*N + 2
      LEWT = LWM + LENWM
      LSAVF = LEWT + N
      LACOR = LSAVF + N
      LENRW = LACOR + N - 1
      IWORK(17) = LENRW
      LIWM = 1
      LENIW = 20 + N
      IF (MITER .EQ. 0 .OR. MITER .EQ. 3) LENIW = 20
      IWORK(18) = LENIW
      IF (LENRW .GT. LRW) GO TO 617
      IF (LENIW .GT. LIW) GO TO 618
      RTOLI = RTOL(1)
      ATOLI = ATOL(1)
      DO 70 I = 1,N
        IF (ITOL .GE. 3) RTOLI = RTOL(I)
        IF (ITOL .EQ. 2 .OR. ITOL .EQ. 4) ATOLI = ATOL(I)
        IF (RTOLI .LT. 0.0E0) GO TO 619
        IF (ATOLI .LT. 0.0E0) GO TO 620
 70     CONTINUE
      IF (ISTATE .EQ. 1) GO TO 100
      JSTART = -1
      IF (NQ .LE. MAXORD) GO TO 90
      DO 80 I = 1,N
 80     RWORK(I+LSAVF-1) = RWORK(I+LWM-1)
 90   IF (MITER .GT. 0) RWORK(LWM) = SQRT(UROUND)
      IF (N .EQ. NYH) GO TO 200
      I1 = LYH + L*NYH
      I2 = LYH + (MAXORD + 1)*NYH - 1
      IF (I1 .GT. I2) GO TO 200
      DO 95 I = I1,I2
 95     RWORK(I) = 0.0E0
      GO TO 200
 100  UROUND = RUMACH()
      TN = T
      IF (ITASK .NE. 4 .AND. ITASK .NE. 5) GO TO 110
      TCRIT = RWORK(1)
      IF ((TCRIT - TOUT)*(TOUT - T) .LT. 0.0E0) GO TO 625
      IF (H0 .NE. 0.0E0 .AND. (T + H0 - TCRIT)*H0 .GT. 0.0E0) &
         H0 = TCRIT - T
 110  JSTART = 0
      IF (MITER .GT. 0) RWORK(LWM) = SQRT(UROUND)
      NHNIL = 0
      NST = 0
      NJE = 0
      NSLAST = 0
      HU = 0.0E0
      NQU = 0
      CCMAX = 0.3E0
      MAXCOR = 3
      MSBP = 20
      MXNCF = 10
      LF0 = LYH + NYH
      CALL F (NEQ, T, Y, RWORK(LF0))
      NFE = 1
      DO 115 I = 1,N
 115    RWORK(I+LYH-1) = Y(I)
      NQ = 1
      H = 1.0E0
      CALL SEWSET (N, ITOL, RTOL, ATOL, RWORK(LYH), RWORK(LEWT))
      DO 120 I = 1,N
        IF (RWORK(I+LEWT-1) .LE. 0.0E0) GO TO 621
 120    RWORK(I+LEWT-1) = 1.0E0/RWORK(I+LEWT-1)
      IF (H0 .NE. 0.0E0) GO TO 180
      TDIST = ABS(TOUT - T)
      W0 = MAX(ABS(T),ABS(TOUT))
      IF (TDIST .LT. 2.0E0*UROUND*W0) GO TO 622
      TOL = RTOL(1)
      IF (ITOL .LE. 2) GO TO 140
      DO 130 I = 1,N
 130    TOL = MAX(TOL,RTOL(I))
 140  IF (TOL .GT. 0.0E0) GO TO 160
      ATOLI = ATOL(1)
      DO 150 I = 1,N
        IF (ITOL .EQ. 2 .OR. ITOL .EQ. 4) ATOLI = ATOL(I)
        AYI = ABS(Y(I))
        IF (AYI .NE. 0.0E0) TOL = MAX(TOL,ATOLI/AYI)
 150    CONTINUE
 160  TOL = MAX(TOL,100.0E0*UROUND)
      TOL = MIN(TOL,0.001E0)
      SUM = SVNORM (N, RWORK(LF0), RWORK(LEWT))
      SUM = 1.0E0/(TOL*W0*W0) + TOL*SUM**2
      H0 = 1.0E0/SQRT(SUM)
      H0 = MIN(H0,TDIST)
      H0 = SIGN(H0,TOUT-T)
 180  RH = ABS(H0)*HMXI
      IF (RH .GT. 1.0E0) H0 = H0/RH
      H = H0
      DO 190 I = 1,N
 190    RWORK(I+LF0-1) = H0*RWORK(I+LF0-1)
      GO TO 270
 200  NSLAST = NST
      GO TO (210, 250, 220, 230, 240), ITASK
 210  IF ((TN - TOUT)*H .LT. 0.0E0) GO TO 250
      CALL SINTDY (TOUT, 0, RWORK(LYH), NYH, Y, IFLAG)
      IF (IFLAG .NE. 0) GO TO 627
      T = TOUT
      GO TO 420
 220  TP = TN - HU*(1.0E0 + 100.0E0*UROUND)
      IF ((TP - TOUT)*H .GT. 0.0E0) GO TO 623
      IF ((TN - TOUT)*H .LT. 0.0E0) GO TO 250
      GO TO 400
 230  TCRIT = RWORK(1)
      IF ((TN - TCRIT)*H .GT. 0.0E0) GO TO 624
      IF ((TCRIT - TOUT)*H .LT. 0.0E0) GO TO 625
      IF ((TN - TOUT)*H .LT. 0.0E0) GO TO 245
      CALL SINTDY (TOUT, 0, RWORK(LYH), NYH, Y, IFLAG)
      IF (IFLAG .NE. 0) GO TO 627
      T = TOUT
      GO TO 420
 240  TCRIT = RWORK(1)
      IF ((TN - TCRIT)*H .GT. 0.0E0) GO TO 624
 245  HMX = ABS(TN) + ABS(H)
      IHIT = ABS(TN - TCRIT) .LE. 100.0E0*UROUND*HMX
      IF (IHIT) GO TO 400
      TNEXT = TN + H*(1.0E0 + 4.0E0*UROUND)
      IF ((TNEXT - TCRIT)*H .LE. 0.0E0) GO TO 250
      H = (TCRIT - TN)*(1.0E0 - 4.0E0*UROUND)
      IF (ISTATE .EQ. 2) JSTART = -2
 250  CONTINUE
      IF ((NST-NSLAST) .GE. MXSTEP) GO TO 500
      CALL SEWSET (N, ITOL, RTOL, ATOL, RWORK(LYH), RWORK(LEWT))
      DO 260 I = 1,N
        IF (RWORK(I+LEWT-1) .LE. 0.0E0) GO TO 510
 260    RWORK(I+LEWT-1) = 1.0E0/RWORK(I+LEWT-1)
 270  TOLSF = UROUND*SVNORM (N, RWORK(LYH), RWORK(LEWT))
      IF (TOLSF .LE. 1.0E0) GO TO 280
      TOLSF = TOLSF*2.0E0
      IF (NST .EQ. 0) GO TO 626
      GO TO 520
 280  IF ((TN + H) .NE. TN) GO TO 290
      NHNIL = NHNIL + 1
      IF (NHNIL .GT. MXHNIL) GO TO 290
      MSG = 'SLSODE-  Warning..internal T (=R1) and H (=R2) are'
      CALL XERRWV (MSG, 50, 101, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG='      such that in the machine, T + H = T on the next step  '
      CALL XERRWV (MSG, 60, 101, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      (H = step size). Solver will continue anyway'
      CALL XERRWV (MSG, 50, 101, 0, 0, 0, 0, 2, TN, H)
      IF (NHNIL .LT. MXHNIL) GO TO 290
      MSG = 'SLSODE-  Above warning has been issued I1 times.  '
      CALL XERRWV (MSG, 50, 102, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      It will not be issued again for this problem'
      CALL XERRWV (MSG, 50, 102, 0, 1, MXHNIL, 0, 0, 0.0E0, 0.0E0)
 290  CONTINUE
      CALL SSTODE (NEQ, Y, RWORK(LYH), NYH, RWORK(LYH), RWORK(LEWT), &
         RWORK(LSAVF), RWORK(LACOR), RWORK(LWM), IWORK(LIWM), &
         F, JAC, SPREPJ, SSOLSY)
      KGO = 1 - KFLAG
      GO TO (300, 530, 540), KGO
 300  INIT = 1
      GO TO (310, 400, 330, 340, 350), ITASK
 310  IF ((TN - TOUT)*H .LT. 0.0E0) GO TO 250
      CALL SINTDY (TOUT, 0, RWORK(LYH), NYH, Y, IFLAG)
      T = TOUT
      GO TO 420
 330  IF ((TN - TOUT)*H .GE. 0.0E0) GO TO 400
      GO TO 250
 340  IF ((TN - TOUT)*H .LT. 0.0E0) GO TO 345
      CALL SINTDY (TOUT, 0, RWORK(LYH), NYH, Y, IFLAG)
      T = TOUT
      GO TO 420
 345  HMX = ABS(TN) + ABS(H)
      IHIT = ABS(TN - TCRIT) .LE. 100.0E0*UROUND*HMX
      IF (IHIT) GO TO 400
      TNEXT = TN + H*(1.0E0 + 4.0E0*UROUND)
      IF ((TNEXT - TCRIT)*H .LE. 0.0E0) GO TO 250
      H = (TCRIT - TN)*(1.0E0 - 4.0E0*UROUND)
      JSTART = -2
      GO TO 250
 350  HMX = ABS(TN) + ABS(H)
      IHIT = ABS(TN - TCRIT) .LE. 100.0E0*UROUND*HMX
 400  DO 410 I = 1,N
 410    Y(I) = RWORK(I+LYH-1)
      T = TN
      IF (ITASK .NE. 4 .AND. ITASK .NE. 5) GO TO 420
      IF (IHIT) T = TCRIT
 420  ISTATE = 2
      RWORK(11) = HU
      RWORK(12) = H
      RWORK(13) = TN
      IWORK(11) = NST
      IWORK(12) = NFE
      IWORK(13) = NJE
      IWORK(14) = NQU
      IWORK(15) = NQ
      RETURN
 500  MSG = 'SLSODE-  At current T (=R1), MXSTEP (=I1) steps   '
      CALL XERRWV (MSG, 50, 201, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      taken on this call before reaching TOUT     '
      CALL XERRWV (MSG, 50, 201, 0, 1, MXSTEP, 0, 1, TN, 0.0E0)
      ISTATE = -1
      GO TO 580
 510  EWTI = RWORK(LEWT+I-1)
      MSG = 'SLSODE-  At T (=R1), EWT(I1) has become R2 .LE. 0.'
      CALL XERRWV (MSG, 50, 202, 0, 1, I, 0, 2, TN, EWTI)
      ISTATE = -6
      GO TO 580
 520  MSG = 'SLSODE-  At T (=R1), too much accuracy requested  '
      CALL XERRWV (MSG, 50, 203, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      for precision of machine..  see TOLSF (=R2) '
      CALL XERRWV (MSG, 50, 203, 0, 0, 0, 0, 2, TN, TOLSF)
      RWORK(14) = TOLSF
      ISTATE = -2
      GO TO 580
 530  MSG = 'SLSODE-  At T(=R1) and step size H(=R2), the error'
      CALL XERRWV (MSG, 50, 204, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      test failed repeatedly or with ABS(H) = HMIN'
      CALL XERRWV (MSG, 50, 204, 0, 0, 0, 0, 2, TN, H)
      ISTATE = -4
      GO TO 560
 540  MSG = 'SLSODE-  At T (=R1) and step size H (=R2), the    '
      CALL XERRWV (MSG, 50, 205, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      corrector convergence failed repeatedly     '
      CALL XERRWV (MSG, 50, 205, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG = '      or with ABS(H) = HMIN   '
      CALL XERRWV (MSG, 30, 205, 0, 0, 0, 0, 2, TN, H)
      ISTATE = -5
 560  BIG = 0.0E0
      IMXER = 1
      DO 570 I = 1,N
        SIZE = ABS(RWORK(I+LACOR-1)*RWORK(I+LEWT-1))
        IF (BIG .GE. SIZE) GO TO 570
        BIG = SIZE
        IMXER = I
 570    CONTINUE
      IWORK(16) = IMXER
 580  DO 590 I = 1,N
 590    Y(I) = RWORK(I+LYH-1)
      T = TN
      RWORK(11) = HU
      RWORK(12) = H
      RWORK(13) = TN
      IWORK(11) = NST
      IWORK(12) = NFE
      IWORK(13) = NJE
      IWORK(14) = NQU
      IWORK(15) = NQ
      RETURN
 601  MSG = 'SLSODE-  ISTATE (=I1) illegal '
      CALL XERRWV (MSG, 30, 1, 0, 1, ISTATE, 0, 0, 0.0E0, 0.0E0)
      IF (ISTATE .LT. 0) GO TO 800
      GO TO 700
 602  MSG = 'SLSODE-  ITASK (=I1) illegal  '
      CALL XERRWV (MSG, 30, 2, 0, 1, ITASK, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 603  MSG = 'SLSODE-  ISTATE .GT. 1 but SLSODE not initialized '
      CALL XERRWV (MSG, 50, 3, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 604  MSG = 'SLSODE-  NEQ (=I1) .LT. 1     '
      CALL XERRWV (MSG, 30, 4, 0, 1, NEQ(1), 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 605  MSG = 'SLSODE-  ISTATE = 3 and NEQ increased (I1 to I2)  '
      CALL XERRWV (MSG, 50, 5, 0, 2, N, NEQ(1), 0, 0.0E0, 0.0E0)
      GO TO 700
 606  MSG = 'SLSODE-  ITOL (=I1) illegal   '
      CALL XERRWV (MSG, 30, 6, 0, 1, ITOL, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 607  MSG = 'SLSODE-  IOPT (=I1) illegal   '
      CALL XERRWV (MSG, 30, 7, 0, 1, IOPT, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 608  MSG = 'SLSODE-  MF (=I1) illegal     '
      CALL XERRWV (MSG, 30, 8, 0, 1, MF, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 609  MSG = 'SLSODE-  ML (=I1) illegal.. .LT.0 or .GE.NEQ (=I2)'
      CALL XERRWV (MSG, 50, 9, 0, 2, ML, NEQ(1), 0, 0.0E0, 0.0E0)
      GO TO 700
 610  MSG = 'SLSODE-  MU (=I1) illegal.. .LT.0 or .GE.NEQ (=I2)'
      CALL XERRWV (MSG, 50, 10, 0, 2, MU, NEQ(1), 0, 0.0E0, 0.0E0)
      GO TO 700
 611  MSG = 'SLSODE-  MAXORD (=I1) .LT. 0  '
      CALL XERRWV (MSG, 30, 11, 0, 1, MAXORD, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 612  MSG = 'SLSODE-  MXSTEP (=I1) .LT. 0  '
      CALL XERRWV (MSG, 30, 12, 0, 1, MXSTEP, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 613  MSG = 'SLSODE-  MXHNIL (=I1) .LT. 0  '
      CALL XERRWV (MSG, 30, 13, 0, 1, MXHNIL, 0, 0, 0.0E0, 0.0E0)
      GO TO 700
 614  MSG = 'SLSODE-  TOUT (=R1) behind T (=R2)      '
      CALL XERRWV (MSG, 40, 14, 0, 0, 0, 0, 2, TOUT, T)
      MSG = '      Integration direction is given by H0 (=R1)  '
      CALL XERRWV (MSG, 50, 14, 0, 0, 0, 0, 1, H0, 0.0E0)
      GO TO 700
 615  MSG = 'SLSODE-  HMAX (=R1) .LT. 0.0  '
      CALL XERRWV (MSG, 30, 15, 0, 0, 0, 0, 1, HMAX, 0.0E0)
      GO TO 700
 616  MSG = 'SLSODE-  HMIN (=R1) .LT. 0.0  '
      CALL XERRWV (MSG, 30, 16, 0, 0, 0, 0, 1, HMIN, 0.0E0)
      GO TO 700
 617  CONTINUE
      MSG='SLSODE-  RWORK length needed, LENRW (=I1), exceeds LRW (=I2)'
      CALL XERRWV (MSG, 60, 17, 0, 2, LENRW, LRW, 0, 0.0E0, 0.0E0)
      GO TO 700
 618  CONTINUE
      MSG='SLSODE-  IWORK length needed, LENIW (=I1), exceeds LIW (=I2)'
      CALL XERRWV (MSG, 60, 18, 0, 2, LENIW, LIW, 0, 0.0E0, 0.0E0)
      GO TO 700
 619  MSG = 'SLSODE-  RTOL(I1) is R1 .LT. 0.0        '
      CALL XERRWV (MSG, 40, 19, 0, 1, I, 0, 1, RTOLI, 0.0E0)
      GO TO 700
 620  MSG = 'SLSODE-  ATOL(I1) is R1 .LT. 0.0        '
      CALL XERRWV (MSG, 40, 20, 0, 1, I, 0, 1, ATOLI, 0.0E0)
      GO TO 700
 621  EWTI = RWORK(LEWT+I-1)
      MSG = 'SLSODE-  EWT(I1) is R1 .LE. 0.0         '
      CALL XERRWV (MSG, 40, 21, 0, 1, I, 0, 1, EWTI, 0.0E0)
      GO TO 700
 622  CONTINUE
      MSG='SLSODE-  TOUT (=R1) too close to T(=R2) to start integration'
      CALL XERRWV (MSG, 60, 22, 0, 0, 0, 0, 2, TOUT, T)
      GO TO 700
 623  CONTINUE
      MSG='SLSODE-  ITASK = I1 and TOUT (=R1) behind TCUR - HU (= R2)  '
      CALL XERRWV (MSG, 60, 23, 0, 1, ITASK, 0, 2, TOUT, TP)
      GO TO 700
 624  CONTINUE
      MSG='SLSODE-  ITASK = 4 OR 5 and TCRIT (=R1) behind TCUR (=R2)   '
      CALL XERRWV (MSG, 60, 24, 0, 0, 0, 0, 2, TCRIT, TN)
      GO TO 700
 625  CONTINUE
      MSG='SLSODE-  ITASK = 4 or 5 and TCRIT (=R1) behind TOUT (=R2)   '
      CALL XERRWV (MSG, 60, 25, 0, 0, 0, 0, 2, TCRIT, TOUT)
      GO TO 700
 626  MSG = 'SLSODE-  At start of problem, too much accuracy   '
      CALL XERRWV (MSG, 50, 26, 0, 0, 0, 0, 0, 0.0E0, 0.0E0)
      MSG='      requested for precision of machine..  See TOLSF (=R1) '
      CALL XERRWV (MSG, 60, 26, 0, 0, 0, 0, 1, TOLSF, 0.0E0)
      RWORK(14) = TOLSF
      GO TO 700
 627  MSG = 'SLSODE-  Trouble in SINTDY.  ITASK = I1, TOUT = R1'
      CALL XERRWV (MSG, 50, 27, 0, 1, ITASK, 0, 1, TOUT, 0.0E0)
 700  ISTATE = -3
      RETURN
 800  MSG = 'SLSODE-  Run aborted.. apparent infinite loop     '
      CALL XERRWV (MSG, 50, 303, 2, 0, 0, 0, 0, 0.0E0, 0.0E0)
      RETURN
      END
      REAL FUNCTION RUMACH ()
      REAL U, COMP
      U = 1.0E0
 10   U = U*0.5E0
      CALL RUMSUM(1.0E0, U, COMP)
      IF (COMP .NE. 1.0E0) GO TO 10
      RUMACH = U*2.0E0
      RETURN
      END
      SUBROUTINE RUMSUM(A,B,C)
      REAL A, B, C
      C = A + B
      RETURN
      END
      SUBROUTINE SCFODE (METH, ELCO, TESCO)
      INTEGER METH
      INTEGER I, IB, NQ, NQM1, NQP1
      REAL ELCO, TESCO
      REAL AGAMQ, FNQ, FNQM1, PC, PINT, RAGQ, &
         RQFAC, RQ1FAC, TSIGN, XPIN
      DIMENSION ELCO(13,12), TESCO(3,12)
      DIMENSION PC(12)
      GO TO (100, 200), METH
 100  ELCO(1,1) = 1.0E0
      ELCO(2,1) = 1.0E0
      TESCO(1,1) = 0.0E0
      TESCO(2,1) = 2.0E0
      TESCO(1,2) = 1.0E0
      TESCO(3,12) = 0.0E0
      PC(1) = 1.0E0
      RQFAC = 1.0E0
      DO 140 NQ = 2,12
        RQ1FAC = RQFAC
        RQFAC = RQFAC/NQ
        NQM1 = NQ - 1
        FNQM1 = NQM1
        NQP1 = NQ + 1
        PC(NQ) = 0.0E0
        DO 110 IB = 1,NQM1
          I = NQP1 - IB
 110      PC(I) = PC(I-1) + FNQM1*PC(I)
        PC(1) = FNQM1*PC(1)
        PINT = PC(1)
        XPIN = PC(1)/2.0E0
        TSIGN = 1.0E0
        DO 120 I = 2,NQ
          TSIGN = -TSIGN
          PINT = PINT + TSIGN*PC(I)/I
 120      XPIN = XPIN + TSIGN*PC(I)/(I+1)
        ELCO(1,NQ) = PINT*RQ1FAC
        ELCO(2,NQ) = 1.0E0
        DO 130 I = 2,NQ
 130      ELCO(I+1,NQ) = RQ1FAC*PC(I)/I
        AGAMQ = RQFAC*XPIN
        RAGQ = 1.0E0/AGAMQ
        TESCO(2,NQ) = RAGQ
        IF (NQ .LT. 12) TESCO(1,NQP1) = RAGQ*RQFAC/NQP1
        TESCO(3,NQM1) = RAGQ
 140    CONTINUE
      RETURN
 200  PC(1) = 1.0E0
      RQ1FAC = 1.0E0
      DO 230 NQ = 1,5
        FNQ = NQ
        NQP1 = NQ + 1
        PC(NQP1) = 0.0E0
        DO 210 IB = 1,NQ
          I = NQ + 2 - IB
 210      PC(I) = PC(I-1) + FNQ*PC(I)
        PC(1) = FNQ*PC(1)
        DO 220 I = 1,NQP1
 220      ELCO(I,NQ) = PC(I)/PC(2)
        ELCO(2,NQ) = 1.0E0
        TESCO(1,NQ) = RQ1FAC
        TESCO(2,NQ) = NQP1/ELCO(1,NQ)
        TESCO(3,NQ) = (NQ+2)/ELCO(1,NQ)
        RQ1FAC = RQ1FAC/FNQ
 230    CONTINUE
      RETURN
      END
      SUBROUTINE SINTDY (T, K, YH, NYH, DKY, IFLAG)
      INTEGER K, NYH, IFLAG
      REAL T, YH, DKY
      DIMENSION YH(NYH,*), DKY(*)
      INTEGER IOWND, IOWNS, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      REAL ROWNS, &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND
      COMMON /SLS001/ ROWNS(209), &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND, &
         IOWND(6), IOWNS(6), &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      INTEGER I, IC, J, JB, JB2, JJ, JJ1, JP1
      REAL C, R, S, TP
      CHARACTER*80 MSG
      IFLAG = 0
      IF (K .LT. 0 .OR. K .GT. NQ) GO TO 80
      TP = TN - HU -  100.0E0*UROUND*SIGN(ABS(TN) + ABS(HU), HU)
      IF ((T-TP)*(T-TN) .GT. 0.0E0) GO TO 90
      S = (T - TN)/H
      IC = 1
      IF (K .EQ. 0) GO TO 15
      JJ1 = L - K
      DO 10 JJ = JJ1,NQ
 10     IC = IC*JJ
 15   C = IC
      DO 20 I = 1,N
 20     DKY(I) = C*YH(I,L)
      IF (K .EQ. NQ) GO TO 55
      JB2 = NQ - K
      DO 50 JB = 1,JB2
        J = NQ - JB
        JP1 = J + 1
        IC = 1
        IF (K .EQ. 0) GO TO 35
        JJ1 = JP1 - K
        DO 30 JJ = JJ1,J
 30       IC = IC*JJ
 35     C = IC
        DO 40 I = 1,N
 40       DKY(I) = C*YH(I,JP1) + S*DKY(I)
 50     CONTINUE
      IF (K .EQ. 0) RETURN
 55   R = H**(-K)
      DO 60 I = 1,N
 60     DKY(I) = R*DKY(I)
      RETURN
 80   MSG = 'SINTDY-  K (=I1) illegal      '
      CALL XERRWV (MSG, 30, 51, 0, 1, K, 0, 0, 0.0E0, 0.0E0)
      IFLAG = -1
      RETURN
 90   MSG = 'SINTDY-  T (=R1) illegal      '
      CALL XERRWV (MSG, 30, 52, 0, 0, 0, 0, 1, T, 0.0E0)
      MSG='      T not in interval TCUR - HU (= R1) to TCUR (=R2)      '
      CALL XERRWV (MSG, 60, 52, 0, 0, 0, 0, 2, TP, TN)
      IFLAG = -2
      RETURN
      END
      SUBROUTINE SPREPJ (NEQ, Y, YH, NYH, EWT, FTEM, SAVF, WM, IWM, &
         F, JAC)
      EXTERNAL F, JAC
      INTEGER NEQ, NYH, IWM
      REAL Y, YH, EWT, FTEM, SAVF, WM
      DIMENSION NEQ(*), Y(*), YH(NYH,*), EWT(*), FTEM(*), SAVF(*), &
         WM(*), IWM(*)
      INTEGER IOWND, IOWNS, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      REAL ROWNS, &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND
      COMMON /SLS001/ ROWNS(209), &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND, &
         IOWND(6), IOWNS(6), &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      INTEGER I, I1, I2, IER, II, J, J1, JJ, LENP, &
         MBA, MBAND, MEB1, MEBAND, ML, ML3, MU, NP1
      REAL CON, DI, FAC, HL0, R, R0, SRUR, YI, YJ, YJJ, &
         SVNORM
      NJE = NJE + 1
      IERPJ = 0
      JCUR = 1
      HL0 = H*EL0
      GO TO (100, 200, 300, 400, 500), MITER
 100  LENP = N*N
      DO 110 I = 1,LENP
 110    WM(I+2) = 0.0E0
      CALL JAC (NEQ, TN, Y, 0, 0, WM(3), N)
      CON = -HL0
      DO 120 I = 1,LENP
 120    WM(I+2) = WM(I+2)*CON
      GO TO 240
 200  FAC = SVNORM (N, SAVF, EWT)
      R0 = 1000.0E0*ABS(H)*UROUND*N*FAC
      IF (R0 .EQ. 0.0E0) R0 = 1.0E0
      SRUR = WM(1)
      J1 = 2
      DO 230 J = 1,N
        YJ = Y(J)
        R = MAX(SRUR*ABS(YJ),R0/EWT(J))
        Y(J) = Y(J) + R
        FAC = -HL0/R
        CALL F (NEQ, TN, Y, FTEM)
        DO 220 I = 1,N
 220      WM(I+J1) = (FTEM(I) - SAVF(I))*FAC
        Y(J) = YJ
        J1 = J1 + N
 230    CONTINUE
      NFE = NFE + N
 240  J = 3
      NP1 = N + 1
      DO 250 I = 1,N
        WM(J) = WM(J) + 1.0E0
 250    J = J + NP1
      CALL SGEFA (WM(3), N, N, IWM(21), IER)
      IF (IER .NE. 0) IERPJ = 1
      RETURN
 300  WM(2) = HL0
      R = EL0*0.1E0
      DO 310 I = 1,N
 310    Y(I) = Y(I) + R*(H*SAVF(I) - YH(I,2))
      CALL F (NEQ, TN, Y, WM(3))
      NFE = NFE + 1
      DO 320 I = 1,N
        R0 = H*SAVF(I) - YH(I,2)
        DI = 0.1E0*R0 - H*(WM(I+2) - SAVF(I))
        WM(I+2) = 1.0E0
        IF (ABS(R0) .LT. UROUND/EWT(I)) GO TO 320
        IF (ABS(DI) .EQ. 0.0E0) GO TO 330
        WM(I+2) = 0.1E0*R0/DI
 320    CONTINUE
      RETURN
 330  IERPJ = 1
      RETURN
 400  ML = IWM(1)
      MU = IWM(2)
      ML3 = ML + 3
      MBAND = ML + MU + 1
      MEBAND = MBAND + ML
      LENP = MEBAND*N
      DO 410 I = 1,LENP
 410    WM(I+2) = 0.0E0
      CALL JAC (NEQ, TN, Y, ML, MU, WM(ML3), MEBAND)
      CON = -HL0
      DO 420 I = 1,LENP
 420    WM(I+2) = WM(I+2)*CON
      GO TO 570
 500  ML = IWM(1)
      MU = IWM(2)
      MBAND = ML + MU + 1
      MBA = MIN(MBAND,N)
      MEBAND = MBAND + ML
      MEB1 = MEBAND - 1
      SRUR = WM(1)
      FAC = SVNORM (N, SAVF, EWT)
      R0 = 1000.0E0*ABS(H)*UROUND*N*FAC
      IF (R0 .EQ. 0.0E0) R0 = 1.0E0
      DO 560 J = 1,MBA
        DO 530 I = J,N,MBAND
          YI = Y(I)
          R = MAX(SRUR*ABS(YI),R0/EWT(I))
 530      Y(I) = Y(I) + R
        CALL F (NEQ, TN, Y, FTEM)
        DO 550 JJ = J,N,MBAND
          Y(JJ) = YH(JJ,1)
          YJJ = Y(JJ)
          R = MAX(SRUR*ABS(YJJ),R0/EWT(JJ))
          FAC = -HL0/R
          I1 = MAX(JJ-MU,1)
          I2 = MIN(JJ+ML,N)
          II = JJ*MEB1 - ML + 2
          DO 540 I = I1,I2
 540        WM(II+I) = (FTEM(I) - SAVF(I))*FAC
 550      CONTINUE
 560    CONTINUE
      NFE = NFE + MBA
 570  II = MBAND + 2
      DO 580 I = 1,N
        WM(II) = WM(II) + 1.0E0
 580    II = II + MEBAND
      CALL SGBFA (WM(3), MEBAND, N, ML, MU, IWM(21), IER)
      IF (IER .NE. 0) IERPJ = 1
      RETURN
      END
      SUBROUTINE SSOLSY (WM, IWM, X, TEM)
      INTEGER IWM
      REAL WM, X, TEM
      DIMENSION WM(*), IWM(*), X(*), TEM(*)
      INTEGER IOWND, IOWNS, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      REAL ROWNS, &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND
      COMMON /SLS001/ ROWNS(209), &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND, &
         IOWND(6), IOWNS(6), &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      INTEGER I, MEBAND, ML, MU
      REAL DI, HL0, PHL0, R
      IERSL = 0
      GO TO (100, 100, 300, 400, 400), MITER
 100  CALL SGESL (WM(3), N, N, IWM(21), X, 0)
      RETURN
 300  PHL0 = WM(2)
      HL0 = H*EL0
      WM(2) = HL0
      IF (HL0 .EQ. PHL0) GO TO 330
      R = HL0/PHL0
      DO 320 I = 1,N
        DI = 1.0E0 - R*(1.0E0 - 1.0E0/WM(I+2))
        IF (ABS(DI) .EQ. 0.0E0) GO TO 390
 320    WM(I+2) = 1.0E0/DI
 330  DO 340 I = 1,N
 340    X(I) = WM(I+2)*X(I)
      RETURN
 390  IERSL = 1
      RETURN
 400  ML = IWM(1)
      MU = IWM(2)
      MEBAND = 2*ML + MU + 1
      CALL SGBSL (WM(3), MEBAND, N, ML, MU, IWM(21), X, 0)
      RETURN
      END
      SUBROUTINE SSRCOM (RSAV, ISAV, JOB)
      INTEGER ISAV, JOB
      INTEGER ILS
      INTEGER I, LENILS, LENRLS
      REAL RSAV,   RLS
      DIMENSION RSAV(*), ISAV(*)
      SAVE LENRLS, LENILS
      COMMON /SLS001/ RLS(218), ILS(37)
      DATA LENRLS/218/, LENILS/37/
      IF (JOB .EQ. 2) GO TO 100
      DO 10 I = 1,LENRLS
 10     RSAV(I) = RLS(I)
      DO 20 I = 1,LENILS
 20     ISAV(I) = ILS(I)
      RETURN
 100  CONTINUE
      DO 110 I = 1,LENRLS
 110     RLS(I) = RSAV(I)
      DO 120 I = 1,LENILS
 120     ILS(I) = ISAV(I)
      RETURN
      END
      SUBROUTINE SSTODE (NEQ, Y, YH, NYH, YH1, EWT, SAVF, ACOR, &
         WM, IWM, F, JAC, PJAC, SLVS)
      EXTERNAL F, JAC, PJAC, SLVS
      INTEGER NEQ, NYH, IWM
      REAL Y, YH, YH1, EWT, SAVF, ACOR, WM
      DIMENSION NEQ(*), Y(*), YH(NYH,*), YH1(*), EWT(*), SAVF(*), &
         ACOR(*), WM(*), IWM(*)
      INTEGER IOWND, IALTH, IPUP, LMAX, MEO, NQNYH, NSLP, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      INTEGER I, I1, IREDO, IRET, J, JB, M, NCF, NEWQ
      REAL CONIT, CRATE, EL, ELCO, HOLD, RMAX, TESCO, &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND
      REAL DCON, DDN, DEL, DELP, DSM, DUP, EXDN, EXSM, EXUP, &
         R, RH, RHDN, RHSM, RHUP, TOLD, SVNORM
      COMMON /SLS001/ CONIT, CRATE, EL(13), ELCO(13,12), &
         HOLD, RMAX, TESCO(3,12), &
         CCMAX, EL0, H, HMIN, HMXI, HU, RC, TN, UROUND, &
         IOWND(6), IALTH, IPUP, LMAX, MEO, NQNYH, NSLP, &
         ICF, IERPJ, IERSL, JCUR, JSTART, KFLAG, L, &
         LYH, LEWT, LACOR, LSAVF, LWM, LIWM, METH, MITER, &
         MAXORD, MAXCOR, MSBP, MXNCF, N, NQ, NST, NFE, NJE, NQU
      KFLAG = 0
      TOLD = TN
      NCF = 0
      IERPJ = 0
      IERSL = 0
      JCUR = 0
      ICF = 0
      DELP = 0.0E0
      IF (JSTART .GT. 0) GO TO 200
      IF (JSTART .EQ. -1) GO TO 100
      IF (JSTART .EQ. -2) GO TO 160
      LMAX = MAXORD + 1
      NQ = 1
      L = 2
      IALTH = 2
      RMAX = 10000.0E0
      RC = 0.0E0
      EL0 = 1.0E0
      CRATE = 0.7E0
      HOLD = H
      MEO = METH
      NSLP = 0
      IPUP = MITER
      IRET = 3
      GO TO 140
 100  IPUP = MITER
      LMAX = MAXORD + 1
      IF (IALTH .EQ. 1) IALTH = 2
      IF (METH .EQ. MEO) GO TO 110
      CALL SCFODE (METH, ELCO, TESCO)
      MEO = METH
      IF (NQ .GT. MAXORD) GO TO 120
      IALTH = L
      IRET = 1
      GO TO 150
 110  IF (NQ .LE. MAXORD) GO TO 160
 120  NQ = MAXORD
      L = LMAX
      DO 125 I = 1,L
 125    EL(I) = ELCO(I,NQ)
      NQNYH = NQ*NYH
      RC = RC*EL(1)/EL0
      EL0 = EL(1)
      CONIT = 0.5E0/(NQ+2)
      DDN = SVNORM (N, SAVF, EWT)/TESCO(1,L)
      EXDN = 1.0E0/L
      RHDN = 1.0E0/(1.3E0*DDN**EXDN + 0.0000013E0)
      RH = MIN(RHDN,1.0E0)
      IREDO = 3
      IF (H .EQ. HOLD) GO TO 170
      RH = MIN(RH,ABS(H/HOLD))
      H = HOLD
      GO TO 175
 140  CALL SCFODE (METH, ELCO, TESCO)
 150  DO 155 I = 1,L
 155    EL(I) = ELCO(I,NQ)
      NQNYH = NQ*NYH
      RC = RC*EL(1)/EL0
      EL0 = EL(1)
      CONIT = 0.5E0/(NQ+2)
      GO TO (160, 170, 200), IRET
 160  IF (H .EQ. HOLD) GO TO 200
      RH = H/HOLD
      H = HOLD
      IREDO = 3
      GO TO 175
 170  RH = MAX(RH,HMIN/ABS(H))
 175  RH = MIN(RH,RMAX)
      RH = RH/MAX(1.0E0,ABS(H)*HMXI*RH)
      R = 1.0E0
      DO 180 J = 2,L
        R = R*RH
        DO 180 I = 1,N
 180      YH(I,J) = YH(I,J)*R
      H = H*RH
      RC = RC*RH
      IALTH = L
      IF (IREDO .EQ. 0) GO TO 690
 200  IF (ABS(RC-1.0E0) .GT. CCMAX) IPUP = MITER
      IF (NST .GE. NSLP+MSBP) IPUP = MITER
      TN = TN + H
      I1 = NQNYH + 1
      DO 215 JB = 1,NQ
        I1 = I1 - NYH
        DO 210 I = I1,NQNYH
 210      YH1(I) = YH1(I) + YH1(I+NYH)
 215    CONTINUE
 220  M = 0
      DO 230 I = 1,N
 230    Y(I) = YH(I,1)
      CALL F (NEQ, TN, Y, SAVF)
      NFE = NFE + 1
      IF (IPUP .LE. 0) GO TO 250
      CALL PJAC (NEQ, Y, YH, NYH, EWT, ACOR, SAVF, WM, IWM, F, JAC)
      IPUP = 0
      RC = 1.0E0
      NSLP = NST
      CRATE = 0.7E0
      IF (IERPJ .NE. 0) GO TO 430
 250  DO 260 I = 1,N
 260    ACOR(I) = 0.0E0
 270  IF (MITER .NE. 0) GO TO 350
      DO 290 I = 1,N
        SAVF(I) = H*SAVF(I) - YH(I,2)
 290    Y(I) = SAVF(I) - ACOR(I)
      DEL = SVNORM (N, Y, EWT)
      DO 300 I = 1,N
        Y(I) = YH(I,1) + EL(1)*SAVF(I)
 300    ACOR(I) = SAVF(I)
      GO TO 400
 350  DO 360 I = 1,N
 360    Y(I) = H*SAVF(I) - (YH(I,2) + ACOR(I))
      CALL SLVS (WM, IWM, Y, SAVF)
      IF (IERSL .LT. 0) GO TO 430
      IF (IERSL .GT. 0) GO TO 410
      DEL = SVNORM (N, Y, EWT)
      DO 380 I = 1,N
        ACOR(I) = ACOR(I) + Y(I)
 380    Y(I) = YH(I,1) + EL(1)*ACOR(I)
 400  IF (M .NE. 0) CRATE = MAX(0.2E0*CRATE,DEL/DELP)
      DCON = DEL*MIN(1.0E0,1.5E0*CRATE)/(TESCO(2,NQ)*CONIT)
      IF (DCON .LE. 1.0E0) GO TO 450
      M = M + 1
      IF (M .EQ. MAXCOR) GO TO 410
      IF (M .GE. 2 .AND. DEL .GT. 2.0E0*DELP) GO TO 410
      DELP = DEL
      CALL F (NEQ, TN, Y, SAVF)
      NFE = NFE + 1
      GO TO 270
 410  IF (MITER .EQ. 0 .OR. JCUR .EQ. 1) GO TO 430
      ICF = 1
      IPUP = MITER
      GO TO 220
 430  ICF = 2
      NCF = NCF + 1
      RMAX = 2.0E0
      TN = TOLD
      I1 = NQNYH + 1
      DO 445 JB = 1,NQ
        I1 = I1 - NYH
        DO 440 I = I1,NQNYH
 440      YH1(I) = YH1(I) - YH1(I+NYH)
 445    CONTINUE
      IF (IERPJ .LT. 0 .OR. IERSL .LT. 0) GO TO 680
      IF (ABS(H) .LE. HMIN*1.00001E0) GO TO 670
      IF (NCF .EQ. MXNCF) GO TO 670
      RH = 0.25E0
      IPUP = MITER
      IREDO = 1
      GO TO 170
 450  JCUR = 0
      IF (M .EQ. 0) DSM = DEL/TESCO(2,NQ)
      IF (M .GT. 0) DSM = SVNORM (N, ACOR, EWT)/TESCO(2,NQ)
      IF (DSM .GT. 1.0E0) GO TO 500
      KFLAG = 0
      IREDO = 0
      NST = NST + 1
      HU = H
      NQU = NQ
      DO 470 J = 1,L
        DO 470 I = 1,N
 470      YH(I,J) = YH(I,J) + EL(J)*ACOR(I)
      IALTH = IALTH - 1
      IF (IALTH .EQ. 0) GO TO 520
      IF (IALTH .GT. 1) GO TO 700
      IF (L .EQ. LMAX) GO TO 700
      DO 490 I = 1,N
 490    YH(I,LMAX) = ACOR(I)
      GO TO 700
 500  KFLAG = KFLAG - 1
      TN = TOLD
      I1 = NQNYH + 1
      DO 515 JB = 1,NQ
        I1 = I1 - NYH
        DO 510 I = I1,NQNYH
 510      YH1(I) = YH1(I) - YH1(I+NYH)
 515    CONTINUE
      RMAX = 2.0E0
      IF (ABS(H) .LE. HMIN*1.00001E0) GO TO 660
      IF (KFLAG .LE. -3) GO TO 640
      IREDO = 2
      RHUP = 0.0E0
      GO TO 540
 520  RHUP = 0.0E0
      IF (L .EQ. LMAX) GO TO 540
      DO 530 I = 1,N
 530    SAVF(I) = ACOR(I) - YH(I,LMAX)
      DUP = SVNORM (N, SAVF, EWT)/TESCO(3,NQ)
      EXUP = 1.0E0/(L+1)
      RHUP = 1.0E0/(1.4E0*DUP**EXUP + 0.0000014E0)
 540  EXSM = 1.0E0/L
      RHSM = 1.0E0/(1.2E0*DSM**EXSM + 0.0000012E0)
      RHDN = 0.0E0
      IF (NQ .EQ. 1) GO TO 560
      DDN = SVNORM (N, YH(1,L), EWT)/TESCO(1,NQ)
      EXDN = 1.0E0/NQ
      RHDN = 1.0E0/(1.3E0*DDN**EXDN + 0.0000013E0)
 560  IF (RHSM .GE. RHUP) GO TO 570
      IF (RHUP .GT. RHDN) GO TO 590
      GO TO 580
 570  IF (RHSM .LT. RHDN) GO TO 580
      NEWQ = NQ
      RH = RHSM
      GO TO 620
 580  NEWQ = NQ - 1
      RH = RHDN
      IF (KFLAG .LT. 0 .AND. RH .GT. 1.0E0) RH = 1.0E0
      GO TO 620
 590  NEWQ = L
      RH = RHUP
      IF (RH .LT. 1.1E0) GO TO 610
      R = EL(L)/L
      DO 600 I = 1,N
 600    YH(I,NEWQ+1) = ACOR(I)*R
      GO TO 630
 610  IALTH = 3
      GO TO 700
 620  IF ((KFLAG .EQ. 0) .AND. (RH .LT. 1.1E0)) GO TO 610
      IF (KFLAG .LE. -2) RH = MIN(RH,0.2E0)
      IF (NEWQ .EQ. NQ) GO TO 170
 630  NQ = NEWQ
      L = NQ + 1
      IRET = 2
      GO TO 150
 640  IF (KFLAG .EQ. -10) GO TO 660
      RH = 0.1E0
      RH = MAX(HMIN/ABS(H),RH)
      H = H*RH
      DO 645 I = 1,N
 645    Y(I) = YH(I,1)
      CALL F (NEQ, TN, Y, SAVF)
      NFE = NFE + 1
      DO 650 I = 1,N
 650    YH(I,2) = H*SAVF(I)
      IPUP = MITER
      IALTH = 5
      IF (NQ .EQ. 1) GO TO 200
      NQ = 1
      L = 2
      IRET = 3
      GO TO 150
 660  KFLAG = -1
      GO TO 720
 670  KFLAG = -2
      GO TO 720
 680  KFLAG = -3
      GO TO 720
 690  RMAX = 10.0E0
 700  R = 1.0E0/TESCO(2,NQU)
      DO 710 I = 1,N
 710    ACOR(I) = ACOR(I)*R
 720  HOLD = H
      JSTART = 1
      RETURN
      END
      SUBROUTINE SEWSET (N, ITOL, RTOL, ATOL, YCUR, EWT)
      INTEGER N, ITOL
      INTEGER I
      REAL RTOL, ATOL, YCUR, EWT
      DIMENSION RTOL(*), ATOL(*), YCUR(N), EWT(N)
      GO TO (10, 20, 30, 40), ITOL
 10   CONTINUE
      DO 15 I = 1,N
 15     EWT(I) = RTOL(1)*ABS(YCUR(I)) + ATOL(1)
      RETURN
 20   CONTINUE
      DO 25 I = 1,N
 25     EWT(I) = RTOL(1)*ABS(YCUR(I)) + ATOL(I)
      RETURN
 30   CONTINUE
      DO 35 I = 1,N
 35     EWT(I) = RTOL(I)*ABS(YCUR(I)) + ATOL(1)
      RETURN
 40   CONTINUE
      DO 45 I = 1,N
 45     EWT(I) = RTOL(I)*ABS(YCUR(I)) + ATOL(I)
      RETURN
      END
      REAL FUNCTION SVNORM (N, V, W)
      INTEGER N,   I
      REAL V, W,   SUM
      DIMENSION V(N), W(N)
      SUM = 0.0E0
      DO 10 I = 1,N
 10     SUM = SUM + (V(I)*W(I))**2
      SVNORM = SQRT(SUM/N)
      RETURN
      END
      SUBROUTINE SGEFA (A, LDA, N, IPVT, INFO)
      INTEGER LDA,N,IPVT(*),INFO
      REAL A(LDA,*)
      REAL T
      INTEGER ISAMAX,J,K,KP1,L,NM1
      INFO = 0
      NM1 = N - 1
      IF (NM1 .LT. 1) GO TO 70
      DO 60 K = 1, NM1
         KP1 = K + 1
         L = ISAMAX(N-K+1,A(K,K),1) + K - 1
         IPVT(K) = L
         IF (A(L,K) .EQ. 0.0E0) GO TO 40
            IF (L .EQ. K) GO TO 10
               T = A(L,K)
               A(L,K) = A(K,K)
               A(K,K) = T
   10       CONTINUE
            T = -1.0E0/A(K,K)
            CALL SSCAL(N-K,T,A(K+1,K),1)
            DO 30 J = KP1, N
               T = A(L,J)
               IF (L .EQ. K) GO TO 20
                  A(L,J) = A(K,J)
                  A(K,J) = T
   20          CONTINUE
               CALL SAXPY(N-K,T,A(K+1,K),1,A(K+1,J),1)
   30       CONTINUE
         GO TO 50
   40    CONTINUE
            INFO = K
   50    CONTINUE
   60 CONTINUE
   70 CONTINUE
      IPVT(N) = N
      IF (A(N,N) .EQ. 0.0E0) INFO = N
      RETURN
      END
      SUBROUTINE SGESL (A, LDA, N, IPVT, B, JOB)
      INTEGER LDA,N,IPVT(*),JOB
      REAL A(LDA,*),B(*)
      REAL SDOT,T
      INTEGER K,KB,L,NM1
      NM1 = N - 1
      IF (JOB .NE. 0) GO TO 50
         IF (NM1 .LT. 1) GO TO 30
         DO 20 K = 1, NM1
            L = IPVT(K)
            T = B(L)
            IF (L .EQ. K) GO TO 10
               B(L) = B(K)
               B(K) = T
   10       CONTINUE
            CALL SAXPY(N-K,T,A(K+1,K),1,B(K+1),1)
   20    CONTINUE
   30    CONTINUE
         DO 40 KB = 1, N
            K = N + 1 - KB
            B(K) = B(K)/A(K,K)
            T = -B(K)
            CALL SAXPY(K-1,T,A(1,K),1,B(1),1)
   40    CONTINUE
      GO TO 100
   50 CONTINUE
         DO 60 K = 1, N
            T = SDOT(K-1,A(1,K),1,B(1),1)
            B(K) = (B(K) - T)/A(K,K)
   60    CONTINUE
         IF (NM1 .LT. 1) GO TO 90
         DO 80 KB = 1, NM1
            K = N - KB
            B(K) = B(K) + SDOT(N-K,A(K+1,K),1,B(K+1),1)
            L = IPVT(K)
            IF (L .EQ. K) GO TO 70
               T = B(L)
               B(L) = B(K)
               B(K) = T
   70       CONTINUE
   80    CONTINUE
   90    CONTINUE
  100 CONTINUE
      RETURN
      END
      SUBROUTINE SGBFA (ABD, LDA, N, ML, MU, IPVT, INFO)
      INTEGER LDA,N,ML,MU,IPVT(*),INFO
      REAL ABD(LDA,*)
      REAL T
      INTEGER I,ISAMAX,I0,J,JU,JZ,J0,J1,K,KP1,L,LM,M,MM,NM1
      M = ML + MU + 1
      INFO = 0
      J0 = MU + 2
      J1 = MIN(N,M) - 1
      IF (J1 .LT. J0) GO TO 30
      DO 20 JZ = J0, J1
         I0 = M + 1 - JZ
         DO 10 I = I0, ML
            ABD(I,JZ) = 0.0E0
   10    CONTINUE
   20 CONTINUE
   30 CONTINUE
      JZ = J1
      JU = 0
      NM1 = N - 1
      IF (NM1 .LT. 1) GO TO 130
      DO 120 K = 1, NM1
         KP1 = K + 1
         JZ = JZ + 1
         IF (JZ .GT. N) GO TO 50
         IF (ML .LT. 1) GO TO 50
            DO 40 I = 1, ML
               ABD(I,JZ) = 0.0E0
   40       CONTINUE
   50    CONTINUE
         LM = MIN(ML,N-K)
         L = ISAMAX(LM+1,ABD(M,K),1) + M - 1
         IPVT(K) = L + K - M
         IF (ABD(L,K) .EQ. 0.0E0) GO TO 100
            IF (L .EQ. M) GO TO 60
               T = ABD(L,K)
               ABD(L,K) = ABD(M,K)
               ABD(M,K) = T
   60       CONTINUE
            T = -1.0E0/ABD(M,K)
            CALL SSCAL(LM,T,ABD(M+1,K),1)
            JU = MIN(MAX(JU,MU+IPVT(K)),N)
            MM = M
            IF (JU .LT. KP1) GO TO 90
            DO 80 J = KP1, JU
               L = L - 1
               MM = MM - 1
               T = ABD(L,J)
               IF (L .EQ. MM) GO TO 70
                  ABD(L,J) = ABD(MM,J)
                  ABD(MM,J) = T
   70          CONTINUE
               CALL SAXPY(LM,T,ABD(M+1,K),1,ABD(MM+1,J),1)
   80       CONTINUE
   90       CONTINUE
         GO TO 110
  100    CONTINUE
            INFO = K
  110    CONTINUE
  120 CONTINUE
  130 CONTINUE
      IPVT(N) = N
      IF (ABD(M,N) .EQ. 0.0E0) INFO = N
      RETURN
      END
      SUBROUTINE SGBSL (ABD, LDA, N, ML, MU, IPVT, B, JOB)
      INTEGER LDA,N,ML,MU,IPVT(*),JOB
      REAL ABD(LDA,*),B(*)
      REAL SDOT,T
      INTEGER K,KB,L,LA,LB,LM,M,NM1
      M = MU + ML + 1
      NM1 = N - 1
      IF (JOB .NE. 0) GO TO 50
         IF (ML .EQ. 0) GO TO 30
         IF (NM1 .LT. 1) GO TO 30
            DO 20 K = 1, NM1
               LM = MIN(ML,N-K)
               L = IPVT(K)
               T = B(L)
               IF (L .EQ. K) GO TO 10
                  B(L) = B(K)
                  B(K) = T
   10          CONTINUE
               CALL SAXPY(LM,T,ABD(M+1,K),1,B(K+1),1)
   20       CONTINUE
   30    CONTINUE
         DO 40 KB = 1, N
            K = N + 1 - KB
            B(K) = B(K)/ABD(M,K)
            LM = MIN(K,M) - 1
            LA = M - LM
            LB = K - LM
            T = -B(K)
            CALL SAXPY(LM,T,ABD(LA,K),1,B(LB),1)
   40    CONTINUE
      GO TO 100
   50 CONTINUE
         DO 60 K = 1, N
            LM = MIN(K,M) - 1
            LA = M - LM
            LB = K - LM
            T = SDOT(LM,ABD(LA,K),1,B(LB),1)
            B(K) = (B(K) - T)/ABD(M,K)
   60    CONTINUE
         IF (ML .EQ. 0) GO TO 90
         IF (NM1 .LT. 1) GO TO 90
            DO 80 KB = 1, NM1
               K = N - KB
               LM = MIN(ML,N-K)
               B(K) = B(K) + SDOT(LM,ABD(M+1,K),1,B(K+1),1)
               L = IPVT(K)
               IF (L .EQ. K) GO TO 70
                  T = B(L)
                  B(L) = B(K)
                  B(K) = T
   70          CONTINUE
   80       CONTINUE
   90    CONTINUE
  100 CONTINUE
      RETURN
      END
      SUBROUTINE SAXPY (N, SA, SX, INCX, SY, INCY)
      REAL SX(*), SY(*), SA
      IF (N.LE.0 .OR. SA.EQ.0.0E0) RETURN
      IF (INCX .EQ. INCY) IF (INCX-1) 5,20,60
    5 IX = 1
      IY = 1
      IF (INCX .LT. 0) IX = (-N+1)*INCX + 1
      IF (INCY .LT. 0) IY = (-N+1)*INCY + 1
      DO 10 I = 1,N
        SY(IY) = SY(IY) + SA*SX(IX)
        IX = IX + INCX
        IY = IY + INCY
   10 CONTINUE
      RETURN
   20 M = MOD(N,4)
      IF (M .EQ. 0) GO TO 40
      DO 30 I = 1,M
        SY(I) = SY(I) + SA*SX(I)
   30 CONTINUE
      IF (N .LT. 4) RETURN
   40 MP1 = M + 1
      DO 50 I = MP1,N,4
        SY(I) = SY(I) + SA*SX(I)
        SY(I+1) = SY(I+1) + SA*SX(I+1)
        SY(I+2) = SY(I+2) + SA*SX(I+2)
        SY(I+3) = SY(I+3) + SA*SX(I+3)
   50 CONTINUE
      RETURN
   60 NS = N*INCX
      DO 70 I = 1,NS,INCX
        SY(I) = SA*SX(I) + SY(I)
   70 CONTINUE
      RETURN
      END
      REAL FUNCTION SDOT (N, SX, INCX, SY, INCY)
      REAL SX(*), SY(*)
      SDOT = 0.0E0
      IF (N .LE. 0) RETURN
      IF (INCX .EQ. INCY) IF (INCX-1) 5,20,60
    5 IX = 1
      IY = 1
      IF (INCX .LT. 0) IX = (-N+1)*INCX + 1
      IF (INCY .LT. 0) IY = (-N+1)*INCY + 1
      DO 10 I = 1,N
        SDOT = SDOT + SX(IX)*SY(IY)
        IX = IX + INCX
        IY = IY + INCY
   10 CONTINUE
      RETURN
   20 M = MOD(N,5)
      IF (M .EQ. 0) GO TO 40
      DO 30 I = 1,M
        SDOT = SDOT + SX(I)*SY(I)
   30 CONTINUE
      IF (N .LT. 5) RETURN
   40 MP1 = M + 1
      DO 50 I = MP1,N,5
      SDOT = SDOT + SX(I)*SY(I) + SX(I+1)*SY(I+1) + SX(I+2)*SY(I+2) + &
                    SX(I+3)*SY(I+3) + SX(I+4)*SY(I+4)
   50 CONTINUE
      RETURN
   60 NS = N*INCX
      DO 70 I = 1,NS,INCX
        SDOT = SDOT + SX(I)*SY(I)
   70 CONTINUE
      RETURN
      END
      SUBROUTINE SSCAL (N, SA, SX, INCX)
      REAL SA, SX(*)
      INTEGER I, INCX, IX, M, MP1, N
      IF (N .LE. 0) RETURN
      IF (INCX .EQ. 1) GOTO 20
      IX = 1
      IF (INCX .LT. 0) IX = (-N+1)*INCX + 1
      DO 10 I = 1,N
        SX(IX) = SA*SX(IX)
        IX = IX + INCX
   10 CONTINUE
      RETURN
   20 M = MOD(N,5)
      IF (M .EQ. 0) GOTO 40
      DO 30 I = 1,M
        SX(I) = SA*SX(I)
   30 CONTINUE
      IF (N .LT. 5) RETURN
   40 MP1 = M + 1
      DO 50 I = MP1,N,5
        SX(I) = SA*SX(I)
        SX(I+1) = SA*SX(I+1)
        SX(I+2) = SA*SX(I+2)
        SX(I+3) = SA*SX(I+3)
        SX(I+4) = SA*SX(I+4)
   50 CONTINUE
      RETURN
      END
      INTEGER FUNCTION ISAMAX (N, SX, INCX)
      REAL SX(*), SMAX, XMAG
      INTEGER I, INCX, IX, N
      ISAMAX = 0
      IF (N .LE. 0) RETURN
      ISAMAX = 1
      IF (N .EQ. 1) RETURN
      IF (INCX .EQ. 1) GOTO 20
      IX = 1
      IF (INCX .LT. 0) IX = (-N+1)*INCX + 1
      SMAX = ABS(SX(IX))
      IX = IX + INCX
      DO 10 I = 2,N
        XMAG = ABS(SX(IX))
        IF (XMAG .GT. SMAX) THEN
          ISAMAX = I
          SMAX = XMAG
        ENDIF
        IX = IX + INCX
   10 CONTINUE
      RETURN
   20 SMAX = ABS(SX(1))
      DO 30 I = 2,N
        XMAG = ABS(SX(I))
        IF (XMAG .GT. SMAX) THEN
          ISAMAX = I
          SMAX = XMAG
        ENDIF
   30 CONTINUE
      RETURN
      END
      SUBROUTINE XERRWV (MSG, NMES, NERR, LEVEL, NI, I1, I2, NR, R1, R2)
      REAL R1, R2
      INTEGER NMES, NERR, LEVEL, NI, I1, I2, NR
      CHARACTER*(*) MSG
      INTEGER LUNIT, IXSAV, MESFLG
      LUNIT = IXSAV (1, 0, .FALSE.)
      MESFLG = IXSAV (2, 0, .FALSE.)
      IF (MESFLG .EQ. 0) GO TO 100
      WRITE (LUNIT,10)  MSG
 10   FORMAT(1X,A)
      IF (NI .EQ. 1) WRITE (LUNIT, 20) I1
 20   FORMAT(6X,'In above message,  I1 =',I10)
      IF (NI .EQ. 2) WRITE (LUNIT, 30) I1,I2
 30   FORMAT(6X,'In above message,  I1 =',I10,3X,'I2 =',I10)
      IF (NR .EQ. 1) WRITE (LUNIT, 40) R1
 40   FORMAT(6X,'In above message,  R1 =',E21.13)
      IF (NR .EQ. 2) WRITE (LUNIT, 50) R1,R2
 50   FORMAT(6X,'In above,  R1 =',E21.13,3X,'R2 =',E21.13)
 100  IF (LEVEL .NE. 2) RETURN
      STOP
      END
      SUBROUTINE XSETF (MFLAG)
      INTEGER MFLAG, JUNK, IXSAV
      IF (MFLAG .EQ. 0 .OR. MFLAG .EQ. 1) JUNK = IXSAV (2,MFLAG,.TRUE.)
      RETURN
      END
      SUBROUTINE XSETUN (LUN)
      INTEGER LUN, JUNK, IXSAV
      IF (LUN .GT. 0) JUNK = IXSAV (1,LUN,.TRUE.)
      RETURN
      END
      INTEGER FUNCTION IXSAV (IPAR, IVALUE, ISET)
      LOGICAL ISET
      INTEGER IPAR, IVALUE
      INTEGER IUMACH, LUNIT, MESFLG
      SAVE LUNIT, MESFLG
      DATA LUNIT/-1/, MESFLG/1/
      IF (IPAR .EQ. 1) THEN
        IF (LUNIT .EQ. -1) LUNIT = IUMACH()
        IXSAV = LUNIT
        IF (ISET) LUNIT = IVALUE
        ENDIF
      IF (IPAR .EQ. 2) THEN
        IXSAV = MESFLG
        IF (ISET) MESFLG = IVALUE
        ENDIF
      RETURN
      END
      INTEGER FUNCTION IUMACH()
      IUMACH = 6
      RETURN
      END
