  0:  LOADI  28,99 
  1:  LOADI  30,104 
  2:  LOADI  29,100 
  3:  LOADI  0,0 
  4:  LOADI  31,_Fim 
  5:      J  main 
  6:  LABEL  minloc 
  7:   LOAD  1,2,30 
  8:  STORE  1,6,30 
  9:   LOAD  1,2,30 
 10:   LOAD  3,1,30 
 11:    ADD  3,1,3 
 12:   LOAD  1,0,3 
 13:  STORE  1,5,30 
 14:   LOAD  1,2,30 
 15:  STORE  1,0,28 
 16:   SUBI  28,28,1 
 17:  LOADI  1,1 
 18:   ADDI  28,28,1 
 19:   LOAD  2,0,28 
 20:    ADD  1,2,1 
 21:  STORE  1,4,30 
 22:   LOAD  1,4,30 
 23:  STORE  1,0,28 
 24:   SUBI  28,28,1 
 25:   LOAD  1,3,30 
 26:   ADDI  28,28,1 
 27:   LOAD  2,0,28 
 28:    SLT  1,2,1 
 29:  LOADI  0,0 
 30:    BEQ  1,0,_Fim_While0 
 31:   LOAD  1,4,30 
 32:   LOAD  3,1,30 
 33:    ADD  3,1,3 
 34:   LOAD  1,0,3 
 35:  STORE  1,0,28 
 36:   SUBI  28,28,1 
 37:   LOAD  1,5,30 
 38:   ADDI  28,28,1 
 39:   LOAD  2,0,28 
 40:    SLT  1,2,1 
 41:  LOADI  0,0 
 42:    BEQ  1,0,_Else0 
 43:   LOAD  1,4,30 
 44:   LOAD  3,1,30 
 45:    ADD  3,1,3 
 46:   LOAD  1,0,3 
 47:  STORE  1,5,30 
 48:   LOAD  1,4,30 
 49:  STORE  1,6,30 
 50:      J  _Fim_If0 
 51:  LABEL  _Else0 
 52:  LABEL  _Fim_If0 
 53:   LOAD  1,4,30 
 54:  STORE  1,0,28 
 55:   SUBI  28,28,1 
 56:  LOADI  1,1 
 57:   ADDI  28,28,1 
 58:   LOAD  2,0,28 
 59:    ADD  1,2,1 
 60:  STORE  1,4,30 
 61:      J  22 
 62:  LABEL  _Fim_While0 
 63:   LOAD  1,6,30 
 64:  STORE  1,0,30 
 65:     JR  31 
 66:     JR  31 
 67:  LABEL  sort 
 68:   LOAD  1,2,30 
 69:  STORE  1,4,30 
 70:   LOAD  1,4,30 
 71:  STORE  1,0,28 
 72:   SUBI  28,28,1 
 73:   LOAD  1,3,30 
 74:  STORE  1,0,28 
 75:   SUBI  28,28,1 
 76:  LOADI  1,1 
 77:   ADDI  28,28,1 
 78:   LOAD  2,0,28 
 79:    SUB  1,2,1 
 80:   ADDI  28,28,1 
 81:   LOAD  2,0,28 
 82:    SLT  1,2,1 
 83:  LOADI  0,0 
 84:    BEQ  1,0,_Fim_While1 
 85:  STORE  31,0,28 
 86:   SUBI  28,28,1 
 87:   LOAD  1,1,30 
 88:   ADDI  30,30,7 
 89:  STORE  1,1,30 
 90:   SUBI  30,30,7 
 91:   LOAD  1,4,30 
 92:   ADDI  30,30,7 
 93:  STORE  1,2,30 
 94:   SUBI  30,30,7 
 95:   LOAD  1,3,30 
 96:   ADDI  30,30,7 
 97:  STORE  1,3,30 
 98:   SUBI  30,30,7 
 99:   ADDI  30,30,7 
