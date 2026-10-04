# import turtle
# import math

# # 1. Screen Setup
# screen = turtle.Screen()
# screen.setup(width=800, height=600)
# screen.bgcolor("#1e1e2e")  # Flat dark matte background
# screen.title("3D Rotating Wireframe Cube")
# screen.tracer(0)  # Turn off instant drawing for smooth animation

# t = turtle.Turtle()
# t.hideturtle()

# # 2. Define the 3D Cube
# # The 8 corners (vertices) of a cube in 3D space
# vertices = [
#     [-1, -1, -1], [ 1, -1, -1], [ 1,  1, -1], [-1,  1, -1], # Back face
#     [-1, -1,  1], [ 1, -1,  1], [ 1,  1,  1], [-1,  1,  1]  # Front face
# ]

# # The lines connecting the corners
# edges = [
#     (0, 1), (1, 2), (2, 3), (3, 0),  # Back face edges
#     (4, 5), (5, 6), (6, 7), (7, 4),  # Front face edges
#     (0, 4), (1, 5), (2, 6), (3, 7)   # Edges connecting front and back
# ]

# # 3. Animation Variables
# angle_x = 0.0
# angle_y = 0.0
# angle_z = 0.0

# # Camera settings for the 3D projection
# fov = 400            # Field of view (how wide the camera sees)
# viewer_distance = 4  # How far the camera is from the cube

# def rotate_3d(x, y, z, ax, ay, az):
#     """Applies math matrices to rotate a 3D point across X, Y, and Z axes."""
#     # Rotate around X axis
#     cos_x, sin_x = math.cos(ax), math.sin(ax)
#     y, z = y * cos_x - z * sin_x, y * sin_x + z * cos_x
    
#     # Rotate around Y axis
#     cos_y, sin_y = math.cos(ay), math.sin(ay)
#     x, z = x * cos_y + z * sin_y, -x * sin_y + z * cos_y
    
#     # Rotate around Z axis
#     cos_z, sin_z = math.cos(az), math.sin(az)
#     x, y = x * cos_z - y * sin_z, x * sin_z + y * cos_z
    
#     return x, y, z

# def animate():
#     global angle_x, angle_y, angle_z
#     t.clear()
    
#     projected_points = []
    
#     # Step 1: Rotate and Project all 3D points into 2D screen points
#     for v in vertices:
#         # Rotate the vertex
#         rx, ry, rz = rotate_3d(v[0], v[1], v[2], angle_x, angle_y, angle_z)
        
#         # Perspective Projection Math
#         # Objects further away (higher Z) get smaller
#         factor = fov / (viewer_distance + rz)
        
#         # Calculate final 2D screen X and Y
#         screen_x = rx * factor
#         screen_y = ry * factor
#         projected_points.append((screen_x, screen_y))

#     # Step 2: Draw the edges (lines) connecting the points
#     t.pensize(3)
#     t.color("#89b4fa") # Flat pastel blue color
    
#     for edge in edges:
#         p1 = projected_points[edge[0]]
#         p2 = projected_points[edge[1]]
        
#         t.penup()
#         t.goto(p1)
#         t.pendown()
#         t.goto(p2)

#     # Step 3: Draw the vertices (corners) as solid dots
#     t.color("#cba6f7") # Flat pastel purple
#     for point in projected_points:
#         t.penup()
#         t.goto(point)
#         t.dot(12) # Draw a 12px dot at each corner

#     screen.update() # Render the frame
    
#     # Advance the rotation angles slightly for the next frame
#     angle_x += 0.02
#     angle_y += 0.015
#     angle_z += 0.01
    
#     # Loop the animation (~60 frames per second)
#     screen.ontimer(animate, 16)

# # Start the animation
# animate()

# # Keep window open
# turtle.done()

import turtle
import math

# 1. Screen Setup
screen = turtle.Screen()
screen.setup(width=800, height=600)
screen.bgcolor("#87CEEB")  # Sky blue background
screen.title("Rotating Sunflower Animation")
screen.tracer(0)  # Turn off instant drawing for smooth animation

