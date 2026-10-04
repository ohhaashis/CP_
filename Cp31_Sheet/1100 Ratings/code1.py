import turtle
import math
import pygame # New import for music!

# --- SETUP MUSIC ---
# Initialize the pygame mixer
pygame.mixer.init()
try:
    # Load the music file (make sure it's in the same folder!)
    pygame.mixer.music.load("tum_prem_ho.mp3")
    # Play the music in an infinite loop (-1 means loop forever)
    pygame.mixer.music.play(-1)
except pygame.error:
    print("Note: Could not find 'tum_prem_ho.mp3'. The animation will still play without music!")
    print("Please make sure the file is in the same folder as this script.")

# --- SCREEN SETUP ---
screen = turtle.Screen()
screen.setup(width=1200, height=700) 
screen.bgcolor("#87CEEB")  
screen.title("For Pastaa 🌻")
screen.tracer(0)  

# Turtle for the animation
t = turtle.Turtle()
t.hideturtle()
t.speed(0)

# Turtle exclusively for the text
text_t = turtle.Turtle()
text_t.hideturtle()
text_t.penup()

# --- THE SPECIAL NOTE ---
def write_special_note():
    message = (
        "Oye Tingu 🐰,\n\n"
        "1st of all chahe jo ho jaye trust rakhna ye sab temporary hi hai,\n"
        "aur tum baate karte raha karo ullu, baate karte hi achhi lagti ho 🐣\n"
        "and yes bahut saari baate karne aur dishes try karne hai 🐥 !!\n\n"
        "Aur ha family wale tumhare, anurag and hum hamesha yahi hai\n"
        "tumhare sath always 🌷✨ .... akela kabhi feel mat karna khudko 🤌🏻🤍 ..\n\n"
        "Baki yes just trust me kuch din bad ye sab sahi ho jayega\n"
        "aur tum wapas aaoge aur mere sath pizza se leke brownie sab khaoge\n"
        "and tum banake bhi khilaoge ..\n\n"
        "Just kisi baat ka mera bura laga ho to maaf kardena,\n"
        "ye tumhara ullu thoda ulluwa gaya hai 🥲 ..\n\n"
        "And yes ek last baat, jab padho ye tab ache se smile karna 🩷✨\n"
        "aur positivity se sabkuch sochna ..\n\n"
        "Take care Pasta ! 🤍🌸"
    )
    
    text_t.goto(-550, 200)
    text_t.color("#1a365d") 
    text_t.write(message, align="left", font=("Arial", 14, "bold"))

# --- SUNFLOWER MATH & DRAWING ---
def draw_leaf_or_petal(x, y, start_dist, angle_deg, arc_radius, extent):
    t.penup()
    t.goto(x, y)
    t.setheading(angle_deg)
    t.forward(start_dist)
    t.setheading(angle_deg - extent / 2)
    t.pendown()
    t.begin_fill()
    t.circle(arc_radius, extent)
    t.left(180 - extent)
    t.circle(arc_radius, extent)
    t.end_fill()

def draw_sunflower(rotation, scale):
    t.clear() 
    
    offset_x = 250 
    
    # 1. Stem
    t.penup()
    t.goto(offset_x, -350)
    t.setheading(90)
    t.pensize(20 * scale)
    t.color("#2e7d32")
    t.pendown()
    t.goto(offset_x, 0)
    
    # 2. Leaves
    t.pensize(2)
    t.color("#1b5e20", "#388e3c")
    draw_leaf_or_petal(offset_x, -100, 0, 30, 150 * scale, 60)
    draw_leaf_or_petal(offset_x, -220, 0, 150, 130 * scale, 60)
    
    # 3. Petals
    num_petals = 20
    seed_radius = 80 * scale
    
    t.color("#fbc02d", "#f57f17") 
    for i in range(num_petals):
        angle_val = i * (360 / num_petals) + rotation
        draw_leaf_or_petal(offset_x, 0, seed_radius * 0.8, angle_val, 160 * scale, 50)
        
    t.color("#fff176", "#ffeb3b") 
    for i in range(num_petals):
        angle_val = i * (360 / num_petals) + rotation + (180 / num_petals)
        draw_leaf_or_petal(offset_x, 0, seed_radius * 0.85, angle_val, 140 * scale, 55)

    # 4. Seed Head
    num_seeds = 250
    spacing = 5.5 * scale  
    golden_angle = 137.508 * (math.pi / 180) 
    
    for i in range(num_seeds):
        r = spacing * math.sqrt(i)
        theta = i * golden_angle + math.radians(rotation)
        
        x = offset_x + r * math.cos(theta)
        y = r * math.sin(theta)
        
        if i < num_seeds * 0.4:
            t.color("#3e2723")
        elif i < num_seeds * 0.7:
            t.color("#5d4037")
        else:
            t.color("#ff9800")
            
        t.penup()
        t.goto(x, y)
        t.dot(8 * scale)

    screen.update()

# --- MAIN ANIMATION LOOP ---
write_special_note()

phase = 0.0
angle = 0.0

def animate():
    global phase, angle
    
    scale = 1.0 + 0.05 * math.sin(phase)
    draw_sunflower(angle, scale)
    
    phase += 0.1    
    angle += 0.4    
    
    screen.ontimer(animate, 30)

animate()
turtle.done()