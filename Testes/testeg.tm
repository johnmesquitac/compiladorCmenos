  0:  LOADI  29,99 
  1:  LOADI  30,100 
  2:  LOADI  31,_Fim 
  3:      J  main 
  4:  LABEL  minloc 
  5:   LOAD  1,2,30 
  6:  STORE  1,6,30 
  7:   LOAD  1,18577905,30 
  8:  STORE  1,5,30 
  9:   LOAD  1,2,30 
 10:  STORE  1,0,29 
 11:  LOADI  1,1 
 12:   LOAD  2,0,29 
 13:    ADD  1,2,1 
 14:  STORE  1,4,30 
 15:   LOAD  1,4,30 
 16:  STORE  1,0,29 
 17:   LOAD  1,3,30 
 18:   LOAD  2,0,29 
 19:    SLT  1,2,1 
 20:    BEQ  1,0,_Fim_While0 
 21:   LOAD  1,18580737,30 
 22:  STORE  1,0,29 
 23:   LOAD  1,5,30 
 24:   LOAD  2,0,29 
 25:    SLT  1,2,1 
 26:    BEQ  1,0,_Else0 
 27:   LOAD  1,18582065,30 
 28:  STORE  1,5,30 
 29:   LOAD  1,4,30 
 30:  STORE  1,6,30 
 31:      J  _Fim_If0 
 32:  LABEL  _Else0 
 33:  LABEL  _Fim_If0 
 34:   LOAD  1,4,30 
 35:  STORE  1,0,29 
 36:  LOADI  1,1 
 37:   LOAD  2,0,29 
 38:    ADD  1,2,1 
 39:  STORE  1,4,30 
 40:      J  15 
 41:  LABEL  _Fim_If0 
 42:   LOAD  1,6,30 
 43:  STORE  1,0,30 
 44:     JR  31 
 45:  LABEL  sort 
 46:   LOAD  1,2,30 
 47:  STORE  1,4,30 
 48:   LOAD  1,4,30 
 49:  STORE  1,0,29 
 50:   LOAD  1,3,30 
 51:  STORE  1,-1,29 
 52:  LOADI  1,1 
 53:   LOAD  2,-1,29 
 54:    SUB  1,2,1 
 55:   LOAD  2,0,29 
 56:    SLT  1,2,1 
 57:    BEQ  1,0,_Fim_While1 
 58:   ADDI  30,30,8 
 59:  STORE  31,0,29 
 60:   ADDI  1,30,1 
 61:  STORE  1,1,30 
 62:   LOAD  1,4,30 
 63:  STORE  1,2,30 
 64:   LOAD  1,3,30 
 65:  STORE  1,3,30 
 66:    JAL  minloc 
 67:   LOAD  31,0,29 
 68:   LOAD  1,0,30 
 69:   SUBI  30,30,8 
 70:  STORE  1,5,30 
 71:   LOAD  1,18593393,30 
 72:  STORE  1,6,30 
 73:   LOAD  1,18594721,30 
 74:  STORE  1,1,30 
 75:   LOAD  1,6,30 
 76:  STORE  1,1,30 
 77:   LOAD  1,4,30 
 78:  STORE  1,0,29 
 79:  LOADI  1,1 
 80:   LOAD  2,0,29 
 81:    ADD  1,2,1 
 82:  STORE  1,4,30 
 83:      J  48 
 84:  LABEL  _Fim_While1 
 85:     JR  31 
 86:  LABEL  gcd 
 87:   LOAD  1,2,30 
 88:  STORE  1,0,29 
 89:  LOADI  1,0 
 90:   LOAD  2,0,29 
 91:    SET  1,2,1 
 92:    BEQ  1,0,_Else1 
 93:   LOAD  1,1,30 
 94:  STORE  1,0,30 
 95:      J  _Fim_If1 
 96:  LABEL  _Else1 
 97:   ADDI  30,30,4 
 98:  STORE  31,0,29 
 99:   LOAD  1,2,30 
