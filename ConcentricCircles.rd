# This is a test/example rd file

Display "Concentric Circles"  "PNM" "rgb"
Format 1000 900


# The next three lines will be ignored by your renderer
CameraEye 250 150 -150
CameraAt  250 150 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

Background 0.0 0.0 0.0

WorldBegin

# Brown
Color 0.6 0.2 0.01
Circle 500 450 0 20
Fill 500 450 0

# Dark gray
Color 0.8 0.8 0.8
Circle 500 450 0 40
Fill 525 450 0

# Light gray
Color 0.2 0.2 0.2
Circle 500 450 0 60
Fill 550 450 0

# Pink
Color 0.9 0.5 0.5
Circle 500 450 0 80
Fill 575 450 0

# Red
Color 0.9 0.2 0.2
Circle 500 450 0 110
Fill 590 450 0

# Orange
Color 1.0 0.6 0.2
Circle 500 450 0 140
Fill 630 450 0

# Yellow
Color 1.0 0.8 0.1
Circle 500 450 0 170
Fill 650 450 0

# Green
Color 0.19 0.63 0.32
Circle 500 450 0 200
Fill 690 450 0

# Blue
Color 0.17 0.49 0.74
Circle 500 450 0 240
Fill 730 450 0

# Purple
Color 0.49 0.1 0.49
Circle 500 450 0 265
Fill 760 450 0

WorldEnd
FrameEnd
