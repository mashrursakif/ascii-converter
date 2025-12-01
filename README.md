# ASCII Image Converter

A C program for converting images and videos to ASCII text

## Functionality

- Load images and videos through `stb_image` and `ffmpeg`
- Map grayscale brightness to ASCII characters
- Output through terminal or save as txt file
- Customize output resolution
- View and playback saved ASCII images and videos in terminal and web browser

## Installation and Usage

1. Clone the repository

```
git clone https://github.com/mashrursakif/ascii-converter.git
```

2. Compile

```
cd ascii-converter; make
```

3. Convert image and video

```
./ascii_converter -i 'images/cat.jpg' -s -r 100
```

4. Open and view converted images and videos from text file

```
./ascii_converter -o 'outputs/cat.txt'
```

### Command Line Flags:

- -i: Specify path for input image
- -s: Save output image (optional, saves as txt file in the outputs/ directory)
- -r: Specify horizontal resolution (optional, default: 80)
- -o: Specify path for saved ascii txt file to open and view
