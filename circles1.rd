# This is a test/example rd file

Display "Concentric Circles"  "PNM" "rgb"
Format 200 200


# The next three lines will be ignored by your renderer
CameraEye 250 150 -150
CameraAt  250 150 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

Background 0.0 0.0 0.0

WorldBegin
# left circles odd
Circle 50 50 0 1
Circle 50 50 0 3
Circle 50 50 0 5
Circle 50 50 0 7
Circle 50 50 0 9
Circle 50 50 0 11

# right circles even
Circle 150 50 0 2
Circle 150 50 0 4
Circle 150 50 0 6
Circle 150 50 0 8
Circle 150 50 0 10
Circle 150 50 0 12


WorldEnd
FrameEnd
