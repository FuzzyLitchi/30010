# Planned features
## Rendering system
I want my game to be built around pixel graphics. The pixels aren't square but by using ▄ we can make them almost square. I might use some other characters like ░, ▒, ▓ and •. I will use a buffer to store the pixel graphics.

There's 16 colors, and we can subdivide each character into 2 pixels (by using ▄). In RAM this will optimally take 4 bits per pixel and 8 bits or 1 byte per character. Sending it over USART take a lot more, but since we only update some pixels we could be smart and save bandwidth. Additionally we could up the USART speed.

## Game objects
### Character
- Spaceship.
- Unaffected (or at least less affected) by the gravity field. (Canonical explanation is that the ship computer auto corrects)
- WASD for moving, arrow keys for aiming/shooting.
- Shift for switching weapon

### Astroid:
- Can be broken for loot and points.
- Somewhat gravitationally attractive.
- Crashing into it hurts.

### Black hole:
- To be avoided.
- Very gravitationally attractive.
- Getting sucked into it kills.

### Enemies:
- Alien ships.
- Similar weapons? (To save development time)
- Very little health/shields compared to player.
- Killing them gives points.

## Weapons:
### Laser weapon
- Bends around black holes.
- Laser travels at light speed.
- Drawn using the aseprite pixel perfect algorithm. (https://imgur.com/uiyzvcY)
- Laser weapon doesn't use ammunition, but it overheats.

### Projectile weapon (maybe rockets)
- Slower projectiles, so they curve more.
- More damage? (Can be fine tuned after play-testing)
- Uses ammunition.

### Nuclear bomb
- It's a nuke.
- High damage within an area.
- Very costly.
- Highlights the dubious ethics of a blood-soaked space conquest.
- Cool, flashy explosion.

### Loot:
- Projectile ammunition
- Repair kit (restores shields/health)
- Super shields (makes you invulnerable for a limited time)
- Nuclear bomb
- Extra lives


## Chosen requirements:
### From the "More than two of the following" section
- Multiple bullets,   (We will have multiple bullets on screen. I think this counts)
- Score / high score, (Destroying enemies and astroids gives points)
- Game controlled through PuTTY/Keyboard,

### From the "More than one of the following" section
- Sound from buzzer, (Noise when player is hit and when nukes go off.)
- Show info on RGB LED, (Health gradient from green to red.)

## HUD
We will show the player the following information in the PuTTY view.
- Lives
- Shield status / health
- Laser temperature
- Projectiles left
- Nukes left

And the following on the LCD
- Lives
- Points


# Timeline
What features/tasks I will do when.

## 11/01
- Game design
- Plan project

## 12/01
- Git repository
- Rendering system
- PuTTY input system
- Game loop

## 13/01
- Player rendering
- Fixed point arithmetic API
- Player movement

## 14/01
- Enemy rendering
- Enemy movement
- Projectiles
- Enemy death

## 15/01
- Enemy bullet
- Player damage/health/death
- Death screen
- Boss key
- Help screen

## 17/01
- Gravity
- Laser
- Weapon switching
- Nuke

## 18/01
- PuTTY HUD
- Astroids
- Loot
  - Projectile ammunition
  - Repair kit (restores shields/health)
  - Super shields (makes you invulnerable for a limited time)
  - Nuclear bomb
  - Extra lives

## 19/01
- Buzzer audio
- Black holes
- Damage from colliding with black holes + astroids + enemies
- Points (from killing stuff)
- LCD HUD

## 20/01
- Record gameplay
- Draw API flowcharts (Ref: Slide #11 of Course Lecture 2)
- Document API and HAL (Ref: Slide #10 of Course Lecture 2)
- Write report

## 21/01
- Write report

## ??/01
I might need additional time as this is a pretty crammed timeline.