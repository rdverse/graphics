Display "Cylinder Test" "Screen" "rgbsingle"

Background 0.5 0.5 0.5

CameraEye -20 1 1
CameraAt -30 1 1
CameraUp 0 0 1
CameraFOV 30.0


CameraEye -20 -10 10
CameraAt 1 -3 3
CameraUp 0 0 1
CameraFOV 30.0


FrameBegin 1
WorldBegin


XformPush # Row of cylinders
Color 0.0 0.0 0.0
Scale 1.0 1.0 1.0
Cylinder 1.0 0.0 1.0 360.0
XformPop

XformPush # Row of cylinders
Translate 2 6 1
Sphere 1.0 -1.0 1.0 360.0
XformPop

XformPush # Row of cylinders
Translate 2 2 2
Scale 2.0 2.0 2.0
Cube
XformPop

WorldEnd
FrameEnd
