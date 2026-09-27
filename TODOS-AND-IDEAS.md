# Todos and ideas
This file is meant to keep track of things that needs to be added or refactored in a short term, as well as ideas for the engine that I don't want to forget before I implement them. It will not feature long-term goals or extremely elaborated and complex ideas, just a few tips and cleans that need to be done.

## Todos
* Improve consistency across `*Data` classes (in [containers](core-systems/include/containers) folder). This might be achieved by making them all accept r-value references instead of Shared<> but other ideas may be even better instead.
* Implement `Matrix3x3::View()` method.
* Maybe make IFont not an `IBindableResource`. Explanation: it might lead to an exquisite pattern if you need to bind a font since each text still needs to know what font is bound in order to be properly rendered, and as of now bound resources aren't easily "gettable" (except for `IRenderingRule`) and their only purpose is to set global states. Maybe this can change in the future but who knows. For now, I think making texts (whenever they're fully implemented) use a specific font directly might be a more organized alternative.
* Add fullscreen support.
* Add `Dot()`, `Cross()` and other missing math methods to vector classes before they're actually needed.
* Consider adding a `IRendererResource::Destroy()` method on each resource instead of solely relying on `IRendererResourceManager::Destroy()` method which can make code more verbose.
* Maybe refactor OGLRendererUser to not require a renderer to be passed through the constructor.
* Maybe create an internal /ogl subfolder to organize implementations

## Ideas
* The engine could feature its own hashing method and map struct instead of relying on `std::hash` and `std::unordered_map`.
