  0:  LOADI  28,99 
  1:  LOADI  30,101 
  2:  LOADI  29,100 
  3:  LOADI  0,0 
  4:  LOADI  31,_Fim 
  5:      J  main 
  6:  LABEL  main 
  7:  LOADI  1,1 
  8:  STORE  1,1,30 
  9:  LOADI  1,2 
 10:  STORE  1,0,28 
 11:   SUBI  28,28,1 
 12:   LOAD  1,1,30 
 13:   ADDI  28,28,1 
 14:   LOAD  2,0,28 
 15:    ADD  1,2,1 
 16:  STORE  1,2,30 
 17:   LOAD  1,1,30 
 18:    OUT  0,1 
 19:   LOAD  1,2,30 
 20:    OUT  1,1 
 21:   LOAD  1,1,30 
 22:  STORE  1,0,28 
 23:   SUBI  28,28,1 
 24:   LOAD  1,2,30 
 25:   ADDI  28,28,1 
 26:   LOAD  2,0,28 
 27:   MULT  1,2,1 
 28:  STORE  1,1,30 
 29:   LOAD  1,2,30 
 30:  STORE  1,0,28 
 31:   SUBI  28,28,1 
 32:   LOAD  1,1,30 
 33:   ADDI  28,28,1 
 34:   LOAD  2,0,28 
 35:    DIV  1,2,1 
 36:  STORE  1,0,28 
 37:   SUBI  28,28,1 
 38:  LOADI  1,1 
 39:   ADDI  28,28,1 
 40:   LOAD  2,0,28 
 41:    ADD  1,2,1 
 42:  STORE  1,2,30 
 43:   LOAD  1,1,30 
 44:    OUT  0,1 
 45:   LOAD  1,2,30 
 46:    OUT  1,1 
 47:     IN  1 
 48:  STORE  1,3,30 
 49:   LOAD  1,3,30 
 50:    OUT  2,1 
 51:   LOAD  1,1,30 
 52:  STORE  1,0,28 
 53:   SUBI  28,28,1 
 54:   LOAD  1,2,30 
 55:   ADDI  28,28,1 
 56:   LOAD  2,0,28 
 57:    SGT  1,2,1 
 58:    BEQ  1,0,_Else0 
 59:   LOAD  1,1,30 
 60:  STORE  1,0,28 
 61:   SUBI  28,28,1 
 62:   LOAD  1,2,30 
 63:   ADDI  28,28,1 
 64:   LOAD  2,0,28 
 65:    ADD  1,2,1 
 66:  STORE  1,1,30 
 67:      J  _Fim_If0 
 68:  LABEL  _Else0 
 69:  LABEL  _Fim_If0 
 70:   LOAD  1,2,30 
 71:  STORE  1,0,28 
 72:   SUBI  28,28,1 
 73:  LOADI  1,2 
 74:   ADDI  28,28,1 
 75:   LOAD  2,0,28 
 76:    SET  1,2,1 
 77:    BEQ  1,0,_Else1 
 78:   LOAD  1,3,30 
 79:  STORE  1,2,30 
 80:      J  _Fim_If1 
 81:  LABEL  _Else1 
 82:  LABEL  _Fim_If1 
 83:   LOAD  1,1,30 
 84:    OUT  0,1 
 85:   LOAD  1,2,30 
 86:    OUT  1,1 
 87:   LOAD  1,1,30 
 88:  STORE  1,0,28 
 89:   SUBI  28,28,1 
 90:  LOADI  1,10 
 91:   ADDI  28,28,1 
 92:   LOAD  2,0,28 
 93:    SLT  1,2,1 
 94:    BEQ  1,0,_Fim_While0 
 95:   LOAD  1,1,30 
 96:  STORE  1,0,28 
 97:   SUBI  28,28,1 
 98:  LOADI  1,1 
 99:   ADDI  28,28,1 
100:   LOAD  2,0,28 
101:    ADD  1,2,1 
102:  STORE  1,1,30 
103:   LOAD  1,1,30 
104:    OUT  2,1 
105:      J  87 
106:  LABEL  _Fim_While0 
107:  LOADI  1,5 
108:    OUT  0,1 
109:  LOADI  1,5 
110:    OUT  1,1 
111:  LOADI  1,5 
112:    OUT  2,1 
113:  STORE  1,0,30 
114:     JR  31 
115:     JR  31 
116:  LABEL  _Fim 
117: HALT 
