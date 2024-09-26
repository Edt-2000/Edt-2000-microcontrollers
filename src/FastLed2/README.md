# Animations

## Tested animations

### `strobo`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports speed.

### `stop`

- Stops all animations and blacks out all led bars.

### `allSingle`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports fade & speed.

### `allDouble`

- Lights up the entire led bar -- cannot be stacked.
- Use black as secondary color to partially light up led bar.
- Uses primary and secondary color, mixed with given percentage.
- Supports fade & speed.

### `partialSingle`

- Only lights up specific leds -- can be stacked.
- Uses primary color.
- Supports fade & speed.

### `allSingleChase`

- Lights up chase across the led bar -- can be stacked.
- Uses primary color.
- Supports fade & speed.

### `allDoubleChase`

- Lights up chase across the led bar -- can be stacked.
- User primary and secondary color.
- Supports fade & speed.

## Pending ideas + todos

- Find solution for Modifier and Speed swaps because of the repeater -- it makes the invoker a bit weird between different animations.
- Find a good naming scheme for all animations (all and one, single bar multi-bar, etc, must be consistent)
    -> "all": entire led bar overwritten
    -> "partial": effect is added
    -> "one": single led bar is used
    -> "single": uses one color
    -> "double": uses 2 colors
- How to tackle the different colors?
    -> KISS: 2 colors: primary + secondary.
    -> 
- Support rainbows everywhere -- almost like a texture so chases can also use it (make a special hsv code for it)
- Support one (as opposed to all) -- requires `ledIndex` setting.
- Support chases (vertical (on / all led bars) and sideways (always all led bars)) + directionality
- Support fire
- Support theatre chase (multiple repeating chases)
- Support swipe (horizontal line across multiple led bars - kinda a narrow chase)
- Support horizontal rainbow (could be 8 "ones")
- Support animations that only affect a section of a led bar (unsure - never used in the old system)
- Support reconnecting network + websocket
- Always save everything to local storage so refreshes are not painful
