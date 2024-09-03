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

- Support rainbows everywhere -- almost like a texture so chases can also use it
- Support one (as opposed to all) -- requires `ledIndex` setting.
- Support chases (vertical (on / all led bars) and sideways (always all led bars))
- Support fire
- Support theatre chase (multiple repeating chases)
- Support swipe (horizontal line across multiple led bars)
- Support animations that only affect a section of a led bar
- Support more stackable animations
