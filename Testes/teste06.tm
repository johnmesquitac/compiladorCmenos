  0:  LOADI  28,99 
  1:  LOADI  30,101 
  2:  LOADI  29,100 
  3:  LOADI  0,0 
  4:  LOADI  31,_Fim 
  5:      J  main 
  6:  LABEL  gcd 
  7:   LOAD  1,2,30 
  8:  STORE  1,0,28 
  9:   SUBI  28,28,1 
 10:  LOADI  1,0 
 11:   ADDI  28,28,1 
 12:   LOAD  2,0,28 
 13:    SET  1,2,1 
 14:  LOADI  0,0 
 15:    BEQ  1,0,_Else0 
 16:   LOAD  1,1,30 
 17:  STORE  1,0,30 
 18:     JR  31 
 19:      J  _Fim_If0 
 20:  LABEL  _Else0 
 21:  STORE  31,0,28 
 22:   SUBI  28,28,1 
 23:   LOAD  1,2,30 
 24:   ADDI  30,30,3 
 25:  STORE  1,1,30 
 26:   SUBI  30,30,3 
 27:   LOAD  1,1,30 
 28:  STORE  1,0,28 
 29:   SUBI  28,28,1 
 30:   LOAD  1,1,30 
 31:  STORE  1,0,28 
 32:   SUBI  28,28,1 
 33:   LOAD  1,2,30 
 34:   ADDI  28,28,1 
 35:   LOAD  2,0,28 
 36:    DIV  1,2,1 
 37:  STORE  1,0,28 
 38:   SUBI  28,28,1 
 39:   LOAD  1,2,30 
 40:   ADDI  28,28,1 
 41:   LOAD  2,0,28 
 42:   MULT  1,2,1 
 43:   ADDI  28,28,1 
 44:   LOAD  2,0,28 
 45:    SUB  1,2,1 
 46:   ADDI  30,30,3 
 47:  STORE  1,2,30 
 48:   SUBI  30,30,3 
 49:   ADDI  30,30,3 
 50:    JAL  gcd 
 51:   ADDI  28,28,1 
 52:   LOAD  31,0,28 
 53:   LOAD  1,0,30 
 54:   SUBI  30,30,3 
 55:  STORE  1,0,30 
 56:     JR  31 
 57:  LABEL  _Fim_If0 
 58:     JR  31 
 59:  LABEL  main 
 60:     IN  1 
 61:  STORE  1,1,30 
 62:     IN  1 
 63:  STORE  1,2,30 
 64:  STORE  31,0,28 
 65:   SUBI  28,28,1 
 66:   LOAD  1,1,30 
 67:   ADDI  30,30,3 
 68:  STORE  1,1,30 
 69:   SUBI  30,30,3 
 70:   LOAD  1,2,30 
 71:   ADDI  30,30,3 
 72:  STORE  1,2,30 
 73:   SUBI  30,30,3 
 74:   ADDI  30,30,3 
 75:    JAL  gcd 
 76:   ADDI  28,28,1 
 77:   LOAD  31,0,28 
 78:   LOAD  1,0,30 
 79:   SUBI  30,30,3 
 80:    OUT  2,1 
 81:     JR  31 
 82:  LABEL  _Fim 
 83: HALT 