# Animations

## Tested animations

### `strobo`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports speed.

### `stop`

- Stops all animations and blacks out all led bars.

### `single`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports fade & speed.

### `double`

- Lights up the entire led bar -- cannot be stacked.
- Use black as secondary color to partially light up led bar.
- Uses primary and secondary color, mixed with given percentage.
- Supports fade & speed.

### `partialSingle`

- Only lights up specific leds -- can be stacked.
- Uses primary color.
- Supports fade & speed.

### `singleChase`

- Lights up chase across the led bar -- can be stacked.
- Uses primary color.
- Supports fade & speed.

### `doubleChase`

- Lights up chase across the led bar -- can be stacked.
- User primary and secondary color.
- Supports fade & speed.

## Pending ideas + todos

- Rename Speed to intensity so it describes what it does
- Find a good naming scheme for all animations
    -> "single": uses one color
    -> "double": uses 2 colors
    -> "partial": effect is added to part of the led
    -> "pulse": single change + optional fade
    -> "chase": moving leds across led bar + optional fade
    client only concepts:
    -> "all": applies to all leds (leds = 255)
    -> "one": applies to some led (leds = bit mask)

- Support chases (vertical (on / all led bars) and sideways (always all led bars)) + directionality
- Support fire
- Support theatre chase (multiple repeating chases)
- Support swipe (horizontal line across multiple led bars - kinda a narrow chase)
- Support horizontal rainbow (could be 8 "ones")
- Support animations that only affect a section of a led bar (unsure - never used in the old system)
- Support reconnecting network + websocket
- Always save everything to local storage so refreshes are not painful
