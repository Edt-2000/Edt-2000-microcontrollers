# Animations

## Tested animations

### `strobo`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports speed.

### `fire`

- Lights up the entire led bar -- cannot be stacked.
- Supports speed.

### `noise`

- Lights up the entire led bar -- cannot be stacked.
- Supports speed.

### `pong`

- Lights up all led bars -- cannot be stacked.
- Supports speed - will stop when speed == 255.

### `stop`

- Stops all animations and blacks out all led bars.

### `singlePulse`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports fade & speed.

### `doublePulse`

- Lights up the entire led bar -- cannot be stacked.
- Use black as secondary color to partially light up led bar.
- Uses primary and secondary color, mixed with given percentage.
- Supports fade & speed.

### `singlePartialPulse`

- Only lights up specific leds -- can be stacked.
- Uses primary color.
- Supports fade & speed.

### `singleChase`

- Lights up chase across the led bar -- can be stacked.
- Uses primary color.
- Supports fade, speed, angle (down 0, up 128, left 64, right 192).

### `doubleChase`

- Lights up chase across the led bar -- can be stacked.
- User primary and secondary color.
- Supports fade, speed, angle (down 0, up 128).

## Pending ideas + todos

- Socket io fixup

- Snake animation
- Outrun / lotus road animation
- Wave chase / eminating circle chase
- Sectional horizontal chase (already kinda implemented -- just need a way to configure the led-mask)

- Find a good naming scheme for all animations
    -> "single": uses one color
    -> "double": uses 2 colors
    -> "partial": effect is added to part of the led
    -> "pulse": single change + optional fade
    -> "chase": moving leds across led bar + optional fade
    client only concepts:
    -> "all": applies to all leds (leds = 255)
    -> "one": applies to some led (leds = bit mask)
    -> "down", "up", "left", "right": applies to directionaly

- Think about Led.random(), and whether it should be configurable
