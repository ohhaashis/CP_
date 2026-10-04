import turtle
import math
import colorsys

# 1. Screen Setup
screen = turtle.Screen()
screen.setup(width=800, height=600)
screen.bgcolor("black")
screen.title("Neon Cosmic Portal")
screen.tracer(0) # Turn off automatic animation for smooth frame rendering

# Set colormode to 1.0 to work easily with the colorsys module (which outputs 0.0 to 1.0)
screen.colormode(1.0)

t = turtle.Turtle()
t.hideturtle()
t.speed(0)

# Animation Variables
hue = 0.0          # Controls the rainbow color shift
rotation = 0.0     # Controls the spinning of the shape
pulse_phase = 0.0  # Controls the breathing/pulsing effect

def draw_spirograph(radius, angle_offset, current_hue):
    """Draws a mathematical rose curve with a neon effect."""
    t.clear()
    
    # Generate our neon color palette dynamically based on the current hue
    # Format: (RGB Color tuple, Pen Thickness)
    neon_layers = [
        (colorsys.hsv_to_rgb(current_hue, 1.0, 0.3), 18),  # Deep shadow glow
        (colorsys.hsv_to_rgb(current_hue, 1.0, 0.7), 10),  # Bright core color
        (colorsys.hsv_to_rgb(current_hue, 0.4, 1.0), 4),   # Bright highlight
        ((1.0, 1.0, 1.0), 1)                               # Pure white center line
    ]
    
    # Draw each layer from thickest to thinnest
    for color, width in neon_layers:
        t.pensize(width)
        t.color(color)
        t.penup()
        
        # We use a mathematical "Rose Curve". k=4 produces an 8-petaled flower/star.
        k = 4 
        steps = 150 # Number of line segments (higher = smoother but slower)
        
        for i in range(steps + 1):
            # Theta goes from 0 to 2*PI
            theta = i * (2 * math.pi / steps)
            
            # The Rose curve formula: r = R * cos(k * theta)
            r = radius * math.cos(k * theta)
            
            # Apply the rotation offset to make the whole shape spin
            rotated_theta = theta + angle_offset
            
            # Convert polar coordinates to Cartesian (x, y)
            x = r * math.cos(rotated_theta)
            y = r * math.sin(rotated_theta)
            
            if i == 0:
                t.goto(x, y)
                t.pendown()
            else:
                t.goto(x, y)
                
    screen.update() # Render the frame

def animate():
    """Main animation loop."""
    global hue, rotation, pulse_phase
    
    # 1. Calculate the pulsing radius (Base size 180, pulses by +/- 40)
    current_radius = 180 + 40 * math.sin(pulse_phase)
    
    # 2. Draw the frame
    draw_spirograph(current_radius, rotation, hue)
    
    # 3. Update the variables for the next frame
    hue += 0.005           # Shift color slightly (wraps around automatically in hsv_to_rgb)
    rotation += 0.02       # Spin the shape
    pulse_phase += 0.08    # Advance the breathing effect
    
    # 4. Schedule the next frame (approx 30ms delay = ~33 FPS)
    screen.ontimer(animate, 30)

# Start the infinite animation loop
animate()

# Keep the window open
turtle.done()