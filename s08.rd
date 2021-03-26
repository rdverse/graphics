# This is a test/example rd file

Display "EdgeTest"  "PNM" "rgb"
Format 100 100 

# Testing filling at edges

Background 0.9 0.9 0.9

# The next three lines will be ignored by your renderer
CameraEye 200 200 -200
CameraAt  200 200 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

WorldBegin

#Lines

Color 0.0 0.0 0.0

Circle 50 50 0 10

Color 0.6 0.1 0.8

#ill 50 50 0


WorldEnd
FrameEnd