100:  STORE  1,1,30 
101:   LOAD  1,1,30 
102:  STORE  1,-1,29 
103:   LOAD  1,1,30 
104:  STORE  1,-2,29 
105:   LOAD  1,2,30 
106:   LOAD  2,-2,29 
107:    DIV  1,2,1 
108:  STORE  1,-2,29 
109:   LOAD  1,2,30 
110:   LOAD  2,-2,29 
111:   MULT  1,2,1 
112:   LOAD  2,-1,29 
113:    SUB  1,2,1 
114:  STORE  1,2,30 
115:    JAL  gcd 
116:   LOAD  31,0,29 
117:   LOAD  1,0,30 
118:   SUBI  30,30,4 
119:  STORE  1,0,30 
120:  LABEL  _Fim_If1 
121:     JR  31 
122:  LABEL  fibonacci 
123:   LOAD  1,1,30 
124:  STORE  1,0,29 
125:  LOADI  1,0 
126:   LOAD  2,0,29 
127:    SGT  1,1,2 
128:    BEQ  1,0,_Else2 
129:  LOADI  1,0 
130:  STORE  1,0,30 
131:      J  _Fim_If2 
132:  LABEL  _Else2 
133:   LOAD  1,1,30 
134:  STORE  1,0,29 
135:  LOADI  1,1 
136:   LOAD  2,0,29 
137:    SET  1,2,1 
138:    BEQ  1,0,_Else2 
139:  LOADI  1,1 
140:  STORE  1,0,30 
141:      J  _Fim_If2 
142:  LABEL  _Else2 
143:  LOADI  1,0 
144:  STORE  1,2,30 
145:  LOADI  1,1 
146:  STORE  1,5,30 
147:  STORE  1,3,30 
148:   LOAD  1,5,30 
149:  STORE  1,0,29 
150:   LOAD  1,1,30 
151:   LOAD  2,0,29 
152:    SLT  1,2,1 
153:    BEQ  1,0,_Fim_While2 
154:   LOAD  1,3,30 
155:  STORE  1,4,30 
156:   LOAD  1,3,30 
157:  STORE  1,0,29 
158:   LOAD  1,2,30 
159:   LOAD  2,0,29 
160:    ADD  1,2,1 
161:  STORE  1,3,30 
162:   LOAD  1,4,30 
163:  STORE  1,2,30 
164:   LOAD  1,5,30 
165:  STORE  1,0,29 
166:  LOADI  1,1 
167:   LOAD  2,0,29 
168:    ADD  1,2,1 
169:  STORE  1,5,30 
170:      J  148 
171:  LABEL  _Fim_While2 
172:   LOAD  1,3,30 
173:  STORE  1,0,30 
174:  LABEL  _Fim_If2 
175:  LABEL  _Fim_If3 
176:     JR  31 
177:  LABEL  buscaBinariaInterno 
178:   LOAD  1,3,30 
179:  STORE  1,0,29 
180:   LOAD  1,2,30 
181:   LOAD  2,0,29 
182:    ADD  1,2,1 
183:  STORE  1,0,29 
184:  LOADI  1,2 
185:   LOAD  2,0,29 
186:    DIV  1,2,1 
187:  STORE  1,5,30 
188:   LOAD  1,3,30 
189:  STORE  1,0,29 
190:   LOAD  1,2,30 
191:   LOAD  2,0,29 
192:    SLT  1,2,1 
193:    BEQ  1,0,_Else4 
194:  LOADI  1,0 
195:  STORE  1,0,29 
196:  LOADI  1,1 
197:   LOAD  2,0,29 
198:    SUB  1,2,1 
199:  STORE  1,0,30 
200:      J  _Fim_If4 
201:  LABEL  _Else4 
202:   LOAD  1,4,30 
203:  STORE  1,0,29 
204:   LOAD  1,4229556,30 
205:   LOAD  2,0,29 
206:    SGT  1,2,1 
207:    BEQ  1,0,_Else4 
208:   ADDI  30,30,7 
209:  STORE  31,0,29 
210:   ADDI  1,30,1 
211:  STORE  1,1,30 
212:   LOAD  1,5,30 
213:  STORE  1,-1,29 
214:  LOADI  1,1 
215:   LOAD  2,-1,29 
216:    ADD  1,2,1 
217:  STORE  1,2,30 
218:   LOAD  1,3,30 
219:  STORE  1,3,30 
220:   LOAD  1,4,30 
221:  STORE  1,4,30 
222:    JAL  buscaBinariaInterno 
223:   LOAD  31,0,29 
224:   LOAD  1,0,30 
225:   SUBI  30,30,7 
226:  STORE  1,0,30 
227:      J  _Fim_If4 
228:  LABEL  _Else4 
229:   LOAD  1,4,30 
230:  STORE  1,0,29 
231:   LOAD  1,4229556,30 
232:   LOAD  2,0,29 
233:    SLT  1,2,1 
234:    BEQ  1,0,_Else4 
235:   ADDI  30,30,7 
236:  STORE  31,0,29 
237:   ADDI  1,30,1 
238:  STORE  1,1,30 
239:   LOAD  1,2,30 
240:  STORE  1,2,30 
241:   LOAD  1,5,30 
242:  STORE  1,-1,29 
243:  LOADI  1,1 
244:   LOAD  2,-1,29 
245:    SUB  1,2,1 
246:  STORE  1,3,30 
247:   LOAD  1,4,30 
248:  STORE  1,4,30 
249:    JAL  buscaBinariaInterno 
250:   LOAD  31,0,29 
251:   LOAD  1,0,30 
252:   SUBI  30,30,7 
253:  STORE  1,0,30 
254:      J  _Fim_If4 
255:  LABEL  _Else4 
256:   LOAD  1,5,30 
257:  STORE  1,0,30 
258:  LABEL  _Fim_If4 
259:  LABEL  _Fim_If5 
260:  LABEL  _Fim_If6 
261:     JR  31 
262:  LABEL  buscaBinaria 
263:   ADDI  30,30,5 
264:  STORE  31,0,29 
265:   ADDI  1,30,1 
266:  STORE  1,1,30 
267:  LOADI  1,1 
268:  STORE  1,2,30 
269:   LOAD  1,2,30 
270:  STORE  1,3,30 
271:   LOAD  1,3,30 
272:  STORE  1,4,30 
273:    JAL  buscaBinariaInterno 
274:   LOAD  31,0,29 
275:   LOAD  1,0,30 
276:   SUBI  30,30,5 
277:  STORE  1,0,30 
278:     JR  31 
279:  LABEL  iteraVector 
280:   LOAD  1,3,30 
281:  STORE  1,0,29 
282:   LOAD  1,2,30 
283:   LOAD  2,0,29 
284:    SLT  1,2,1 
285:    BEQ  1,0,_Else7 
286:   LOAD  1,4,30 
287:  STORE  1,0,29 
288:  LOADI  1,0 
289:   LOAD  2,0,29 
290:    SET  1,2,1 
291:    BEQ  1,0,_Else7 
292:     IN  1 
293:  STORE  1,1,30 
294:      J  _Fim_If7 
295:  LABEL  _Else7 
296:    OUT  18641216,1 
297:  LABEL  _Fim_If7 
298:   ADDI  30,30,8 
299:  STORE  31,0,29 
300:   ADDI  1,30,1 
301:  STORE  1,1,30 
302:   LOAD  1,2,30 
303:  STORE  1,2,30 
304:   LOAD  1,3,30 
305:  STORE  1,-1,29 
306:  LOADI  1,1 
307:   LOAD  2,-1,29 
308:    ADD  1,2,1 
309:  STORE  1,3,30 
310:   LOAD  1,4,30 
311:  STORE  1,4,30 
312:    JAL  iteraVector 
313:   LOAD  31,0,29 
314:   LOAD  1,0,30 
315:   SUBI  30,30,8 
316:      J  _Fim_If8 
317:  LABEL  _Else8 
318:  LABEL  _Fim_If8 
319:     JR  31 
320:  LABEL  inputVector 
321:   ADDI  30,30,4 
322:  STORE  31,0,29 
323:   ADDI  1,30,1 
324:  STORE  1,1,30 
325:   LOAD  1,2,30 
326:  STORE  1,2,30 
327:  LOADI  1,0 
328:  STORE  1,3,30 
329:  LOADI  1,0 
330:  STORE  1,4,30 
331:    JAL  iteraVector 
332:   LOAD  31,0,29 
333:   LOAD  1,0,30 
334:   SUBI  30,30,4 
335:     JR  31 
336:  LABEL  outputVector 
337:   ADDI  30,30,4 
338:  STORE  31,0,29 
339:   ADDI  1,30,1 
340:  STORE  1,1,30 
341:   LOAD  1,2,30 
342:  STORE  1,2,30 
343:  LOADI  1,0 
344:  STORE  1,3,30 
345:  LOADI  1,1 
346:  STORE  1,4,30 
347:    JAL  iteraVector 
348:   LOAD  31,0,29 
349:   LOAD  1,0,30 
350:   SUBI  30,30,4 
351:     JR  31 
352:  LABEL  main 
353:     IN  1 
354:  STORE  1,1,30 
355:   LOAD  1,1,30 
356:  STORE  1,0,29 
357:  LOADI  1,0 
358:   LOAD  2,0,29 
359:    SGT  1,2,1 
360:    BEQ  1,0,_Fim_While3 
361:   LOAD  1,1,30 
362:  STORE  1,0,29 
363:  LOADI  1,1 
364:   LOAD  2,0,29 
365:    SET  1,2,1 
366:    BEQ  1,0,_Else9 
367:   ADDI  30,30,13 
368:  STORE  31,0,29 
369:   LOAD  1,0,30 
370:  STORE  1,1,30 
371:  LOADI  1,10 
372:  STORE  1,2,30 
373:    JAL  inputVector 
374:   LOAD  31,0,29 
375:   LOAD  1,0,30 
376:   SUBI  30,30,13 
377:   ADDI  30,30,13 
378:  STORE  31,0,29 
379:   LOAD  1,0,30 
380:  STORE  1,1,30 
381:  LOADI  1,0 
382:  STORE  1,2,30 
383:  LOADI  1,10 
384:  STORE  1,3,30 
385:    JAL  sort 
386:   LOAD  31,0,29 
387:   LOAD  1,0,30 
388:   SUBI  30,30,13 
389:   ADDI  30,30,13 
390:  STORE  31,0,29 
391:   LOAD  1,0,30 
392:  STORE  1,1,30 
393:  LOADI  1,10 
394:  STORE  1,2,30 
395:    JAL  outputVector 
396:   LOAD  31,0,29 
397:   LOAD  1,0,30 
398:   SUBI  30,30,13 
399:      J  _Fim_If9 
400:  LABEL  _Else9 
401:   LOAD  1,1,30 
402:  STORE  1,0,29 
403:  LOADI  1,2 
404:   LOAD  2,0,29 
405:    SET  1,2,1 
406:    BEQ  1,0,_Else9 
407:     IN  1 
408:  STORE  1,2,30 
409:     IN  1 
410:  STORE  1,3,30 
411:    OUT  18659504,1 
412:      J  _Fim_If9 
413:  LABEL  _Else9 
414:   LOAD  1,1,30 
415:  STORE  1,0,29 
416:  LOADI  1,3 
417:   LOAD  2,0,29 
418:    SET  1,2,1 
419:    BEQ  1,0,_Else9 
420:    OUT  18661344,1 
421:      J  _Fim_If9 
422:  LABEL  _Else9 
423:   LOAD  1,1,30 
424:  STORE  1,0,29 
425:  LOADI  1,4 
426:   LOAD  2,0,29 
427:    SET  1,2,1 
428:    BEQ  1,0,_Else9 
429:     IN  1 
430:  STORE  1,2,30 
431:    OUT  18663696,1 
432:      J  _Fim_If9 
433:  LABEL  _Else9 
434:  LABEL  _Fim_If9 
435:  LABEL  _Fim_If10 
436:  LABEL  _Fim_If11 
437:  LABEL  _Fim_If12 
438:     IN  1 
439:  STORE  1,1,30 
440:      J  355 
441:  LABEL  _Fim_If12 
442:     JR  31 
443:  LABEL  _Fim 
444: HALT 