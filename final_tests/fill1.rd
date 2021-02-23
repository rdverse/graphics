# This is a test/example rd file

Display "EdgeTest"  "Screen" "rgbsingle"
Format 1000 1000

# Testing filling at edges

Background 0.12 0.14 0.2

# The next three lines will be ignored by your renderer
CameraEye 200 200 -200
CameraAt  200 200 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

WorldBegin

Color 1.0 1.0 1.0

# Square
Line 200 200 0 200 800 0
Line 200 800 0 800 800 0
Line 800 800 0 800 200 0
Line 800 200 0 200 200 0

# Intersecting lines
Line 500 50 0 500 950 0
Line 50 500 0 950 500 0

# Replace intersecting points
Color 0.12 0.14 0.2
Point 500 500 0

# Fill quadrants
Color 0.99 0.54 0.27
Fill 250 250 0

Color 0.0 0.84 0.82
Fill 250 750 0

Color 0.99 0.81 0.42
Fill 750 750 0

Color 0.01 0.9 0.58
Fill 750 250 0

WorldEnd
FrameEnd
