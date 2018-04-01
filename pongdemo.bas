SCREEN 7, 0, 1, 0

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

DO
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
IF press$ = "q" AND p1y > 40 THEN p1y = p1y - 5
IF press$ = "a" AND p1y < 130 THEN p1y = p1y + 5
'paddle two
LINE (p2x, p2y)-(p2x - 7, p2y + 30), 15, BF
IF press$ = CHR$(0) + CHR$(72) AND p2y > 40 THEN p2y = p2y - 5
IF press$ = CHR$(0) + CHR$(80) AND p2y < 130 THEN p2y = p2y + 5

'top board
LINE (b1x, b1y)-(b1x + 260, b1y + 20), 15, BF
'bottom board
LINE (b2x, b2y)-(b2x + 260, b2y - 20), 15, BF
'collision detection
IF bx <= p1x + 12 AND by > p1y - 1 AND by < p1y + 30 THEN xadj = 1
IF bx >= p2x - 12 AND by > p2y - 1 AND by < p2y + 30 THEN xadj = -1
IF by <= b1y + 20 AND bx > b1x - 1 AND by < b1x + 260 THEN yadj = 1
IF by >= b2y - 20 AND bx > b2x - 1 AND by < b2x + 260 THEN yadj = -1
'score keeping
IF bx <= 1 THEN score2 = score2 + 1: bx = 160: by = 100: SLEEP 1: xadj = 1
IF bx >= 320 THEN score1 = score1 + 1: bx = 160: by = 100: SLEEP 1: xadj = -1

LOOP UNTIL press$ = CHR$(27)