t = turtle.Turtle()
t.hideturtle()
t.speed(0)

def draw_leaf_or_petal(x, y, start_dist, angle_deg, arc_radius, extent):
    """Draws a pointed leaf or petal shape using two intersecting arcs."""
    t.penup()
    t.goto(x, y)
    t.setheading(angle_deg)
    t.forward(start_dist)
    
    # Adjust heading so the petal is perfectly centered on the angle
    t.setheading(angle_deg - extent / 2)
    t.pendown()
    t.begin_fill()
    
    # Draw the two sides of the petal
    t.circle(arc_radius, extent)
    t.left(180 - extent)
    t.circle(arc_radius, extent)
    t.end_fill()

def draw_sunflower(rotation, scale):
    """Draws the complete sunflower at a specific rotation and size."""
    t.clear()
    
    # 1. Draw the Stem
    t.penup()
    t.goto(0, -350)
    t.setheading(90)
    t.pensize(20 * scale)
    t.color("#2e7d32") # Dark green
    t.pendown()
    t.forward(350)     # Draw stem up to the center (0,0)
    
    # 2. Draw Leaves on the stem
    t.pensize(2)
    t.color("#1b5e20", "#388e3c") # Outline, Fill
    # Right leaf
    draw_leaf_or_petal(0, -100, 0, 30, 150 * scale, 60)
    # Left leaf lower down
    draw_leaf_or_petal(0, -220, 0, 150, 130 * scale, 60)
    
    # 3. Draw the Petals (Two layers for depth)
    num_petals = 20
    seed_radius = 80 * scale
    
    # Layer 1: Back petals (darker, slightly orange/gold)
    t.color("#fbc02d", "#f57f17") 
    for i in range(num_petals):
        angle = i * (360 / num_petals) + rotation
        draw_leaf_or_petal(0, 0, seed_radius * 0.8, angle, 160 * scale, 50)
        
    # Layer 2: Front petals (bright yellow)
    t.color("#fff176", "#ffeb3b") 
    for i in range(num_petals):
        # Offset the angle so they sit between the back petals
        angle = i * (360 / num_petals) + rotation + (180 / num_petals)
        draw_leaf_or_petal(0, 0, seed_radius * 0.85, 140 * scale, 55, 55) # slightly smaller

    # 4. Draw the Seed Head using Fermat's Spiral (Golden Ratio)
    num_seeds = 250
    spacing = 5.5 * scale  
    golden_angle = 137.508 * (math.pi / 180) # The mathematical angle in nature
    
    for i in range(num_seeds):
        # Math for the spiral
        r = spacing * math.sqrt(i)
        theta = i * golden_angle + math.radians(rotation)
        
        # Convert to X and Y coordinates
        x = r * math.cos(theta)
        y = r * math.sin(theta)
        
        # Create a color gradient from the center outwards
        if i < num_seeds * 0.4:
            t.color("#3e2723") # Dark brown core
        elif i < num_seeds * 0.7:
            t.color("#5d4037") # Medium brown middle
        else:
            t.color("#ff9800") # Orange/gold outer rim
            
        t.penup()
        t.goto(x, y)
        t.dot(8 * scale) # Draw the individual seed

    screen.update() # Reveal the drawn frame to the screen

# Animation Tracking Variables
phase = 0.0
angle = 0.0

def animate():
    """Main animation loop for breathing and rotating."""
    global phase, angle
    
    # Calculate a gentle "breathing" scale effect using sine wave
    # Base scale is 1.0, pulses gently by +/- 0.05
    scale = 1.0 + 0.05 * math.sin(phase)
    
    draw_sunflower(angle, scale)
    
    # Advance the animation counters
    phase += 0.1    # Controls the speed of the breathing
    angle += 0.4    # Controls how fast the flower spins
    
    # Schedule the next frame in roughly 30 milliseconds
    screen.ontimer(animate, 30)

# Start the animation loop
animate()

# Keep the window open
turtle.done()