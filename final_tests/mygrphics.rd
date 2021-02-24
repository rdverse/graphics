# Creating an artifact

Display "MyGraphics"  "Screen" "rgbsingle"
Format 650 1000


Background 0.12 0.14 0.2

# The next three lines will be ignored by your renderer
CameraEye 200 200 -200
CameraAt  200 200 0
CameraUp  0.0 -1.0 0.0


FrameBegin 1

WorldBegin

#Lines

Color 0.9 0.9 0.9

Circle 250 500 0 20
Circle 240 500 0 30
Circle 230 500 0 40
Circle 220 500 0 50
Circle 210 500 0 60
Circle 200 500 0 70
Circle 190 500 0 80
Circle 180 500 0 90
Circle 170 500 0 110
Circle 160 500 0 130
Circle 150 500 0 140


Circle 400 500 0 20
Circle 410 500 0 30
Circle 420 500 0 40
Circle 430 500 0 50
Circle 440 500 0 60
Circle 450 500 0 70
Circle 460 500 0 80
Circle 470 500 0 90
Circle 480 500 0 110
Circle 490 500 0 130
Circle 500 500 0 140

# Face Border
Line 10 500 0 10 750 0
Line 10 500 0 10 250 0
Line 10 750 0 210 900 0

Line 440 900 0 210 900 0

Line 640 500 0 640 750 0
Line 640 500 0 640 250 0
Line 440 900 0 640 750 0

# Hair

Line 10 250 0 650 250 0
Line 10 250 0 650 200 0
Line 10 250 0 650 150 0
Line 10 250 0 650 100 0


#Nose
Line 320 600 0 350 660 0
Line 320 600 0 290 660 0
Line 351 660 0 290 660 0
Line 320 600 0 320 660 0



#Mouth NOse color

Color 0.8 0.8 0.8
Fill 314 646 0
Color 0.6 0.6 0.6
Fill 329 642 0

#Mouth
Color 0.8 0.1 0.1
Circle 230 750 0 50
Circle 230 750 0 48
Circle 230 750 0 46
Circle 230 750 0 44
Circle 230 750 0 42
Circle 230 750 0 40
Circle 230 750 0 38
Circle 230 750 0 36
Circle 230 750 0 34
Circle 230 750 0 32
Circle 230 750 0 30
Circle 230 750 0 28
Circle 230 750 0 26
Circle 230 750 0 24
Circle 230 750 0 22
Circle 230 750 0 20
Circle 230 750 0 18
Circle 230 750 0 16
Circle 230 750 0 14
Circle 230 750 0 12
Circle 230 750 0 10
Circle 230 750 0 8
Circle 230 750 0 6
Circle 230 750 0 4
Circle 230 750 0 2
Circle 230 750 0 1


#EXTRAS
Circle 72 84 0 20
Circle 187 942 0 20
Circle 402 945 0 30
Circle 190 155 0 10
Circle 493 49 0 20

Circle 32 827 0 20
Circle 364 125 0 10
Circle 595 857 0 10
Circle 264 21 0 10
Circle 264 21 0 10



# extra color
Color 0.15 0.52 0.21
Fill 72 84 0
Fill 187 942 0
Fill 402 945 0
Fill 190 155 0
Fill 493 49 0

Color 0.52 0.2 0.1
Fill 32 827 0
Fill 364 125 0
Fill 595 857 0
Fill 264 21 0
Fill 264 21 0

#hAIR COLOR
Color 0.5 0.2 0.6
Fill 593 227 0
Color 0.4 0.1 0.5
Fill 601 185 0
Color 0.2 0.1 0.4
Fill 602 135 0

# Left eye color
Color 0.1 0.1 0.1
Fill 250 500 0
Color 0.2 0.5 0.8
Fill 220 500 0
Color 0.6 0.75 0.85
Fill 205 500 0
Color 0.6 0.75 0.85
Fill 205 500 0
Color 0.8 0.8 0.8
Fill 183 500 0
Color 0.6 0.75 0.75
Fill 162 500 0
Color 0.6 0.75 0.75
Fill 162 500 0
Color 0.3 0.65 0.85
Fill 143 500 0
Color 0.3 0.85 0.65
Fill 125 500 0
Color 0.3 0.65 0.95
Fill 100 500 0
Color 0.3 0.85 0.95
Fill 77 500 0
Color 0.23 0.35 0.95
Fill 45 500 0
Color 0.1 0.2 0.5
Fill 22 500 0


# Right eye color

Color 0.1 0.1 0.1
Fill 406 500 0
Color 0.75 0.5 0.25
Fill 429 500 0
Color 0.8 0.75 0.65
Fill 452 500 0

Color 0.85 0.5 0.1
Fill 470 500 0
Color 0.8 0.8 0.8
Fill 483 500 0
Color 0.75 0.75 0.6
Fill 496 500 0
Color 0.75 0.75 0.4
Fill 514 500 0
Color 0.85 0.65 0.3
Fill 533 500 0
Color 0.65 0.85 0.3
Fill 555 500 0
Color 0.95 0.65 0.25
Fill 576 500 0
Color 0.95 0.35 0.30
Fill 602 500 0
Color 0.5 0.2 0.1
Fill 628 500 0
Color 0.5 0.2 0.1
Fill 22 500 0


Color 0.6 0.6 0.6
Line 320 250 0 320 900 0
Fill 25 266 0

Color 0.8 0.8 0.8
Fill 428 881 0


WorldEnd
FrameEnd
