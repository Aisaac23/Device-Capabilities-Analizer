# Device-Capabilities-Analizer
You can pass as argument the name of a file (previously created or not) and you'll get the capabilities analysis there.
Also you may pass no arguments and you'll have the report in stdout (normally your screen).

Inside "examples" folder you'll find what the program found in multiple devices with multiple platforms.

This tool will help you find the following:
- integer and character storage sizes.
- integer and character ranges/limits.
- floating point types storage sizes and ranges/limits.
- Mantisa ranges/limits.
- Exponent ranges/limits.
- Clocks ticks per second.
- Basic performance characteristics.
- Basic locale settings.

It could be extremely helpful to know and keep track of all this system specific characteristics before and during any software development project in C language or even in other languages. It also could be helpful while debugging.
