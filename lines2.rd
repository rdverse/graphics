# This is a test/example rd file

Display "EdgeTest"  "Screen" "rgbdouble"
Format 400 400 

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

Line 195 0 0 195 399 0
Line 205 0 0 205 399 0

Line 295 0 0 95 399 0
Line 305 0 0 105 399 0

Line 395 0 0 0 395 0
Line 399 5 0 5 399 0

Line 399 95 0 0 295 0
Line 399 105 0 0 305 0

Line 399 195 0 0 195 0
Line 399 205 0 0 205 0

Line 399 295 0 0 95 0
Line 399 305 0 0 105 0

Line 399 395 0 5 0 0
Line 395 399 0 0 5 0

Line 295 399 0 95 0 0
Line 305 399 0 105 0 0 



WorldEnd
FrameEnd
