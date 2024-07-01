const input =
`
# Ray Tracer 3: reflections
0 0  5        #viewpoint (x, y, z)
8 8           #world x and y dims

# Floor
plane
0 0 7         # Color
0.9           # Diffuse
0.75          # Specular
# Plane specific data
-40 -4 0      # Point
0 1 0         # Normal

# Light
pointlight
6 6 6         # Emissivity
-1.5 2 -0.25  # center

# Light
pointlight
6 6 6         # Emissivity
1.5 2 -0.25   # center

#Sun
pointlight
30 30 30      # Emissivity
0 4 -20       # center

# Triangle
triangle
6 0 0         # color
0.9           # diffuse
0             # specular
#Plane specific data
 -4 -3.5 -2   # Point
1 0 0.5       # Normal
#Triangle specific data
1 0 0         # Orient 1
2             # Edge 0 length
1 1 0         # Orient 2
2             # Edge 1 length

# Rectangle
rectangle
0 7 0         # Color
.75           # Diffuse
.75           # Specular
#Plane Specific data
 3 -1 -3      # Point
-1 0 0        # Normal
#Rectangle Specific data
0.2 0 1       # Orientation Vector
3 4           # Width and Length

# Sphere
sphere
5 5 5         # color
.75           # diffuse
.75           # specular
#Sphere specific data
-0  -1 -5     # center
2             # radius

# Small sphere
sphere
2 2 6         # color
.75           # diffuse
0             # specular
#Sphere specific data
-2.5 2 -2     # center
0.50          # radius

# Small sphere
sphere
9 3 3         # color
.75           # diffuse
.75           # specular
#Sphere specific data
2.5 -3.00 -5  # center
0.50          # radius

# Small sphere
sphere
9 3 3         # color
.75           # diffuse
0             # specular
#Sphere specific data
1.5 2.50 -3   # center
0.50          # radius


`;
