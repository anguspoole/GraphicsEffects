# GraphicsEffects
Combining stencil + scissor buffer, cube map reflection, and blur

By: Angus Poole

## Instructions

Build/Run in Release/x64

Use WASD to move the dalek.
Hold Alt+WASDQE to move the camera. You have to scroll first to adjust the camera's speed.

## Graphics Effects

* Off-screen textures: the scene is rendered from an angle to an off-screen texture, and combined with a second texture to make a screen with a "shattered glass" sort of look. If you move the Dalek around, the image on the screen changes.
* Full Screen Rendering: the scene is rendered to an FBO and then copied onto the quad FullScreenQuad.
* Full-Screen Effect: a blur effect is applied to the full-screen quad
* Scissor Buffer (combined with stencil buffer #2): the left quarter or so of the screen is under the effect of the scissor buffer, with flags set to prevent it from clearing the depth. As such, the objects with a red outline (all but the tv, dalek, and tv screen) that pass into that side will have their red outline completely covering the object instead of showing the proper colour.
* Stencil Buffer #1: using the room and door models for the stencil buffer, the dalek starts inside the room. If you move backwards, you'll exit the room through the door, and can then see the rest of the level through the doorway. Note that all of this is only visible on the "tv screen", from the dalek's perspective.
* Stencil Buffer #2 (combines with scissor buffer): by creating copies of various objects, then scaling the copies up and changing their colour, the second stencil buffer is used to give these objects a red outline. When passing into the area that has not been cropped by the scissor buffer, the "true" red outline is visible, covering the entire object.