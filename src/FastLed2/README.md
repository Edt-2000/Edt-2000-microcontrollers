# Animations

## Tested animations

### `strobo`

- Lights up the entire led bar -- cannot be stacked.
- Uses primary color.
- Supports speed.

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

## Pending ideas + todos

- Find a good naming scheme for all animations (all and one, single bar multi-bar, etc, must be consistent)
    -> "all": entire led bar overwritten
    -> "single": uses one color
    -> "double": uses 2 colors
    -> 
- How to tackle the different colors?
    -> KISS: 2 colors: primary + secondary.
    -> 
- Speed and duration need to be tweaked per animation type (partialSingle needs slow fade but high speed)
- Support rainbows everywhere -- almost like a texture so chases can also use it (make a special hsv code for it)
- Support one (as opposed to all) -- requires `ledIndex` setting.
- Support chases (vertical (on / all led bars) and sideways (always all led bars)) + directionality
- Support fire
- Support theatre chase (multiple repeating chases)
- Support swipe (horizontal line across multiple led bars)
- Support animations that only affect a section of a led bar
- Support more stackable animations
