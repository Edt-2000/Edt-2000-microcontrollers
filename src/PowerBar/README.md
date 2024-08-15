# PowerBar

The PowerBar system consists of several moving parts:

- Globals
- Main loop
- Leds
- Web socket handling
- Time

## Globals

The globals consists of 3 things: all animations, the current animation, and settings. All animations is an array that contains all animations, which are all ready to start. The current animation is a pointer to one of those animations. The settings is a struct containing things like speed, duration, colors etc. Those settings are used by the animations.

```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end
```

## Main loop

The main loop does one thing: if there is a current animation, and is active, the `loop()` method will be called every loop. The active animation reads from the current global settings, so it can respond to setting changes while active.

```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end

    subgraph Main
    main[Main loop]
    main <-->|Read| currentAnimation
    
    main -->check{Has active animation?}
    style main fill:#faa,stroke:#f00
    check -->|Yes| animation("Current animation loop()")
    end

    animation -->|Reads| settings
    check -->|No| main
```

## Leds

If the active animation wants to output to the leds, it can invoke `FastLED.show()`:

```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end

    subgraph Leds
    leds[Leds]
    end

    subgraph Main
    main[Main loop]
    main <-->|Read| currentAnimation
    
    main -->check{Has active animation?}
    style main fill:#faa,stroke:#f00
    check -->|Yes| animation("Current animation loop()")
    end
    
    animation -->|Reads| settings
    animation -->|"FastLED.show()"| leds
    check -->|No| main
```

## Web socket handling

Before running the main loop, the main setup setups the Web socket handling which responds to incoming web socket messages. These messages can either update the global settings, or change the current animation:


```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end

    subgraph Leds
    leds[Leds]
    end

    subgraph Main
    main[Main loop]
    main <-->|Read| currentAnimation
    
    main -->check{Has active animation?}
    style main fill:#faa,stroke:#f00
    check -->|Yes| animation("Current animation loop()")
    end

    subgraph Web socket
    ws[Web socket] -->message(Received message)
    end

    updateAnimation -->|Writes| currentAnimation
    
    animation -->|Reads| settings
    animation -->|"FastLED.show()"| leds
    
    message -->|Contains animation| updateAnimation(Update animation)

    message -->|Contains settings| updateSettings(Update settings)
    updateSettings -->|Writes| settings
    
    check -->|No| main
```

## Time

If the animation needs to invoke `delay()` to time certain effects, the animation can call `delay()`.

```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end

    subgraph Leds
    leds[Leds]
    end

    subgraph Time
    time[Time] 
    end

    subgraph Main
    main[Main loop]
    main <-->|Read| currentAnimation
    
    main -->check{Has active animation?}
    style main fill:#faa,stroke:#f00
    check -->|Yes| animation("Current animation loop()")
    end

    subgraph Web socket
    ws[Web socket] -->message(Received message)
    end

    animation <-->|"delay()"| time
    updateAnimation -->|Writes| currentAnimation
    
    animation -->|Reads| settings
    animation -->|"FastLED.show()"| leds
    
    message -->|Contains animation| updateAnimation(Update animation)

    message -->|Contains settings| updateSettings(Update settings)
    updateSettings -->|Writes| settings
    
    check -->|No| main
```

Because `delay()` does not give control back to the main loop until the delay finished, this can make switching animations be very delayed. This is resolved by interrupting any running `delay()` when the web socket receives a new message, and have that `delay()` jump back to the main loop. This avoids running remaining instructions in the `loop()` of the animation that is being stopped.

```mermaid
flowchart TD
    subgraph Globals
    allAnimations[All animations]
    currentAnimation[Current animation]
    settings[Settings]
    end

    subgraph Leds
    leds[Leds]
    end

    subgraph Time
    time[Time] 
    end

    subgraph Main
    main[Main loop]
    main <-->|Read| currentAnimation
    
    main -->check{Has active animation?}
    style main fill:#faa,stroke:#f00
    check -->|Yes| animation("Current animation loop()")
    end

    subgraph Web socket
    ws[Web socket] -->message(Received message)
    end

    animation <-->|"delay()"| time
    updateAnimation -->|Writes| currentAnimation
    updateAnimation -->|Interrupts| time
    
    animation -->|Reads| settings
    animation -->|"FastLED.show()"| leds
    
    message -->|Contains animation| updateAnimation(Update animation)

    message -->|Contains settings| updateSettings(Update settings)
    updateSettings -->|Writes| settings
    
    time -->|jumps| main
    check -->|No| main
```
