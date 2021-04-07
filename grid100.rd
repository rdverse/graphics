Display "Grid Test" "Screen"  "rgbsingle"

Background 0.6 0.7 0.8

CameraAt 0 0 0
CameraEye -100 -50  50
CameraUp 0 0 1

ObjectBegin "Axes"
Color 1 0 0
Line 0 0 0  10 0 0
Color 0 1 0
Line 0 0 0  0 10 0
Color 0 0 1
Line 0 0 0  0 0 10
ObjectEnd # Axes

ObjectBegin "Row5"
Line 0 0 0   200 0 0
Line 0 10 0  200 10 0
Line 0 20 0  200 20 0
Line 0 30 0  200 30 0
Line 0 40 0  200 40 0
ObjectEnd  # "Row5"

ObjectBegin "Row200"
XformPush
Translate -100 -100 0
ObjectInstance "Row5"
Translate 0 50 0
ObjectInstance "Row5"
Translate 0 50 0
ObjectInstance "Row5"
Translate 0 50 0
ObjectInstance "Row5"
XformPop
ObjectEnd # Row200

ObjectBegin "Grid100"
XformPush
ObjectInstance "Row200"

Rotate "Z" -90

ObjectInstance "Row200"
XformPop
ObjectEnd # Grid100

WorldBegin

ObjectInstance "Axes"

Color 0 0 0

ObjectInstance "Grid100"

Translate 100 0 0

ObjectInstance "Grid100"

Translate 100 0 0
ObjectInstance "Grid100"

WorldEnd