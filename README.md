# ASCII Image Converter

A C program for converting images to ASCII text

## Functionality

- Load image with `stb_image`
- Map grayscale brightness to ASCII characters
- Output through terminal or save as txt file
- Customize output resolution

## Installation and Usage

1. Clone the repository

```
git clone https://github.com/mashrursakif/ascii-converter.git
```

2. Compile

```
cd ascii-converter; make
```

3. Run

```
./ascii_converter -i 'images/cat.jpg' -s -r 100
```

### Command Line Flags:

- -i: Specify path for input image (required)
- -s: Save output image (optional, saves as txt file in the outputs/ directory)
- -r: horizontal resolution (optional, default: 80)