100:    JAL  minloc 
101:   ADDI  28,28,1 
102:   LOAD  31,0,28 
103:   LOAD  1,0,30 
104:   SUBI  30,30,7 
105:  STORE  1,5,30 
106:   LOAD  1,5,30 
107:   LOAD  3,1,30 
108:    ADD  3,1,3 
109:   LOAD  1,0,3 
110:  STORE  1,6,30 
111:   LOAD  1,4,30 
112:   LOAD  3,1,30 
113:    ADD  3,1,3 
114:   LOAD  1,0,3 
115:  STORE  1,0,28 
116:   SUBI  28,28,1 
117:   LOAD  1,5,30 
118:   ADDI  28,28,1 
119:   LOAD  2,0,28 
120:   LOAD  3,1,30 
121:    ADD  3,1,3 
122:  STORE  2,0,3 
123:   LOAD  1,6,30 
124:  STORE  1,0,28 
125:   SUBI  28,28,1 
126:   LOAD  1,4,30 
127:   ADDI  28,28,1 
128:   LOAD  2,0,28 
129:   LOAD  3,1,30 
130:    ADD  3,1,3 
131:  STORE  2,0,3 
132:   LOAD  1,4,30 
133:  STORE  1,0,28 
134:   SUBI  28,28,1 
135:  LOADI  1,1 
136:   ADDI  28,28,1 
137:   LOAD  2,0,28 
138:    ADD  1,2,1 
139:  STORE  1,4,30 
140:      J  70 
141:  LABEL  _Fim_While1 
142:     JR  31 
143:  LABEL  main 
144:  LOADI  1,0 
145:  STORE  1,1,30 
146:   LOAD  1,1,30 
147:  STORE  1,0,28 
148:   SUBI  28,28,1 
149:  LOADI  1,3 
150:   ADDI  28,28,1 
151:   LOAD  2,0,28 
152:    SLT  1,2,1 
153:  LOADI  0,0 
154:    BEQ  1,0,_Fim_While2 
155:     IN  1 
156:  STORE  1,0,28 
157:   SUBI  28,28,1 
158:   LOAD  1,1,30 
159:   ADDI  28,28,1 
160:   LOAD  2,0,28 
161:    ADD  3,1,29 
162:  STORE  2,0,3 
163:   LOAD  1,1,30 
164:  STORE  1,0,28 
165:   SUBI  28,28,1 
166:  LOADI  1,1 
167:   ADDI  28,28,1 
168:   LOAD  2,0,28 
169:    ADD  1,2,1 
170:  STORE  1,1,30 
171:      J  146 
172:  LABEL  _Fim_While2 
173:  STORE  31,0,28 
174:   SUBI  28,28,1 
175:   ADDI  1,29,0 
176:   ADDI  30,30,2 
177:  STORE  1,1,30 
178:   SUBI  30,30,2 
179:  LOADI  1,0 
180:   ADDI  30,30,2 
181:  STORE  1,2,30 
182:   SUBI  30,30,2 
183:  LOADI  1,3 
184:   ADDI  30,30,2 
185:  STORE  1,3,30 
186:   SUBI  30,30,2 
187:   ADDI  30,30,2 
188:    JAL  sort 
189:   ADDI  28,28,1 
190:   LOAD  31,0,28 
191:   LOAD  1,0,30 
192:   SUBI  30,30,2 
193:  LOADI  1,0 
194:  STORE  1,1,30 
195:   LOAD  1,1,30 
196:  STORE  1,0,28 
197:   SUBI  28,28,1 
198:  LOADI  1,3 
199:   ADDI  28,28,1 
200:   LOAD  2,0,28 
201:    SLT  1,2,1 
202:  LOADI  0,0 
203:    BEQ  1,0,_Fim_While3 
204:   LOAD  1,1,30 
205:    ADD  3,1,29 
206:   LOAD  1,0,3 
207:    OUT  2,1 
208:   LOAD  1,1,30 
209:  STORE  1,0,28 
210:   SUBI  28,28,1 
211:  LOADI  1,1 
212:   ADDI  28,28,1 
213:   LOAD  2,0,28 
214:    ADD  1,2,1 
215:  STORE  1,1,30 
216:      J  195 
217:  LABEL  _Fim_While3 
218:     JR  31 
219:  LABEL  _Fim 
220: HALT 