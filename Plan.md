# Planned features
## Rendering system
I want my game to be built around pixel graphics. The pixels aren't square but by using ▄ we can make them almost square. I might use some other characters like ░, ▒, ▓ and •. I will use a buffer to store the pixel graphics.

There's 16 colors, and we can subdivide each character into 2 pixels (by using ▄). In RAM this will optimally take 4 bits per pixel and 8 bits or 1 byte per character. Sending it over USART take a lot more, but since we only update some pixels we could be smart and save bandwidth. Additionally we could up the USART speed.

## Game objects
### Character
- Spaceship.
- (Nice to have) Unaffected (or at least less affected) by the gravity field. (Canonical explanation is that the ship computer auto corrects)
- WASD for moving, arrow keys for aiming/shooting.
- (Nice to have) Shift for switching weapon

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

## Weapons: (Only make 2)
### Laser weapon (Nice to have)
- Bends around black holes.
- Laser travels at light speed.
- Drawn using the aseprite pixel perfect algorithm. (https://imgur.com/uiyzvcY)
- Laser weapon doesn't use ammunition, but it overheats.

### Projectile weapon (maybe rockets)
- Slower projectiles, so they curve more.
- More damage? (Can be fine tuned after play-testing)
- Uses ammunition.

### Nuclear bomb (Not feeling it)
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
- [X] Game design
- [X] Plan project

## 12/01
- [X] Git repository
- [X] Rendering system
- [X] PuTTY input system
- [X] Game loop

## 13/01
- [X] Player rendering
- [X] Fixed point arithmetic API
- [X] Player movement

## 14/01
- [X] Enemy rendering
- [X] Enemy movement (+ AI)
- [X] Projectiles
- [X] Enemy bullet
- [X] Multiple enemies 

## 15/01
- [X] Enemy death
- [X] Player damage/health/death
- [X] Death screen
- [ ] Boss key (Måske)
- [ ] Help screen

MVP, write on report. Flowchart + Blokdiagram.

## 17/01
- [ ] Laser
- [ ] Gravity
- [ ] Weapon switching
- [ ] Nuke

## 18/01
- [ ] LCD HUD
- [ ] PuTTY HUD
- [ ] Astroids
- [ ] Loot
  - Projectile ammunition
  - Repair kit (restores shields/health)
  - Super shields (makes you invulnerable for a limited time)
  - Nuclear bomb
  - Extra lives

## 19/01
- [ ] Buzzer audio
- [ ] Black holes
- [ ] Damage from colliding with black holes + astroids + enemies
- [ ] Points (from killing stuff)

## 20/01
- Record gameplay
- Draw API flowcharts (Ref: Slide #11 of Course Lecture 2)
- Document API and HAL (Ref: Slide #10 of Course Lecture 2)
- Write report

## 21/01
- Write report

## ??/01
I might need additional time as this is a pretty crammed timeline.


# Improvements

Make the firing phase for AI only fire a max of 5 shots.

## AI plan
Firing -> (Idle, Approaching)
Idle -> (Approaching, Firing)
Approaching -> Firing

Flee -> (Flee, Firing)
Damage   => Flee (sometimes, when under a health limit)
0 health => Dying (plays little animation and the removes self)

When ships are outside the screen, they shouldn't be able to fire. But it would be cool if they could come back. I might just make ships that go off screen vanish, as that is easiest. But they'd only vanish if they're Fleeing.

## Bullets
Blue bullets hitting enemies should be instant
Blue bullets only have self grace
Purple bullets ???
    Every bullet has a "shooter" id, 0 is player, 1 and up is enemies
    Bullets have a grace period but only for the relevant id.

## Death screen
~~Add glowy pink stuff~~ Couldn't do because of the limitations of UART and my rendering system.
Add the ability to reset the game