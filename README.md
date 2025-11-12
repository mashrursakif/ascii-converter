# ASCII Image Converter

A C program for converting images to ASCII art

## Functionality

- Load image with `stb_image`
- Map grayscale brightness to ASCII characters
- Output through terminal or save as txt file
- Customize output resolution

## Installation and Usage

1. Clone the repository

```
git clone
```

2. Compile

```
gcc src/main.c -o ascii_converter -lm
```

3. Run

```
./ascii_converter -i 'images/cat.jpg' -o 'output.txt' -r 100
```

### Flags:

-i: Specify path for input image (required)
-o: Specify path for output image (optional, defaults to outputting directly in terminal)
-r: horizontal resolution (optional, default: 80)
