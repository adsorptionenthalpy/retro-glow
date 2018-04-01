SCREEN 7, 0, 1, 0

DEF SEG = 0 ' Needed for peek instruction

bx = 160
by = 100
p1x = 20
p1y = 80
p2y = 80
p2x = 300
xadj = 1
yadj = 1
b1x = 30
b1y = 20
b2x = 30
b2y = 180

SOUND 300, 2
SOUND 500, 2
SOUND 300, 2
SOUND 500, 2

DO
POKE &H1C, PEEK(&H1A) 'CLEAR KEYS

PCOPY 1, 0
LINE (0, 0)-(320, 200), 0, BF

LINE (160, 20)-(160, 180), 15
LOCATE 1, 3: PRINT score1
LOCATE 1, 36.5: PRINT score2
LOCATE 1, 17: PRINT "P O N G"

bx = bx + xadj
by = by + yadj
CIRCLE (bx, by), 3
PAINT (bx, by), 15, 15
press$ = INKEY$
'paddle one
LINE (p1x, p1y)-(p1x + 7, p1y + 30), 15, BF
IF INP(&H60) = 72 AND p1y > 40 THEN p1y = p1y - 5
IF INP(&H60) = 80 AND p1y < 130 THEN p1y = p1y + 5

'paddle two
LINE (p2x, p2y)-(p2x - 7, p2y + 30), 15, BF

k = PEEK(&H417)
IF (k AND 4) AND p2y > 40 THEN p2y = p2y - 5
IF (k AND 8) AND p2y < 130 THEN p2y = p2y + 5

'top board
LINE (b1x, b1y)-(b1x + 260, b1y + 20), 15, BF
'bottom board
LINE (b2x, b2y)-(b2x + 260, b2y - 20), 15, BF
'collision detection
IF bx <= p1x + 12 AND by > p1y - 1 AND by < p1y + 30 THEN xadj = xadj * -1: SOUND 550, 1
IF bx >= p2x - 12 AND by > p2y - 1 AND by < p2y + 30 THEN xadj = xadj * -1: SOUND 550, 1
IF by <= b1y + 20 AND bx > b1x - 1 AND by < b1x + 260 THEN yadj = yadj * -1: SOUND 550, 1
IF by >= b2y - 20 AND bx > b2x - 1 AND by < b2x + 260 THEN yadj = yadj * -1: SOUND 550, 1
'score keeping
IF bx <= 1 THEN score2 = score2 + 1: bx = 160: by = 100: xadj = xadj * -1 + 2: SOUND 300, 1: SLEEP 1
IF bx >= 320 THEN score1 = score1 + 1: bx = 160: by = 100: xadj = xadj * -1 - 2: SOUND 300, 1: SLEEP 1

IF xadj >= 8 THEN xadj = 8

LOOP UNTIL press$ = CHR$(27)
SOUND 300, 4
SOUND 250, 4

