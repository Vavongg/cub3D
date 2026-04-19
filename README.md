<div align="center">

# 🎮 cub3D

_A raycasting engine written from scratch — because Wolfenstein 3D was just the beginning._

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr/)
[![Grade](https://img.shields.io/badge/Grade-105%2F100-success?style=for-the-badge)]()
[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c&logoColor=white)]()
[![Graphics](https://img.shields.io/badge/Library-MiniLibX-orange?style=for-the-badge)]()
[![Norminette](https://img.shields.io/badge/Norminette-Passing-brightgreen?style=for-the-badge)]()

</div>

---

## 📖 About

**cub3D** is a 42 graphics project inspired by the legendary **Wolfenstein 3D** (id Software, 1992) — the game that invented the FPS genre. The goal: build a fully functional 3D maze engine from scratch in C, using only the **MiniLibX** window library and **raycasting** mathematics.

No OpenGL. No game engine. No shortcuts. Just trigonometry, a pixel buffer, and 1,920 × 1,080 pixels of pure determination.

The engine parses a custom `.cub` map format, loads XPM wall textures, and renders a first-person perspective view in real time — with keyboard-controlled movement and rotation.

---

## 🎯 Project scope

- ✅ **Mandatory** — raycasting engine, textured walls, floor/ceiling colors, WASD + arrow key movement, `.cub` parsing with full error handling
- ✅ **Bonus** — smooth wall collision detection with margin offset *(+5 points)*

---

## 🔧 Usage

```bash
./cub3D maps/good/map.cub
```

The single argument is a path to a `.cub` scene description file.

### Controls

| Key            | Action                  |
|:---------------|:------------------------|
| `W`            | Move forward            |
| `S`            | Move backward           |
| `A`            | Strafe left             |
| `D`            | Strafe right            |
| `←` `→`        | Rotate camera           |
| `ESC`          | Quit                    |

---

## 🗺️ The `.cub` file format

A scene file has two sections: a **configuration block** then a **map block**.

```
NO textures/north.xpm      # North wall texture (XPM)
SO textures/south.xpm      # South wall texture (XPM)
WE textures/west.xpm       # West wall texture  (XPM)
EA textures/east.xpm       # East wall texture  (XPM)

F 76,76,76                 # Floor color (R,G,B)
C 99,99,99                 # Ceiling color (R,G,B)

1111111111
10W1001001
1011000001
1001001111
1111111111
```

### Map characters

| Char | Meaning                                    |
|:-----|:-------------------------------------------|
| `1`  | Wall                                       |
| `0`  | Walkable floor                             |
| `N` `S` `E` `W` | Player spawn + initial facing direction |

### Validation rules enforced at startup

- Every element (`NO`, `SO`, `WE`, `EA`, `F`, `C`) must appear **exactly once** before the map
- Texture paths must point to existing `.xpm` files
- RGB values must be integers in **[0, 255]**
- The map must be **fully enclosed by walls** (verified by flood-fill from the player's spawn)
- No empty lines inside the map, no invalid characters, exactly **one player** spawn

---

## 🧠 How it works

### The raycasting algorithm

```
                Player (pos_x, pos_y)
                      │
              ────────┼──────── camera plane
                      │
        FOV = 60°     │
        ┌─────────────┼─────────────┐
        │             │             │
     ray[0]        ray[x]        ray[WIDTH-1]
        │             │             │
        ▼             ▼             ▼
      hit          hit            hit
      dist         dist           dist
        │             │             │
      wall         wall           wall
      height       height         height
```

For every vertical column `x` (0 → WIDTH−1), a ray is cast from the player's position in a direction computed from the camera plane. The algorithm used is **DDA (Digital Differential Analysis)** — the same technique id Software used in 1992.

**Step 1 — Ray direction**
```
camera_x = -(2 * x / WIDTH - 1)          // maps column to [-1, +1]
ray_dir_x = dir_x + plane_x * camera_x
ray_dir_y = dir_y + plane_y * camera_x
```

**Step 2 — DDA traversal**

The ray steps through the grid cell by cell, checking only the exact grid boundaries — never wasting time on the interior:
```
delta_dist_x = |1 / ray_dir_x|    // distance to cross one X-cell
delta_dist_y = |1 / ray_dir_y|    // distance to cross one Y-cell

// At each step: advance on the shorter axis
if (side_dist_x < side_dist_y)  { side_dist_x += delta_dist_x; map_x += step_x; side = 0; }
else                             { side_dist_y += delta_dist_y; map_y += step_y; side = 1; }
```

**Step 3 — Wall height**

Once the ray hits a `'1'` cell, the **perpendicular** wall distance is computed (not Euclidean — avoids the fish-eye effect):
```
if (side == 0)  perp_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x
else            perp_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y

line_height = HEIGHT / perp_dist
```

**Step 4 — Texture mapping**

The exact hit position within the wall cell (`wall_x`) determines which column of the XPM texture to sample. The texture is then drawn vertically, stretched to `line_height` pixels. The correct texture (N/S/E/W) is selected based on the ray's side and direction.

```
                          N texture
                  ┌───────────────────┐
                  │  ░░░░░░░░░░░░░░░  │
        W texture │  ░ player view ░  │ E texture
                  │  ░░░░░░░░░░░░░░░  │
                  └───────────────────┘
                          S texture
```

### Wall collision — the margin trick

A naive implementation checks whether `(int)new_x, (int)new_y` is a wall. This lets the player clip through corners and press flat against walls with no breathing room.

The bonus collision system checks **5 points** instead of one — the new position plus four points offset by a `margin` of `0.2` units in all directions:

```c
double margin = 0.2;

can_move(new_x, new_y)          // center
can_move(new_x + margin, new_y) // right side
can_move(new_x - margin, new_y) // left side
can_move(new_x, new_y + margin) // front
can_move(new_x, new_y - margin) // back
```

If the full 5-point check fails but a partial slide is possible (e.g. only `new_x` is safe), the player slides along the wall instead of stopping dead — smooth wall-sliding movement.

### Rendering pipeline

```
 every frame (mlx_loop_hook):
 ┌──────────────────────────────────────┐
 │ 1. handle_keys → update pos/angle   │
 │ 2. draw_ceiling_floor → fill buffer │
 │ 3. for x in [0..WIDTH]:             │
 │      cast_ray(x)                    │
 │      draw_textured_line(x)          │
 │ 4. mlx_put_image_to_window          │
 └──────────────────────────────────────┘
```

Everything is written to a single off-screen image buffer (`mlx_new_image`) and flushed to the window in one call — no tearing, no flickering.

---

## 🛠️ Build

```bash
# Clone (with MiniLibX submodule or copy)
git clone https://github.com/Vavongg/cub3D.git
cd cub3D

# Build (also compiles MiniLibX automatically)
make

# Run with one of the provided maps
./cub3D maps/good/bombardiro.cub

# Cleanup
make clean    # remove .o files
make fclean   # remove .o files + binary
make re       # full rebuild
```

> **Dependencies (Linux):** `gcc`, `make`, `libX11-dev`, `libXext-dev`

---

## 🧪 Error handling test maps

The parser is battle-tested against every edge case. A selection from `maps/bad/`:

| Map file                    | What it tests                            |
|:----------------------------|:-----------------------------------------|
| `map_unclosed.cub`          | Wall with a hole — must be rejected      |
| `player_none.cub`           | Missing spawn point                      |
| `double_player.cub`         | Two spawn characters — invalid           |
| `color_overflow.cub`        | RGB value of 256 — out of range          |
| `color_negative.cub`        | Negative RGB — out of range              |
| `textures_not_xpm.cub`      | Texture without `.xpm` extension         |
| `textures_duplicates.cub`   | Same identifier declared twice           |
| `empty_line_in_map.cub`     | Empty line inside the map grid           |
| `map_first.cub`             | Map appears before config elements       |
| `disconnected_island.cub`   | Isolated section of map not reachable    |
| `spaces_in_map_middle.cub`  | Space character inside enclosed area     |

All of these print a clear error to stdout and exit with code `1`.

---

## 📁 Structure

```
cub3D/
├── Makefile
├── include/
│   └── cub3d.h               # All structs, constants, prototypes
├── get_next_line/            # GNL for reading the .cub file
├── src/
│   ├── main.c                # Entry point, config init, mlx launch
│   ├── parsing/
│   │   ├── parse_cub.c       # Top-level parser & error dispatcher
│   │   ├── parsing_file.c    # File reading, line counting
│   │   ├── parsing_config.c  # NO/SO/WE/EA/F/C line parsing
│   │   ├── parsing_map.c     # Map grid extraction & player detection
│   │   ├── parsing_utils.c   # Identifier detection helpers
│   │   ├── check_map.c       # Char validation, player count
│   │   └── map_floodfill.c   # Closure check via flood-fill
│   ├── game/
│   │   ├── init_mlx.c        # MLX init, window, texture loading
│   │   ├── init2_mlx.c       # Image buffer creation
│   │   ├── raycasting.c      # cast_ray, DDA, wall hit, texture select
│   │   ├── raycasting2.c     # init_ray, set_step, perform_dda
│   │   ├── render.c          # render_frame, draw_textured_line
│   │   ├── render2.c         # put_pixel, get_texture_color, ceiling/floor
│   │   ├── movement.c        # is_wall, can_move, rotate
│   │   ├── movement2.c       # apply_movement, move_forward/back/strafe
│   │   └── hooks.c           # key_press, key_release, game_loop, setup
│   └── utils/
│       ├── atoi.c
│       ├── split.c
│       ├── utils.c
│       ├── utils2.c
│       └── error_utils.c
├── maps/
│   ├── good/                 # 20+ valid maps (maze, cross, diagonal…)
│   └── bad/                  # 40+ deliberately invalid maps for testing
└── textures/
    ├── north.xpm
    ├── south.xpm
    ├── east.xpm
    └── west.xpm
```

---

## 🧪 Key concepts learned

- **Raycasting** — DDA algorithm, perpendicular distance correction, fish-eye fix
- **Texture mapping** — sampling XPM pixel data at sub-cell precision
- **MiniLibX** — image buffers, event hooks, the render loop
- **Map parsing** — multi-pass validation, flood-fill closure check
- **Collision detection** — multi-point margin sampling, wall-slide response
- **C project architecture** — splitting a large codebase across logical modules while staying Norminette-compliant
- **Memory management** — full cleanup on every error path, no leaks

---

<div align="center">

Built with 🎮 (and a lot of trigonometry) at **42 School**
by [Vavongg](https://github.com/Vavongg) & [wbaali](https://github.com/wassim971)

</div>
